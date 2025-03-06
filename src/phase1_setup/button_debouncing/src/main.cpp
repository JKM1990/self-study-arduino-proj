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

void setup() {
  // Set up serial port
  Serial.begin(115200);
  Serial.println("=== Enhanced Button Debounce Demonstration with Bounce Simulation ===");
  
  // Configure I/O pins
  pinMode(buttonPin, INPUT_PULLUP);  // Button with pull-up resistor
  pinMode(ledPin, OUTPUT);           // Built-in LED 
  pinMode(externalLedPin, OUTPUT);   // External LED
  
  // Initialize states with current readings
  buttonState = digitalRead(buttonPin);
  integratedState = buttonState;
  
  // LED test sequence to verify hardware
  digitalWrite(ledPin, HIGH);
  digitalWrite(externalLedPin, HIGH);
  delay(300);
  digitalWrite(ledPin, LOW);
  digitalWrite(externalLedPin, LOW);
  delay(300);
  digitalWrite(ledPin, HIGH);
  digitalWrite(externalLedPin, HIGH);
  delay(300);
  digitalWrite(ledPin, LOW);
  digitalWrite(externalLedPin, LOW);
  
  // Set initial states
  digitalWrite(ledPin, ledState);
  digitalWrite(externalLedPin, externalLedState);
  
  Serial.println("\nMethod 1: Time-based debouncing (built-in LED)");
  Serial.println("Method 2: Counter-based debouncing (external LED)");
  Serial.println("\nPress and hold button for >1 second to enable bounce simulation");
  Serial.println("Setup complete. Press button to toggle LEDs.\n");
  
  lastReportTime = millis();
}

void printPerformanceMetrics() {
  Serial.println("\n--- Performance Metrics ---");
  Serial.print("Detected bounce events: ");
  Serial.println(bounceEvents);
  Serial.print("Time-based debounce response: ");
  Serial.print(responseTime);
  Serial.println(" ms");
  Serial.print("Counter-based stable readings required: ");
  Serial.println(MAX_COUNT);
  Serial.print("Bounce simulation: ");
  Serial.println(simulateBounce ? "ENABLED" : "DISABLED");
  Serial.println("----------------------------\n");
  
  // Reset bounce counter after reporting
  bounceEvents = 0;
}

// Get button reading, either real or simulated
int getButtonReading() {
  int reading;
  
  if (simulateBounce && buttonActive) {
    // We're in an active bounce simulation
    unsigned long currentTime = millis();
    
    // Check if we're still within bounce duration
    if (currentTime - buttonPressStart < BOUNCE_DURATION) {
      // Time to change bounce state?
      if (currentTime - lastBounceTime >= BOUNCE_INTERVAL) {
        currentBounce = (currentBounce + 1) % BOUNCE_COUNT;
        lastBounceTime = currentTime;
        // Log the simulated bounce
        Serial.print("Simulated bounce: ");
        Serial.println(bouncePattern[currentBounce] == HIGH ? "RELEASED" : "PRESSED");
      }
      reading = bouncePattern[currentBounce];
    } else {
      // Bounce simulation finished, settle to final state (pressed)
      reading = LOW;
      buttonActive = false;
      Serial.println("Bounce simulation complete, button settled");
    }
  } else {
    // Normal reading
    reading = digitalRead(buttonPin);
    
    // Check for long press to enable/disable bounce simulation
    if (reading == LOW) {
      if (!buttonActive) {
        // Button just pressed
        buttonActive = true;
        buttonPressStart = millis();
        currentBounce = 0;
      } else {
        // Check for long press (1 second)
        if ((millis() - buttonPressStart > 1000) && reading == LOW) {
          simulateBounce = !simulateBounce;
          Serial.print("Bounce simulation ");
          Serial.println(simulateBounce ? "ENABLED" : "DISABLED");
          // Wait for button release to avoid immediate simulation
          while (digitalRead(buttonPin) == LOW) {
            delay(10);
          }
          buttonActive = false;
          return HIGH; // Return released state after toggle
        }
      }
    } else {
      // Button released
      buttonActive = false;
    }
  }
  
  return reading;
}

void loop() {
  // Get button reading (real or simulated)
  int reading = getButtonReading();
  unsigned long currentTime = millis();
  
  // PART 1: TIME-BASED DEBOUNCING (traditional method)
  // If reading changed from last time, reset the debounce timer
  if (reading != lastButtonState) {
    // Count bounces (transitions between HIGH and LOW)
    if (lastButtonState != buttonState) { // Only count as bounce if unstable
      bounceEvents++;
    }
    
    // If this is the first detection of a press, note the time
    if (buttonState == HIGH && reading == LOW) {
      lastPressTime = currentTime;
    }
    
    // Reset debounce timer
    lastDebounceTime = currentTime;
    
    // Log the raw state change
    Serial.print("Raw: ");
    Serial.println(reading == HIGH ? "RELEASED" : "PRESSED");
  }
  
  // Check if debounce time has passed
  if ((currentTime - lastDebounceTime) > debounceDelay) {
    // If the button state has changed and is stable:
    if (reading != buttonState) {
      buttonState = reading;
      
      // Measure response time for presses
      if (buttonState == LOW) {
        responseTime = currentTime - lastPressTime;
        
        // Report debounced state change
        Serial.print("Time-debounced: PRESSED (response: ");
        Serial.print(responseTime);
        Serial.println("ms)");
        
        // Toggle LED state
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
        Serial.print("Built-in LED: ");
        Serial.println(ledState == HIGH ? "ON" : "OFF");
      } else {
        Serial.println("Time-debounced: RELEASED");
      }
    }
  }
  
  // PART 2: COUNTER-BASED DEBOUNCING (integrator method)
  // Check if current reading matches the integrated state
  if (reading == integratedState) {
    // Reading is stable and matches our current state
    stableCount = 0; // Reset counter as no change is happening
  } else {
    // Reading differs from current stable state
    stableCount++; // Increment counter for this potential new state
    
    // If we've had enough consistent readings, change the integrated state
    if (stableCount >= MAX_COUNT) {
      integratedState = reading; // Accept the new state
      stableCount = 0; // Reset counter
      
      // Handle the debounced state change
      if (integratedState == LOW) { // Button is pressed (LOW due to pull-up)
        Serial.println("Counter-debounced: PRESSED");
        
        // Toggle external LED
        externalLedState = !externalLedState;
        digitalWrite(externalLedPin, externalLedState);
        Serial.print("External LED: ");
        Serial.println(externalLedState == HIGH ? "ON" : "OFF");
      } else {
        Serial.println("Counter-debounced: RELEASED");
      }
    }
  }
  
  // Periodic performance metrics reporting
  if (currentTime - lastReportTime >= REPORT_INTERVAL) {
    printPerformanceMetrics();
    lastReportTime = currentTime;
  }
  
  // Save current reading for next comparison
  lastButtonState = reading;
  
  // Small delay to avoid overwhelming the serial monitor while still 
  // being responsive enough to catch button bounces
  delay(1);
}