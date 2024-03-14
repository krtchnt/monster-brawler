#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "include/damage.h"

struct MonsterInfo {
    public:
        char* title;
        char* icon;
};

class Monster {
    public:
        Monster(const MonsterInfo info, const uint16_t vit, const uint16_t def);
        virtual void take_damage(const Damage damage) = 0;
        virtual void display(bool verbose = false) = 0;
        virtual void increment() const = 0;
        [[nodiscard]] inline bool is_dead() const { return hp == 0; }

    protected:
        MonsterInfo info;
        uint16_t hp;
        uint16_t vit;
        uint16_t def;
};

class Mob : public Monster {
    public:
        Mob();
        Mob(const MonsterInfo info, const uint16_t vit, const uint16_t def);
        void take_damage(const Damage damage) override;
        void display(const bool verbose = false) override;
        void increment() const override;
};

class Boss : public Monster {
    protected:
        std::vector<Damage> combo;
        size_t combo_i;
        size_t combo_n;
        void take_combo_damage(const Damage damage,
                               const bool reversed = false);
        void populate_combo();

    public:
        Boss();
        Boss(const MonsterInfo info, const uint16_t vit, const uint16_t def,
             const size_t combo_n);
        void take_damage(const Damage damage) override;
        void display(const bool verbose = false) override;
        void increment() const override;
};

class NeoBoss : public Boss {
    protected:
        double damage_negate_chance;

    public:
        NeoBoss();
        NeoBoss(const MonsterInfo info, const uint16_t vit, const uint16_t def,
                const size_t combo_n, const double damage_negate_chance);
        void display(const bool verbose = false) override;
        void take_damage(const Damage damage) override;
        void increment() const override;
};

class FinalBoss : public NeoBoss {
        double damage_reverse_chance;

    public:
        FinalBoss();
        FinalBoss(const MonsterInfo info, const uint16_t vit,
                  const uint16_t def, const size_t combo_needed,
                  const double damage_negate_chance,
                  const double damage_reverse_chance);
        void display(const bool verbose = false) override;
        void take_damage(const Damage damage) override;
        void increment() const override;
};
