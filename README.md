# 👾 Monster Brawler

> [!IMPORTANT]
> This hardware project is developed under the **01204114 Introduction to Computer Hardware Development** course of **Department of Computer Engineering**, **Faculity of Engineering**, **Kasetsart University**.

## 👥 Project Developers Information

### Team Title

#### Group 9

> **พิซซ่าหน้ากระเพราพริกเกลือ**

### Team Members

- *กฤชณัท ธนพิพัฒนศิริ*
- *ชยกร ศรุตยาพร*
- *ณัฐรพี บัวแก้ว*
- *ปิติภูมิ ยิ่งวงศ์วิวัฒน์*

## 📂 Directory Structure

> [!TIP]
> Files without postfixed notes are implementation details.

```hs
monster-brawler
│   .gitignore
│   flows.json  -- Node-RED Flow file
│   LICENSE.txt 
│   README.md   -- You are here
├───monster-brawler-rx  -- "Receiver" part (Handles game processes)
│   │   .clang-format
│   │   monster-brawler-rx.ino -- Main sketch file
│   │
│   ├───assets
│   │       Schematic_Monster-Brawler-(Receiver)_2024-03-15.pdf -- Schematic file
│   │
│   ├───include
│   │       broker_config.h -- Broker-related config file
│   │       broker_topic.h  -- Broker topic config file
│   │       config.h        -- Main game config file
│   │       damage.h
│   │       game.h
│   │       game_default.h  -- Monster titles & icons config file
│   │       iot.h
│   │       level.h
│   │       monster-brawler-rx.h
│   │       monster.h
│   │       oled.h
│   │       spawn_mode.h
│   │
│   └───src
│           broker_topic.cpp
│           game.cpp
│           iot.cpp
│           level.cpp
│           monster-brawler-rx.cpp
│           monster.cpp
│           oled.cpp
│
└───monster-brawler-tx  -- "Transmitter" part (Publishes damage values from read acceleration data)
    │   .clang-format
    │   monster-brawler-tx.ino -- Main sketch file
    │
    ├───assets
    │       Schematic_Monster-Brawler-(Transmitter)_2024-03-15.pdf -- Schematic file
    │
    ├───include
    │       accel.h
    │       broker_config.h -- Broker-related config file
    │       config.h        -- Main accelerometer config file
    │       damage.h
    │       iot.h
    │       monster-brawler-tx.h
    │
    └───src
            accel.cpp
            damage.cpp
            iot.cpp
            monster-brawler-tx.cpp
```

## 🔌 Hardware Used

- Microcontroller (`ESP32-S3-DevKitC-1`): **3 ea.**
- Accelerometer (`GY-291 ADXL345`): **2 ea.**
- OLED (`SSD1306`): **2 ea.**
- Exercise Gloves: **1 ea.**
- Power Banks (*Optional; Interchangeable with user-owned hardwares*): **2 ea.**

## 📚 Libraries Used

### Accelerometer

- [Adafruit ADXL345](https://github.com/adafruit/Adafruit_ADXL345) & [Adafruit Unified Sensor Driver](https://github.com/adafruit/Adafruit_Sensor) (Dependency)

### OLED

- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library) & [Adafruit Bus IO Library](https://github.com/adafruit/Adafruit_BusIO) (Dependency)
- [Wire](https://www.arduino.cc/en/Reference/Wire)
- [SPI](https://www.arduino.cc/en/Reference/SPI)

### MQTT Connectivity

- [PubSubClient](https://www.arduino.cc/reference/en/libraries/pubsubclient/)
- [WiFi](https://www.arduino.cc/reference/en/libraries/wifi/)

> [!NOTE]  
> Libraries from the C++ Standard Libraries are omitted in this list.

---
