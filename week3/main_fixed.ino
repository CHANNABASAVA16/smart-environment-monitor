// Smart Environment Monitoring and Alert System - Week 3 FIXED/OPTIMIZED VERSION
// Platform: ESP32 + Arduino framework
// Sensor: DHT22 on GPIO 4
// Communication: UART/USB Serial at 115200 baud
// Week 3 focus: debugging, fault handling, timing correction, and output optimization.

#include <DHT.h>

#define DHT_PIN 4
#define DHT_TYPE DHT22
DHT dht(DHT_PIN, DHT_TYPE);

// Corrected timing requirement from Week 1/2.
const unsigned long SAMPLE_INTERVAL_MS = 2000;
const float TEMP_WARNING_C = 35.0f;
const float HUM_WARNING_PERCENT = 80.0f;

unsigned long lastSampleTime = 0;
unsigned long sampleCount = 0;
const char* lastStatus = "INIT";

const char* evaluateStatus(float temperature, float humidity) {
  // Inclusive boundary handling: exactly 35.0 C or 80.0 % is a warning.
  if (temperature >= TEMP_WARNING_C || humidity >= HUM_WARNING_PERCENT) {
    return "WARNING";
  }
  return "NORMAL";
}

void reportMeasurement(unsigned long elapsedMs,
                       float temperature,
                       float humidity,
                       const char* status) {
  // Compact one-line log reduces serial formatting/output overhead.
  Serial.print("sample=");
  Serial.print(sampleCount);
  Serial.print(" time_ms=");
  Serial.print(elapsedMs);
  Serial.print(" temp_c=");
  Serial.print(temperature, 1);
  Serial.print(" hum_pct=");
  Serial.print(humidity, 1);
  Serial.print(" status=");
  Serial.println(status);

  if (strcmp(status, lastStatus) != 0) {
    Serial.print("STATE_CHANGE: ");
    Serial.println(status);
    lastStatus = status;
  }
}

void performSensorCycle(unsigned long elapsedMs) {
  sampleCount++;

  const float humidity = dht.readHumidity();
  const float temperature = dht.readTemperature();

  // Fault handling: reject invalid data and continue to the next cycle.
  if (isnan(humidity) || isnan(temperature)) {
    Serial.print("sample=");
    Serial.print(sampleCount);
    Serial.println(" error=INVALID_DHT22_READING action=RETRY_NEXT_CYCLE");
    return;
  }

  const char* status = evaluateStatus(temperature, humidity);
  reportMeasurement(elapsedMs, temperature, humidity, status);
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  Serial.println("Smart Environment Monitor - Week 3 fixed firmware");
  Serial.println("DHT22 GPIO=4 | interval=2000 ms | UART=115200");
  Serial.println("TEMP_LIMIT=35.0 C | HUM_LIMIT=80.0 %");
}

void loop() {
  // Non-blocking scheduler: loop() remains free between measurement events.
  const unsigned long currentTime = millis();

  if (lastSampleTime == 0 ||
      (currentTime - lastSampleTime) >= SAMPLE_INTERVAL_MS) {
    lastSampleTime = currentTime;
    performSensorCycle(currentTime);
  }
}
