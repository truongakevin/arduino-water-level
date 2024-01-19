<!-- ABOUT THE PROJECT -->
#   Arduino Water Level Timer Tracker

The purpose of this project was to create a device that can track liquid level, status, and presence in a cup. With the data collected by the various measurements, the device would then calculate the time taken to drink a full cup of liquid (eg. water, soda, or beer). Using an Arduino microcontroller and other various electronic components, the device would measure the presence of liquid in a cup and determine if a user is drinking from the cup and time how long it may take them to drink all the liquid from the cup.

* The project aimed to create a device using an Arduino microcontroller that could track liquid level, status, and presence in a cup to calculate the time taken to drink a full cup of liquid. 
* The device utilized a self-made capacitance sensor, an RGB LED to indicate the different states of the cup, and a timer to track the duration of drinking. A screen was added to display the time taken to drink, and a calibration mode and countdown button were included for better accuracy and game experience. 
* The project provided the opportunity to learn about electrical engineering, including designing a sensor with limited resources, using an OLED screen, and understanding raw data from voltage readings.

## Table of Contents
- [Libraries Used](#libraries-used)
- [Pin Declaration](#pin-declaration)
- [Settings](#settings)
- [Setup Function](#setup-function)
- [Variable Declarations](#variable-declarations)
- [Main Loop](#main-loop)
- [RGB Color Function](#rgb-color-function)
- [Countdown Function](#countdown-function)
- [Display Text Function](#display-text-function)
- [Draw Star Function](#draw-star-function)
- [Rainbow Function](#rainbow-function)

## Libraries Used
- [RBD_Capacitance](link-to-library)
- [RBD_Threshold](link-to-library)
- [RBD_WaterSensor](link-to-library)
- [ezButton](link-to-library)
- [Adafruit_GFX](link-to-library)
- [Adafruit_SSD1306](link-to-library)

## Pin Declaration
- Water Sensor
  - Level Send Pin: 3
  - Level Receive Pin: 2
- LED
  - Red Light Pin: 9
  - Green Light Pin: 10
  - Blue Light Pin: 11
- Button
  - Count Button: 13
  - Calibration Button: 12
- OLED Screen
  - Screen Width: 128
  - Screen Height: 64
  - Screen Address: 0x3C

## Settings
- Screen Toggle
- LED Test Toggle
- Calibration Toggle
- Countdown Toggle
- Water Sensor Toggle
- Show Raw Value Toggle
- Timer Toggle

## Setup Function
The setup function initializes the system by configuring serial communication, setting up LED pins, and initializing components based on the defined settings.

## Variable Declarations
This section declares variables used in the project, including calibration values, button states, and timer-related variables.

## Main Loop
The main loop executes various functionalities, including LED testing, calibration, countdown, and water sensor updates. It also handles the timer when the user is drinking from the cup.

## RGB Color Function
The RGB color function is used to control the RGB LED by setting specific color values.

## Countdown Function
The countdown function creates a visual countdown on the RGB LED before starting the timer.

## Display Text Function
The display text function is responsible for displaying text on the OLED screen.

## Draw Star Function
The draw star function displays a custom star image on the OLED screen.

## Rainbow Function
The rainbow function produces a color-changing effect on the RGB LED.

Feel free to customize this README.md template further based on additional details, images, or specific instructions related to your project.
