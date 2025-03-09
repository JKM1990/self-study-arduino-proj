# Experiment 5: Multi-Pattern LED Sequence with OOP

## Date
March 10, 2025

## Objective
Apply object-oriented programming principles to create a reusable LED pattern library that demonstrates classes, header files, non-blocking code, and state machine concepts. Implement multiple LED patterns with automatic and manual pattern switching.

## Components Used
- Arduino Uno R3
- 3 LEDs (different colors)
- 3 resistors (220Ω)
- 1 pushbutton
- Jumper wires
- Breadboard

## Circuit Documentation
- 3 LEDs connected to PWM pins 9, 10, and 11 through 220Ω resistors to GND
- Button connected to pin 2 with internal pull-up resistor
- All ground connections shared on breadboard negative rail

## Code
The code is organized into three files:

1. **LedPatterns.h** - Class definition header file (in include/ directory)
2. **LedPatterns.cpp** - Class implementation (in src/ directory)
3. **main.cpp** - Main application (in src/ directory)

Key concepts demonstrated:

```cpp
// Header guard to prevent multiple inclusion
#ifndef LED_PATTERNS_H
#define LED_PATTERNS_H

// Class with private and public members
class LedPatterns {
  private:
    // Private member variables
    byte* ledPins;      // Array of pin numbers
    byte ledCount;      // Number of LEDs
    
    // Private methods
    void runBlinkPattern();
    void runChasePattern();
    
  public:
    // Constructor
    LedPatterns(byte* pins, byte count);
    
    // Public methods
    void begin();
    void update();
};

#endif
```

## Results
The experiment successfully demonstrated all intended concepts:

1. **Object-Oriented Programming**
   - Created a reusable `LedPatterns` class
   - Properly separated interface (header) from implementation
   - Used encapsulation to hide internal details

2. **LED Pattern Generation**
   - Successfully implemented four distinct patterns:
     - Blink: All LEDs turned on and off together
     - Chase: Single LED moved back and forth across the array
     - Fade: LEDs smoothly faded in and out with phase offsets
     - Random: Random LED states created interesting patterns

3. **Non-Blocking Code**
   - All patterns ran without using `delay()`
   - System remained responsive to button presses at all times
   - Multiple timing operations happened concurrently

4. **State Machine Implementation**
   - Used enum type to clearly define available states
   - Implemented clean state transitions via button and timer

5. **Code Organization**
   - Split code into logical components with proper separation of concerns
   - Used header guards to prevent multiple inclusion issues
   - Implemented functions for specific tasks to avoid repetition

## Learning Outcomes
- Mastered C++ class definition and implementation in separate files
- Understood object instantiation and method/property access
- Applied enum types for clear state representation
- Implemented proper constructor and initialization methods
- Used pointers to pass arrays to objects efficiently
- Created reusable, modular code for future projects
- Applied non-blocking timing for responsive interfaces
- Managed multiple concurrent processes without conflicts
- Optimized code structure for better maintainability

## Next Steps
1. Expand the library to support different LED arrangements (matrix, ring, etc.)
2. Add parameter customization methods for each pattern
3. Implement EEPROM storage to remember the last pattern
4. Create more advanced patterns using combinations of the basic patterns
5. Add brightness control using PWM
6. Create a serial interface for remote pattern control
7. Apply these OOP principles to upcoming stepper motor control tasks

## References
1. Arduino OOP reference: https://www.arduino.cc/reference/en/
2. C++ Header Files: https://www.learncpp.com/cpp-tutorial/header-files/
3. Non-blocking Patterns: https://www.arduino.cc/en/Tutorial/BuiltInExamples/BlinkWithoutDelay
4. State Machine Design: https://www.state-machine.com/arduino
5. Project documentation on C++ fundamentals
