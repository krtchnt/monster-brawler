#pragma once

#include <array>
#include <cstddef>

#include "include/game_default.h"
#include "include/monster.h"

class Level {
    private:
        std::array<Mob, MOBS_PER_LEVEL> mobs;
        Boss boss;

    public:
        [[nodiscard]] Mob get_mob(const size_t index) const;
        void set_mob(const Mob mob, const size_t index);
        [[nodiscard]] Boss get_boss() const;
        void set_boss(const Boss boss);
};

class FinalLevel {
    public:
        [[nodiscard]] NeoBoss get_neo_boss(const size_t index) const;
        void set_neo_boss(const NeoBoss neo_boss, const size_t index);
        [[nodiscard]] FinalBoss get_final_boss() const;
        void set_final_boss(const FinalBoss final_boss);

    private:
        std::array<NeoBoss, NORMAL_LEVELS_PER_GAME> neo_bosses;
        FinalBoss final_boss;
};
