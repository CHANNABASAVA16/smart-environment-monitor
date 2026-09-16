// Smart Environment Monitoring and Alert System - Week 2 Firmware
// Platform: ESP32 + Arduino framework
// Sensor: DHT22 on GPIO 4
// Communication: UART/USB Serial at 115200 baud
// Simulation target: Sensbench
//
// Week 2 scope:
// - Initialize DHT22 and UART.
// - Sample temperature and humidity at a nominal 2-second interval.
// - Validate sensor values and recover from invalid readings.
// - Apply configurable warning thresholds.
// - Report measurements and status through UART.
//
// The LDR, OLED, buzzer and Wi-Fi blocks from Week 1 are reserved for
// later integration after this sensor/communication core is verified.

#include <DHT.h>

#define DHT_PIN 4
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

const unsigned long SAMPLE_INTERVAL_MS = 2000;
const float TEMP_WARNING_C = 35.0f;
const float HUM_WARNING_PERCENT = 80.0f;

unsigned long lastSampleTime = 0;
unsigned long sampleCount = 0;

const char* evaluateStatus(float temperature, float humidity) {
  if (temperature >= TEMP_WARNING_C ||
      humidity >= HUM_WARNING_PERCENT) {
    return "WARNING";
  }
  return "NORMAL";
}

void reportMeasurement(unsigned long elapsedMs,
                       float temperature,
                       float humidity,
                       const char* status) {
  Serial.println("------------------------------");
  Serial.print("Sample:      ");
  Serial.println(sampleCount);
  Serial.print("Time:        ");
  Serial.print(elapsedMs);
  Serial.println(" ms");
  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.println(" C");
  Serial.print("Humidity:    ");
  Serial.print(humidity, 1);
  Serial.println(" %");
  Serial.print("Status:      ");
  Serial.println(status);
  Serial.println("------------------------------");
}

void performSensorCycle(unsigned long elapsedMs) {
  sampleCount++;

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.print("[Sample ");
    Serial.print(sampleCount);
    Serial.println("] ERROR: Invalid DHT22 reading; retrying next cycle.");
    return;
  }

  const char* status = evaluateStatus(temperature, humidity);
  reportMeasurement(elapsedMs, temperature, humidity, status);
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  Serial.println();
  Serial.println("Smart Environment Monitor");
  Serial.println("Week 2 firmware started");
  Serial.println("DHT22 initialized on GPIO 4");
  Serial.println("Sampling interval: 2000 ms");
  Serial.println("Temperature warning: 35.0 C");
  Serial.println("Humidity warning: 80.0 %");
}

void loop() {
  unsigned long currentTime = millis();

  if (lastSampleTime == 0 ||
      (currentTime - lastSampleTime) >= SAMPLE_INTERVAL_MS) {
    lastSampleTime = currentTime;
    performSensorCycle(currentTime);
  }
}
