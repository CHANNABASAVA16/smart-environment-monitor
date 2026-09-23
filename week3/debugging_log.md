# Week 3 Debugging Log

## Baseline
Week 2 firmware: ESP32 + DHT22, nominal 2000 ms sampling, UART at 115200 baud.

## BUG-01 - Excessive sampling
- Injected change: `SAMPLE_INTERVAL_MS = 500`.
- Symptom: 20 scheduled samples in a 10 s window instead of 5.
- Cause: timing parameter no longer matches the 2 s requirement.
- Fix: restore 2000 ms and keep non-blocking `millis()` scheduling.

## BUG-02 - Threshold boundary error
- Injected change: used `>` instead of `>=`.
- Symptom: exactly 35.0 C or 80.0 % RH remains NORMAL.
- Cause: strict comparison excludes the configured boundary.
- Fix: use inclusive comparisons for the warning thresholds.

## BUG-03 - Invalid sensor data handling
- Injected change: removed `isnan()` validation.
- Symptom: invalid sensor values could reach the status/print path.
- Cause: firmware assumes every sensor read is valid.
- Fix: reject invalid values, print a diagnostic record, and retry on the next scheduled cycle.

## Optimization
The fixed version keeps the non-blocking scheduler, restores the required 2 s interval, and uses a compact UART record with an extra message only when the system state changes. This reduces the scheduled sensor/reporting load while preserving the information needed for debugging.

## Validation
`validation/validation_sim.py` checks scheduler counts, exact threshold boundaries, invalid readings, and the reduction in scheduled monitoring events. The checks are deterministic supporting validation; they are not presented as direct physical-board measurements.
