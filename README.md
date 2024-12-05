# pocket-bob-arduino
Arduino based quote display. Display quotes out to ILI9341


## Code Setup
Using https://wokwi.com/, you can copy over the code and json to get the correct configuration of arduino, screen and buttons.

## PARTS
- 1x ILI9341 Screen
- 1x Arduino Uno
- 4x Push buttons
- Many wires

## Arduino Schematic
- ILI9341 -> Arduino
  - VCC -> 5V
  - GND -> Digital GND
  - CS -> 10
  - DC -> 9
  - MOSI -> 11
  - SCK -> 13
  - MISO -> 12
- Up Button -> Arduino
  - 1:1.l -> Power GND
  - 1:2.r -> 7
- Down Button -> Arduino
  - 1:1.l -> Power GND
  - 1:2.r -> 6
- A Button -> Arduino
  - 1:1.l -> Power GND
  - 1:2.r -> 5
- B Button -> Arduino
  - 1:1.l -> Power GND
  - 1:2.r -> 4

## Other Stuff
- LCDWIKI API Docs: http://pan.jczn1688.com/directlink/1/SPI%20%20display%20module/2.8inch_SPI_Module_ILI9341.zip
