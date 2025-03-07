# Practical Applications

Now let's move into the practical application part of our C++ fundamentals lesson for Arduino. This is where we'll bring together everything you've learned so far and apply it to a real project. 

## Multi-Pattern LED Sequence

We'll start by building a multi-pattern LED sequence that demonstrates:
- Non-blocking timing
- State machines
- Bit manipulation
- Function organization

This project will serve as a foundation for your 2D plotter, especially when you need to control multiple outputs simultaneously and handle different operational states.

### Project Overview

We'll create a system that:
1. Controls multiple LEDs with different patterns
2. Changes patterns automatically every few seconds
3. Uses non-blocking code throughout
4. Organizes code in a modular way

### Step 1: Setting Up the Project

First, let's set up a new PlatformIO project for this exercise:

```cpp
#include <Arduino.h>

// LED pins (assuming 3 LEDs on PWM pins)
const byte LED_PINS[] = {9, 10, 11};
const byte LED_COUNT = 3;

// Pattern state management
enum PatternState {
  PATTERN_BLINK,    // All LEDs blink together
  PATTERN_CHASE,    // LEDs light up in sequence
  PATTERN_FADE,     // LEDs fade in and out
  PATTERN_RANDOM,   // Random LED patterns
  PATTERN_COUNT     // Total number of patterns (automatically updates)
};

// Current state
PatternState currentPattern = PATTERN_BLINK;
byte patternStep = 0;          // Current step within pattern
unsigned long lastUpdateTime = 0;
unsigned long patternDuration = 5000;  // Switch patterns every 5 seconds
unsigned long stepDuration = 100;      // Time between animation steps

// Function prototypes
void updatePattern();
void runBlinkPattern();
void runChasePattern();
void runFadePattern();
void runRandomPattern();
void setAllLeds(byte value);

void setup() {
  // Initialize LED pins
  for (byte i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  
  Serial.begin(115200);
  Serial.println(F("Multi-pattern LED sequence"));
  Serial.println(F("---------------------------"));
}

void loop() {
  unsigned long currentTime = millis();
  
  // Update the pattern state (non-blocking)
  if (currentTime - lastUpdateTime >= stepDuration) {
    lastUpdateTime = currentTime;
    updatePattern();
  }
  
  // Change to next pattern every patternDuration milliseconds
  if (currentTime % patternDuration < 10) { // Check if we just crossed a 5-second boundary
    currentPattern = (PatternState)((currentPattern + 1) % PATTERN_COUNT);
    patternStep = 0;
    
    // Display which pattern we're showing
    Serial.print(F("Switching to pattern: "));
    switch (currentPattern) {
      case PATTERN_BLINK: Serial.println(F("Blink")); break;
      case PATTERN_CHASE: Serial.println(F("Chase")); break;
      case PATTERN_FADE: Serial.println(F("Fade")); break;
      case PATTERN_RANDOM: Serial.println(F("Random")); break;
      default: break;
    }
  }
}
```

In this initial setup, I've defined:
- The LED pins we'll use
- A state enum for our different patterns
- Timing variables for non-blocking operation
- Function prototypes to organize our code

The state machine pattern is particularly important for your 2D plotter project, as you'll need to handle different operational states (idle, drawing, error, etc.).

### Step 2: Implementing the Pattern Functions

Now let's implement each pattern function:

