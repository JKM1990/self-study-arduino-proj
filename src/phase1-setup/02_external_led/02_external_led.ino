// External LED Test
// Pin 8 controls the external LED
const int ledPin = 8;  // Changed from LED_BUILTIN to pin 8

void setup() {
  pinMode(ledPin, OUTPUT);  // Set pin 8 as output
}

void loop() {
  digitalWrite(ledPin, HIGH);  // Turn LED on
  delay(500);                  // Wait half second
  digitalWrite(ledPin, LOW);   // Turn LED off
  delay(500);                  // Wait half second
}