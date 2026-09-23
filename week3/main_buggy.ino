// Smart Environment Monitoring and Alert System - Week 3 BUGGY VERSION
// Purpose: intentionally introduce common firmware defects for debugging practice.

#include <DHT.h>

#define DHT_PIN 4
#define DHT_TYPE DHT22
DHT dht(DHT_PIN, DHT_TYPE);

// BUG 1: This interval is shorter than the Week 1/2 design target of 2000 ms.
// It causes unnecessary sampling and changes the intended monitoring behavior.
const unsigned long SAMPLE_INTERVAL_MS = 500;

const float TEMP_WARNING_C = 35.0f;
const float HUM_WARNING_PERCENT = 80.0f;

unsigned long lastSampleTime = 0;
unsigned long sampleCount = 0;

const char* evaluateStatus(float temperature, float humidity) {
  // BUG 2: Strict '>' misses an exact threshold value such as 35.0 C.
  if (temperature > TEMP_WARNING_C || humidity > HUM_WARNING_PERCENT) {
    return "WARNING";
  }
  return "NORMAL";
}

void performSensorCycle(unsigned long elapsedMs) {
  sampleCount++;

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // BUG 3: There is no NaN/invalid-reading check.
  // Invalid readings can be reported as if they were normal numeric data.
  Serial.print("Sample=");
  Serial.print(sampleCount);
  Serial.print(" time=");
  Serial.print(elapsedMs);
  Serial.print("ms temp=");
  Serial.print(temperature, 1);
  Serial.print("C hum=");
  Serial.print(humidity, 1);
  Serial.print("% status=");
  Serial.println(evaluateStatus(temperature, humidity));
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  Serial.println("Week 3 BUGGY firmware started");
}

void loop() {
  unsigned long currentTime = millis();

  if (lastSampleTime == 0 || (currentTime - lastSampleTime) >= SAMPLE_INTERVAL_MS) {
    lastSampleTime = currentTime;
    performSensorCycle(currentTime);
  }
}
