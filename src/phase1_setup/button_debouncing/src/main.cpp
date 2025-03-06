/**
 * Button Debouncing Experiment
 * 
 * Demonstrates software debouncing for a push button using time-based approach.
 * - Uses a pull-up resistor configuration
 * - Visualizes debounced state with an LED
 * - Reports both raw and debounced states via Serial Monitor
 */

#include <Arduino.h>

// Pin definitions
const int pin_button = 2;  // Button connected to digital pin 2
const int pin_led = 13;    // Built-in LED on pin 13

// Debouncing variables
const unsigned long debounceDelay = 50;  // Debounce time in milliseconds
unsigned long lastDebounceTime = 0;      // Last time the button state changed

// Button state variables
int buttonState = HIGH;             // Current debounced state (HIGH = not pressed with pull-up)
int lastButtonState = HIGH;         // Previous debounced state
int lastRawState = HIGH;            // Last raw reading for detecting changes

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Button Debouncing Experiment");
  Serial.println("----------------------------");
  Serial.println("Press the button to see both raw and debounced states");
  
  // Configure pin modes
  pinMode(pin_button, INPUT_PULLUP);  // Button with internal pull-up resistor
  pinMode(pin_led, OUTPUT);           // LED as output
  
  // Initialize LED to match initial button state (OFF when not pressed)
  digitalWrite(pin_led, !buttonState);  // Invert because of pull-up logic
}

void loop() {
  // Read the current raw state of the button (inverted due to pull-up)
  int rawState = digitalRead(pin_button);
  
  // Check if raw reading has changed
  if (rawState != lastRawState) {
    // Raw state changed, print to serial
    Serial.print("Raw button state changed to: ");
    Serial.println(rawState == LOW ? "PRESSED" : "RELEASED");
    
    // Update the timing for debounce checking
    lastDebounceTime = millis();
  }
  
  // Save the raw reading for next comparison
  lastRawState = rawState;
  
  // Check if enough time has passed since the last change
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed after debouncing
    if (rawState != buttonState) {
      buttonState = rawState;
      
      // Print the debounced state change
      Serial.print("Debounced button state changed to: ");
      Serial.println(buttonState == LOW ? "PRESSED" : "RELEASED");
      
      // Update the LED to match the debounced button state
      // (LOW = pressed with pull-up, so we invert for the LED)
      digitalWrite(pin_led, !buttonState);
    }
  }
  
  // Small delay to prevent overwhelming the serial monitor
  delay(1);
}