#include "include/game.h"

#include <Arduino.h>

#include "include/broker_topic.h"
#include "include/config.h"
#include "include/game_default.h"
#include "include/iot.h"

size_t total_brawled;
size_t mobs_brawled;
size_t bosses_brawled;
size_t neo_bosses_brawled;
size_t final_bosses_brawled;
size_t complete_playthroughs;
std::array<bool, TOTAL_MONSTERS> monster_brawled_catalogue;

uint32_t last_spawned;
SpawnMode spawn_mode;
MonsterIndex monster_i;
bool during_grace_period;
bool disable_negate;
bool disable_reverse;
double damage_multiplier;
std::unique_ptr<Monster> monster;

MonsterIndex::MonsterIndex() : i(0){};
MonsterIndex::MonsterIndex(const size_t i) : i(i){};

size_t MonsterIndex::get() const { return i; }
void MonsterIndex::set(const size_t i) {
    this->i = i;
    mqtt.publish(TOPIC_PROGRESS_LEVEL_CURR.c_str(),
                 String(this->level_i() + 1).c_str());
    mqtt.publish(TOPIC_PROGRESS_MONSTER_CURR.c_str(),
                 String(this->monster_j() + 1).c_str());
    mqtt.publish(TOPIC_PROGRESS_MONSTER_MAX.c_str(),
                 String(this->max_monster_j()).c_str());
}
void MonsterIndex::incr() { set(get() + 1); }
void MonsterIndex::iadd(const size_t d) { set(get() + d); }
void MonsterIndex::decr() { set(get() - 1); }
void MonsterIndex::isub(const size_t d) { set(get() - d); }

size_t MonsterIndex::level_i() const {
    if (i < TOTAL_NORMAL_MONSTERS) {
        const auto q = i / MONSTERS_PER_LEVEL;
        return q;
    }

    return LEVELS_PER_GAME - 1;
}

size_t MonsterIndex::monster_j() const {
    if (i < TOTAL_NORMAL_MONSTERS) {
        const auto r = i % MONSTERS_PER_LEVEL;
        return r;
    }

    const auto i_ = i - TOTAL_NORMAL_MONSTERS;
    return i_;
}

size_t MonsterIndex::max_monster_j() const {
    return i < TOTAL_NORMAL_MONSTERS ? MONSTERS_PER_LEVEL : LEVELS_PER_GAME;
}

LevelManager::LevelManager(
    const MonsterInfo mob_infos[NORMAL_LEVELS_PER_GAME][MOBS_PER_LEVEL],
    const MonsterInfo boss_infos[NORMAL_LEVELS_PER_GAME],
    const MonsterInfo neo_boss_infos[NORMAL_LEVELS_PER_GAME],
    const MonsterInfo final_boss_info) {
    for (size_t i = 0; i < NORMAL_LEVELS_PER_GAME; i++) {
        const auto l = i + 1;
        for (size_t j = 0; j < NORMAL_LEVELS_PER_GAME; j++) {
            const auto mob_info = mob_infos[i][j];
            const auto hp = BASE_VIT * l + MOB_VIT_STEP * j;
            const auto def = BASE_MOB_DEF * i;
            const Mob mob(mob_info, hp, def);

            levels[i].set_mob(mob, j);
        }

        const auto boss_info = boss_infos[i];
        const auto hp = BASE_VIT * l * MOBS_PER_LEVEL;
        const auto def = BASE_BOSS_DEF * l;
        const auto combos = l * BASE_BOSS_COMBO;
        const Boss boss(boss_info, hp, def, combos);

        levels[i].set_boss(boss);
    }

    for (size_t i = 0; i < NORMAL_LEVELS_PER_GAME; i++) {
        const auto l = i + 1;

        const auto neo_boss_info = neo_boss_infos[i];
        const auto hp = BASE_VIT * l * MOBS_PER_LEVEL;
        const auto def = BASE_NEO_BOSS_DEF * l;
        const auto combos = l * BASE_NEO_BOSS_COMBO;
        const auto damage_negate_chance = BASE_NEO_BOSS_NEGATE_CHANCE * l;
        const NeoBoss neo_boss(neo_boss_info, hp, def, combos,
                               damage_negate_chance);

        final_level.set_neo_boss(neo_boss, i);
    }

    const auto hp =
        BASE_VIT * LEVELS_PER_GAME * MOBS_PER_LEVEL * FINAL_BOSS_VIT_MULTIPLIER;
    const auto def = FINAL_BOSS_DEF_MULTIPLIER * LEVELS_PER_GAME;
    const auto combos = LEVELS_PER_GAME * FINAL_BOSS_COMBO_MULTIPLIER;
    const auto damage_negate_chance =
        FINAL_BOSS_NEGATE_CHANCE_MULTIPLIER * LEVELS_PER_GAME;
    const auto damage_reverse_chance = FINAL_BOSS_DAMAGE_REVERSE_CHANCE;
    const FinalBoss final_boss(final_boss_info, hp, def, combos,
                               damage_negate_chance, damage_reverse_chance);

    final_level.set_final_boss(final_boss);
}

