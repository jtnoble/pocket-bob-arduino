# pocket-bob-arduino
Arduino based quote display. Display quotes out to ILI9341


## Code Setup
Using https://wokwi.com/, you can copy over the code and json to get the correct configuration of arduino, screen and buttons.

## PARTS
- 1x ILI9341 Screen
- 1x Arduino Uno
- 4x Push buttons
- 2x 2AA Battery Connectors
- 4x 10k Resistors
- Many wires

## Wiring

#### Battery Power:

- Arduino VIN -> Sliding Switch, Middle Pin
- Sliding Switch, Left Pin -> Positive Battery 1 Terminal
- Negative Battery 1 Terminal -> Positive Battery 2 Terminal
- Negative Battery 2 Terminal -> Ground 

#### ILI9341:
- VCC -> Arduino 5V
- GND -> Ground
- CS -> Arduino A5
- RESET -> Ardunio A4
- D/C -> Arduino A3
- MOSI -> Arduino D11
- SCK -> Arduino D13
- LED -> Arduino V3.3
- MISO -> Arduino D12

#### Buttons
- Top Right -> Arduino DATA PIN
  - UP = 7
  - DOWN = 6
  - A = 5
  - B = 4
- Bottom Left -> Arduino 5V
- Bottom Right -> 10k Resistor -> Arduino Ground

#### Arduino
*May seem redundant, but reiterating in case*
- VIN -> Sliding Switch, Middle Pin
- 5V ->
  - ALL BUTTONS, Bottom Left Pin
  - ILI9341 VCC Pin
- Ground -> Ground
- 3.3V -> ILI9341 LED Pin
- A5 -> ILI9341 CS Pin
- A4 -> ILI9341 RESET Pin
- A3 -> ILI9341 D/C Pin
- D13 -> ILI9341 SCK Pin
- D12 -> ILI9341 MISO Pin
- D11 -> ILI9341 MOSI Pin
- D7 -> Top Right Switch, Button UP
- D6 -> Top Right Switch, Button DOWN
- D5 -> Top Right Switch, Button A
- D4 -> Top Right Switch, Button B