```cpp
// Update the current pattern based on state
void updatePattern() {
  switch (currentPattern) {
    case PATTERN_BLINK:
      runBlinkPattern();
      break;
    case PATTERN_CHASE:
      runChasePattern();
      break;
    case PATTERN_FADE:
      runFadePattern();
      break;
    case PATTERN_RANDOM:
      runRandomPattern();
      break;
  }
  
  patternStep++;
}

// Pattern implementations
void runBlinkPattern() {
  // Simple on/off pattern - toggles all LEDs together
  if (patternStep % 2 == 0) {
    setAllLeds(HIGH);
  } else {
    setAllLeds(LOW);
  }
}

void runChasePattern() {
  // Reset pattern step if we've gone through all LEDs
  byte currentLed = patternStep % (LED_COUNT * 2);
  
  // Clear all LEDs
  setAllLeds(LOW);
  
  // If we're in the first half of the pattern
  if (currentLed < LED_COUNT) {
    digitalWrite(LED_PINS[currentLed], HIGH);
  } 
  // If we're in the second half, go backwards
  else {
    digitalWrite(LED_PINS[2 * LED_COUNT - currentLed - 1], HIGH);
  }
}

void runFadePattern() {
  // Create a sine wave for smooth fading
  // Each LED is at a different phase of the wave
  
  // Use patternStep to determine the base angle (0-255 maps to 0-360 degrees)
  byte angle = patternStep % 256;
  
  for (byte i = 0; i < LED_COUNT; i++) {
    // Offset each LED by a phase
    byte ledAngle = (angle + (i * 85)) % 256; // Divide 255 by 3 to space them evenly
    
    // Use sine function to create a smooth fade
    // Convert angle (0-255) to radians (0-2π)
    float radians = (ledAngle / 255.0) * 2 * PI;
    
    // Calculate brightness value (0-255)
    byte brightness = (sin(radians) + 1) * 127;
    
    // Write PWM value to the LED
    analogWrite(LED_PINS[i], brightness);
  }
}

void runRandomPattern() {
  // Every 4 steps, generate a new random pattern
  if (patternStep % 4 == 0) {
    for (byte i = 0; i < LED_COUNT; i++) {
      // 50% chance of each LED being on or off
      byte state = random(2);
      digitalWrite(LED_PINS[i], state);
    }
  }
}

// Utility functions
void setAllLeds(byte value) {
  for (byte i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], value);
  }
}
```

Let's analyze each pattern:

1. **Blink Pattern**: This is the simplest - all LEDs turn on and off together.

2. **Chase Pattern**: One LED is on at a time, moving back and forth in a "Knight Rider" style. Note how we use modulo arithmetic to create a cyclic pattern.

3. **Fade Pattern**: Uses sine wave mathematics to create smooth fading effects. Each LED is offset in phase to create a visually interesting effect. This demonstrates how to use `analogWrite()` for PWM control.

4. **Random Pattern**: Generates random LED patterns periodically. This demonstrates the use of Arduino's `random()` function.

### Step 3: Adding User Interaction

Let's enhance our project by adding button input to allow the user to manually change patterns:

```cpp
const byte BUTTON_PIN = 2;  // Button on pin 2

// Button state tracking
bool lastButtonState = HIGH;  // Pull-up resistor means HIGH when not pressed
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;  // 50ms debounce period

// Modify the loop() function
void loop() {
  unsigned long currentTime = millis();
  
  // Handle button input with debouncing
  int reading = digitalRead(BUTTON_PIN);
  
  // If the button state changed, reset debounce timer
  if (reading != lastButtonState) {
    lastDebounceTime = currentTime;
  }
  
  // If debounce time has passed and the button is pressed
  if ((currentTime - lastDebounceTime) > debounceDelay) {
    // If the button state has changed and is now stable
    if (reading == LOW && lastButtonState == HIGH) {
      // Button was pressed - change to next pattern
      currentPattern = (PatternState)((currentPattern + 1) % PATTERN_COUNT);
      patternStep = 0;
      
      // Reset automatic pattern change timer
      lastUpdateTime = currentTime;
      
      // Display which pattern we're showing
      Serial.print(F("Button pressed! Changed to pattern: "));
      switch (currentPattern) {
        case PATTERN_BLINK: Serial.println(F("Blink")); break;
        case PATTERN_CHASE: Serial.println(F("Chase")); break;
        case PATTERN_FADE: Serial.println(F("Fade")); break;
        case PATTERN_RANDOM: Serial.println(F("Random")); break;
        default: break;
      }
    }
  }
  
  // Save current button state for next comparison
  lastButtonState = reading;
  
  // Rest of the loop function (pattern updates, etc.) remains unchanged
  // Update the pattern state (non-blocking)
  if (currentTime - lastUpdateTime >= stepDuration) {
    lastUpdateTime = currentTime;
    updatePattern();
  }
  
  // Automatic pattern change every patternDuration milliseconds
  if (currentTime % patternDuration < 10) {
    currentPattern = (PatternState)((currentPattern + 1) % PATTERN_COUNT);
    patternStep = 0;
    
    Serial.print(F("Auto-switching to pattern: "));
    switch (currentPattern) {
      case PATTERN_BLINK: Serial.println(F("Blink")); break;
      case PATTERN_CHASE: Serial.println(F("Chase")); break;
      case PATTERN_FADE: Serial.println(F("Fade")); break;
      case PATTERN_RANDOM: Serial.println(F("Random")); break;
      default: break;
    }
  }
}

// Don't forget to add this to setup():
void setup() {
  // Initialize LED pins
  for (byte i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  
  // Initialize button pin with pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  Serial.begin(115200);
  Serial.println(F("Multi-pattern LED sequence with button control"));
  Serial.println(F("---------------------------------------------"));
}
```

