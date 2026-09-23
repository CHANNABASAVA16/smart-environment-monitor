# Week 4 - System Integration and Final Testing

## Project
Smart Environment Monitoring and Alert System

## Scope
Week 4 combines the major modules defined and developed across the earlier weeks into one integrated ESP32 firmware model:

- DHT22 temperature and humidity input on GPIO 4
- LDR relative light input through ADC GPIO 34
- SSD1306 OLED on I2C GPIO 21/22
- Buzzer alert on GPIO 25
- UART/USB diagnostic logging at 115200 baud
- Non-blocking 2000 ms monitoring scheduler
- Week 3 fault handling and threshold corrections

## Main firmware
`firmware/final_integrated.ino`

The firmware reads all inputs in one scheduled cycle, validates the DHT22 reading, evaluates warning conditions, updates the OLED, controls the buzzer, and reports a compact UART record.

## Configuration
- `configuration/pin_map.md`
- `configuration/integration_config.json`
- `configuration/libraries.txt`

## Validation
Run:

```bash
python validation/integration_validation.py
```

The deterministic integration harness checks normal operation, temperature/humidity boundaries, low-light boundary, invalid DHT input, scheduler interval, and cycle count. The recorded run passes 7/7 logic checks.

## Evidence boundary
The Week 2 simulator screenshot is retained as direct ESP32 + DHT22 baseline evidence. The Week 4 full integration is documented as an implementation-ready target configuration plus deterministic software-level validation; no physical-board measurement is claimed.
