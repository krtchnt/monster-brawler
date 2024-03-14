#include "include/accel.h"
#include "include/config.h"
#include "include/damage.h"
#include "include/iot.h"

void setup() {
    Serial.begin(BAUD_RATE);

    setup_accel();
    setup_iot();
}

void loop() {
    mqtt.loop();
    wait_for_damage_and_publish();
}