#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_BME680 bme;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  if (!bme.begin(0x77)) {
    Serial.println("[Binome 1 - MANZANAS & AGNES] BME680 introuvable");
    lcd.print("BME680 absent");
    while (1);
  }

  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(0, 0);
}

void loop() {
  if (!bme.performReading()) {
    Serial.println("[Binome 1 - MANZANAS & AGNES] Erreur de mesure");
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(bme.temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(bme.humidity);
  lcd.print(" %");

  Serial.print("[Binome 1 - MANZANAS & AGNES] Temp: ");
  Serial.print(bme.temperature);
  Serial.print(" C | Hum: ");
  Serial.print(bme.humidity);
  Serial.println(" %");

  delay(2000);
}