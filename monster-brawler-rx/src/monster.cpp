#include "include/monster.h"

#include "include/broker_topic.h"
#include "include/game.h"
#include "include/iot.h"
#include "include/oled.h"

Monster::Monster(const MonsterInfo info, const uint16_t vit, const uint16_t def)
    : info(info), vit(vit), hp(vit), def(def) {}

Mob::Mob() : Monster({"", ""}, 0, 0){};
Mob::Mob(const MonsterInfo info, const uint16_t vit, const uint16_t def)
    : Monster(info, vit, def) {}

void Mob::take_damage(const Damage damage) {
    hp = (hp > damage.amount) ? hp - damage.amount : 0;
}

void Mob::display(const bool verbose) {
    if (verbose) {
        mqtt.publish(TOPIC_MONSTER_VIT.c_str(), String(vit).c_str());
        mqtt.publish(TOPIC_MONSTER_DEF.c_str(), String(def).c_str());
        mqtt.publish(TOPIC_MONSTER_TITLE.c_str(), info.title);
        mqtt.publish(TOPIC_MONSTER_ICON.c_str(), info.icon);
        mqtt.publish(TOPIC_MONSTER_NEGATE.c_str(), disable_negate ? "-" : "0");
        mqtt.publish(TOPIC_MONSTER_REVERSE.c_str(),
                     disable_reverse ? "-" : "0");
    }

    mqtt.publish(TOPIC_MONSTER_HP.c_str(), String(hp).c_str());
    clear_oleds();
}

void Mob::increment() const {
    total_brawled++;
    mqtt.publish(TOPIC_STATS_BRAWLED_TOTAL.c_str(),
                 String(total_brawled).c_str());
    mobs_brawled++;
    mqtt.publish(TOPIC_STATS_BRAWLED_MOBS.c_str(),
                 String(mobs_brawled).c_str());
}

Boss::Boss() : Monster({"", ""}, 0, 0), combo_n(0), combo_i(0), combo({}){};
Boss::Boss(const MonsterInfo info, const uint16_t vit, const uint16_t def,
           const size_t combo_n)
    : Monster(info, vit, def), combo({}), combo_n(combo_n), combo_i(0) {}

void Boss::populate_combo() {
    const auto combo_dmg = vit / combo_n;

    const auto upper_combo_dmg = static_cast<uint16_t>(4 / 3. * combo_dmg);
    const auto lower_combo_dmg = static_cast<uint16_t>(2 / 3. * combo_dmg);

    for (size_t i = 0; i < combo_n; ++i) {
        combo.push_back({random(lower_combo_dmg, upper_combo_dmg),
                         random(2) ? Chirality::R : Chirality::L});
    }
    mqtt.publish(TOPIC_NOTIFY_DAMAGE.c_str(),
                 "Look at your OLEDs for combo damages!");
}

void Boss::take_combo_damage(const Damage damage, const bool reversed) {
    const auto combo_ith = combo[combo_i];

    const uint16_t actual_damage =
        (damage.amount > def) ? damage.amount - def : 0;
    if (combo_ith.chirality == damage.chirality) {
        combo[combo_i].amount =
            (combo_ith.amount > actual_damage)
                ? (reversed ? combo_ith.amount + actual_damage
                            : combo_ith.amount - actual_damage)
                : 0;

        if (combo[combo_i].amount == 0) {
            combo_i++;
        }

        if (combo_i == combo_n) {
            hp = 0;
        }
    } else {
        mqtt.publish(TOPIC_NOTIFY_WARNING.c_str(),
                     "You are making damage with the wrong chirality!");
    }
};

void Boss::take_damage(const Damage damage) { take_combo_damage(damage); }

void Boss::display(const bool verbose) {
    if (verbose) {
        populate_combo();
        mqtt.publish(TOPIC_MONSTER_VIT.c_str(),
                     (String(combo.size()) + "cmb").c_str());
        mqtt.publish(TOPIC_MONSTER_DEF.c_str(), String(def).c_str());
        mqtt.publish(TOPIC_MONSTER_TITLE.c_str(), info.title);
        mqtt.publish(TOPIC_MONSTER_ICON.c_str(), info.icon);
        mqtt.publish(TOPIC_MONSTER_NEGATE.c_str(), disable_negate ? "-" : "0");
        mqtt.publish(TOPIC_MONSTER_REVERSE.c_str(),
                     disable_reverse ? "-" : "0");
    }

    mqtt.publish(TOPIC_MONSTER_HP.c_str(),
                 (String(combo.size() - combo_i) + "cmb").c_str());
    clear_oleds();

    const auto combo_ith = combo[combo_i];
    auto oled = combo_ith.chirality == Chirality::R ? &oled_r : &oled_l;

    oled->setTextSize(5);
    oled->setTextColor(WHITE);
    oled->setCursor(0, 10);
    oled->println(combo_ith.amount);
    oled->display();
}

void Boss::increment() const {
    total_brawled++;
    mqtt.publish(TOPIC_STATS_BRAWLED_TOTAL.c_str(),
                 String(total_brawled).c_str());
    bosses_brawled++;
    mqtt.publish(TOPIC_STATS_BRAWLED_BOSSES.c_str(),
                 String(bosses_brawled).c_str());
}

