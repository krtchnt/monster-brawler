#include "include/accel.h"
#include "include/config.h"
#include "include/iot.h"

double max_accel = 0.0;
auto above_threshold = false;

constexpr uint8_t OFFSET_MAX_ACCEL = MAX_ACCEL - DAMAGE_THRESHOLD;
constexpr double NORMALISING_FACTOR =
    static_cast<double>(OFFSET_MAX_ACCEL) / MAX_DAMAGE;

inline uint8_t calculate_damage(const double accel) {
    const double offset_accel = accel - DAMAGE_THRESHOLD;

    return static_cast<uint8_t>(offset_accel / NORMALISING_FACTOR);
}

void wait_for_damage_and_publish() {
    const double accel = get_accel();

    if (accel > DAMAGE_THRESHOLD) {
        above_threshold = true;
        if (accel > max_accel) {
            max_accel = accel;
        }
    } else if (above_threshold) {
        const auto damage = calculate_damage(max_accel);
        printf("%s damage: %3d\n", CHIRALITY, damage);

        char damage_str[4];
        sprintf(damage_str, "%d", damage);
        mqtt.publish(TOPIC_DAMAGE.c_str(), damage_str);

        max_accel = 0.0;
        above_threshold = false;
    }
}