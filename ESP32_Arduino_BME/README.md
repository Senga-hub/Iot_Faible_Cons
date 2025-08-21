# ESP32 Arduino BME680 Example with PlatformIO

This project provides an example of how to use the BME680 environmental sensor with the ESP32 microcontroller and the Adafruit BME680 library. The project supports both I2C and SPI connections to the sensor, allowing you to choose the interface that best fits your hardware setup.

Main source code is located in `src/main.cpp`, and optional headers are in the `include/` directory.

## Prerequisites

- [PlatformIO Core](https://docs.platformio.org/page/core.html) installed
- Visual Studio Code (recommended)
- [Adafruit BME680 Library](https://github.com/adafruit/Adafruit_BME680) (will be installed via PlatformIO Library Manager)

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

## Sensor Connection

You can connect the BME680 sensor to the ESP32 using either I2C or SPI. Refer to the Adafruit BME680 library documentation for wiring details and code examples for both interfaces.

## Resources

- [PlatformIO Documentation](https://docs.platformio.org/)
- [ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [ESP32 Arduino Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
- [Adafruit BME680 Library](https://github.com/adafruit/Adafruit_BME680)