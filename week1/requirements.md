# System Requirements – Smart Environment Monitoring and Alert System

## 1. Functional Requirements

| ID | Requirement | Primary Block | Verification Idea |
|---|---|---|---|
| FR-01 | Measure room temperature | DHT22 | Check that firmware receives a temperature value during each monitoring cycle. |
| FR-02 | Measure relative humidity | DHT22 | Check that humidity is received with the temperature reading. |
| FR-03 | Measure room light level | LDR + ADC | Change the simulated light input and confirm the ADC value changes. |
| FR-04 | Display measured values | SSD1306 OLED | Confirm that the OLED shows current readings and system status. |
| FR-05 | Generate abnormal-condition alert | Buzzer | Cross the configured threshold and confirm that the buzzer turns on. |
| FR-06 | Send monitoring data remotely | ESP32 Wi-Fi | Check that readings can be sent through the planned Wi-Fi interface. |
| FR-07 | Provide development logs | UART/USB serial | Confirm that readings, states, and errors appear in the serial log. |
| FR-08 | Continue monitoring after recoverable sensor errors | Firmware error handling | Simulate an invalid reading and confirm that monitoring continues. |

## 2. Performance and Timing Requirements

| ID | Target | Reason |
|---|---|---|
| PR-01 | Nominal sensor update interval: 2 s | Simple and repeatable sampling schedule for room monitoring. |
| PR-02 | Display refresh within one monitoring cycle | Latest valid readings should appear after each cycle. |
| PR-03 | Alert response within about 2.5 s of a sampled threshold violation | Allows sensing and decision-making to complete within the normal cycle. |
| PR-04 | Prototype operating target: 0–50 °C, 20–90 % RH | Practical room-monitoring target, not a certified accuracy specification. |
| PR-05 | Light represented as relative level / ADC value | Avoids claiming accurate lux without calibration. |

## 3. Interface Requirements

| ID | Connection | Interface | Purpose |
|---|---|---|---|
| IF-01 | DHT22 → ESP32 | Digital single-wire data connection | Temperature and humidity data. |
| IF-02 | LDR divider → ESP32 | Analog ADC input | Relative light-level measurement. |
| IF-03 | OLED → ESP32 | I2C | Display data using SDA and SCL. |
| IF-04 | Buzzer → ESP32 | GPIO/PWM | Alert control. |
| IF-05 | ESP32 ↔ PC / remote system | UART over USB and Wi-Fi | Development logs and planned remote monitoring. |

## 4. Power Requirements

- Input source: 5 V USB supply for the prototype.
- The development board provides the regulated low-voltage logic rail required by the connected modules.
- Week 1 focuses on reliable active monitoring; battery-saving modes are not required.

## 5. Real-Time and Reliability Constraints

- The firmware should not wait indefinitely for sensor or communication operations.
- A failed operation should return control to the main program so local monitoring can continue.
- The normal monitoring cycle is approximately 2 seconds.
- A threshold violation should update the display and alert within about one monitoring cycle.
- Clearly invalid sensor readings should be rejected.
- The buzzer should start in the OFF state.
- Stale readings should not be presented as fresh measurements.
- Communication failure should be reported without stopping local sensing and display functions.

## 6. Provisional ESP32 Pin Allocation

| Block | ESP32 Connection | Signal Type | Purpose |
|---|---|---|---|
| DHT22 data | GPIO 4 | Digital input | Temperature + humidity data |
| LDR divider output | GPIO 34 | ADC input | Relative light level |
| OLED SDA | GPIO 21 | I2C data | Display data |
| OLED SCL | GPIO 22 | I2C clock | Display clock |
| Buzzer | GPIO 25 | Digital/PWM output | Alert control |
| Serial | USB/UART interface | UART | Development and debugging |
| Wi-Fi | ESP32 internal radio | Wireless | Planned remote monitoring |

> Pin assignments are provisional and will be verified during Week 2 simulation.
