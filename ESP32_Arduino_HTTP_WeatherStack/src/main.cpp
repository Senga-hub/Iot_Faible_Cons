
// This code is part of an ESP32 Arduino project that connects to a WiFi network,
// fetches weather data from the WeatherStack API, and displays it on the Serial Monitor.
// It uses the ArduinoJson library to parse the JSON response from the API.
#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

#define CITY "Paris" 
const char* ssid = "iPhone_de_EM";
const char* password = "toto123456789";

void setup() {
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    // wait for WiFi connection
    if ((WiFi.status() == WL_CONNECTED)) {
        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        String url = String("http://api.weatherstack.com/current?access_key=") + WEATHERSTACK_API_KEY + "&query=" CITY;
        http.begin(url);

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);

            // Convert to JSON
            JsonDocument doc;
            DeserializationError err = deserializeJson(doc, payload);
            if (err) {
                Serial.printf("JSON error: %s", err.c_str());
            } else if (doc["success"] == false) {
                Serial.printf("API error: %s", doc["error"]["info"] | "unknown");
            } else {
                // Read and display values
                const char* city = doc["location"]["name"];
                const char* localtime = doc["location"]["localtime"];  // "YYYY-MM-DD HH:MM"
                float temp = doc["current"]["temperature"];
                float wind = doc["current"]["wind_speed"];  // km/h

                Serial.println("-----------------------------");
                Serial.printf("City        : %s", city);
                Serial.printf("Time        : %s", localtime);
                Serial.printf("Temperature : %.1f *C", temp);
                Serial.printf("Wind speed  : %.1f km/h", wind);
                Serial.println("-----------------------------");
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
    }
    delay(5000);
}
