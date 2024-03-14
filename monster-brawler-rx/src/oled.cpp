#include "include/oled.h"
#include "include/config.h"

#include <Adafruit_GFX.h>
#include <Wire.h>

Adafruit_SSD1306 oled_r(OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT, &Wire, -1);
Adafruit_SSD1306 oled_l(OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT, &Wire, -1);

void setup_oleds() {
    Wire.begin(OLED_SDA, OLED_SCL);

    if (!oled_r.begin(SSD1306_SWITCHCAPVCC, OLED_1_I2CADDR)) {
        Serial.println(F("R SSD1306 allocation failed"));
        for (;;)
            ;
    }

    if (!oled_l.begin(SSD1306_SWITCHCAPVCC, OLED_2_I2CADDR)) {
        Serial.println(F("L SSD1306 allocation failed"));
        for (;;)
            ;
    }

    clear_oleds();
}
