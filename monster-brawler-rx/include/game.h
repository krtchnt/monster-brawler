#pragma once

#include <array>
#include <cstddef>
#include <memory>

#include "include/config.h"
#include "include/game_default.h"
#include "include/level.h"
#include "include/spawn_mode.h"

constexpr size_t TOTAL_NORMAL_MONSTERS =
    NORMAL_LEVELS_PER_GAME * MONSTERS_PER_LEVEL;

constexpr size_t TOTAL_MONSTERS =
    TOTAL_NORMAL_MONSTERS + NORMAL_LEVELS_PER_GAME + 1;

class MonsterIndex {
    public:
        MonsterIndex();
        MonsterIndex(const size_t i);

        [[nodiscard]] size_t get() const;
        void set(const size_t j);
        void incr();
        void iadd(const size_t d);
        void decr();
        void isub(const size_t d);

        [[nodiscard]] size_t level_i() const;
        [[nodiscard]] size_t monster_j() const;
        [[nodiscard]] size_t max_monster_j() const;

    private:
        size_t i;
};

class LevelManager {
    public:
        explicit LevelManager(
            const MonsterInfo mob_infos[NORMAL_LEVELS_PER_GAME][MOBS_PER_LEVEL],
            const MonsterInfo boss_infos[NORMAL_LEVELS_PER_GAME],
            const MonsterInfo neo_boss_infos[NORMAL_LEVELS_PER_GAME],
            const MonsterInfo final_boss_info);

        [[nodiscard]] std::unique_ptr<Monster> ith_monster(
            const MonsterIndex i) const;
        [[nodiscard]] std::unique_ptr<Monster> rand_monster() const;

    private:
        std::array<Level, NORMAL_LEVELS_PER_GAME> levels;
        FinalLevel final_level;
};

extern LevelManager level_manager;

extern size_t total_brawled;
extern size_t mobs_brawled;
extern size_t bosses_brawled;
extern size_t neo_bosses_brawled;
extern size_t final_bosses_brawled;
extern size_t complete_playthroughs;
extern std::array<bool, TOTAL_MONSTERS> monster_brawled_catalogue;

extern uint32_t last_spawned;
extern SpawnMode spawn_mode;
extern double damage_multiplier;
extern bool during_grace_period;
extern bool disable_negate;
extern bool disable_reverse;
extern MonsterIndex monster_i;
extern std::unique_ptr<Monster> monster;

void setup_game();
void spawn_monster();
void spawn_next_monster();