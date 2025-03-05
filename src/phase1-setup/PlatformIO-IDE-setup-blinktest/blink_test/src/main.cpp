#include <Arduino.h>

const int LED_PIN = 8;  // External LED on pin 8

void setup() {
  pinMode(LED_PIN, OUTPUT);
  randomSeed(analogRead(0));  // Initialize random number generator
}

void candleFlicker() {
  // For a standard digital LED, we'll simulate flicker with timing patterns
  // LED mostly stays on, with occasional rapid flickers
  
  // Normal state is ON
  digitalWrite(LED_PIN, HIGH);
  delay(random(50, 200));
  
  // Simulate small flicker (30% chance)
  if (random(10) < 3) {
    // Quick off-on flicker
    digitalWrite(LED_PIN, LOW);
    delay(random(10, 40));
    digitalWrite(LED_PIN, HIGH);
    delay(random(30, 100));
  }
  
  // Simulate medium flicker (15% chance)
  if (random(20) < 3) {
    // Medium off-on flicker
    digitalWrite(LED_PIN, LOW);
    delay(random(20, 60));
    digitalWrite(LED_PIN, HIGH);
    delay(random(10, 30));
    digitalWrite(LED_PIN, LOW);
    delay(random(5, 20));
    digitalWrite(LED_PIN, HIGH);
    delay(random(40, 120));
  }
  
  // Simulate strong wind or draft (5% chance)
  if (random(20) == 0) {
    // Series of flickers
    for (int i = 0; i < random(2, 5); i++) {
      digitalWrite(LED_PIN, LOW);
      delay(random(5, 50));
      digitalWrite(LED_PIN, HIGH);
      delay(random(10, 80));
    }
    delay(random(50, 150));
  }
}

void loop() {
  candleFlicker();
}