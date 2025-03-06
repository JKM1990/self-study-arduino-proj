// First Arduino Program: Blink
// Date: January 30, 2025
// Description: Blinks the built-in LED on pin 13

const int ledPin = LED_BUILTIN;  // LED_BUILTIN is usually pin 13

void setup() {
  // Initialize digital pin LED_BUILTIN as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);   // Turn the LED on
  delay(1000);                  // Wait for one second
  digitalWrite(ledPin, LOW);    // Turn the LED off
  delay(1000);                  // Wait for one second
}