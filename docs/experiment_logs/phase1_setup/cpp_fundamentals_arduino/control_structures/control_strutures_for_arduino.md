# C++ Control Structures for Arduino

Let's continue with the next part of Hour 1: Control structures with Arduino-specific examples. You'll find many of these structures familiar from your experience with other programming languages, but with some Arduino-specific considerations.

## If-Else Statements

The basic structure is similar to other languages you know, but there are some Arduino-specific idioms:

```cpp
// Basic if-else statement with Arduino pin reading
if (digitalRead(buttonPin) == LOW) {  
  digitalWrite(ledPin, HIGH);
} else {
  digitalWrite(ledPin, LOW);
}
```

One important note: With `INPUT_PULLUP` pins (common for buttons), `LOW` means the button is pressed, which might seem counter-intuitive at first. This is because the internal pull-up resistor pulls the pin HIGH when the button is not pressed.

You can also use compound conditions:

```cpp
// Check if temperature is in safe range
if (temperature > 0 && temperature < 85) {
  // Temperature is safe, continue operation
  digitalWrite(statusLedPin, HIGH);
} else if (temperature <= 0) {
  // Too cold, activate heater
  digitalWrite(heaterPin, HIGH);
  digitalWrite(statusLedPin, LOW);
} else {
  // Too hot, activate cooling
  digitalWrite(coolingPin, HIGH);
  digitalWrite(statusLedPin, LOW);
}
```

## For Loops

For loops are useful for repeated operations, like controlling multiple LEDs or reading multiple sensors:

```cpp
// Blink LED 5 times with increasing speed
for (int i = 0; i < 5; i++) {
  digitalWrite(ledPin, HIGH);
  delay(500 - i * 100);  // Decreasing delay: 500, 400, 300, 200, 100 ms
  digitalWrite(ledPin, LOW);
  delay(500 - i * 100);
}

// Read all analog inputs
const int NUM_SENSORS = 6;
int sensorValues[NUM_SENSORS];

for (int i = 0; i < NUM_SENSORS; i++) {
  sensorValues[i] = analogRead(A0 + i);  // Read A0, A1, A2, etc.
}
```

A neat thing about Arduino is that the analog pins can be referenced sequentially like this.

## While and Do-While Loops

While loops are perfect for waiting for certain conditions:

```cpp
// Wait for button press before continuing
while (digitalRead(buttonPin) == HIGH) {
  // Button not pressed yet (HIGH due to pull-up resistor)
  digitalWrite(ledPin, HIGH);  // Blink LED while waiting
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(100);
}

// Button was pressed, continue with program
```

Do-while loops ensure the body executes at least once:

```cpp
int calibrationValue;

do {
  // Read sensor for calibration
  calibrationValue = analogRead(sensorPin);
  
  // Display value on serial
  Serial.print("Calibrating: ");
  Serial.println(calibrationValue);
  
  delay(500);  // Wait half a second between readings
  
} while (calibrationValue < 100);  // Continue until we get a good value

// Now calibrated
Serial.println("Calibration complete!");
```

## Switch Statements

Switch statements are very useful for state machines, which you'll use a lot in Arduino programming:

```cpp
// Define possible system states
enum SystemState {
  STATE_IDLE,
  STATE_RUNNING,
  STATE_ERROR,
  STATE_CALIBRATION
};

// Current state variable
SystemState currentState = STATE_IDLE;

// Handle different states
switch (currentState) {
  case STATE_IDLE:
    // LEDs show idle pattern
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, LOW);
    break;
    
  case STATE_RUNNING:
    // LEDs show running pattern
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, HIGH);
    break;
    
  case STATE_ERROR:
    // LEDs show error pattern (blink red)
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, !digitalRead(redLed));  // Toggle red LED
    digitalWrite(blueLed, LOW);
    break;
    
  case STATE_CALIBRATION:
    // LEDs show calibration pattern
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, HIGH);
    break;
    
  default:
    // Unknown state, reset to idle
    currentState = STATE_IDLE;
    break;
}
```

The `enum` type creates a set of named integer constants, making your code more readable than using raw numbers for states.

## Arduino-Specific: Non-Blocking Patterns

One crucial concept in Arduino programming is **avoiding blocking code**. This is a major difference from scripting languages:

