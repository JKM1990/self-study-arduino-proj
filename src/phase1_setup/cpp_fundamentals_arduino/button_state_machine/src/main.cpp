#include <Arduino.h>

// Pin definitions
const byte BUTTON_PIN = 2;
const byte RED_LED = 9;
const byte GREEN_LED = 10;
const byte BLUE_LED = 11;

// System states
enum SystemState {
  STATE_OFF,
  STATE_LOW,
  STATE_MEDIUM,
  STATE_HIGH,
  NUM_STATES  // Automatically equals the number of states
};

// Current state tracking
SystemState currentState = STATE_OFF;
byte buttonPresses = 0;

// Timing variables for non-blocking operation
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
int lastButtonState = HIGH;
int buttonState = HIGH;

// LED brightness levels
const byte brightness[] = {0, 64, 150, 255};  // For OFF, LOW, MED, HIGH

void setup() {
  // Configure pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  
  // Initial LED state
  updateLeds();
  
  Serial.begin(9600);
  Serial.println(F("Button State Machine Example"));
  Serial.println(F("Press button to cycle through states"));
}

void loop() {
  // Read button with debouncing
  int reading = digitalRead(BUTTON_PIN);
  
  // If button state changed, reset debounce timer
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  // If debounce delay passed, check if button state is stable
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed and is now stable
    if (reading != buttonState) {
      buttonState = reading;
      
      // If button is pressed (LOW with pull-up resistor)
      if (buttonState == LOW) {
        // Cycle to next state
        buttonPresses++;
        currentState = (SystemState)(buttonPresses % NUM_STATES);
        
        // Update LEDs based on new state
        updateLeds();
        
        // Print the current state
        Serial.print(F("Changed to state: "));
        
        switch (currentState) {
          case STATE_OFF:
            Serial.println(F("OFF"));
            break;
          case STATE_LOW:
            Serial.println(F("LOW"));
            break;
          case STATE_MEDIUM:
            Serial.println(F("MEDIUM"));
            break;
          case STATE_HIGH:
            Serial.println(F("HIGH"));
            break;
        }
      }
    }
  }
  
  // Save current reading for next comparison
  lastButtonState = reading;
}

// Function to update LED outputs based on current state
void updateLeds() {
  // Update LED brightness based on current state
  analogWrite(RED_LED, brightness[currentState]);
  analogWrite(GREEN_LED, brightness[currentState]);
  analogWrite(BLUE_LED, brightness[currentState]);
}