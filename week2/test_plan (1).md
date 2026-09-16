# Week 2 Test Plan

| ID | Test case | Expected result | Evidence status |
|---|---|---|---|
| TC-01 | Compile and start ESP32 + DHT22 firmware | Compilation succeeds and DHT22 initialization message appears | Observed in supplied Sensbench screenshot |
| TC-02 | Read valid temperature and humidity | Numeric values appear in UART output | Verify during final simulation run |
| TC-03 | Check monitoring interval | New sample appears approximately every 2000 ms | Implemented; verify from serial timestamps |
| TC-04 | Cross 35.0 C temperature threshold | Status becomes WARNING | Logic implemented; verify in simulation |
| TC-05 | Cross 80.0 % humidity threshold | Status becomes WARNING | Logic implemented; verify in simulation |
| TC-06 | Force invalid sensor value | Error is reported and loop continues | Logic implemented; verify with fault injection |

## Worked verification examples

**TC-04:** 37.2 C, 63.0 % -> `37.2 >= 35.0` is true -> expected `WARNING`.

**TC-05:** 28.4 C, 82.0 % -> `82.0 >= 80.0` is true -> expected `WARNING`.

**TC-06:** invalid/NaN reading -> error message -> function returns -> scheduler remains active -> later cycle can retry.

Only TC-01 is labeled observed in the report because that is the result directly visible in the supplied screenshot. The other procedures are reproducible verification steps and are not represented as observed results.
