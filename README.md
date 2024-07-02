# Freely Paintable Canvas On 3.5" TFT LCD Touchscreen With Arduino UNO R3/R4

![GitHub License](https://img.shields.io/github/license/Aditya-A-garwal/Arduino-TFT-LCD-3-5-Canvas-Paint)
![GitHub forks](https://img.shields.io/github/forks/Aditya-A-garwal/Arduino-TFT-LCD-3-5-Canvas-Paint?style=flat-square&color=blue)
![GitHub Repo stars](https://img.shields.io/github/stars/Aditya-A-garwal/Arduino-TFT-LCD-3-5-Canvas-Paint?style=flat-square&color=blue)
![GitHub issues](https://img.shields.io/github/issues-raw/Aditya-A-garwal/Arduino-TFT-LCD-3-5-Canvas-Paint?style=flat-square&color=indianred)
![GitHub closed issues](https://img.shields.io/github/issues-closed-raw/Aditya-A-garwal/Arduino-TFT-LCD-3-5-Canvas-Paint?style=flat-square)
![GitHub pull requests](https://img.shields.io/github/issues-pr/Aditya-A-garwal/Arduino-TFT-LCD-3-5-Canvas-Paint?style=flat-square&color=indianred)
![GitHub closed pull requests](https://img.shields.io/github/issues-pr-closed/Aditya-A-garwal/Arduino-TFT-LCD-3-5-Canvas-Paint?style=flat-square)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/Aditya-A-garwal/Arduino-TFT-LCD-3-5-Canvas-Paint/build.yml?style=flat-square)

## Overview

This repository contains a program to create a freely paintable canvas with an Arduino UNO R3/R4 and a 3.5" touch screen display shield, as shown below -

|![Image of LCD Touch Shield from Top](images/LCD_top.png)|![Image of LCD Touch Shield from Bottom](images/LCD_bottom.png)|
|-|-|

Most 3.5" TFT LCD Touch displays use the ILI9486 Display Driver and include a resistive touchscreen. **The PCB Layout & silkscreen text may vary slightly between displays. This does not change their behaviour and functionality.** This repository depends on the following libraries -

- [Adafruit Touch Screen Library](https://github.com/adafruit/Adafruit_TouchScreen) to manage touch input
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library/tree/master) for graphics primitives
- [This fork of the MCUFriend KBV library](https://github.com/slviajero/MCUFRIEND_kbv) to drive the display (this makes it compatible with the UNO R4)

The program has been written using PlatformIO, and has been tested on the [Arduino UNO R3](https://docs.arduino.cc/hardware/uno-rev3/), [Arduino UNO R4 Minima](https://docs.arduino.cc/hardware/uno-r4-minima/) & [Arduino UNO R4 WiFi](https://docs.arduino.cc/hardware/uno-r4-wifi/).

## Building/Uploading With PlatformIO

Since this project has been written using PlatformIO by default, simply run the following commands to fetch the libraries, build the project and upload the program -

```shell
pio pkg install
pio run
pio run --target upload
```

## Building/Uploading With Arduino IDE

Create a new sketch and copy the contents of [```src/main.cpp```](/src/main.cpp) from this repository into the default ```.ino``` file. Create a new tab/file in the IDE named ```constants.h``` and copy the contents of [```src/constants.h```](/src/constants.h) from this repository into this file.

Install the Adafruit Touch Screen Library and Adafruit GFX Library from the Library Manager (under *Sketch>Include Library>Manage Libraries...*)

Download [this](https://github.com/slviajero/MCUFRIEND_kbv) repository as a ZIP file and install it by navigating to *Sketch>Include Library>Add .ZIP Library*, and selecting the downloaded file from the file explorer.

After this, you can Build and Upload the program as usual.


## Using the Example

As soon as the program is uploaded, the display should turn black and the following widgets should be displays -

- *Color Selection Grid* with 9 colors to choose from (bottom-left of the screen)
- *Thickness Selection Grid* with 4 sizes to choose from (bottom-right of the screen)
- *Paintable Canvas* to paint in covering roughly the top two-thirds of the entire screen

To choose a color/pen-size, simply tap its icon. The icons in the thickness selection grid display the currently active color.

The colors being shown can be changed by changing the following values in [```src/constants.h```](/src/constants.h)

```cpp
const uint16_t PAINT_COORS[][3] = {
    {0, 0, RED},    {35, 0, GREEN},     {70, 0, BLUE},      // colors in top-row
    {0, 35, CYAN},  {35, 35, MAGENTA},  {70, 35, YELLOW},   // colors in middle-row
    {0, 70, WHITE}, {35, 70, GRAY},     {70, 70, BLACK}     // colors in bottom-row
};
```

The pen-sizes  being shown can be changed by changing the following values in [```src/constants.h```](/src/constants.h)

```cpp
const uint16_t THICKNESS_OPTIONS[] = {3, 5, 7, 9};
```

**Note that the above two snippets contain comments for clarity which are not present in the source file.**

## Troubleshooting

Some common problems and their solutions -

|Problem|Solution|
|-|-|
|Display stays white after uploading program|Non-Standard Driver (not ILI9486)|
|Display not responding after touch|Try changing the order of the touch pins in [```src/constants.h```](/src/constants.h) file, i.e. swap the values of ```XP```, ```YP```, ```XM``` and ```YM```|
|Compilation issues related to SPI|Update the Arduino IDE version and/or install the SPI library|
|Display Flickering/Arduino is reset automatically|Faulty Power Supply/Cable|