This code applies your button debouncing knowledge from your previous experiment to allow user interaction. This is important practice for your 2D plotter, which will need user input for control.

## Creating Reusable Components with Header Files

Now let's take this project to the next level by organizing it into reusable components. This is a critical skill for larger Arduino projects like your 2D plotter.

### Step 1: Create a Header File

First, let's create a header file for our LED patterns. In PlatformIO, you would typically create this in the `include` directory of your project.

**LedPatterns.h:**

```cpp
#ifndef LED_PATTERNS_H
#define LED_PATTERNS_H

#include <Arduino.h>

// Pattern state enum
enum PatternState {
  PATTERN_BLINK,
  PATTERN_CHASE,
  PATTERN_FADE,
  PATTERN_RANDOM,
  PATTERN_COUNT
};

class LedPatterns {
  private:
    // LED configuration
    byte* ledPins;
    byte ledCount;
    
    // Pattern state
    PatternState currentPattern;
    byte patternStep;
    unsigned long lastUpdateTime;
    unsigned long patternDuration;
    unsigned long stepDuration;
    
    // Private methods
    void runBlinkPattern();
    void runChasePattern();
    void runFadePattern();
    void runRandomPattern();
    void setAllLeds(byte value);
    
  public:
    // Constructor
    LedPatterns(byte* pins, byte count);
    
    // Public methods
    void begin();
    void update();
    void setPattern(PatternState pattern);
    PatternState getCurrentPattern();
    void setPatternDuration(unsigned long duration);
    void setStepDuration(unsigned long duration);
};

#endif
```

This header file defines our `LedPatterns` class with all the necessary methods and properties. Let's break down what's happening:

1. The `#ifndef/#define/#endif` block is a header guard that prevents the file from being included multiple times.

2. We define the `PatternState` enum outside the class so it can be used by other parts of our code.

3. The class has:
   - Private member variables for configuration and state
   - Private methods for running each pattern
   - Public methods for interfacing with the class

### Step 2: Create the Implementation File

Next, let's create the implementation file that defines the actual behavior of our class. In PlatformIO, this would typically go in the `src` directory.

**LedPatterns.cpp:**

```cpp
#include "LedPatterns.h"

// Constructor
LedPatterns::LedPatterns(byte* pins, byte count) {
  ledPins = pins;
  ledCount = count;
  currentPattern = PATTERN_BLINK;
  patternStep = 0;
  lastUpdateTime = 0;
  patternDuration = 5000;
  stepDuration = 100;
}

void LedPatterns::begin() {
  // Initialize LED pins
  for (byte i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void LedPatterns::update() {
  unsigned long currentTime = millis();
  
  // Update the pattern state
  if (currentTime - lastUpdateTime >= stepDuration) {
    lastUpdateTime = currentTime;
    
    // Run the current pattern
    switch (currentPattern) {
      case PATTERN_BLINK:
        runBlinkPattern();
        break;
      case PATTERN_CHASE:
        runChasePattern();
        break;
      case PATTERN_FADE:
        runFadePattern();
        break;
      case PATTERN_RANDOM:
        runRandomPattern();
        break;
    }
    
    patternStep++;
  }
}

// Pattern implementations
void LedPatterns::runBlinkPattern() {
  // Simple on/off pattern
  if (patternStep % 2 == 0) {
    setAllLeds(HIGH);
  } else {
    setAllLeds(LOW);
  }
}

void LedPatterns::runChasePattern() {
  // Implementation similar to previous example
  byte currentLed = patternStep % (ledCount * 2);
  
  // Clear all LEDs
  setAllLeds(LOW);
  
  if (currentLed < ledCount) {
    digitalWrite(ledPins[currentLed], HIGH);
  } else {
    digitalWrite(ledPins[2 * ledCount - currentLed - 1], HIGH);
  }
}

void LedPatterns::runFadePattern() {
  // Implementation similar to previous example
  byte angle = patternStep % 256;
  
  for (byte i = 0; i < ledCount; i++) {
    byte ledAngle = (angle + (i * (255 / ledCount))) % 256;
    float radians = (ledAngle / 255.0) * 2 * PI;
    byte brightness = (sin(radians) + 1) * 127;
    analogWrite(ledPins[i], brightness);
  }
}

void LedPatterns::runRandomPattern() {
  // Implementation similar to previous example
  if (patternStep % 4 == 0) {
    for (byte i = 0; i < ledCount; i++) {
      byte state = random(2);
      digitalWrite(ledPins[i], state);
    }
  }
}

// Setter methods
void LedPatterns::setPattern(PatternState pattern) {
  if (pattern < PATTERN_COUNT) {
    currentPattern = pattern;
    patternStep = 0;
  }
}

PatternState LedPatterns::getCurrentPattern() {
  return currentPattern;
}

void LedPatterns::setPatternDuration(unsigned long duration) {
  patternDuration = duration;
}

void LedPatterns::setStepDuration(unsigned long duration) {
  stepDuration = duration;
}

// Utility functions
void LedPatterns::setAllLeds(byte value) {
  for (byte i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], value);
  }
}
```

