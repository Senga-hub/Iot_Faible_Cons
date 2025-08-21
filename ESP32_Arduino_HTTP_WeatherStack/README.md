# ESP32 Arduino HTTP WeatherStack Example with PlatformIO

This project demonstrates how to call an external web API (WeatherStack) from the ESP32 microcontroller using the Arduino framework. The response is parsed using the ArduinoJson library. The main source code is located in `src/main.cpp`, and optional headers are in the `include/` directory.

## Prerequisites

- [PlatformIO Core](https://docs.platformio.org/page/core.html) installed
- Visual Studio Code (recommended)
- [ArduinoJson Library](https://github.com/bblanchon/ArduinoJson) (will be installed via PlatformIO Library Manager)

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

Before building, configure your WiFi SSID, password, and your WeatherStack API key in `src/main.cpp`:

- Set your WiFi credentials (`ssid` and `password`)
- Set your WeatherStack API key (`WEATHERSTACK_API_KEY`)

## Resources

- [PlatformIO Documentation](https://docs.platformio.org/)
- [ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [ESP32 Arduino Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
- [WeatherStack API](https://weatherstack.com/)
- [ArduinoJson Library](https://github.com/bblanchon/ArduinoJson)