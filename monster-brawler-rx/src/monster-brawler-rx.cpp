#include "include/config.h"
#include "include/game.h"
#include "include/iot.h"
#include "include/oled.h"

void setup() {
    Serial.begin(BAUD_RATE);

    randomSeed(analogRead(0));
    setup_oleds();
    setup_iot();

    setup_game();
}

void loop() {
    mqtt.loop();

    const uint32_t now = millis();
    during_grace_period = now - last_spawned < GRACE_PERIOD;
}