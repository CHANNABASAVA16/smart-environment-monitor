# Week 1 – System Requirements and Architecture

## Project
Smart Environment Monitoring and Alert System

## Week 1 Objective
Define the system requirements and prepare the hardware and software architecture for the embedded monitoring prototype.

## System Summary
The proposed system uses an ESP32 microcontroller to monitor room temperature, humidity, and relative light level. A DHT22 provides temperature and humidity data, while an LDR with a voltage divider provides an analog light signal to the ESP32 ADC. The system presents the latest readings on an SSD1306 I2C OLED display, activates a buzzer when a configured threshold is exceeded, and provides UART/USB serial logs. Wi-Fi is reserved for planned remote monitoring.

## Main Design Targets
- Monitoring cycle: approximately 2 seconds
- Temperature and humidity monitoring: DHT22
- Light sensing: LDR + ADC
- Local display: SSD1306 OLED over I2C
- Alert: buzzer via GPIO/PWM
- Development/debugging: UART over USB
- Prototype power: 5 V USB supply
- Simulation-first development: Wokwi

## Files
- `requirements.md` – system requirements, interfaces, power, timing, and reliability targets
- `block_diagram.png` – hardware architecture and major data/power paths
- `software_architecture.png` – planned firmware module architecture
- `week1_report.docx` – submitted Week 1 report

## Status
Week 1 – requirements and architecture completed. Pin assignments are provisional and will be verified during Week 2 simulation.
