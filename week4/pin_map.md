# Week 4 Integrated Pin Map

| Module | ESP32 pin | Signal | Purpose |
|---|---:|---|---|
| DHT22 | GPIO 4 | Digital data | Temperature + humidity |
| LDR divider | GPIO 34 | ADC input | Relative light level |
| OLED | GPIO 21 | SDA | I2C data |
| OLED | GPIO 22 | SCL | I2C clock |
| Buzzer | GPIO 25 | Digital output | Alert indication |
| UART/USB | USB/UART | Serial | Debugging and status logs |
| Power | USB/board rail | 5 V input / board regulation | Prototype power |

Note: the light value is intentionally treated as a relative ADC value rather than calibrated lux.
