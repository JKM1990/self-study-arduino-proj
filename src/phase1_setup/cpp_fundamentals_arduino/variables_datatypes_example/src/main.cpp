#include <Arduino.h>

// Pin definitions
const byte LED_PIN = 13;          // Using byte saves memory over int
const byte BUTTON_PIN = 2;

// System states
bool systemRunning = false;       // Boolean for system state
unsigned long startTime = 0;      // For tracking time since start

// Performance tracking
unsigned int cycleCount = 0;      // Counter for loop cycles
byte errorCode = 0;               // Error status code (0 = no error)

// Function to check available RAM
int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println(F("System initializing..."));  // Using F() to save RAM
  
  // Set pin modes
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Record start time
  startTime = millis();
  
  // Show memory usage for debugging
  Serial.print(F("Free RAM: "));
  Serial.print(freeRam());  // We'll implement this function
  Serial.println(F(" bytes"));
}

unsigned long lastSecondCheck = 0;

void loop() {
  // Track current time (rolls over after ~49 days)
  unsigned long currentTime = millis();
  
  // Read button (LOW when pressed with INPUT_PULLUP)
  if (digitalRead(BUTTON_PIN) == LOW) {
    systemRunning = !systemRunning;  // Toggle system state
    
    if (systemRunning) {
      Serial.println(F("System started"));
      digitalWrite(LED_PIN, HIGH);
    } else {
      Serial.println(F("System stopped"));
      digitalWrite(LED_PIN, LOW);
    }
    
    // Simple debounce
    delay(300);
  }
  
  // Every second, print status
  if (currentTime- lastSecondCheck >= 1000) {  // Check if we just crossed a second boundary
    lastSecondCheck = currentTime; // Update the timestamp
    Serial.print(F("Uptime: "));
    Serial.print(currentTime / 1000);  // Convert to seconds
    Serial.print(F(" seconds, cycles: "));
    Serial.println(cycleCount);
    
    // Reset cycle counter
    cycleCount = 0;
  }

  // Track performance 
  cycleCount++;
}