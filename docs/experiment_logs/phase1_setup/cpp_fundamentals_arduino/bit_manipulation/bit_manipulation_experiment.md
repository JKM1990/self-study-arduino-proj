# Experiment 4: LED Control with Bit Manipulation

## Date
March 9, 2025

## Objective
Implement and understand C++ bit manipulation techniques by creating an 8-LED control system that demonstrates bitwise operations, direct port manipulation, and efficient memory usage through various lighting patterns.

## Components Used
- Arduino Uno R3
- 8 LEDs (red, green, blue, yellow, white and additional colors)
- 8 220Ω resistors
- 1 pushbutton (tactile switch)
- 1 10kΩ resistor (for button pull-up)
- Jumper wires
- Breadboard

## Circuit Documentation
The circuit connects 8 LEDs to digital pins 2-9:
- Each LED is connected through a 220Ω current-limiting resistor
- LED anodes (+) connect to Arduino pins through resistors
- LED cathodes (-) connect to common ground
- Pushbutton connects pin 10 to ground when pressed
- 10kΩ pull-up resistor between pin 10 and 5V ensures stable HIGH state when button is not pressed

## Code
The code is stored in the project's repository at:
`src/phase1_setup/cpp_fundamentals_arduino/bit_manipulation/src/main.cpp`

Key code sections include:

```cpp
// Direct port manipulation (much faster than digitalWrite)
// For pins 2-7 (PORTD)
DDRD |= 0b11111100;  // Set pins 2-7 as outputs (bits 2-7)
PORTD = (PORTD & 0b00000011) | ((ledState << 2) & 0b11111100);

// For pins 8-9 (PORTB)
DDRB |= 0b00000011;  // Set pins 8-9 as outputs (bits 0-1)
PORTB = (PORTB & 0b11111100) | ((ledState >> 6) & 0b00000011);
```

```cpp
// Knight Rider/KITT pattern (light moves back and forth)
byte pos = patternStep % (2 * NUM_LEDS - 2);
if (pos >= NUM_LEDS) {
  pos = 2 * NUM_LEDS - 2 - pos; // Reverse direction
}
ledState = 1 << pos; // Set only the bit at position 'pos'
```

## Results
The experiment was completely successful. All six LED patterns functioned as intended:

1. **Binary Count**: LEDs displayed binary counting pattern from 0-255, clearly visualizing 8-bit binary representation.

2. **Shift Left**: A single illuminated LED rotated left around the array, demonstrating left bit shift operations with wraparound.

3. **Shift Right**: A single illuminated LED rotated right, showing right bit shift operations with wraparound.

4. **Alternating Bits**: LEDs alternated between 01010101 and 10101010 patterns, demonstrating binary literals and toggling.

5. **Random Bits**: Created interesting random patterns with progressive bit masking effects.

6. **Knight Rider**: Produced a smooth back-and-forth scanning effect that was particularly visually appealing.

The button successfully cycled through patterns with reliable debouncing. Direct port manipulation resulted in instantaneous LED updates with no visible delay or flicker.

## Learning Outcomes
- Successfully implemented bitwise operations (AND, OR, XOR, shifts) in a practical application
- Understood and applied direct port manipulation for significantly faster I/O operations
- Learned to use a single byte variable to efficiently control multiple outputs
- Mastered bit shifting techniques for creating complex patterns
- Implemented bit masking to isolate and modify specific bits
- Gained practical understanding of binary, hexadecimal, and decimal representations
- Applied non-blocking code patterns for smooth LED animations
- Understood the Arduino's internal port architecture (PORTD, PORTB)
- Implemented enum type for clean pattern state management
- Used the modulo operator for elegant pattern cycling (particularly in Knight Rider pattern)

## Next Steps
1. Expand the project to include an additional 8-LED array for 16-bit operations
2. Implement PWM control with bit manipulation for LED brightness variation
3. Add a second button for bidirectional pattern navigation
4. Create more complex patterns using combined bit operations
5. Develop a binary data visualization tool using these techniques
6. Apply bit manipulation knowledge to optimize future Arduino projects
7. Investigate creating a binary clock using similar techniques

## References
1. Arduino-specific C++ features lesson from project documentation
2. Arduino Port Manipulation Reference: https://www.arduino.cc/en/Reference/PortManipulation
3. Bit Manipulation section in "Practical Arduino: Cool Projects for Open Source Hardware"
4. C++ Bitwise Operators Documentation: https://en.cppreference.com/w/cpp/language/operator_arithmetic
5. ELEGOO Uno R3 Starter Kit component specifications
