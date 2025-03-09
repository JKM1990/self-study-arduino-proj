#include <Arduino.h>
#include "LedPatterns.h"

/**
 * Multi-Pattern LED Sequence
 * 
 * This program demonstrates object-oriented programming principles
 * by creating a reusable LED pattern library. It implements several
 * different patterns with non-blocking code and a button interface.
 * 
 * Circuit:
 * - 3 LEDs connected to pins 9, 10, 11 (through 220Ω resistors)
 * - Button connected to pin 2 (with internal pull-up)
 */

// Pin definitions
const byte LED_PINS[] = {9, 10, 11};  // Must be PWM pins for fade pattern
const byte LED_COUNT = 3;
const byte BUTTON_PIN = 2;

// Create LED patterns object
LedPatterns ledPatterns((byte*)LED_PINS, LED_COUNT);

// Button state tracking
bool lastButtonState = HIGH;  // Pull-up means HIGH when not pressed
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;  // 50ms debounce period

// Timing for automatic pattern changes
unsigned long lastPatternChangeTime = 0;
const unsigned long patternChangeDuration = 10000;  // 10 seconds

// Function prototypes
void handleButtonPress();
void checkAutoPatternChange();

void setup() {
  // Initialize serial at higher baud rate for smoother output
  Serial.begin(115200);
  Serial.println(F("Multi-Pattern LED Sequence"));
  Serial.println(F("-------------------------"));
  Serial.println(F("Press button to change patterns"));
  
  // Initialize button pin with pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Initialize LED patterns
  ledPatterns.begin();
  
  // Set initial pattern timing
  ledPatterns.setStepDuration(100);  // 100ms between steps
  
  // Display initial pattern
  Serial.print(F("Initial pattern: "));
  Serial.println(ledPatterns.getPatternName());
}

void loop() {
  // Update LED patterns (non-blocking)
  ledPatterns.update();
  
  // Handle button presses (with debouncing)
  handleButtonPress();
  
  // Check for automatic pattern changes
  checkAutoPatternChange();
  
  // Other code can run here without being blocked
  // This demonstrates the non-blocking approach
}

// Handle button presses with debouncing
void handleButtonPress() {
  // Read current button state
  int reading = digitalRead(BUTTON_PIN);
  unsigned long currentTime = millis();
  
  // If the button state changed, reset debounce timer
  if (reading != lastButtonState) {
    lastDebounceTime = currentTime;
  }
  
  // If debounce delay has passed, check if button state is stable
  if ((currentTime - lastDebounceTime) > debounceDelay) {
    // If button is newly pressed (LOW due to pull-up)
    if (reading == LOW && lastButtonState == HIGH) {
      // Change to next pattern
      PatternState currentPattern = ledPatterns.getCurrentPattern();
      PatternState nextPattern = (PatternState)((currentPattern + 1) % PATTERN_COUNT);
      ledPatterns.setPattern(nextPattern);
      
      // Reset automatic pattern change timer
      lastPatternChangeTime = currentTime;
      
      // Display the new pattern name
      Serial.print(F("Button pressed! Changed to pattern: "));
      Serial.println(ledPatterns.getPatternName());
    }
  }
  
  // Save button state for next comparison
  lastButtonState = reading;
}

// Check if it's time for an automatic pattern change
void checkAutoPatternChange() {
  unsigned long currentTime = millis();
  
  // If enough time has passed since last pattern change
  if (currentTime - lastPatternChangeTime >= patternChangeDuration) {
    lastPatternChangeTime = currentTime;
    
    // Change to next pattern
    PatternState currentPattern = ledPatterns.getCurrentPattern();
    PatternState nextPattern = (PatternState)((currentPattern + 1) % PATTERN_COUNT);
    ledPatterns.setPattern(nextPattern);
    
    // Display the new pattern name
    Serial.print(F("Auto-switching to pattern: "));
    Serial.println(ledPatterns.getPatternName());
  }
}
