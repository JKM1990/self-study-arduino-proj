#include "LedPatterns.h"

/**
 * LedPatterns class implementation
 * 
 * Contains all the code that makes the patterns work
 */

// Constructor - initializes the class with LED pins
LedPatterns::LedPatterns(byte* pins, byte count) {
  ledPins = pins;
  ledCount = count;
  currentPattern = PATTERN_BLINK;
  patternStep = 0;
  lastUpdateTime = 0;
  patternDuration = 5000;  // 5 seconds default
  stepDuration = 100;      // 100ms default step time
}

// Initialize pins and set up initial state
void LedPatterns::begin() {
  // Initialize all LED pins as outputs
  for (byte i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  // Initialize to known state
  setAllLeds(LOW);
}

// Main update function - call this frequently
void LedPatterns::update() {
  unsigned long currentTime = millis();
  
  // Update the pattern state if enough time has passed
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
      default:
        // Invalid state - reset to blink
        currentPattern = PATTERN_BLINK;
        break;
    }
    
    // Increment pattern step for next update
    patternStep++;
  }
}

// Pattern implementations

// Simple blink pattern - all LEDs on/off together
void LedPatterns::runBlinkPattern() {
  // Toggle between all on and all off every step
  if (patternStep % 2 == 0) {
    setAllLeds(HIGH);
  } else {
    setAllLeds(LOW);
  }
}

// Chase pattern - one LED at a time, back and forth
void LedPatterns::runChasePattern() {
  // Calculate which LED should be on
  // The pattern reverses direction when it reaches the end
  byte pos = patternStep % (2 * ledCount - 2);
  if (pos >= ledCount) {
    pos = 2 * ledCount - 2 - pos; // Reverse direction
  }
  
  // Turn all LEDs off
  setAllLeds(LOW);
  
  // Turn on just the active LED
  digitalWrite(ledPins[pos], HIGH);
}

// Fade pattern - smoothly fade LEDs using sine wave
void LedPatterns::runFadePattern() {
  // Base angle from current step (0-255)
  byte angle = patternStep % 256;
  
  // Update each LED with a different phase offset
  for (byte i = 0; i < ledCount; i++) {
    // Each LED gets a different phase offset
    byte ledAngle = (angle + (i * (255 / ledCount))) % 256;
    
    // Convert angle to radians (0-2π)
    float radians = (ledAngle / 255.0) * 2 * PI;
    
    // Calculate brightness using sine function (0-255)
    // sin() returns -1 to 1, so we add 1 and multiply by 127
    byte brightness = (sin(radians) + 1) * 127;
    
    // Set LED brightness using PWM
    analogWrite(ledPins[i], brightness);
  }
}

// Random pattern - random LED states
void LedPatterns::runRandomPattern() {
  // Only change pattern every few steps for visibility
  if (patternStep % 4 == 0) {
    // Set each LED to a random state
    for (byte i = 0; i < ledCount; i++) {
      // 50% chance of on/off for each LED
      byte state = random(2);
      digitalWrite(ledPins[i], state);
    }
  }
}

// Utility to set all LEDs to same state
void LedPatterns::setAllLeds(byte value) {
  for (byte i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], value);
  }
}

// Public methods for pattern control

// Set current pattern
void LedPatterns::setPattern(PatternState pattern) {
  if (pattern < PATTERN_COUNT) {
    currentPattern = pattern;
    patternStep = 0;  // Reset step for new pattern
  }
}

// Get current pattern
PatternState LedPatterns::getCurrentPattern() {
  return currentPattern;
}

// Get current pattern name as string
const char* LedPatterns::getPatternName() {
  switch (currentPattern) {
    case PATTERN_BLINK:
      return "Blink";
    case PATTERN_CHASE:
      return "Chase";
    case PATTERN_FADE:
      return "Fade";
    case PATTERN_RANDOM:
      return "Random";
    default:
      return "Unknown";
  }
}

// Set duration between pattern changes
void LedPatterns::setPatternDuration(unsigned long duration) {
  patternDuration = duration;
}

// Set duration between animation steps
void LedPatterns::setStepDuration(unsigned long duration) {
  stepDuration = duration;
}
