#include "include/broker_topic.h"

#include <string>

#include "include/broker_config.h"

using std::string;

const string TOPIC_DAMAGE_R(string(TOPIC_PREFIX) + "/" + DAMAGE_TOPIC + "/r");
const string TOPIC_DAMAGE_L(string(TOPIC_PREFIX) + "/" + DAMAGE_TOPIC + "/l");

const string TOPIC_MONSTER_HP(string(TOPIC_PREFIX) + "/" + MONSTER_TOPIC +
                              "/hp");
const string TOPIC_MONSTER_VIT(string(TOPIC_PREFIX) + "/" + MONSTER_TOPIC +
                               "/vit");
const string TOPIC_MONSTER_DEF(string(TOPIC_PREFIX) + "/" + MONSTER_TOPIC +
                               "/def");
const string TOPIC_MONSTER_TITLE(string(TOPIC_PREFIX) + "/" + MONSTER_TOPIC +
                                 "/title");
const string TOPIC_MONSTER_ICON(string(TOPIC_PREFIX) + "/" + MONSTER_TOPIC +
                                "/icon");
const string TOPIC_MONSTER_NEGATE(string(TOPIC_PREFIX) + "/" + MONSTER_TOPIC +
                                  "/negate");
const string TOPIC_MONSTER_REVERSE(string(TOPIC_PREFIX) + "/" + MONSTER_TOPIC +
                                   "/reverse");

const string TOPIC_SETTINGS_DAMAGE_MULTIPLIER(string(TOPIC_PREFIX) + "/" +
                                              SETTINGS_TOPIC + "/" +
                                              DAMAGE_TOPIC + "/multiplier");
const string TOPIC_SETTINGS_DAMAGE_DISABLE_NEGATE(string(TOPIC_PREFIX) + "/" +
                                                  SETTINGS_TOPIC + "/" +
                                                  DAMAGE_TOPIC +
                                                  "/disable_negate");
const string TOPIC_SETTINGS_DAMAGE_DISABLE_REVERSE(string(TOPIC_PREFIX) + "/" +
                                                   SETTINGS_TOPIC + "/" +
                                                   DAMAGE_TOPIC +
                                                   "/disable_reverse");
const string TOPIC_SETTINGS_SPAWN_MODE(string(TOPIC_PREFIX) + "/" +
                                       SETTINGS_TOPIC + "/spawn_mode");

const string TOPIC_STATS_BRAWLED_MOBS(string(TOPIC_PREFIX) + "/" + STATS_TOPIC +
                                      "/" + BRAWLED_TOPIC + "/mobs");
const string TOPIC_STATS_BRAWLED_BOSSES(string(TOPIC_PREFIX) + "/" +
                                        STATS_TOPIC + "/" + BRAWLED_TOPIC +
                                        "/bosses");
const string TOPIC_STATS_BRAWLED_NEO_BOSSES(string(TOPIC_PREFIX) + "/" +
                                            STATS_TOPIC + "/" + BRAWLED_TOPIC +
                                            "/neo_bosses");
const string TOPIC_STATS_BRAWLED_FINAL_BOSSES(string(TOPIC_PREFIX) + "/" +
                                              STATS_TOPIC + "/" +
                                              BRAWLED_TOPIC + "/final_bosses");
const string TOPIC_STATS_BRAWLED_TOTAL(string(TOPIC_PREFIX) + "/" +
                                       STATS_TOPIC + "/" + BRAWLED_TOPIC +
                                       "/total");
const string TOPIC_STATS_PLAYTHROUGHS(string(TOPIC_PREFIX) + "/" + STATS_TOPIC +
                                      "/playthroughs");

const string TOPIC_NAV_MONSTER_NEXT(string(TOPIC_PREFIX) + "/" + NAV_TOPIC +
                                    "/" + MONSTER_TOPIC + "/next");
const string TOPIC_NAV_MONSTER_PREV(string(TOPIC_PREFIX) + "/" + NAV_TOPIC +
                                    "/" + MONSTER_TOPIC + "/prev");
const string TOPIC_NAV_MONSTER_FIRST(string(TOPIC_PREFIX) + "/" + NAV_TOPIC +
                                     "/" + MONSTER_TOPIC + "/first");
const string TOPIC_NAV_MONSTER_LAST(string(TOPIC_PREFIX) + "/" + NAV_TOPIC +
                                    "/" + MONSTER_TOPIC + "/last");
const string TOPIC_NAV_LEVEL_NEXT(string(TOPIC_PREFIX) + "/" + NAV_TOPIC + "/" +
                                  LEVEL_TOPIC + "/next");
const string TOPIC_NAV_LEVEL_PREV(string(TOPIC_PREFIX) + "/" + NAV_TOPIC + "/" +
                                  LEVEL_TOPIC + "/prev");
const string TOPIC_NAV_LEVEL_FIRST(string(TOPIC_PREFIX) + "/" + NAV_TOPIC +
                                   "/" + LEVEL_TOPIC + "/first");
const string TOPIC_NAV_LEVEL_LAST(string(TOPIC_PREFIX) + "/" + NAV_TOPIC + "/" +
                                  LEVEL_TOPIC + "/last");

const string TOPIC_PROGRESS_MONSTER_CURR(string(TOPIC_PREFIX) + "/" +
                                         PROGRESS_TOPIC + "/" + MONSTER_TOPIC +
                                         "/curr");
const string TOPIC_PROGRESS_MONSTER_MAX(string(TOPIC_PREFIX) + "/" +
                                        PROGRESS_TOPIC + "/" + MONSTER_TOPIC +
                                        "/max");
const string TOPIC_PROGRESS_LEVEL_CURR(string(TOPIC_PREFIX) + "/" +
                                       PROGRESS_TOPIC + "/" + LEVEL_TOPIC +
                                       "/curr");
const string TOPIC_PROGRESS_LEVEL_MAX(string(TOPIC_PREFIX) + "/" +
                                      PROGRESS_TOPIC + "/" + LEVEL_TOPIC +
                                      "/max");

const string TOPIC_NOTIFY_CONGRATS(string(TOPIC_PREFIX) + "/" + NOTIFY_TOPIC +
                                   "/congrats");
const string TOPIC_NOTIFY_WARNING(string(TOPIC_PREFIX) + "/" + NOTIFY_TOPIC +
                                  "/warning");
const string TOPIC_NOTIFY_INFO(string(TOPIC_PREFIX) + "/" + NOTIFY_TOPIC +
                                  "/info");
const string TOPIC_NOTIFY_DAMAGE(string(TOPIC_PREFIX) + "/" + NOTIFY_TOPIC +
                                 "/" + DAMAGE_TOPIC);