This implementation file contains all the code that makes our class work. Notice how:

1. Each method is prefixed with `LedPatterns::` to indicate it belongs to that class.

2. We've moved all our pattern code into class methods, making it more organized and reusable.

3. We've added setter methods to allow customization of the patterns.

### Step 3: Use the Class in the Main File

Finally, let's modify our main file to use our new class:

**main.cpp:**

```cpp
#include <Arduino.h>
#include "LedPatterns.h"

// Define LED pins
const byte LED_PINS[] = {9, 10, 11};
const byte LED_COUNT = 3;
const byte BUTTON_PIN = 2;

// Create LED patterns object
LedPatterns ledPatterns((byte*)LED_PINS, LED_COUNT);

// Button state tracking
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// Timing for automatic pattern changes
unsigned long lastPatternChangeTime = 0;
const unsigned long patternChangeDuration = 10000;  // 10 seconds between automatic changes

void setup() {
  Serial.begin(115200);
  Serial.println(F("LED Patterns Library Example"));
  
  // Initialize button
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Initialize LED patterns
  ledPatterns.begin();
  
  // Optional: Customize timing
  ledPatterns.setStepDuration(150);  // Slower steps
}

void loop() {
  // Update LED patterns (non-blocking)
  ledPatterns.update();
  
  // Handle button input with debouncing
  unsigned long currentTime = millis();
  int reading = digitalRead(BUTTON_PIN);
  
  // If the button state changed, reset debounce timer
  if (reading != lastButtonState) {
    lastDebounceTime = currentTime;
  }
  
  // If debounce time has passed and the button is pressed
  if ((currentTime - lastDebounceTime) > debounceDelay) {
    // If the button state has changed and is now stable
    if (reading == LOW && lastButtonState == HIGH) {
      // Button was pressed - change to next pattern
      PatternState currentPattern = ledPatterns.getCurrentPattern();
      PatternState nextPattern = (PatternState)((currentPattern + 1) % PATTERN_COUNT);
      ledPatterns.setPattern(nextPattern);
      
      // Reset automatic pattern change timer
      lastPatternChangeTime = currentTime;
      
      // Display which pattern we're showing
      Serial.print(F("Button pressed! Changed to pattern: "));
      switch (nextPattern) {
        case PATTERN_BLINK: Serial.println(F("Blink")); break;
        case PATTERN_CHASE: Serial.println(F("Chase")); break;
        case PATTERN_FADE: Serial.println(F("Fade")); break;
        case PATTERN_RANDOM: Serial.println(F("Random")); break;
        default: break;
      }
    }
  }
  
  // Save current button state for next comparison
  lastButtonState = reading;
  
  // Automatic pattern change
  if (currentTime - lastPatternChangeTime >= patternChangeDuration) {
    lastPatternChangeTime = currentTime;
    
    PatternState currentPattern = ledPatterns.getCurrentPattern();
    PatternState nextPattern = (PatternState)((currentPattern + 1) % PATTERN_COUNT);
    ledPatterns.setPattern(nextPattern);
    
    Serial.print(F("Auto-switching to pattern: "));
    switch (nextPattern) {
      case PATTERN_BLINK: Serial.println(F("Blink")); break;
      case PATTERN_CHASE: Serial.println(F("Chase")); break;
      case PATTERN_FADE: Serial.println(F("Fade")); break;
      case PATTERN_RANDOM: Serial.println(F("Random")); break;
      default: break;
    }
  }
  
  // Your other code can run here without being blocked
}
```

