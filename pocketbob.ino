/*
  Project to output quotes from an array of strings to the screen.
*/

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_SPI.h> //Hardware-specific library

// TFT Defines
#define MODEL ILI9341
#define TFT_LED A0
#define TFT_RST A4
#define TFT_DC A3
#define TFT_CS A5
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_SCK 13
LCDWIKI_SPI tft = LCDWIKI_SPI(MODEL, TFT_CS, TFT_DC, TFT_MISO, TFT_MOSI, TFT_RST, TFT_SCK, TFT_LED);

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

// Quotes Array
const char* quotes[] = {
    "q1", 
    "q2", 
    "q3", 
    "The fitnessgram pacer test is a multistage aerobic capacity test"
};
const int quotes_len = sizeof(quotes) / sizeof(quotes[0]);

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
void clear_screen() {
    tft.Fill_Screen(ILI9341_BLACK);
}

void center_cursor() {
    // tft.setCursor(100, 100);
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
        change_state(1);
    } else if (current_state == 1) {
        change_state(selection_menu_curr_selection + 2);
    }
}

void b_press() {
    if (current_state != 0) {
        change_state(1);
    }
}

// Core Menu Screens
void start_screen() {
    Serial.println("Starting");
    clear_screen();
    // tft.setCursor(40, 20);
    tft.Set_Text_colour(ILI9341_GREEN);
    tft.Set_Text_Size(2);
    tft.Print_String("####################", 40, 0);
    delay(500);
    // tft.setCursor(40, 50);
    tft.Print_String("###  POCKET BOB  ###", 40, 20);
    delay(500);
    // tft.setCursor(40, 80);
    tft.Print_String("####################", 40, 40);
    delay(500);
    // tft.setCursor(40, 180);
    tft.Print_String("Press A To Continue.", 40, 120);
}

void selection_menu() {
    clear_screen();
    // tft.setCursor(0, 0);
    tft.Print_String("Menu:\n", 0, 0);
    for (int i = 0; i < menu_len; i++) {
        if (i == selection_menu_curr_selection) {
            tft.Print_String("> " + (String)menu_options[i], 0, i*40+40);
        } else {
            tft.Print_String("  " + (String)menu_options[i], 0, i*40+40);
        }
    }

    
}

void random_quote_menu() {
    clear_screen();
    randomSeed(millis());
    int rand = random(quotes_len);
    // tft.setCursor(0, 0);
    tft.Print_String("Random Quote:", 0, 0);
    tft.Print_String(quotes[rand], 0, 40);
}

void browse_quotes_menu() {
    clear_screen();
    // tft.setCursor(0, 0);
    tft.Print_String((String)quotes_menu_curr_selection + 1, 0, 0);
    tft.Print_String("/", 10, 0);
    tft.Print_String((String)quotes_len, 20, 0);
    tft.Print_String(": ", 30, 0);
    tft.Print_String(quotes[quotes_menu_curr_selection], 0, 40);
}

void credits_menu() {
    clear_screen();
    // tft.setCursor(0, 0);
    tft.Print_String("Made by Jtnoble\n\nPress B to go back.", 0, 0);
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
    tft.Init_LCD();
    tft.Set_Rotation(3);
    for (int i = 0; i < NUM_BUTTONS; i++) {
        pinMode(buttonPins[i], INPUT);
    }
    start_screen();
}

void loop() {
    checkButtonStates();
    delay(100); // Obligatory Arduino delay
}
