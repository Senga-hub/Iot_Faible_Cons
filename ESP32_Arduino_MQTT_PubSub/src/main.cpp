/***************************************************

 This example is based on https://github.com/adafruit/Adafruit_MQTT_Library/blob/0a19fd0b14d48cc65e61654a6ec0443b0da0b51d/examples/mqtt_esp8266_callback/mqtt_esp8266_callback.ino

 This code is an example of how to use the Adafruit MQTT library with an ESP32 to connect to Adafruit IO and publish/subscribe to feeds.
 It requires the Adafruit MQTT library and the WiFi library for ESP32.

 Make sure to replace WLAN_SSID, WLAN_PASS, MQTT_USERNAME, and MQTT_KEY with your actual WiFi and Adafruit IO credentials.
 
 The code sets up a WiFi connection, connects to the MQTT server, and publishes data from a photocell sensor while subscribing to a LED feed to control an LED based on received commands.
 The photocell value is incremented and published every loop iteration, while the LED feed is checked for incoming messages to control the LED state.

****************************************************/

#include <Arduino.h>
#include <WiFi.h>

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define WLAN_SSID "WiFiHostpot"
#define WLAN_PASS "WiFiPassword"
#define MQTT_SERVER "io.adafruit.com"
#define MQTT_SERVERPORT 1883  // use 8883 for SSL
#define MQTT_USERNAME "MY_IO_USERNAME"
#define MQTT_KEY "MY_IO_KEY"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_KEY);
// Setup a feed called 'photocell' for publishing.
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, MQTT_USERNAME "/feeds/photocell");
// Setup a feed called 'led' for subscribing to changes. A second Adafruit_MQTT_Publish is used to ask for the last value (works on AdafruitIO server).
Adafruit_MQTT_Subscribe led = Adafruit_MQTT_Subscribe(&mqtt, MQTT_USERNAME "/feeds/led");
Adafruit_MQTT_Publish led_lastpub = Adafruit_MQTT_Publish(&mqtt, MQTT_USERNAME "/feeds/led/get");

uint32_t x = 0;

void MQTT_connect();

void ledcallback(char *data, uint16_t len) {
    Serial.print("Here is the led callback, the value is: ");
    Serial.print(data);
    Serial.print(" of size ");
    Serial.println(len);
}

void setup() {
    Serial.begin(115200);
    delay(10);
    Serial.println(F("Adafruit MQTT demo"));

    // Connect to WiFi access point.
    Serial.print("Connecting to ");
    Serial.println(WLAN_SSID);
    WiFi.begin(WLAN_SSID, WLAN_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("WiFi connected. IP address: ");
    Serial.println(WiFi.localIP());

    // Setup MQTT subscription for led feed.
    led.setCallback(ledcallback);
    mqtt.subscribe(&led);

    MQTT_connect();
    led_lastpub.publish("\0");  // Ask the last value at startup, works with AdafruitIO server.
}

void loop() {
    MQTT_connect();

    // Read the received messages, select the time to wait.
    mqtt.processPackets(5000);

    // Now we can publish stuff!
    Serial.print(F("\nSending photocell val "));
    Serial.print(x);
    Serial.print("...");
    Serial.println(F(!photocell.publish(x++) ? "Failed" : "OK!"));
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
    int8_t ret;
    // Stop if already connected.
    if (mqtt.connected()) {
        return;
    }
    Serial.print("Connecting to MQTT... ");
    uint8_t retries = 3;
    while ((ret = mqtt.connect()) != 0) {  // connect will return 0 for connected
        Serial.println(mqtt.connectErrorString(ret));
        Serial.println("Retrying MQTT connection in 5 seconds...");
        mqtt.disconnect();
        delay(5000);  // wait 5 seconds
        retries--;
        if (retries == 0) {
            // basically die and wait for WDT to reset me
            while (1);
        }
    }
    Serial.println("MQTT Connected!");
}