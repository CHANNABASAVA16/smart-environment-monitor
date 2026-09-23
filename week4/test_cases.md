# Week 4 Integration Test Cases

| ID | Condition | Input | Expected | Evidence status |
|---|---|---|---|---|
| T01 | Normal cycle | 28.4 C, 61.0 %, 2500 ADC | NORMAL, buzzer OFF | PASS - logic validation |
| T02 | Temp boundary | 35.0 C | WARNING, buzzer ON | PASS - logic validation |
| T03 | Humidity boundary | 80.0 % | WARNING, buzzer ON | PASS - logic validation |
| T04 | Low-light boundary | 1200 ADC | WARNING, buzzer ON | PASS - logic validation |
| T05 | Invalid DHT | NaN temperature | Error, safe state, next cycle continues | PASS - logic validation |
| T06 | Scheduler | 2000 ms | One cycle per 2 s target | PASS - logic validation |
| T07 | 10 s window | 2000 ms interval | 5 scheduled cycles | PASS - deterministic count |
| T08 | Startup safety | Startup | Buzzer OFF | PASS - code inspection |
| T09 | OLED update | Valid sample | OLED shows values/status | REVIEW - target configuration; live evidence not captured |
| T10 | UART | Valid sample | Compact log + state change | PASS - code/config inspection |
