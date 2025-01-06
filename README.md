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

## Images

##### Main Menu:
![pocketbob_mainmenu](https://github.com/user-attachments/assets/aeb79c00-efba-4f31-867d-5c3113fa9ec1)

##### Selection Menu:
![pocketbob_selectionmenu](https://github.com/user-attachments/assets/9d879e88-9cba-4773-a1c0-459825d955d2)

##### Printed Model Outside/Inside:
![pbob_model_outside](https://github.com/user-attachments/assets/1f7b10d4-be9a-409a-8033-ad6e0c66a193)
![pbob_model_inside](https://github.com/user-attachments/assets/b6ff9c99-cef6-414e-b3c2-63946eb80f7e)



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
