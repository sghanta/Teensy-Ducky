# Teensy Ducky

## Description

This script turns the Teensy into a keyboard (HID) that uses Ducky Script to execute commands.

## Requirements

* Arduino IDE
* Install Teensyduino add-on for Arduino IDE
* Under the tools dropdown in Arduino IDE,
    * Set Board to whichever Teensy you are using
    * Set USB Type to "Keyboard"
    * Set CPU speed to highest available
    * Set Optimize to "Smallest Code"

## Instructions

1. Download the teensy_ducky folder
2. Open teensy_ducky in the Arduino IDE
3. Edit payload_lines[] with payload commands in teensy_ducky.ino
4. If using powershell in the payload,
    - Set DEFAULT_DELAY to 0 before typing anything into powershell. Use only 'STRING' commands while this is set to 0.
    - This will use scroll lock to wait until a powershell command is done executing before continuing the rest of the commands in the payload.
    - Set DEFAULT_DELAY to greater than 0 after typing in powershell is complete.

## References

* https://www.pjrc.com/teensy/td_keyboard.html
* https://docs.hak5.org/hc/en-us/articles/360010555153-Ducky-Script-the-USB-Rubber-Ducky-language
* https://github.com/hak5darren/USB-Rubber-Ducky/wiki/Duckyscript
