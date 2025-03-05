// Modified Blink: Faster Pattern
// Date: January 30, 2025
// Description: Blinks the built-in LED on pin 13 with a faster pattern

const int ledPin = LED_BUILTIN;  // LED_BUILTIN is usually pin 13

void setup() {
  // Initialize digital pin LED_BUILTIN as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);   // Turn the LED on
  delay(200);                   // Wait for 0.2 seconds
  digitalWrite(ledPin, LOW);    // Turn the LED off
  delay(200);                   // Wait for 0.2 seconds
}