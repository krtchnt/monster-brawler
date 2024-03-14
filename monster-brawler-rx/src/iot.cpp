#include "include/iot.h"

#include <PubSubClient.h>
#include <WiFi.h>

#include <algorithm>

#include "include/broker_config.h"
#include "include/broker_topic.h"
#include "include/config.h"
#include "include/game.h"
#include "include/oled.h"

WiFiClient wifiClient;
PubSubClient mqtt(MQTT_BROKER, 1883, wifiClient);

void connect_wifi() {
    printf("WiFi MAC address is %s\n", WiFi.macAddress().c_str());
    printf("Connecting to WiFi %s.\n", WIFI_SSID);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        printf(".");
        fflush(stdout);
        delay(500);
    }
    printf("\nWiFi connected.\n");
}

void mqtt_callback(const char* topic, byte* payload, const unsigned int length);

void connect_mqtt() {
    printf("Connecting to MQTT broker at %s.\n", MQTT_BROKER);
    if (!mqtt.connect("", MQTT_USER, MQTT_PASS)) {
        printf("Failed to connect to MQTT broker.\n");
        for (;;)
            ;
    }
    mqtt.setCallback(mqtt_callback);

    mqtt.subscribe(TOPIC_DAMAGE_R.c_str());
    mqtt.subscribe(TOPIC_DAMAGE_L.c_str());

    mqtt.subscribe(TOPIC_SETTINGS_DAMAGE_MULTIPLIER.c_str());
    mqtt.subscribe(TOPIC_SETTINGS_DAMAGE_DISABLE_NEGATE.c_str());
    mqtt.subscribe(TOPIC_SETTINGS_DAMAGE_DISABLE_REVERSE.c_str());
    mqtt.subscribe(TOPIC_SETTINGS_SPAWN_MODE.c_str());

    mqtt.subscribe(TOPIC_NAV_MONSTER_LAST.c_str());
    mqtt.subscribe(TOPIC_NAV_MONSTER_NEXT.c_str());
    mqtt.subscribe(TOPIC_NAV_MONSTER_PREV.c_str());
    mqtt.subscribe(TOPIC_NAV_MONSTER_FIRST.c_str());
    mqtt.subscribe(TOPIC_NAV_LEVEL_LAST.c_str());
    mqtt.subscribe(TOPIC_NAV_LEVEL_NEXT.c_str());
    mqtt.subscribe(TOPIC_NAV_LEVEL_PREV.c_str());
    mqtt.subscribe(TOPIC_NAV_LEVEL_FIRST.c_str());

    printf("MQTT broker connected.\n");
}

void publish_empty_monster() {
    mqtt.publish(TOPIC_MONSTER_TITLE.c_str(), "-");
    mqtt.publish(TOPIC_MONSTER_VIT.c_str(), "-");
    mqtt.publish(TOPIC_MONSTER_DEF.c_str(), "-");
    mqtt.publish(TOPIC_MONSTER_ICON.c_str(), "-");
    mqtt.publish(TOPIC_MONSTER_HP.c_str(), "-");
    mqtt.publish(TOPIC_MONSTER_NEGATE.c_str(), "-");
    mqtt.publish(TOPIC_MONSTER_REVERSE.c_str(), "-");

    mqtt.publish(TOPIC_PROGRESS_LEVEL_CURR.c_str(), "0");
    mqtt.publish(TOPIC_PROGRESS_MONSTER_CURR.c_str(), "0");
}

void handle_damage_topics(const char* topic, byte* payload,
                          const unsigned int length) {
    Chirality chirality;

    if (during_grace_period) {
        return;
    }

    if (strcmp(topic, TOPIC_DAMAGE_R.c_str()) == 0) {
        chirality = Chirality::R;
    } else if (strcmp(topic, TOPIC_DAMAGE_L.c_str()) == 0) {
        chirality = Chirality::L;
    } else {
        return;
    }

    payload[length] = 0;

    const uint16_t dmg_amount =
        atoi(reinterpret_cast<char*>(payload)) * damage_multiplier;
    if (!monster) {
        mqtt.publish(TOPIC_NOTIFY_WARNING.c_str(),
                     "Navigate to the first level to play again.");
        return;
    }
    monster->take_damage({dmg_amount, chirality});
    auto monster_is_dead = monster->is_dead();
    if (monster_is_dead) {
        monster_brawled_catalogue[monster_i.get()] = true;
        spawn_next_monster();

        if (!monster) {
            mqtt.publish(TOPIC_NOTIFY_CONGRATS.c_str(),
                         "You have completed Monster Brawler!");

            publish_empty_monster();
            return;
        } else {
            mqtt.publish(TOPIC_NOTIFY_INFO.c_str(),
                         "Monster killed! Spawning next...");
        }
    }
    monster->display(monster_is_dead);
}