NeoBoss::NeoBoss() : Boss(), damage_negate_chance(0){};
NeoBoss::NeoBoss(const MonsterInfo info, const uint16_t vit, const uint16_t def,
                 const size_t combo_n, const double damage_negate_chance)
    : Boss(info, vit, def, combo_n),
      damage_negate_chance(damage_negate_chance) {}

void NeoBoss::take_damage(const Damage damage) {
    const double random_chance = random(101) / 100.;

    if (random_chance < damage_negate_chance && !disable_negate) {
        mqtt.publish(TOPIC_NOTIFY_DAMAGE.c_str(), "Damage Negated!");
        return;
    }

    take_combo_damage(damage);
}

void NeoBoss::display(const bool verbose) {
    if (verbose) {
        populate_combo();
        mqtt.publish(TOPIC_MONSTER_VIT.c_str(),
                     (String(combo.size()) + "cmb").c_str());
        mqtt.publish(TOPIC_MONSTER_DEF.c_str(), String(def).c_str());
        mqtt.publish(TOPIC_MONSTER_TITLE.c_str(), info.title);
        mqtt.publish(TOPIC_MONSTER_ICON.c_str(), info.icon);
        mqtt.publish(
            TOPIC_MONSTER_NEGATE.c_str(),
            disable_negate ? "-" : String(damage_negate_chance * 100).c_str());
        mqtt.publish(TOPIC_MONSTER_REVERSE.c_str(),
                     disable_reverse ? "-" : "0");
    }

    mqtt.publish(TOPIC_MONSTER_HP.c_str(),
                 (String(combo.size() - combo_i) + "cmb").c_str());
    clear_oleds();

    const auto combo_ith = combo[combo_i];
    auto oled = combo_ith.chirality == Chirality::R ? &oled_r : &oled_l;

    oled->setTextSize(5);
    oled->setTextColor(WHITE);
    oled->setCursor(0, 10);
    oled->println(combo_ith.amount);
    oled->display();
}

void NeoBoss::increment() const {
    total_brawled++;
    mqtt.publish(TOPIC_STATS_BRAWLED_TOTAL.c_str(),
                 String(total_brawled).c_str());
    neo_bosses_brawled++;
    mqtt.publish(TOPIC_STATS_BRAWLED_NEO_BOSSES.c_str(),
                 String(neo_bosses_brawled).c_str());
}

FinalBoss::FinalBoss() : NeoBoss(), damage_reverse_chance(0){};
FinalBoss::FinalBoss(const MonsterInfo info, const uint16_t vit,
                     const uint16_t def, const size_t combo_n,
                     const double damage_negate_chance,
                     const double damage_reverse_chance)
    : NeoBoss(info, vit, def, combo_n, damage_negate_chance),
      damage_reverse_chance(damage_reverse_chance) {}

void FinalBoss::take_damage(const Damage damage) {
    const double random_reverse_chance = random(101) / 100.;

    if (random_reverse_chance < damage_reverse_chance && !disable_reverse) {
        take_combo_damage(damage, true);
        mqtt.publish(TOPIC_NOTIFY_DAMAGE.c_str(), "Damage Reversed!");
        return;
    }

    const double random_negate_chance = random(101) / 100.;
    if (random_negate_chance < damage_negate_chance && !disable_negate) {
        mqtt.publish(TOPIC_NOTIFY_DAMAGE.c_str(), "Damage Negated!");
        return;
    }
    take_combo_damage(damage);
}

void FinalBoss::display(const bool verbose) {
    if (verbose) {
        populate_combo();
        mqtt.publish(TOPIC_MONSTER_VIT.c_str(),
                     (String(combo.size()) + "cmb").c_str());
        mqtt.publish(TOPIC_MONSTER_DEF.c_str(), String(def).c_str());
        mqtt.publish(TOPIC_MONSTER_TITLE.c_str(), info.title);
        mqtt.publish(TOPIC_MONSTER_ICON.c_str(), info.icon);
        mqtt.publish(
            TOPIC_MONSTER_NEGATE.c_str(),
            disable_negate ? "-" : String(damage_negate_chance * 100).c_str());
        mqtt.publish(TOPIC_MONSTER_REVERSE.c_str(),
                     disable_reverse
                         ? "-"
                         : String(damage_reverse_chance * 100).c_str());
    }

    mqtt.publish(TOPIC_MONSTER_HP.c_str(),
                 (String(combo.size() - combo_i) + "cmb").c_str());
    clear_oleds();

    const auto combo_ith = combo[combo_i];
    auto oled = combo_ith.chirality == Chirality::R ? &oled_r : &oled_l;

    oled->setTextSize(5);
    oled->setTextColor(WHITE);
    oled->setCursor(0, 10);
    oled->println(combo_ith.amount);
    oled->display();
}

void FinalBoss::increment() const {
    total_brawled++;
    mqtt.publish(TOPIC_STATS_BRAWLED_TOTAL.c_str(),
                 String(total_brawled).c_str());
    final_bosses_brawled++;
    mqtt.publish(TOPIC_STATS_BRAWLED_FINAL_BOSSES.c_str(),
                 String(final_bosses_brawled).c_str());

    if (std::all_of(std::begin(monster_brawled_catalogue),
                    std::end(monster_brawled_catalogue),
                    [](bool i) { return i; })) {
        complete_playthroughs++;
        mqtt.publish(TOPIC_STATS_PLAYTHROUGHS.c_str(),
                     String(complete_playthroughs).c_str());
    }

    monster_brawled_catalogue.fill(false);
}