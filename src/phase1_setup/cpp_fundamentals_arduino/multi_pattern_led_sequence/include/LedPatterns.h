#ifndef LED_PATTERNS_H
#define LED_PATTERNS_H

#include <Arduino.h>

/**
 * LedPatterns - A class for controlling multiple LED pattern animations
 * 
 * This class demonstrates:
 * - Object-oriented programming in Arduino/C++
 * - Non-blocking pattern generation with millis()
 * - State machine implementation
 * - Memory-efficient code organization
 */

// Pattern state enum - defines all available patterns
enum PatternState {
  PATTERN_BLINK,    // All LEDs blink together
  PATTERN_CHASE,    // LEDs light up in sequence
  PATTERN_FADE,     // LEDs fade in and out using PWM
  PATTERN_RANDOM,   // Random LED patterns
  PATTERN_COUNT     // Total number of patterns (automatically updates)
};

class LedPatterns {
  private:
    // LED configuration
    byte* ledPins;      // Array of pin numbers
    byte ledCount;      // Number of LEDs
    
    // Pattern state
    PatternState currentPattern;     // Currently active pattern
    byte patternStep;                // Current step within pattern
    unsigned long lastUpdateTime;    // Last time pattern was updated
    unsigned long patternDuration;   // Time between automatic pattern changes
    unsigned long stepDuration;      // Time between steps in animation
    
    // Private methods for pattern implementations
    void runBlinkPattern();
    void runChasePattern();
    void runFadePattern();
    void runRandomPattern();
    void setAllLeds(byte value);
    
  public:
    // Constructor
    LedPatterns(byte* pins, byte count);
    
    // Public methods
    void begin();                 // Initialize pins
    void update();                // Update pattern (call this in loop)
    
    // Pattern control
    void setPattern(PatternState pattern);
    PatternState getCurrentPattern();
    const char* getPatternName();  // Get current pattern name as string
    
    // Timing control
    void setPatternDuration(unsigned long duration);
    void setStepDuration(unsigned long duration);
};

#endif
