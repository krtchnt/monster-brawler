#pragma once

#include <string>

using std::string;

constexpr const char* DAMAGE_TOPIC = "damage";
constexpr const char* STATS_TOPIC = "stats";
constexpr const char* MONSTER_TOPIC = "monster";
constexpr const char* PROGRESS_TOPIC = "progress";
constexpr const char* SETTINGS_TOPIC = "settings";
constexpr const char* BRAWLED_TOPIC = "brawled";
constexpr const char* NAV_TOPIC = "nav";
constexpr const char* LEVEL_TOPIC = "level";
constexpr const char* NOTIFY_TOPIC = "notify";

extern const string TOPIC_DAMAGE_R;
extern const string TOPIC_DAMAGE_L;

extern const string TOPIC_STATS_BRAWLED_MOBS;
extern const string TOPIC_STATS_BRAWLED_BOSSES;
extern const string TOPIC_STATS_BRAWLED_NEO_BOSSES;
extern const string TOPIC_STATS_BRAWLED_FINAL_BOSSES;
extern const string TOPIC_STATS_BRAWLED_TOTAL;
extern const string TOPIC_STATS_PLAYTHROUGHS;

extern const string TOPIC_SETTINGS_DAMAGE_MULTIPLIER;
extern const string TOPIC_SETTINGS_DAMAGE_DISABLE_NEGATE;
extern const string TOPIC_SETTINGS_DAMAGE_DISABLE_REVERSE;
extern const string TOPIC_SETTINGS_SPAWN_MODE;

extern const string TOPIC_MONSTER_HP;
extern const string TOPIC_MONSTER_VIT;
extern const string TOPIC_MONSTER_DEF;
extern const string TOPIC_MONSTER_TITLE;
extern const string TOPIC_MONSTER_ICON;
extern const string TOPIC_MONSTER_NEGATE;
extern const string TOPIC_MONSTER_REVERSE;

extern const string TOPIC_PROGRESS_MONSTER_CURR;
extern const string TOPIC_PROGRESS_MONSTER_MAX;
extern const string TOPIC_PROGRESS_LEVEL_CURR;
extern const string TOPIC_PROGRESS_LEVEL_MAX;

extern const string TOPIC_NAV_MONSTER_LAST;
extern const string TOPIC_NAV_MONSTER_NEXT;
extern const string TOPIC_NAV_MONSTER_PREV;
extern const string TOPIC_NAV_MONSTER_FIRST;
extern const string TOPIC_NAV_LEVEL_LAST;
extern const string TOPIC_NAV_LEVEL_NEXT;
extern const string TOPIC_NAV_LEVEL_PREV;
extern const string TOPIC_NAV_LEVEL_FIRST;

extern const string TOPIC_NOTIFY_CONGRATS;
extern const string TOPIC_NOTIFY_WARNING;
extern const string TOPIC_NOTIFY_INFO;
extern const string TOPIC_NOTIFY_DAMAGE;