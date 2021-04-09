# RAKwireless Arduino core for the ESP32
<!--[![Build Status](https://travis-ci.org/espressif/arduino-esp32.svg?branch=master)](https://travis-ci.org/espressif/arduino-esp32) ![](https://github.com/espressif/arduino-esp32/workflows/ESP32%20Arduino%20CI/badge.svg) -->
<center><img src="./docs/RAK.png" alt="Modules" width="150"> <img src="./docs/rakstar.jpg" alt="Modules" width="100"></center>      
<center><img src="./docs/RAK11200.png" alt="Modules" width="250"></center>

## Credits
This BSP is based on the [ArduinoESP32 BSP](https://github.com/espressif/arduino-esp32). We will keep this BSP inline with the original BSP.

## Contents
<!-- [Development Status](#development-status) -->
- [Installation Instructions](#installation-instructions)
- [Decoding Exceptions](#decoding-exceptions)
- [Issue/Bug reports](#issuebug-reports)
- [RAK11200 Connector PINMAP](#rak11200-connector-pinmap)

<!--
### Development Status

Latest Stable Release  [![Release Version](https://img.shields.io/github/release/espressif/arduino-esp32.svg?style=plastic)](https://github.com/espressif/arduino-esp32/releases/latest/) [![Release Date](https://img.shields.io/github/release-date/espressif/arduino-esp32.svg?style=plastic)](https://github.com/espressif/arduino-esp32/releases/latest/) [![Downloads](https://img.shields.io/github/downloads/espressif/arduino-esp32/latest/total.svg?style=plastic)](https://github.com/espressif/arduino-esp32/releases/latest/)

Latest Development Release  [![Release Version](https://img.shields.io/github/release/espressif/arduino-esp32/all.svg?style=plastic)](https://github.com/espressif/arduino-esp32/releases/latest/) [![Release Date](https://img.shields.io/github/release-date-pre/espressif/arduino-esp32.svg?style=plastic)](https://github.com/espressif/arduino-esp32/releases/latest/) [![Downloads](https://img.shields.io/github/downloads-pre/espressif/arduino-esp32/latest/total.svg?style=plastic)](https://github.com/espressif/arduino-esp32/releases/latest/)
-->

### Installation Instructions
- Using Arduino IDE Boards Manager (preferred)
  + [Instructions for Boards Manager](http://docs.rakwireless.com/Product-Categories/WisBlock/RAK11200/Quickstart/#arduino-ide-bsp-installation)

### Decoding exceptions

You can use [EspExceptionDecoder](https://github.com/me-no-dev/EspExceptionDecoder) to get meaningful call trace.

### Issue/Bug reports 
Please report issues and bugs in the [RAKwireless Forum](https://forum.rakwireless.com/c/wisblock/67).

### RAK11200 Connector PINMAP

The RAK11200 module has a ESP32-WROVER module at its core. The figure below shows the core module pins and connection information.

![ESP32 pinout](./docs/ESP32-Pinout.png)

WisBlock Core RAK11200 Pin Assignment

| Pin number WisBlock | Function | Pin name | Pin number ESP32|
| :----------: | ---------| ---- | ------- |
| 1 |  VBAT | VBAT | -- |
| 2 |  VBAT | VBAT | -- |
| 3 |  GND | GND | 1, 15, 38 |
| 4 |  GND | GND | 1, 15, 38 |
| 5 |  3V3 | 3V3 | 2 |
| 6 |  3V3 | 3V3 | 2 |
| 7 |  USB_DP |  USB_DP | -- |
| 8 |  USB_DN | USB_DN | -- |
| 9 |  NC | NC | -- |
| 10 |  SW1 | GPIO34 | 6 |
| 11 |  UART0_TX | GPIO1 | 35 |
| 12 |  UART0_RX | GPIO3 | 34 |
| 13 |  EN | EN | 3 |
| 14 |  LED1 | GPIO12 | 14 |
| 15 |  LED2 | GPIO2 | 24 |
| 16 |  NC | NC | -- |
| 17 |  3V3 | 3V3 | 2 |
| 18 |  3V3 | 3V3 | 2 |
| 19 |  I2C1_SDA | GPIO4 | 26 |
| 20 |  I2C1_SCL | GPIO5 | 29 |
| 21 |  AIN0 | GPIO36 | 4 |
| 22 |  AIN1 | GPIO39 | 5 |
| 23 |  BOOT | GPIO0 | 25 |
| 24 |  NC | NC | -- |
| 25 |  SPI_CS | GPIO32 | 8 |
| 26 |  SPI_CLK | GPIO33| 9 |
| 27 |  SPI_MISO | GPIO35  | 7 |
| 28 |  SPI_MOSI | GPIO25 | 10 |
| 29 | IO1  | GPIO14 | 13 |
| 30 | IO2  | GPIO27 | 12 |
| 31 | IO3  | GPIO26 | 11 |
| 32 | IO4  | GPIO23 | 37 |
| 33 | UART1_TX | GPIO21 | 33 |
| 34|  UART1_RX | GPIO19 | 31 |
| 35 | I2C2_SDA | GPIO15 | 23 |
| 36 | I2C2_SCL | GPIO18 | 30 |
| 37 |  IO5 | GPIO13 | 16 |
| 38 |  IO6 | GPIO22 | 36 |
| 39 |  GND | GND | 1, 15, 38 |
| 40 |  GND | GND | 1, 15, 38 |

### Tip

Sometimes to program ESP32 via serial you must keep GPIO0 LOW during the programming process
