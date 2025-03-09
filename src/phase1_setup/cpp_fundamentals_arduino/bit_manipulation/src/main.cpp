#include <Arduino.h>

/*
 * LED Bit Manipulation Demo
 * 
 * This program demonstrates different bit manipulation techniques
 * to control 8 LEDs connected to pins 2-9. The program cycles
 * through various LED patterns using bitwise operations.
 * 
 * Button on pin 10 changes the active pattern.
 */

// Pin configurations
const byte FIRST_LED_PIN = 2;    // First LED is on pin 2
const byte NUM_LEDS = 8;         // Total of 8 LEDs (pins 2-9)
const byte BUTTON_PIN = 10;      // Button on pin 10

// Pattern definitions
enum PatternType {
  PATTERN_BINARY_COUNT,     // Binary counting pattern (0-255)
  PATTERN_SHIFT_LEFT,       // Left shifting pattern
  PATTERN_SHIFT_RIGHT,      // Right shifting pattern
  PATTERN_ALTERNATE,        // Alternating bits pattern
  PATTERN_RANDOM_BITS,      // Random bit pattern
  PATTERN_KNIGHT_RIDER,     // Back and forth pattern
  PATTERN_COUNT             // Total number of patterns
};

// Global variables
PatternType currentPattern = PATTERN_BINARY_COUNT;
byte ledState = 0;          // Current state of all LEDs as a byte
unsigned long lastUpdate = 0;
unsigned long updateInterval = 100; // Default 100ms between updates
unsigned long lastDebounceTime = 0;
byte lastButtonState = HIGH;
byte buttonState = HIGH;
unsigned int patternStep = 0;
byte randomByte = 0;       // For random pattern

// Function prototypes
void updateLeds();
void handleButton();
void runCurrentPattern();
void displayPatternName();

void setup() {
  // Initialize all LED pins as outputs
  for (byte i = 0; i < NUM_LEDS; i++) {
    pinMode(FIRST_LED_PIN + i, OUTPUT);
  }
  
  // Initialize button pin as input with pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Initialize Serial for debugging
  Serial.begin(9600);
  Serial.println(F("LED Bit Manipulation Demo"));
  Serial.println(F("Press button to change patterns"));
  
  // Display initial pattern
  displayPatternName();
}

void loop() {
  // Handle button presses (debounced)
  handleButton();
  
  // Update LED pattern at regular intervals
  unsigned long currentTime = millis();
  if (currentTime - lastUpdate >= updateInterval) {
    lastUpdate = currentTime;
    
    // Run the currently selected pattern
    runCurrentPattern();
    
    // Update LEDs based on the ledState variable
    updateLeds();
    
    // Increment pattern step counter
    patternStep++;
  }
}

// Update all LEDs based on ledState byte
void updateLeds() {
  // Method 1: Using individual digitalWrite calls
  /*
  for (byte i = 0; i < NUM_LEDS; i++) {
    // Check if the bit at position i is set
    bool bitValue = (ledState >> i) & 1;
    digitalWrite(FIRST_LED_PIN + i, bitValue);
  }
  */
  
  // Method 2: Using direct port manipulation (much faster)
  // For pins 2-7 (PORTD)
  DDRD |= 0b11111100;  // Set pins 2-7 as outputs (bits 2-7)
  PORTD = (PORTD & 0b00000011) | ((ledState << 2) & 0b11111100);
  
  // For pins 8-9 (PORTB)
  DDRB |= 0b00000011;  // Set pins 8-9 as outputs (bits 0-1)
  PORTB = (PORTB & 0b11111100) | ((ledState >> 6) & 0b00000011);
}

// Handle button press with debouncing
void handleButton() {
  // Read the button state (LOW when pressed with pull-up)
  byte reading = digitalRead(BUTTON_PIN);
  
  // If the button state changed, reset debounce timer
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  // If debounce delay has passed, check if button state is stable
  if ((millis() - lastDebounceTime) > 50) {
    // If the button state has changed and is now stable
    if (reading != buttonState) {
      buttonState = reading;
      
      // If button is pressed (LOW with pull-up resistor)
      if (buttonState == LOW) {
        // Switch to next pattern
        currentPattern = (PatternType)((currentPattern + 1) % PATTERN_COUNT);
        
        // Reset pattern step and ledState
        patternStep = 0;
        ledState = 0;
        
        // Display the name of the new pattern
        displayPatternName();
      }
    }
  }
  
  // Save the current reading for the next comparison
  lastButtonState = reading;
}

// Run the currently selected pattern
void runCurrentPattern() {
  switch (currentPattern) {
    case PATTERN_BINARY_COUNT:
      // Simple binary counter (0-255)
      ledState = patternStep & 0xFF; // Wrap around at 255
      break;
      
    case PATTERN_SHIFT_LEFT:
      // Left shift pattern (1 bit moving left, wrapping around)
      if (patternStep % NUM_LEDS == 0) {
        ledState = 1; // Start with just the rightmost bit
      } else {
        // Shift left by 1 bit
        ledState = (ledState << 1) | (ledState >> (NUM_LEDS - 1)); // Rotating left shift
      }
      break;
      
    case PATTERN_SHIFT_RIGHT:
      // Right shift pattern (1 bit moving right, wrapping around)
      if (patternStep % NUM_LEDS == 0) {
        ledState = 0x80; // Start with just the leftmost bit
      } else {
        // Shift right by 1 bit
        ledState = (ledState >> 1) | (ledState << (NUM_LEDS - 1)); // Rotating right shift
      }
      break;
      
    case PATTERN_ALTERNATE:
      // Alternating bits pattern (toggle between 01010101 and 10101010)
      if (patternStep % 2 == 0) {
        ledState = 0x55; // 01010101 in binary
      } else {
        ledState = 0xAA; // 10101010 in binary
      }
      break;
      
    case PATTERN_RANDOM_BITS:
      // Generate new random pattern every 8 steps
      if (patternStep % 8 == 0) {
        // Generate a new random byte
        randomByte = random(256);
      }
      
      // Use a different mask based on step to create interesting effects
      byte mask = (1 << (patternStep % 8)) - 1;
      ledState = randomByte & mask;
      break;
      
    case PATTERN_KNIGHT_RIDER:
      // Knight Rider/KITT pattern (light moves back and forth)
      byte pos = patternStep % (2 * NUM_LEDS - 2);
      if (pos >= NUM_LEDS) {
        pos = 2 * NUM_LEDS - 2 - pos; // Reverse direction
      }
      ledState = 1 << pos; // Set only the bit at position 'pos'
      break;
  }
}

// Display the name of the current pattern
void displayPatternName() {
  Serial.print(F("Pattern: "));
  
  switch (currentPattern) {
    case PATTERN_BINARY_COUNT:
      Serial.println(F("Binary Counter"));
      updateInterval = 100;
      break;
    case PATTERN_SHIFT_LEFT:
      Serial.println(F("Shift Left"));
      updateInterval = 150;
      break;
    case PATTERN_SHIFT_RIGHT:
      Serial.println(F("Shift Right"));
      updateInterval = 150;
      break;
    case PATTERN_ALTERNATE:
      Serial.println(F("Alternating Bits"));
      updateInterval = 300;
      break;
    case PATTERN_RANDOM_BITS:
      Serial.println(F("Random Bits"));
      updateInterval = 80;
      break;
    case PATTERN_KNIGHT_RIDER:
      Serial.println(F("Knight Rider"));
      updateInterval = 100;
      break;
  }
}
