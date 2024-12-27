/*
  Project to output quotes from an array of strings to the screen.
*/

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <avr/pgmspace.h>

// TFT Defines
#define MODEL ILI9341
#define TFT_LED A0
#define TFT_RST A4
#define TFT_DC A3
#define TFT_CS A5
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_SCK 13
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST, TFT_MISO);

// Button Defines
#define UP_BTN 7
#define DOWN_BTN 6
#define A_BTN 5
#define B_BTN 4

#define NUM_BUTTONS 4
const int buttonPins[NUM_BUTTONS] = {UP_BTN, DOWN_BTN, A_BTN, B_BTN};
bool buttonStates[NUM_BUTTONS] = {false};

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

// Global State Variables
int current_state = 0;
int selection_menu_curr_selection = 0;
int quotes_menu_curr_selection = 0;
#define MAX_TEXT_LEN 200
char lastPrintedText[MAX_TEXT_LEN] = "";

// Quotes Array
const char quote1[] PROGMEM = "This is the first quote";
const char quote2[] PROGMEM = "A slightly longer second quote";
const char quote3[] PROGMEM = "A much longer, yet still relatively normal quote for the third of the bunch";
const char quote4[] PROGMEM = "The fitnessgram Pacer Test quote, a.k.a quote 4";
const char* const quotes[] PROGMEM = {quote1, quote2, quote3, quote4};
const int quotes_len = sizeof(quotes) / sizeof(quotes[0]);

// Quote Buffer
char buffer[100];

// Menu Options
const char* menu_options[] = {"Random Quote", "Browse Quotes", "Credits"};
const int menu_len = sizeof(menu_options) / sizeof(menu_options[0]);

// Function Prototypes
void start_screen();
void selection_menu();
void random_quote_menu();
void browse_quotes_menu();
void credits_menu();
void handleButtonPress(int buttonIndex);

// Function Pointer Array for State Management
typedef void (*StateFunction)();
StateFunction states[] = {start_screen, selection_menu, random_quote_menu, browse_quotes_menu, credits_menu};

// Utility Functions
void overwriteLastText() {
    tft.setTextColor(ILI9341_BLACK); // Set text color to black
    tft.setCursor(0, 40);            // Adjust the cursor position if needed
    tft.println(lastPrintedText);   // Print the last stored text
}

void clear_screen() {
    tft.fillScreen(ILI9341_BLACK);  // Clear entire screen
}

void clear_top_bar() {
    tft.fillRect(0, 0, tft.height(), 35, ILI9341_BLACK);  // Clear just the top bar where "Random Quote" is
}

void clear_menu() {
    tft.fillRect(0, 15, 15, 80, ILI9341_BLACK); // Clear just the menu cursor
}

void center_cursor() {
    tft.setCursor(100, 100);  // Place cursor roughly centered (kinda not needed)
}

void change_state(int next_state) {
    current_state = next_state;
    states[current_state]();
}

// Button Handlers
void up_press() {
  
    if (current_state == 1 && selection_menu_curr_selection > 0) {
        selection_menu_curr_selection--;
    } else if (current_state == 3 && quotes_menu_curr_selection > 0) {
        quotes_menu_curr_selection--;
    } else if (current_state == 3) {
        quotes_menu_curr_selection = quotes_len - 1; // Loop around
    }
    states[current_state]();
}

void down_press() {
    if (current_state == 1 && selection_menu_curr_selection < menu_len - 1) {
        selection_menu_curr_selection++;
    } else if (current_state == 3 && quotes_menu_curr_selection < quotes_len - 1) {
        quotes_menu_curr_selection++;
    } else if (current_state == 3) {
        quotes_menu_curr_selection = 0; // Loop around
    }
    states[current_state]();
}

void a_press() {
    if (current_state == 0) {
        clear_screen();
        change_state(1);
    } else if (current_state == 1) {
        clear_screen();
        change_state(selection_menu_curr_selection + 2);
    }
}

void b_press() {
    // Always return to state 1
    clear_screen();
    change_state(1);
}

// Core Menu Screens
void start_screen() {
    clear_screen();
    tft.setCursor(40, 20);
    tft.setTextColor(ILI9341_GREEN);
    tft.setTextSize(2);
    tft.println("####################");
    delay(500);
    tft.setCursor(40, 50);
    tft.println("###  POCKET BOB  ###");
    delay(500);
    tft.setCursor(40, 80);
    tft.println("####################");
    delay(500);
    tft.setCursor(40, 180);
    tft.println("Press A To Continue.");
}

void selection_menu() {
    clear_menu();
    tft.setCursor(0, 0);
    tft.println("Menu:");
    for (int i = 0; i < menu_len; i++) {
        if (i == selection_menu_curr_selection) {
            tft.print("> ");
        } else {
            tft.print("  ");
        }
        tft.println(menu_options[i]);
    }
}

void displayQuote(int index) {
    if (index < 0 || index >= quotes_len) {
        return; // Index out of bounds
    }
    // Overwrite the last text before printing the new one
    overwriteLastText();
    
    // Retrieve the new quote from PROGMEM
    strcpy_P(buffer, (char*)pgm_read_word(&(quotes[index])));
    
    // Store the new text
    strncpy(lastPrintedText, buffer, MAX_TEXT_LEN);
    
    // Print the new text
    tft.setTextColor(ILI9341_GREEN); // Set text color to green
    tft.setCursor(0, 40);             // Adjust the cursor position
    tft.println(buffer);
}

// Random Quote Menu
void random_quote_menu() {
    clear_top_bar();
    randomSeed(millis());
    int rand = random(quotes_len);
    tft.setCursor(0, 0);
    tft.println("Random Quote:");
    displayQuote(rand); // Display a random quote
}

// Browse Quotes Menu
void browse_quotes_menu() {
    clear_top_bar();
    tft.setCursor(0, 0);
    tft.print(quotes_menu_curr_selection + 1);
    tft.print("/");
    tft.print(quotes_len);
    tft.print(": ");
    displayQuote(quotes_menu_curr_selection); // Display the selected quote
}

void credits_menu() {
    clear_screen();
    tft.setCursor(0, 0);
    tft.println("Made by Jtnoble\n\nPress B to go back.");
}

// Handle Button Presses
void handleButtonPress(int buttonIndex) {
    switch (buttonIndex) {
        case 0:
            up_press();
            break;
        case 1:
            down_press();
            break;
        case 2:
            a_press();
            break;
        case 3:
            b_press();
            break;
    }
}

void checkButtonStates() {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        bool currentState = digitalRead(buttonPins[i]);
        if (currentState == HIGH && !buttonStates[i] && (millis() - lastDebounceTime > debounceDelay)) {
            handleButtonPress(i);
            buttonStates[i] = true;
            lastDebounceTime = millis();
        } else if (currentState == LOW) {
            buttonStates[i] = false;
        }
    }
}

// Setup and Main Loop
void setup() {
    tft.begin();
    tft.setRotation(3);
    for (int i = 0; i < NUM_BUTTONS; i++) {
        pinMode(buttonPins[i], INPUT);
    }
    start_screen();
}

void loop() {
    checkButtonStates();
    delay(100); // Obligatory Arduino delay
}
