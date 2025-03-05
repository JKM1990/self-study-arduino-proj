# Experiment 01: First Arduino Blink
Date: January 30, 2025
Objective: Verify Arduino setup and basic functionality

## Equipment Used
- ELEGOO UNO R3 Controller Board
- USB Cable

## Program Explanation
This program will blink the built-in LED (connected to digital pin 13) on and off at 1-second intervals. 
The built-in LED is labeled "L" on the Arduino board.

## Code
```cpp
// Pin 13 has a built-in LED on most Arduino boards
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
```

## Key Concepts
1. `setup()`: Runs once at startup
   - Used for initializing pins and starting serial communication
   - `pinMode()` configures a pin as either INPUT or OUTPUT

2. `loop()`: Runs continuously after setup
   - Main program loop where most code goes
   - Arduino executes this function repeatedly

3. `digitalWrite()`: Sets a digital pin HIGH (5V) or LOW (0V)
   - HIGH = On = 5V
   - LOW = Off = 0V

4. `delay()`: Pauses program execution
   - Takes milliseconds as parameter (1000ms = 1 second)

## Test Process
1. Open Arduino IDE
2. Create new sketch
3. Copy code above
4. Select correct board (Tools > Board > Arduino Uno)
5. Select correct port (Tools > Port > COM port with Arduino)
6. Click upload button (→)

## Expected Results
- LED labeled "L" on board should:
  1. Turn on for 1 second
  2. Turn off for 1 second
  3. Repeat indefinitely

## Success Criteria
- [ ] IDE recognizes Arduino - COMPLETE
- [ ] Code compiles successfully - COMPLETE
- [ ] Upload completes without errors - COMPLETE
- [ ] LED blinks as expected - COMPLETE