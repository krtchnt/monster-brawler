#include "include/accel.h"

#include <Adafruit_ADXL345_U.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "include/config.h"

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

void setup_accel() {
    Wire.begin(ACCEL_SDA_GPIO, ACCEL_SCL_GPIO);

    if (!accel.begin()) {
        Serial.println("No ADXL345 sensor detected.");
        for (;;)
            ;
    }

    accel.setRange(range_t::ADXL345_RANGE_16_G);
}

double get_accel() {
    sensors_event_t event;
    accel.getEvent(&event);
    const float x = event.acceleration.x;
    const float y = event.acceleration.y;
    const float z = event.acceleration.z;

    const double accel =
        sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)) - GRAVITY_OFFSET;

    return accel;
}