void handle_settings_topics(const char* topic, byte* payload,
                            const unsigned int length) {
    if (strcmp(topic, TOPIC_SETTINGS_DAMAGE_MULTIPLIER.c_str()) == 0) {
        payload[length] = 0;

        const double new_multiplier = atof(reinterpret_cast<char*>(payload));
        damage_multiplier = new_multiplier;

        if (monster) {
            spawn_monster();
            monster->display(true);
        }
    }
    if (strcmp(topic, TOPIC_SETTINGS_DAMAGE_DISABLE_NEGATE.c_str()) == 0) {
        payload[length] = 0;

        const bool new_disable_negate = atoi(reinterpret_cast<char*>(payload));
        disable_negate = new_disable_negate;

        if (monster) {
            spawn_monster();
            monster->display(true);
        }
    }
    if (strcmp(topic, TOPIC_SETTINGS_DAMAGE_DISABLE_REVERSE.c_str()) == 0) {
        payload[length] = 0;

        const bool new_disable_reverse = atoi(reinterpret_cast<char*>(payload));
        disable_reverse = new_disable_reverse;

        if (monster) {
            spawn_monster();
            monster->display(true);
        }
    }
    if (strcmp(topic, TOPIC_SETTINGS_SPAWN_MODE.c_str()) == 0) {
        payload[length] = 0;

        const SpawnMode new_spawn_mode =
            static_cast<SpawnMode>(atoi(reinterpret_cast<char*>(payload)));
        spawn_mode = new_spawn_mode;

        if (monster) {
            spawn_monster();
            monster->display(true);
        }
    }
}

void handle_nav_topic(const char* topic) {
    if (strcmp(topic, TOPIC_NAV_MONSTER_FIRST.c_str()) == 0 ||
        strcmp(topic, TOPIC_NAV_MONSTER_PREV.c_str()) == 0 ||
        strcmp(topic, TOPIC_NAV_MONSTER_NEXT.c_str()) == 0 ||
        strcmp(topic, TOPIC_NAV_MONSTER_LAST.c_str()) == 0 ||
        strcmp(topic, TOPIC_NAV_LEVEL_FIRST.c_str()) == 0 ||
        strcmp(topic, TOPIC_NAV_LEVEL_PREV.c_str()) == 0 ||
        strcmp(topic, TOPIC_NAV_LEVEL_NEXT.c_str()) == 0 ||
        strcmp(topic, TOPIC_NAV_LEVEL_LAST.c_str()) == 0) {
        if (spawn_mode != SpawnMode::SINGLE_MONSTER_PRACTICE &&
            spawn_mode != SpawnMode::RANDOM_ENDLESS) {
            if (strcmp(topic, TOPIC_NAV_MONSTER_FIRST.c_str()) == 0) {
                monster_i.isub(monster_i.monster_j());
            }
            if (strcmp(topic, TOPIC_NAV_MONSTER_PREV.c_str()) == 0) {
                if (monster_i.get() > 0) {
                    monster_i.decr();
                }
            }
            if (strcmp(topic, TOPIC_NAV_MONSTER_NEXT.c_str()) == 0) {
                if (monster_i.get() < TOTAL_MONSTERS - 1) {
                    monster_i.incr();
                }
            }
            if (strcmp(topic, TOPIC_NAV_MONSTER_LAST.c_str()) == 0) {
                monster_i.iadd(monster_i.max_monster_j() -
                               monster_i.monster_j() - 1);
            }

            if (spawn_mode != SpawnMode::LEVEL_PRACTICE) {
                if (strcmp(topic, TOPIC_NAV_LEVEL_FIRST.c_str()) == 0) {
                    monster_i.set(0);
                }
                if (strcmp(topic, TOPIC_NAV_LEVEL_PREV.c_str()) == 0) {
                    if (monster_i.level_i() > 0) {
                        monster_i.isub(
                            monster_i.monster_j() +
                            (monster_i.get() == TOTAL_NORMAL_MONSTERS - 1
                                 ? NORMAL_LEVELS_PER_GAME
                                 : monster_i.max_monster_j()));
                    }
                }
                if (strcmp(topic, TOPIC_NAV_LEVEL_NEXT.c_str()) == 0) {
                    if (monster_i.level_i() < NORMAL_LEVELS_PER_GAME) {
                        monster_i.iadd(monster_i.max_monster_j() -
                                       monster_i.monster_j());
                    }
                }
                if (strcmp(topic, TOPIC_NAV_LEVEL_LAST.c_str()) == 0) {
                    monster_i.set(TOTAL_NORMAL_MONSTERS);
                }
            }
        }

        spawn_monster();
        if (monster) {
            monster->display(true);
        }
    }
}

void mqtt_callback(const char* topic, byte* payload,
                   const unsigned int length) {
    handle_damage_topics(topic, payload, length);
    handle_settings_topics(topic, payload, length);
    handle_nav_topic(topic);
}

void setup_iot() {
    connect_wifi();
    connect_mqtt();
}