#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define PREFIX "[Binome 01 - MANZANAS & AGNES] "

#define WLAN_SSID "iPhone"
#define WLAN_PASS "toto1234"
#define MQTT_SERVER "io.adafruit.com"
#define MQTT_SERVERPORT 1883
#define MQTT_USERNAME "USERNAME"
#define MQTT_KEY "API_KEY"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_KEY);
Adafruit_MQTT_Publish temperatureFeed = Adafruit_MQTT_Publish(&mqtt, MQTT_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish humidityFeed = Adafruit_MQTT_Publish(&mqtt, MQTT_USERNAME "/feeds/humidity");

Adafruit_BME680 bme;

void MQTT_connect();

/*
AI use

I didn't know how to configure the BME680
AI explained the oversampling, IIR filter and gas heater lines
*/

void setup() {
    Serial.begin(115200);
    delay(10);
    Serial.println(PREFIX "Adafruit MQTT demo");

    if (!bme.begin(0x77)) {
        Serial.println(PREFIX "BME680 introuvable");
        while (1);
    }
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(0, 0);

    Serial.print(PREFIX "Connecting to ");
    Serial.println(WLAN_SSID);
    WiFi.begin(WLAN_SSID, WLAN_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print(PREFIX "WiFi connected. IP address: ");
    Serial.println(WiFi.localIP());

    MQTT_connect();
}

void loop() {
    MQTT_connect();

    if (bme.performReading()) {
        Serial.print(PREFIX "Sending temperature ");
        Serial.print(bme.temperature);
        if (temperatureFeed.publish(bme.temperature)) {
            Serial.println(" OK!");
        } else {
            Serial.println(" Failed");
        }
        Serial.print(PREFIX "Sending humidity ");
        Serial.print(bme.humidity);
        if (temperatureFeed.publish(bme.temperature)) {
            Serial.println(" OK!");
        } else {
            Serial.println(" Failed");
        }
    } else {
        Serial.println(PREFIX "BME680 reading failed");
    }

    mqtt.processPackets(10000);
}

void MQTT_connect() {
    int8_t ret;
    if (mqtt.connected()) {
        return;
    }
    Serial.println(PREFIX "Connecting to MQTT... ");
    uint8_t retries = 3;
    while ((ret = mqtt.connect()) != 0) {
        Serial.print(PREFIX);
        Serial.println(mqtt.connectErrorString(ret));
        Serial.println(PREFIX "Retrying MQTT connection in 5 seconds...");
        mqtt.disconnect();
        delay(5000);
        retries--;
        if (retries == 0) {
            while (1);
        }
    }
    Serial.println(PREFIX "MQTT Connected!");
}