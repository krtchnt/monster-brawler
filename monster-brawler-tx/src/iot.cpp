#include "include/iot.h"

#include <PubSubClient.h>
#include <WiFi.h>

#include "include/config.h"

const String TOPIC_DAMAGE(String(TOPIC_PREFIX) + "/" + DAMAGE_TOPIC + "/" +
                          CHIRALITY);
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

void mqtt_callback(char* topic, byte* payload, unsigned int length);

void connect_mqtt() {
    printf("Connecting to MQTT broker at %s.\n", MQTT_BROKER);
    if (!mqtt.connect("", MQTT_USER, MQTT_PASS)) {
        printf("Failed to connect to MQTT broker.\n");
        for (;;)
            ;
    }
    mqtt.setCallback(mqtt_callback);
    printf("MQTT broker connected.\n");
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {}

void setup_iot() {
    connect_wifi();
    connect_mqtt();
}