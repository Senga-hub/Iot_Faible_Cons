

# ESP32: ULP, Timer and Deep Sleep

This project demonstrates how to use the ESP32's Ultra Low Power (ULP) coprocessor to perform ADC measurements during deep sleep, and how to use timers to wake up the microcontroller.

## Features

- Use of the ULP coprocessor for ultra low power ADC measurements
- Periodic wake-up of the ESP32 using timers
- Example of entering and exiting deep sleep mode

## Prerequisites

- [PlatformIO Core](https://docs.platformio.org/page/core.html) installed
- Visual Studio Code (recommended)

## Project Structure

- `main/`: main source code (`main.c`)
- `ulp/`: ULP assembly code and configuration
- `platformio.ini` and `CMakeLists.txt`: project configuration

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

## Example Source

This project is based on the official PlatformIO example for ULP ADC:
- https://github.com/platformio/platform-espressif32/tree/develop/examples/espidf-ulp-adc

## Resources

- [PlatformIO Documentation](https://docs.platformio.org/)
- [ULP ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/ulp.html)
- [Deep Sleep ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html)
