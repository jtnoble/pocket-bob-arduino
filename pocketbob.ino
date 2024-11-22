/*
  Project to output quotes from an array of strings to the screen.
*/

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// States
// {"START", "MENU", "ALL_QUOTES", "RANDOM_QUOTE", "CREDITS"};
int current_state = 0;

// TFT Defines
#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// Button Defines
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

#define UP_BTN 7
int up_btn_state = 0;
bool up_btn_pressed = false;

#define DOWN_BTN 6
int down_btn_state = 0;
bool down_btn_pressed = false;

#define A_BTN 5
int a_btn_state = 0;
bool a_btn_pressed = false;

#define B_BTN 4
int b_btn_state = 0;
bool b_btn_pressed = false;

// Selection Menu Save
int selection_menu_curr_selection = 0;

// Browse Quotes Menu Save
int quotes_menu_curr_selection = 0;

// Quotes Handling
const unsigned int quotes_len = 4;
String quotes[quotes_len] = {"q1", "q2", "q3", "The fitnessgram pacer test is a multistage aerobic capacity test"};

// Setup Home Screen
void setup() {
  tft.begin();

  tft.setRotation(3);
  tft.setCursor(40, 20);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  tft.println("####################");
  delay((500));
  tft.setCursor(40, 50);
  tft.println("###  POCKET BOB  ###");
  delay((500));
  tft.setCursor(40, 80);
  tft.println("####################");
  delay((500));
  tft.setCursor(40, 180);
  tft.println("Press A To Continue.");

}


// Handle presses
void up_press() {
  switch (current_state) {
    case 1:
      // change selector
      if (selection_menu_curr_selection > 0) {
        selection_menu_curr_selection--;
      }
      change_state(1);
      break;
    
    case 3:
      // change selector
      if (quotes_menu_curr_selection > 0) {
        quotes_menu_curr_selection--;
      }
      else {
        quotes_menu_curr_selection = quotes_len - 1;
      }
      change_state(3);
      break;
  }
}

void down_press() {
  switch (current_state) {
    case 1:
      // change selector
      if (selection_menu_curr_selection < 2) {
        selection_menu_curr_selection++;
      }
      change_state(1);
      break;
    
    case 3:
      // change selector
      if (quotes_menu_curr_selection < quotes_len - 1) {
        quotes_menu_curr_selection++;
      }
      else {
        quotes_menu_curr_selection = 0;
      }
      change_state(3);
      break;
  }
}

void a_press() {
  switch (current_state) {
    case 0:
      clear_screen();
      change_state(1);
      break;
    case 1:
      // select
      clear_screen();
      change_state(selection_menu_curr_selection + 2);
      break;
  }
}

void b_press() {
    clear_screen();
    change_state(1);
}

void clear_screen() {
  tft.fillScreen(ILI9341_BLACK);
}

void center_cursor() {
  tft.setCursor(100, 100);
}

// Update current menu state
void change_state(int next_state) {
  current_state = next_state;

  switch (current_state) {
    case 1:
      selection_menu();
      break;
    
    case 2:
      random_quote_menu();
      break;
    
    case 3:
      browse_quotes_menu();
      break;
    
    case 4:
      credits_menu();
      break;
    
    default:
      selection_menu();
      break;
  }
}

// STATE 1
void selection_menu() {
  String options[3] = {"Random Quote", "Browse Quotes", "Credits"};
  
  switch (selection_menu_curr_selection) {
    case 0:
      options[0] = "> Random Quote";
      options[1] = "Browse Quotes";
      options[2] = "Credits";
      break;
    case 1:
      options[0] = "Random Quote";
      options[1] = "> Browse Quotes";
      options[2] = "Credits";
      break;
    case 2:
      options[0] = "Random Quote";
      options[1] = "Browse Quotes";
      options[2] = "> Credits";
      break;
    default:
      break;
  }

  String msg = "Menu:\n" + options[0] + "\n" + options[1] + "\n" + options[2];
  clear_screen();
  center_cursor();
  tft.println(msg);
}

// STATE 2
void random_quote_menu() {
  int rand = random(quotes_len);
  tft.setCursor(0, 0);
  tft.print(rand);
  tft.print(". ");
  String msg = quotes[rand];
  tft.println(msg);
}

// STATE 3
void browse_quotes_menu() {
  clear_screen();
  tft.setCursor(0, 0);
  tft.print(quotes_menu_curr_selection + 1);
  tft.print("/");
  tft.print(quotes_len);
  tft.print(": ");
  tft.println(quotes[quotes_menu_curr_selection]);
}

// STATE 4
void credits_menu() {
  tft.setCursor(0, 0);
  tft.println("Made by Jtnoble\n\nPress B to go back.");
}

void loop() {

  // Get Button States
  up_btn_state = digitalRead(UP_BTN);
  down_btn_state = digitalRead(DOWN_BTN);
  a_btn_state = digitalRead(A_BTN);
  b_btn_state = digitalRead(B_BTN);

  // Debounce
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Handle Up Press
    if (up_btn_state == HIGH && !up_btn_pressed) {
      up_press();
      up_btn_pressed = true;
      lastDebounceTime = millis();
    }

    // Handle Down Press
    if (down_btn_state == HIGH && !down_btn_pressed) {
      down_press();
      down_btn_pressed = true;
    }
    
    // Handle A Press
    if (a_btn_state == HIGH && !a_btn_pressed) {
      a_press();
      a_btn_pressed = true;
    }

    // Handle B Press
    if (b_btn_state == HIGH && !b_btn_pressed) {
      b_press();
      b_btn_pressed = true;
    }
  }
  // Handlers for depressing
  if (up_btn_state == LOW && up_btn_pressed) {
    up_btn_pressed = false;
  }
  if (down_btn_state == LOW && down_btn_pressed) {
    down_btn_pressed = false;
  }
  if (a_btn_state == LOW && a_btn_pressed) {
    a_btn_pressed = false;
  }
  if (b_btn_state == LOW && b_btn_pressed) {
    b_btn_pressed = false;
  }

  // Obligatory Arduino delay
  delay(100);
}
