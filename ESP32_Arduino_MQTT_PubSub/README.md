


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

## Resources

- [PlatformIO Documentation](https://docs.platformio.org/)
- [ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [Adafruit MQTT Library](https://github.com/adafruit/Adafruit_MQTT_Library)