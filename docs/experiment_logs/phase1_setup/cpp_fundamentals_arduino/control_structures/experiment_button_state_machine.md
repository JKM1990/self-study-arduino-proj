# Experiment 02: Button State Machine with Control Structures

## Date
March 6, 2025

## Objective
Implement a C++ state machine using control structures (switch, if-else) to cycle through multiple LED brightness levels using a button input, while demonstrating non-blocking button debouncing.

## Components Used
- Arduino Uno R3 board
- Breadboard
- 1 pushbutton (tactile switch)
- 3 LEDs (red, green, and blue)
- 3 resistors (220Ω) for the LEDs
- Jumper wires

## Circuit Documentation
State machine circuit with:
- Button connected to pin 2 (using internal pull-up resistor)
- RGB LEDs connected as follows:
  - Red LED: pin 9 -> LED anode (+) -> LED cathode (-) -> 220Ω -> GND
  - Green LED: pin 10 -> LED anode (+) -> LED cathode (-) -> 220Ω -> GND
  - Blue LED: pin 11 -> LED anode (+) -> LED cathode (-) -> 220Ω -> GND
- Button wiring:
  - Button pin 1 -> Arduino pin 2
  - Button pin 3 -> GND (using diagonal connection of button)
- All GND connections made using the breadboard's negative power rail 

## Code
Located in src/phase1_setup/cpp_fudamentals_arduino/button_state_machine/src/main.cpp

## Results
The experiment successfully implemented a state machine with the following results:

1. Button Press Behavior:
   - Each press of the button reliably advanced to the next state
   - Debouncing worked effectively, preventing false triggers
   - The state properly cycled back to OFF after reaching HIGH
   
2. LED Brightness Control:
   - OFF state: All LEDs off (brightness 0)
   - LOW state: All LEDs dimly lit (brightness 64/255)
   - MEDIUM state: All LEDs at medium brightness (brightness 150/255)
   - HIGH state: All LEDs at full brightness (brightness 255/255)
   
3. State Machine Implementation:
   - `enum` type successfully defined the possible states
   - Switch statement handled state-specific messages
   - Modulo operation (`buttonPresses % NUM_STATES`) provided elegant state cycling
   
4. Non-Blocking Implementation:
   - Button debouncing worked without using delay()
   - System remained responsive throughout operation

## Learning Outcomes
- Implemented a C++ state machine using enum types for better code readability
- Used switch-case statements for state-specific behavior
- Created a non-blocking debounce algorithm for button input
- Applied modulo operator for elegant cycling through states
- Used arrays to store and access state-specific data (brightness levels)
- Understood the concept of function prototypes in C++
- Learned PWM output using analogWrite() for LED brightness control
- Practiced proper type casting with (SystemState) when changing states
- Implemented a reusable function (updateLeds()) for code organization

## Next Steps
1. Expand the state machine to include different color combinations
2. Add a second button to allow navigation backward through states
3. Implement timing-based auto-transitions between states
4. Add fade transitions between brightness levels
5. Create a system that remembers the last state after power cycling

## References
1. Arduino State Change Detection: https://www.arduino.cc/en/Tutorial/BuiltInExamples/StateChangeDetection
2. Arduino Debounce Tutorial: https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
3. C++ Enum Types: https://en.cppreference.com/w/cpp/language/enum
4. PWM with analogWrite(): https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
