# Teensy-Payloads
## Description
This script turns the Teensy into a keyboard (HID) that uses Ducky Script to execute commands.
## Requirements
- Set USB Type to Keyboard on Arduino IDE
## Instructions
1. Edit payload_lines[] with payload commands
2. If using powershell in the payload,
  - Set DEFAULT_DELAY to 0 before typing anything into powershell. Use only 'STRING' commands while this is set to 0.
  - This will use scroll lock to wait until a powershell command is done executing before continuing the rest of the commands in the payload.
  - Set DEFAULT_DELAY to greater than 0 after typing in powershell is complete.
## References
- https://www.pjrc.com/teensy/td_keyboard.html
- https://docs.hak5.org/hc/en-us/articles/360010555153-Ducky-Script-the-USB-Rubber-Ducky-language
- https://github.com/hak5darren/USB-Rubber-Ducky/wiki/Duckyscript
