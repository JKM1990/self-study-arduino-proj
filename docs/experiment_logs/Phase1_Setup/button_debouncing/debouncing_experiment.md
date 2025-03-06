# Experiment 3: Button Debouncing Methods Comparison

## Date
March 5, 2025

## Objective
Compare multiple button debouncing techniques to understand their performance characteristics and implement a bounce simulation to visualize the physical phenomena.

## Components Used
- Arduino Uno R3
- Tactile pushbutton (4-pin)
- LED (blue)
- 220Ω resistor
- Jumper wires
- Breadboard

## Circuit Documentation
Button connected diagonally (pins 1-3) to ensure proper operation:
- Pin 1 connected to D2 (using INPUT_PULLUP)
- Pin 3 connected to ground
- Built-in LED on pin 13 controlled by time-based debouncing
- External LED on pin 8 (with 220Ω resistor) controlled by counter-based debouncing

## Code
```cpp
#include <Arduino.h>

// Enhanced button debouncing with simulated bounce
// Shows multiple debouncing methods for comparison

// Pin definitions
const int buttonPin = 2;      // Button connected to pin 2
const int ledPin = LED_BUILTIN; // Built-in LED
const int externalLedPin = 8; // External LED for comparing debounce methods

// Debounce method 1: Time-based (current method)
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;    // 50ms debounce period
int lastButtonState = HIGH;   // Previous reading from button
int buttonState = HIGH;       // Current debounced state
int ledState = LOW;           // Current state of the LED

// Debounce method 2: Integrator/counter-based
const int MAX_COUNT = 5;      // Number of consistent readings needed
int stableCount = 0;          // Counter for consecutive stable readings
int integratedState = HIGH;   // Current integrated button state
int externalLedState = LOW;   // State for external LED

// Performance metrics
unsigned long bounceEvents = 0;      // Count of detected bounces
unsigned long lastPressTime = 0;     // Timestamp of last press
unsigned long responseTime = 0;      // Time from press to stable reading
unsigned long lastReportTime = 0;    // Last time we sent a report
const unsigned long REPORT_INTERVAL = 3000; // Status reporting interval (ms)

// Bounce simulation variables
bool simulateBounce = false;          // Enable/disable bounce simulation
bool buttonActive = false;            // Track if button is currently being pressed
unsigned long buttonPressStart = 0;   // When the button was first pressed
const int BOUNCE_DURATION = 50;       // How long bounce simulation lasts (ms)
int bouncePattern[] = {HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH}; // Bounce pattern
const int BOUNCE_COUNT = 7;           // Number of bounces to simulate
int currentBounce = 0;                // Current position in bounce pattern
unsigned long lastBounceTime = 0;     // Last time we changed bounce state
const int BOUNCE_INTERVAL = 5;        // Time between bounces (ms)

// Full code truncated for brevity - full version in src/phase1_setup/button_debouncing/src/main.cpp
```

## Results
The experiment successfully demonstrated both debouncing methods:

### Normal Button Operation
- Both LEDs toggled correctly on button press
- Minimal natural bounce detected with the buttons from the kit
- Both methods effectively debounced the input
- Counter-based method typically responded slightly faster but very unnoticeable to the human eye

### With Bounce Simulation
- Simulated bounces were clearly visible in serial monitor
- Multiple rapid state changes (7 in 50ms) were filtered out correctly
- Time-based method consistently responded in ~50ms after bounce completion
- Counter-based method responded after 5 consecutive stable readings
- Performance metrics showed 6-7 bounce events per press as expected

### Key Observations
- Without simulation, the tactile buttons showed no bounce due to debouncing and high quality button
- With simulation, the difference between raw and debounced signals was clear
- Counter-based method was more responsive with clean signals
- Time-based method provided more consistent response timing
- Serial monitor at 115200 baud rate provided sufficient resolution to observe bounces

## Learning Outcomes
- Understood the physical nature of button bounce as mechanical contact rebound
- Implemented and compared two common software debouncing techniques
- Learned how to simulate hardware effects in software for testing
- Gained experience with timing-critical code and event detection
- Developed better understanding of different serial baud rates
- Recognized the importance of debouncing for reliable input systems

## Optional Next Steps to gain advanced knowledge in debouncing
1. Implement a multi-button input system using lessons learned
2. Create a hardware debouncing circuit using capacitors for comparison
3. Develop an adaptive debouncing algorithm that self-calibrates
4. Apply debouncing principles to other input types (encoders, etc.)
5. Implement a hybrid approach that combines benefits of both methods

## References
1. Arduino Button State Change Detection - https://www.arduino.cc/en/Tutorial/BuiltInExamples/StateChangeDetection
2. Debouncing Algorithms - https://www.embedded.com/electronics-blogs/break-points/4024981/My-favorite-software-debouncers
3. Elegoo Super Starter Kit for UNO - Component documentation
4. PlatformIO documentation - https://docs.platformio.org/
5. Claude API - https://console.anthropic.com