std::unique_ptr<Monster> LevelManager::ith_monster(const MonsterIndex i) const {
    if (i.get() < TOTAL_NORMAL_MONSTERS) {
        const auto level = levels[i.level_i()];
        const auto j = i.monster_j();
        if (j == MOBS_PER_LEVEL) {
            const Boss boss = level.get_boss();

            return std::make_unique<Boss>(boss);
        }

        return std::make_unique<Mob>(level.get_mob(j));
    }

    const auto j = i.monster_j();
    if (j >= LEVELS_PER_GAME - 1) {
        return std::make_unique<FinalBoss>(final_level.get_final_boss());
    }
    return std::make_unique<NeoBoss>(final_level.get_neo_boss(j));
}

std::unique_ptr<Monster> LevelManager::rand_monster() const {
    const auto r_i = random(TOTAL_MONSTERS);

    return ith_monster(r_i);
}

void spawn_monster() {
    switch (spawn_mode) {
        case SpawnMode::NORMAL:
        case SpawnMode::ENDLESS:
        case SpawnMode::LEVEL_PRACTICE:
        case SpawnMode::SINGLE_MONSTER_PRACTICE:
            monster = level_manager.ith_monster(monster_i);
            break;
        case SpawnMode::RANDOM_ENDLESS:
            monster = level_manager.rand_monster();
            break;
        default:
            break;
    }

    last_spawned = millis();
}

void spawn_next_monster() {
    monster->increment();
    switch (spawn_mode) {
        case SpawnMode::NORMAL:
            monster_i.incr();
            monster = monster_i.get() < TOTAL_MONSTERS
                          ? level_manager.ith_monster(monster_i)
                          : nullptr;
            break;
        case SpawnMode::ENDLESS:
            monster_i.set((monster_i.get() + 1) % TOTAL_MONSTERS);
            monster = level_manager.ith_monster(monster_i);
            break;
        case SpawnMode::RANDOM_ENDLESS:
            monster = level_manager.rand_monster();
            break;
        case SpawnMode::LEVEL_PRACTICE:
            monster_i.incr();
            if (monster_i.monster_j() == 0) {
                monster_i.isub(monster_i.max_monster_j());
            }
            monster = level_manager.ith_monster(monster_i);
            break;
        case SpawnMode::SINGLE_MONSTER_PRACTICE:
            monster = level_manager.ith_monster(monster_i);
            break;
        default:
            break;
    }

    last_spawned = millis();
}

LevelManager level_manager(MOB_INFOS, BOSS_INFOS, NEO_BOSS_INFOS,
                           FINAL_BOSS_INFO);

void setup_game() {
    total_brawled = 0;
    mobs_brawled = 0;
    bosses_brawled = 0;
    neo_bosses_brawled = 0;
    final_bosses_brawled = 0;
    complete_playthroughs = 0;
    monster_brawled_catalogue.fill(false);

    damage_multiplier = 1.;
    spawn_mode = DEFAULT_SPAWN_MODE;
    // spawn_mode = SpawnMode::NORMAL;
    disable_negate = false;
    disable_reverse = false;
    monster = level_manager.ith_monster(monster_i);
    last_spawned = millis();
    during_grace_period = true;

    mqtt.publish(TOPIC_STATS_BRAWLED_MOBS.c_str(), "0");
    mqtt.publish(TOPIC_STATS_BRAWLED_BOSSES.c_str(), "0");
    mqtt.publish(TOPIC_STATS_BRAWLED_NEO_BOSSES.c_str(), "0");
    mqtt.publish(TOPIC_STATS_BRAWLED_FINAL_BOSSES.c_str(), "0");
    mqtt.publish(TOPIC_STATS_BRAWLED_TOTAL.c_str(), "0");
    mqtt.publish(TOPIC_STATS_PLAYTHROUGHS.c_str(), "0");

    mqtt.publish(TOPIC_PROGRESS_LEVEL_CURR.c_str(), "1");
    mqtt.publish(TOPIC_PROGRESS_LEVEL_MAX.c_str(),
                 String(LEVELS_PER_GAME).c_str());
    mqtt.publish(TOPIC_PROGRESS_MONSTER_CURR.c_str(), "1");
    mqtt.publish(TOPIC_PROGRESS_MONSTER_MAX.c_str(),
                 String(MONSTERS_PER_LEVEL).c_str());

    monster->display(true);
}