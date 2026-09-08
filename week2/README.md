# Week 2 – Firmware Development and Implementation

## Project
Smart Environment Monitoring and Alert System

## Week 2 Scope

This week focuses on implementing and testing the first firmware layer of the
environment monitoring system using an ESP32 and DHT22 sensor.

The firmware:
- Initializes the ESP32 serial interface and DHT22 sensor.
- Reads temperature and humidity values.
- Performs periodic monitoring at a nominal 2-second interval.
- Checks sensor readings for invalid values.
- Compares readings against configurable warning thresholds.
- Reports the measurements and system status through the serial interface.

## Hardware Used

- ESP32 development board
- DHT22 temperature and humidity sensor

### Interface

DHT22 data line → ESP32 GPIO 4

UART/USB serial → development and debugging output

## Firmware Behavior

The basic execution flow is:

Initialize system
→ Read sensor
→ Validate data
→ Check thresholds
→ Report result
→ Wait for next monitoring cycle
→ Repeat

## Prototype Parameters

- Sampling interval: 2000 ms
- Temperature warning threshold: 35.0 °C
- Humidity warning threshold: 80.0 % RH
- Serial baud rate: 115200

## Example Output

```text
Smart Environment Monitor
Week 2 firmware started
DHT22 initialized on GPIO 4

Sample: 1
Temperature: 28.4 C
Humidity: 61.0 %
Status: NORMAL
