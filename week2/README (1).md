# Week 2 - Firmware Development and Implementation

## Project
Smart Environment Monitoring and Alert System

## Implemented scope
This week implements the first working firmware slice using an ESP32 and DHT22:

- DHT22 on GPIO 4
- UART/USB serial at 115200 baud
- nominal 2000 ms sampling interval
- temperature warning threshold = 35.0 C
- humidity warning threshold = 80.0 %
- invalid-reading detection and recovery
- structured serial logging

The LDR, OLED, buzzer and Wi-Fi blocks from Week 1 remain reserved for later incremental integration.

## Files
- `firmware/main.ino` - complete Week 2 firmware.
- `evidence/sensbench_dht22_compile.png` - supplied simulation evidence.
- `week2_report.docx` - detailed report.
- `submission_description.txt` - website description.
- `test_plan.md` - verification matrix and worked examples.

## How to run in Sensbench
1. Open the ESP32 + DHT22 example.
2. Confirm DHT22 DATA is connected to GPIO 4.
3. Confirm the DHT library is available.
4. Replace the example sketch with `firmware/main.ino`.
5. Run the simulation and open the serial/output console.
6. Check the startup configuration messages.
7. Observe temperature/humidity reports.
8. Change simulated values and verify NORMAL/WARNING transitions.
9. Test the invalid-data path if the simulator allows fault injection.

## Example serial record
The values below are illustrative, not claimed simulator measurements:

```text
Smart Environment Monitor
Week 2 firmware started
DHT22 initialized on GPIO 4
Sampling interval: 2000 ms
Temperature warning: 35.0 C
Humidity warning: 80.0 %
------------------------------
Sample:      1
Time:        2000 ms
Temperature: 28.4 C
Humidity:    61.2 %
Status:      NORMAL
------------------------------
```

## Worked examples
- Normal: 28.4 C and 61.2 % -> both below thresholds -> NORMAL.
- Temperature warning: 37.2 C and 63.0 % -> 37.2 >= 35.0 -> WARNING.
- Humidity warning: 28.4 C and 82.0 % -> 82.0 >= 80.0 -> WARNING.
- Invalid reading: NaN on either value -> print error -> return to main loop -> retry later.

## Key functions
`setup()` initializes UART and DHT22.
`loop()` performs periodic scheduling using `millis()`.
`performSensorCycle()` reads and validates the sensor.
`evaluateStatus()` applies the configured thresholds.
`reportMeasurement()` prints a consistent debugging record.

## Timing design note
The Week 2 brief gives timer interrupts or UART as example techniques. UART is implemented here, and timing is implemented with `millis()` rather than a blocking delay. DHT22 sensor I/O remains in normal program context instead of an interrupt service routine.
