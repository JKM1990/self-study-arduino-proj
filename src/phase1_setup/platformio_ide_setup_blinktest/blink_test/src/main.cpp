#include <Arduino.h>

// Define the built-in LED pin
const int LED_PIN = 13;  // Built-in LED on most Arduino boards

void setup() {
  // Initialize the digital pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);   // Turn the LED on
  delay(1000);                   // Wait for one second
  digitalWrite(LED_PIN, LOW);    // Turn the LED off
  delay(1000);                   // Wait for one second
}