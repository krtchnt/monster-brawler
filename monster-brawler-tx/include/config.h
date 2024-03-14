#pragma once

// `ESP32-S3-DevKitC-1` Baud Rate for I/O.
constexpr uint32_t BAUD_RATE = 115200;
// The Damage Message Topic.
constexpr const char* DAMAGE_TOPIC = "damage";
// Which side of the Monster Brawler Transmitter this board is ("l" for left /
// "r" for right).
constexpr const char* CHIRALITY = "r";
// How much acceleration is needed to register as a damage.
constexpr uint8_t DAMAGE_THRESHOLD = 50;
// The maximum amount of damage possible.
constexpr uint8_t MAX_DAMAGE = 100;
// The maximum measure of acceleration as the maximum damage possible.
constexpr uint8_t MAX_ACCEL = 200;
// The GPIO of `ESP32-S3-DevKitC-1` to connect to the SDA pin of `GY-291
// ADXL345`.
constexpr uint8_t ACCEL_SDA_GPIO = 19;
// The GPIO of `ESP32-S3-DevKitC-1` to connect to the SCL pin of `GY-291
// ADXL345`.
constexpr uint8_t ACCEL_SCL_GPIO = 20;
// The idle acceleration vector modulus, which will always include the
// gravitational acceleration.
constexpr double GRAVITY_OFFSET = 9.586;