# Experiment 2: First External LED Circuit

## Date
March 2025

## Objective
Create a simple external LED circuit using a breadboard to learn about basic electronics connections.

## Components Used
- Arduino UNO R3 board
- Breadboard
- Blue LED
- 220Ω resistor
- Jumper wires

## Circuit Documentation
- Blue LED positive leg connected to Pin 8 through 220Ω resistor
- Blue LED negative leg connected to GND
- Breadboard used for connections

## Code
```cpp
const int ledPin = 8;  // LED connected to digital pin 8

void setup() {
  pinMode(ledPin, OUTPUT);  // Set the pin as output
}

void loop() {
  digitalWrite(ledPin, HIGH);  // Turn LED on
  delay(500);                  // Wait for half a second
  digitalWrite(ledPin, LOW);   // Turn LED off
  delay(500);                  // Wait for half a second
}
```

## Results
Successfully created my first external circuit. The blue LED blinks with a 1-second cycle (500ms on, 500ms off).

## Learning Outcomes
- Learned breadboard layout and connection principles
- Understood the need for current-limiting resistors with LEDs
- Successfully uploaded code independently
- Practiced wiring connections between Arduino and breadboard

## Next Steps
Try creating a circuit with button input to learn about digital inputs and debouncing.

## References
- Arduino Project Hub: Basic LED circuits
- ELEGOO UNO R3 Project Super Starter Kit manual