```cpp
// BAD: Blocking approach
void loop() {
  digitalWrite(ledPin, HIGH);
  delay(1000);  // Program stops here for 1 second!
  digitalWrite(ledPin, LOW);
  delay(1000);  // Stops here too!
  
  // Other critical code can't run during delays
  checkButton();  // This function might miss button presses
}

// GOOD: Non-blocking approach using millis()
unsigned long previousMillis = 0;
const long interval = 1000;
bool ledState = LOW;

void loop() {
  unsigned long currentMillis = millis();
  
  // Check if it's time to toggle the LED
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    // Toggle LED
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
  
  // This runs continuously without being blocked
  checkButton();  // Can check buttons constantly
}
```

The non-blocking approach is essential for responsive systems that need to handle multiple tasks simultaneously, like reading sensors while controlling motors or LEDs.

## Real-World Example: Button State Machine

Let's combine these control structures into a practical example - a button-controlled state machine for your Arduino:

```cpp
#include <Arduino.h>

// Pin definitions
const byte BUTTON_PIN = 2;
const byte RED_LED = 9;
const byte GREEN_LED = 10;
const byte BLUE_LED = 11;

// System states
enum SystemState {
  STATE_OFF,
  STATE_LOW,
  STATE_MEDIUM,
  STATE_HIGH,
  NUM_STATES  // Automatically equals the number of states
};

// Current state tracking
SystemState currentState = STATE_OFF;
byte buttonPresses = 0;

// Timing variables for non-blocking operation
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
int lastButtonState = HIGH;
int buttonState = HIGH;

// LED brightness levels
const byte brightness[] = {0, 64, 150, 255};  // For OFF, LOW, MED, HIGH

void setup() {
  // Configure pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  
  // Initial LED state
  updateLeds();
  
  Serial.begin(9600);
  Serial.println(F("Button State Machine Example"));
  Serial.println(F("Press button to cycle through states"));
}

void loop() {
  // Read button with debouncing
  int reading = digitalRead(BUTTON_PIN);
  
  // If button state changed, reset debounce timer
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  // If debounce delay passed, check if button state is stable
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed and is now stable
    if (reading != buttonState) {
      buttonState = reading;
      
      // If button is pressed (LOW with pull-up resistor)
      if (buttonState == LOW) {
        // Cycle to next state
        buttonPresses++;
        currentState = (SystemState)(buttonPresses % NUM_STATES);
        
        // Update LEDs based on new state
        updateLeds();
        
        // Print the current state
        Serial.print(F("Changed to state: "));
        
        switch (currentState) {
          case STATE_OFF:
            Serial.println(F("OFF"));
            break;
          case STATE_LOW:
            Serial.println(F("LOW"));
            break;
          case STATE_MEDIUM:
            Serial.println(F("MEDIUM"));
            break;
          case STATE_HIGH:
            Serial.println(F("HIGH"));
            break;
        }
      }
    }
  }
  
  // Save current reading for next comparison
  lastButtonState = reading;
}

// Function to update LED outputs based on current state
void updateLeds() {
  // Update LED brightness based on current state
  analogWrite(RED_LED, brightness[currentState]);
  analogWrite(GREEN_LED, brightness[currentState]);
  analogWrite(BLUE_LED, brightness[currentState]);
}
```

In this example, we:
1. Define a state machine with four brightness states
2. Use enums to make the states readable and maintainable
3. Implement non-blocking button debouncing
4. Use `switch` to handle different states
5. Use the modulo operator (`%`) for elegant state cycling

The modulo operation is particularly elegant here. Each button press increments `buttonPresses`, and `buttonPresses % NUM_STATES` wraps around to cycle through all the states.

## Break and Continue

Two more control flow statements you should know about:

```cpp
// Break example - exit a loop early
for (int i = 0; i < 100; i++) {
  int sensorValue = analogRead(A0);
  
  // If sensor detects a problem, exit loop immediately
  if (sensorValue > 900) {
    Serial.println(F("High value detected! Stopping."));
    break;  // Exit the for loop immediately
  }
  
  // Normal processing continues if no break
  Serial.println(sensorValue);
  delay(100);
}

// Continue example - skip the rest of this iteration
for (int i = 0; i < 10; i++) {
  // Skip even numbers
  if (i % 2 == 0) {
    continue;  // Skip to next iteration
  }
  
  // This code only runs for odd values of i
  Serial.print(F("Processing odd number: "));
  Serial.println(i);
}
```