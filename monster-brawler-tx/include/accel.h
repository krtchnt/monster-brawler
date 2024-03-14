#pragma once

#include <Adafruit_ADXL345_U.h>

extern Adafruit_ADXL345_Unified accel;

void setup_accel();

double get_accel();