# Steno-Keyboard Firmware

High-performance firmware for RP2040/RP2350 based stenography keyboards, built using the Raspberry Pi Pico SDK and TinyUSB.

## Features

- **Matrix Scanning**: Efficient 11x6 matrix scanning implementation.
- **HID Protocol**: Custom 4-byte (27-key) HID bitmap reports for NKRO (N-Key Rollover) support.
- **Debouncing**: Eager debouncing logic for minimal latency.
- **USB Stack**: Integrated TinyUSB for lightweight HID communication.

## Project Structure

- [Steno-Keyboard.c](Steno-Keyboard.c): Main entry point and hardware initialization.
- [keyboard.c](keyboard.c): Matrix scanning and HID report generation logic.
- [usb_descriptors.c](usb_descriptors.c): USB descriptor definitions.
- [sys_debounce/](sys_debounce/): Core debouncing implementation.

## Getting Started

### Prerequisites

- [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk)
- CMake (3.13+)
- Ninja or Make build system

### Build Instructions

1. Create and enter the build directory:
   ```bash
   mkdir build
   cd build
   ```

2. Generate build files:
   ```bash
   cmake ..
   ```

3. Compile the project:
   ```bash
   ninja
   ```

4. Flash the `Steno-Keyboard.uf2` file to the device.

## Technical Notes

- **HID Buffer Size**: The HID report buffer is configured to 32 bytes to accommodate the custom bitmap structure.
- **Chord Collection**: Implements a buffer collection mechanism to ensure synchronized delivery of stenographic chords.
- **SDK Usage**: Utilizes native Pico SDK hardware APIs for optimal performance.
