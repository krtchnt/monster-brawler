#pragma once

#include "include/monster.h"

constexpr size_t MONSTERS_PER_LEVEL = 5;
constexpr size_t LEVELS_PER_GAME = 5;

constexpr size_t MOBS_PER_LEVEL = MONSTERS_PER_LEVEL - 1;
constexpr size_t NORMAL_LEVELS_PER_GAME = LEVELS_PER_GAME - 1;

constexpr MonsterInfo MOB_INFOS[NORMAL_LEVELS_PER_GAME][MOBS_PER_LEVEL] = {
    {
        {"เเมวที่รอดักตีคุณ", "https://i.imgur.com/k5AqVPK.png"},
        {"Green Rimuru", "https://i.imgur.com/RuMAPUk.png"},
        {"หมีน้อย", "https://i.imgur.com/dv5KSLO.jpg"},
        {"Shiba กล้ามโต", "https://i.imgur.com/usivO9Z.png"},
    },
    {
        {"ผมมาทำอะไรที่นี้", "https://i.imgur.com/dnvJ64W.jpg"},
        {"Rakkun (Kon Diao <3)", "https://i.imgur.com/kvCP1vT.jpg"},
        {"จอมยุทธ์ก๋วยเตี๋ยว", "https://i.imgur.com/6zgw9Kp.jpg"},
        {"Johnsus", "https://i.imgur.com/pYsZUqO.jpg"},
    },
    {
        {"นักฆ่าเลือดเย็น", "https://i.imgur.com/AtLu0LY.jpg"},
        {"Capybara", "https://i.imgur.com/dX4uy3y.jpg"},
        {"พ่อ Capybara ที่มาเเก้เเค้น", "https://i.imgur.com/9z6zbO7.jpg"},
        {"ผู้ใช้ดวงตาริคุกัน", "https://i.imgur.com/bGqnLGb.jpg"},
    },
    {
        {"ลากหัวคมๆ", "https://i.imgur.com/5djkuJH.jpg"},
        {"ทอมหัวไก่", "https://i.imgur.com/N5wB8t9.jpg"},
        {"ชาลลัลลาลัลลาวัน", "https://i.imgur.com/u5ZbfTf.jpg"},
        {"Oshi The Rock!", "https://i.imgur.com/Ngdr1jS.png"},
    },
};

constexpr MonsterInfo BOSS_INFOS[NORMAL_LEVELS_PER_GAME] = {
    {"void team(void) { team(); } team();", "https://i.imgur.com/KEZBGib.png"},
    {"\"Poom-Me-Poll\" Kung & Shrek", "https://i.imgur.com/kYVaQWl.jpg"},
    {"Keenimouse", "https://i.imgur.com/JbFF5ZL.jpg"},
    {"Est-canor", "https://i.imgur.com/0cbVpih.png"},
};

constexpr MonsterInfo NEO_BOSS_INFOS[NORMAL_LEVELS_PER_GAME] = {
    {"char title[5] = \"TEAMKRITCHANATTHANAPIPHATSIRI\";",
     "https://i.imgur.com/OqsSQpp.png"},
    {"Natra-pajira-long-korn", "https://i.imgur.com/UKGvlyx.png"},
    {"Keenald Duck", "https://i.imgur.com/t4XMt4V.png"},
    {"Est-arossa", "https://i.imgur.com/PHcwhWy.png"},
};

constexpr MonsterInfo FINAL_BOSS_INFO = {"AutoCAD ก็ไม่เป็นแล้วจะ Figma เป็นมั้ยเนี่ย",
                                         "https://i.imgur.com/17quE6Q.jpg"};