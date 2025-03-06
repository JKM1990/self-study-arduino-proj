#include <Arduino.h>

// Simple button with debounce directly controlling built-in LED

const int buttonPin = 2;      // Button connected to pin 2
const int ledPin = LED_BUILTIN;        // Built-in LED on uno board

// Variables will change:
int ledState = LOW;           // Current state of the LED
int buttonState;              // Current reading from button
int lastButtonState = HIGH;   // Previous reading from button

// Debounce timing
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;    // 50ms debounce period

void setup() {
  // Set up serial port
  Serial.begin(9600);
  Serial.println("Button Debounce Test");
  
  // Set up I/O pins
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  
  // Initialize buttonState with current reading
  buttonState = digitalRead(buttonPin);
  
  // LED test - blink twice to confirm it works
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  
  // Set initial LED state
  digitalWrite(ledPin, ledState);
  
  Serial.println("Setup complete. Press button to toggle LED.");
  Serial.print("Initial button state: ");
  Serial.println(buttonState == HIGH ? "RELEASED" : "PRESSED");
}

void loop() {
  // Read button - it's LOW when pressed (due to INPUT_PULLUP)
  int reading = digitalRead(buttonPin);
  
  // If the button reading changed, reset debounce timer and report raw change
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
    Serial.print("Raw button change detected: ");
    Serial.println(reading == HIGH ? "RELEASED" : "PRESSED");
  }
  
  // Check if debounce time has passed
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed and is stable:
    if (reading != buttonState) {
      buttonState = reading;
      
      // Report debounced state change
      Serial.print("Debounced button state: ");
      Serial.println(buttonState == HIGH ? "RELEASED" : "PRESSED");
      
      // Only toggle the LED if button is pressed (LOW)
      if (buttonState == LOW) {
        ledState = !ledState; // Toggle LED
        Serial.print("Button pressed - toggling LED to: ");
        Serial.println(ledState == HIGH ? "ON" : "OFF");
      }
      
      // Set the LED based on current state
      digitalWrite(ledPin, ledState);
    }
  }
  
  // Save current reading for next comparison
  lastButtonState = reading;
  
  // Small delay to avoid flooding the serial monitor
  delay(10);
}