Our main file is now much cleaner and more focused on the application logic, with all the LED pattern details encapsulated in our `LedPatterns` class.

### Benefits of This Approach

This object-oriented approach offers several advantages:

1. **Modularity**: The LED pattern code is isolated and can be reused in other projects.

2. **Maintainability**: Changes to the LED patterns don't require modifying the main code.

3. **Encapsulation**: Implementation details are hidden, making the code easier to use.

4. **Scalability**: You can create multiple instances of the class to control different sets of LEDs.

These principles will be crucial as your 2D plotter project grows in complexity. By organizing your code into reusable components, you'll make it much easier to maintain and extend.

## Connecting to Your 2D Plotter Project

Let's discuss how these concepts will apply to your 2D plotter project:

1. **State Machines**: Your plotter will have different operational states (idle, drawing, homing, error, etc.). Using a state machine pattern similar to our LED patterns will help manage this complexity.

2. **Non-Blocking Code**: For your plotter to move smoothly while still responding to user input or emergency stops, non-blocking code is essential.

3. **Object-Oriented Organization**: Breaking your plotter code into components (motor control, user interface, drawing logic) will make the overall project more manageable.

4. **Memory Efficiency**: You'll need to optimize memory usage when storing drawing paths and motor control parameters.

### Example Plotter Component

For example, you might create a `StepperMotor` class for your plotter:

```cpp
#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include <Arduino.h>

class StepperMotor {
  private:
    // Pin configuration
    byte stepPin;
    byte dirPin;
    byte enablePin;
    
    // Motor parameters
    unsigned int stepsPerRevolution;
    float maxSpeed;          // Steps per second
    float acceleration;      // Steps per second per second
    
    // Current state
    long currentPosition;
    long targetPosition;
    float currentSpeed;
    unsigned long lastStepTime;
    bool isMoving;
    
    // Private methods
    void calculateSpeed();
    
  public:
    // Constructor
    StepperMotor(byte step_pin, byte dir_pin, byte enable_pin, 
                 unsigned int steps_per_rev);
    
    // Configuration
    void begin();
    void setMaxSpeed(float speed);
    void setAcceleration(float acc);
    
    // Movement
    void moveTo(long position);
    void move(long steps);
    void stop();
    void setCurrentPosition(long position);
    
    // Status
    long getCurrentPosition();
    bool isRunning();
    
    // Must be called frequently
    void update();
};

#endif
```

This class could manage all the complexities of stepper motor control, including acceleration profiles and non-blocking movement, while presenting a simple interface to your main code.

## Creating Practical Exercises

To reinforce your learning, here are some practical exercises you could work on:

1. **Enhanced Button Control**: Add different button functions (short press for next pattern, long press for previous pattern, double-click for random pattern).

2. **Serial Command Interface**: Allow pattern selection and configuration via serial commands.

3. **Parameter Customization**: Add methods to customize each pattern's parameters (speed, colors, etc.).

4. **EEPROM Storage**: Save the last used pattern to EEPROM so it's restored after power cycling.

These exercises will help you build the skills you need for your 2D plotter project, especially the parts that involve user interaction and configuration.

## Looking Ahead: Applying These Skills to Your 2D Plotter

As you move forward with your 2D plotter project, you'll apply these C++ fundamentals in increasingly complex ways:

1. For **motor control**, you'll need precise timing and efficient code.

2. For **coordinate systems**, you'll use math operations and data structures to track position.

3. For **user interfaces**, you'll implement state machines and event handling.

4. For **drawing capabilities**, you'll need to parse and execute drawing commands.

The foundation you're building now with C++ fundamentals will make all of these challenges more manageable.

## Summary

We've applied C++ fundamentals to create a practical LED pattern controller. We've explored:

1. **Code Organization**: Using functions, classes, and files to structure our code.
2. **State Machines**: Managing different operational states and transitions.
3. **Non-Blocking Patterns**: Ensuring our system remains responsive.
4. **Object-Oriented Design**: Encapsulating functionality in reusable components.

These skills directly apply to your 2D plotter project and will help you build a more reliable, maintainable system.