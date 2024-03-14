#pragma once

#include <cstddef>
#include <cstdint>

#include "include/spawn_mode.h"

// `ESP32-S3-DevKitC-1` Baud Rate for I/O.
constexpr uint32_t BAUD_RATE = 115200;

// `ESP32-S3-DevKitC-1` GPIO Pin That connects to `SSD1306` OLED's SDA Pin.
constexpr uint8_t OLED_SDA = 48;
// `ESP32-S3-DevKitC-1` GPIO Pin That connects to `SSD1306` OLED's SCL Pin.
constexpr uint8_t OLED_SCL = 47;
// `SSD1306` OLED screen width in pixels.
constexpr uint8_t OLED_SCREEN_WIDTH = 128;
// `SSD1306` OLED screen height in pixels.
constexpr uint8_t OLED_SCREEN_HEIGHT = 64;
// `SSD1306` OLED #1 (Main) I²C Address.
constexpr uint8_t OLED_1_I2CADDR = 0x3C;
// `SSD1306` OLED #2 (Alternate) I²C Address.
constexpr uint8_t OLED_2_I2CADDR = 0x3D;

// New monster spawn grace period; How long will newly spawned monsters be
// invincible, in milliseconds.
constexpr uint16_t GRACE_PERIOD = 1000;
// The `VIT` for the weakest monster (first monster of the first level).
constexpr uint16_t BASE_VIT = 100;
// The `VIT` step progression for each monster in the same level.
constexpr uint16_t MOB_VIT_STEP = 20;
// The `DEF` for the weakest monster (first monster of the first level).
constexpr uint16_t BASE_MOB_DEF = 2;
// The `DEF` for the weakest boss (boss of the first level).
constexpr uint16_t BASE_BOSS_DEF = 3;
// The `DEF` for the weakest neo-boss (first neo-boss of the final level).
constexpr uint16_t BASE_NEO_BOSS_DEF = 4;
// The base `DEF` multplier for the final boss.
constexpr uint16_t FINAL_BOSS_DEF_MULTIPLIER = 5;
// The combo amount for the weakest boss (boss of the first level).
constexpr size_t BASE_BOSS_COMBO = 2;
// The combo amount for the weakest neo-boss (first neo-boss of the final
// level).
constexpr size_t BASE_NEO_BOSS_COMBO = 2;
// The damage negation chance for the weakest neo-boss (first neo-boss of the
// final level).
constexpr double BASE_NEO_BOSS_NEGATE_CHANCE = 0.05;
// The base `VIT` multplier for the final boss.
constexpr size_t FINAL_BOSS_VIT_MULTIPLIER = 2;
// The base combo amount multplier for the final boss.
constexpr size_t FINAL_BOSS_COMBO_MULTIPLIER = 3;
// The base damage negation chance multplier for the final boss.
constexpr double FINAL_BOSS_NEGATE_CHANCE_MULTIPLIER = 0.06;
// The base damage reversal chance multplier for the final boss.
constexpr double FINAL_BOSS_DAMAGE_REVERSE_CHANCE = 0.1;
// The default monster spawning mode.
constexpr SpawnMode DEFAULT_SPAWN_MODE = SpawnMode::NORMAL;