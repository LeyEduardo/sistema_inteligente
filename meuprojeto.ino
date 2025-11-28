#define BLYNK_TEMPLATE_ID "TMPL2cMwf_9_H"
#define BLYNK_TEMPLATE_NAME "Meu projeto"
#define BLYNK_AUTH_TOKEN "U_vJYvwUmZyNP6DgmcQmu-y2dERm1eGD"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WIFI
char ssid[] = "Ley";
char pass[] = "Eduardo98@";

BlynkTimer timer;

// Sensores
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_BME280.h>
#include <Adafruit_BMP280.h>

// Pinos
#define DHTPIN 2
#define DHTTYPE DHT22
#define MQ2_PIN 34
#define I2C_SDA 21
#define I2C_SCL 22

static const float ADC_VREF = 3.3;
static const int ADC_MAX = 4095;

DHT_Unified dht(DHTPIN, DHTTYPE);
Adafruit_BME280 bme;
Adafruit_BMP280 bmp;

bool hasBME = false;
bool hasBMP = false;

// ===== Função de leitura =====
float readMQ2() {
  uint32_t acc = 0;
  for (int i = 0; i < 10; i++) {
    acc += analogRead(MQ2_PIN);
    delay(5);
  }
  return float(acc) / 10.0;
}

// ===== Função que envia dados para o Blynk =====
void sendData() {
  sensors_event_t event;

  dht.temperature().getEvent(&event);
  float temperatura = event.temperature;

  dht.humidity().getEvent(&event);
  float umidade = event.relative_humidity;

  float raw = readMQ2();
  float gasVoltage = (raw / ADC_MAX) * ADC_VREF;

  float pressao = 0;
  if (hasBME) {
    pressao = bme.readPressure() / 100.0;
  } else if (hasBMP) {
    pressao = bmp.readPressure() / 100.0;
  }

  // Enviar ao Blynk
  Blynk.virtualWrite(V0, temperatura);
  Blynk.virtualWrite(V1, umidade);
  Blynk.virtualWrite(V2, pressao);
  Blynk.virtualWrite(V3, gasVoltage);

  // Debug
  Serial.println("------ DADOS ------");
  Serial.print("Temp: "); Serial.println(temperatura);
  Serial.print("Umid: "); Serial.println(umidade);
  Serial.print("Press: "); Serial.println(pressao);
  Serial.print("Gas: "); Serial.println(gasVoltage);
}

void setup() {
  Serial.begin(115200);

  Wire.begin(I2C_SDA, I2C_SCL);
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  dht.begin();

  if (bme.begin(0x76) || bme.begin(0x77)) hasBME = true;
  else if (bmp.begin(0x76) || bmp.begin(0x77)) hasBMP = true;

  // Conectar ao Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Timer: envia dados a cada 2 segundos
  timer.setInterval(2000L, sendData);
}

void loop() {
  Blynk.run();
  timer.run();
}
