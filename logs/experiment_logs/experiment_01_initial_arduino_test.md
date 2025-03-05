# Experiment 1: Initial Arduino Test

## Date
March 2025

## Objective
Verify Arduino IDE setup and test basic functionality using the built-in LED.

## Components Used
- Arduino UNO R3 board
- USB cable
- Arduino IDE

## Circuit Documentation
Used built-in LED on pin 13 - no external components required.

## Code
```cpp
void setup() {
  // Initialize digital pin LED_BUILTIN as an output
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED on
  delay(200);                         // Wait for 200 milliseconds
  digitalWrite(LED_BUILTIN, LOW);    // Turn the LED off
  delay(200);                         // Wait for 200 milliseconds
}
```

## Results
Successfully verified IDE setup. Modified the standard blink program to use a 200ms blink rate. Confirmed the upload process works correctly.

## Learning Outcomes
- Successfully installed and configured Arduino IDE
- Learned basic Arduino program structure (setup/loop)
- Understood how to modify and upload sketches
- Identified the built-in LED location on the board

## Next Steps
Try an external LED circuit on a breadboard to learn about connecting physical components.

## References
- Arduino IDE installation guide
- Built-in Examples > Basics > Blink
