#include "include/level.h"

[[nodiscard]] Mob Level::get_mob(const size_t index) const {
    return this->mobs[index];
}
void Level::set_mob(const Mob mob, size_t index) {
    this->mobs[index] = mob;
}
[[nodiscard]] Boss Level::get_boss() const { return this->boss; }
void Level::set_boss(const Boss boss) { this->boss = boss; }

[[nodiscard]] NeoBoss FinalLevel::get_neo_boss(
    const size_t index) const {
    return this->neo_bosses[index];
}
void FinalLevel::set_neo_boss(const NeoBoss neo_boss,
                                     const size_t index) {
    this->neo_bosses[index] = neo_boss;
}

[[nodiscard]] FinalBoss FinalLevel::get_final_boss() const {
    return this->final_boss;
}
void FinalLevel::set_final_boss(const FinalBoss final_boss) {
    this->final_boss = final_boss;
}
