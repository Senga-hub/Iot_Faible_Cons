# ESP32 Arduino MQTT Example with PlatformIO

This project demonstrates how to use MQTT with the ESP32 microcontroller using the Arduino framework and the Adafruit MQTT Library. The main source code is located in `src/main.cpp`, and optional headers are in the `include/` directory.

## Prerequisites

- [PlatformIO Core](https://docs.platformio.org/page/core.html) installed
- Visual Studio Code (recommended)
- [Adafruit MQTT Library](https://github.com/adafruit/Adafruit_MQTT_Library) (will be installed via PlatformIO Library Manager)

## Project Structure

- `src/`: main source files (`main.cpp`)
- `include/`: header files
- `platformio.ini`: PlatformIO configuration


## Build and Upload

Open a terminal in the project folder and run:

```powershell
# Build the project
pio run

# Upload firmware to ESP32
pio run --target upload

# Clean build files
pio run --target clean
```

## Configuration

Before building, configure the following elements in `src/main.cpp`:

```cpp
#define WLAN_SSID "WiFiHostpot"
#define WLAN_PASS "WiFiPassword"
#define MQTT_SERVER "io.adafruit.com"
#define MQTT_SERVERPORT 1883  // use 8883 for SSL
#define MQTT_USERNAME "MY_IO_USERNAME"
#define MQTT_KEY "MY_IO_KEY"
```

Set your WiFi credentials, MQTT server details and credentials.

## Resources

- [PlatformIO Documentation](https://docs.platformio.org/)
- [ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [ESP32 Arduino Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
- [Adafruit MQTT Library](https://github.com/adafruit/Adafruit_MQTT_Library)