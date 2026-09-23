"""Deterministic host-side validation for the Week 3 firmware logic.

This is not a replacement for hardware/simulator evidence. It validates the
scheduler and boundary/error-handling logic using repeatable test inputs.
"""

from __future__ import annotations

from dataclasses import dataclass
from math import nan, isnan

BUGGY_INTERVAL_MS = 500
FIXED_INTERVAL_MS = 2000
TEMP_LIMIT = 35.0
HUM_LIMIT = 80.0


def buggy_status(temp: float, hum: float) -> str:
    return "WARNING" if temp > TEMP_LIMIT or hum > HUM_LIMIT else "NORMAL"


def fixed_status(temp: float, hum: float) -> str:
    return "WARNING" if temp >= TEMP_LIMIT or hum >= HUM_LIMIT else "NORMAL"


def safe_reading_status(temp: float, hum: float) -> str:
    if isnan(temp) or isnan(hum):
        return "ERROR"
    return fixed_status(temp, hum)


def scheduled_sample_times(interval_ms: int, total_ms: int) -> list[int]:
    times = []
    t = interval_ms
    while t <= total_ms:
        times.append(t)
        t += interval_ms
    return times


@dataclass
class Result:
    name: str
    passed: bool
    detail: str


def main() -> None:
    results: list[Result] = []

    buggy_times = scheduled_sample_times(BUGGY_INTERVAL_MS, 10_000)
    fixed_times = scheduled_sample_times(FIXED_INTERVAL_MS, 10_000)
    results.append(Result(
        "TIM-01 sampling interval",
        fixed_times == [2000, 4000, 6000, 8000, 10000],
        f"buggy samples={len(buggy_times)} at 500 ms; fixed samples={len(fixed_times)} at 2000 ms",
    ))

    results.append(Result(
        "THR-01 exact temperature boundary",
        buggy_status(35.0, 40.0) == "NORMAL" and fixed_status(35.0, 40.0) == "WARNING",
        "35.0 C is missed by '>' but detected by '>='",
    ))

    results.append(Result(
        "THR-02 exact humidity boundary",
        buggy_status(25.0, 80.0) == "NORMAL" and fixed_status(25.0, 80.0) == "WARNING",
        "80.0 % is missed by '>' but detected by '>='",
    ))

    results.append(Result(
        "ERR-01 invalid reading handling",
        safe_reading_status(nan, 60.0) == "ERROR" and safe_reading_status(28.0, 60.0) == "NORMAL",
        "NaN becomes ERROR; valid sample remains processable",
    ))

    # Deterministic output-volume comparison over ten seconds.
    buggy_samples = len(buggy_times)
    fixed_samples = len(fixed_times)
    # Approximate compact-vs-expanded log line count for the same reporting content.
    buggy_lines = buggy_samples * 1
    fixed_lines = fixed_samples * 1
    reduction = (1 - fixed_samples / buggy_samples) * 100
    results.append(Result(
        "OPT-01 monitoring load",
        fixed_samples < buggy_samples,
        f"sampling events reduced from {buggy_samples} to {fixed_samples} in 10 s ({reduction:.1f}% fewer events)",
    ))

    print("Week 3 validation - deterministic host-side logic checks")
    print("-------------------------------------------------------")
    for r in results:
        print(f"{'PASS' if r.passed else 'FAIL'} | {r.name} | {r.detail}")
    print("-------------------------------------------------------")
    print(f"All tests passed: {all(r.passed for r in results)}")


if __name__ == "__main__":
    main()
