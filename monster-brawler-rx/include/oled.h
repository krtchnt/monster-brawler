#pragma once

#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 oled_r;
extern Adafruit_SSD1306 oled_l;

void setup_oleds();
inline void clear_oleds(const bool l = true, const bool r = true) {
    if (l) {
        oled_l.clearDisplay();
        oled_l.display();
    }
    if (r) {
        oled_r.clearDisplay();
        oled_r.display();
    }
}