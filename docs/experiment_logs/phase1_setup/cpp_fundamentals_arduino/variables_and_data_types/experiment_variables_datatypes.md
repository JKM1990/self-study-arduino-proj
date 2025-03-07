# Experiment 01: C++ Variables and Data Types

## Date
March 6, 2025

## Objective
Explore C++ variables, data types, and memory management on Arduino, with a focus on understanding the memory footprint of different data types and how to use them efficiently.

## Components Used
- Arduino Uno R3 board
- Breadboard
- 1 LED (connected to pin 13/built-in)
- 1 pushbutton
- 220Ω resistor
- Jumper wires

## Circuit Documentation
Simple circuit with:
- Button connected to pin 2 (using INPUT_PULLUP, no external resistor needed)
- LED connected to pin 13 (built-in LED)
- Connections:
  - Button pin 1 -> Arduino pin 2
  - Button pin 3 -> GND
  - Built-in LED on pin 13 used for this simple test

## Code
Located in src/phase1_setup/cpp_fudamentals_arduino/variables_datatypes_example/src/main.cpp

## Results
The experiment successfully demonstrated:

1. Memory usage reporting:
   - Initial free RAM was reported around 1850 bytes on the Arduino Uno
   - Using the F() macro successfully kept strings in flash memory
   
2. Data type usage:
   - Using appropriate smaller data types (byte instead of int for LED pin)
   - Using unsigned types for values that can't be negative
   - Using long types for time tracking with millis()
   
3. Button control:
   - Successfully toggled the LED on/off using the button
   - Simple debounce prevented multiple triggers
   
4. Performance tracking:
   - Console displayed the number of loop cycles executed per second
   - On average, achieved approximately 30,000-40,000 cycles per second with this code
   - Demonstrated the speed of the Arduino for simple operations

## Learning Outcomes
- Understood the memory constraints of Arduino (2KB RAM, 32KB flash)
- Learned about different C++ data types and their memory footprint:
  - byte (1 byte): 0-255, ideal for pin numbers and small values
  - int (2 bytes): -32,768 to 32,767, standard integer type
  - unsigned int (2 bytes): 0-65,535, good for larger positive-only values
  - long and unsigned long (4 bytes): needed for time tracking with millis()
  - bool (1 byte): true/false values
- Learned how to measure available RAM using the freeRam() function
- Understood the F() macro for storing strings in flash instead of RAM
- Implemented non-blocking timing using millis() for the status updates
- Used proper variable types to optimize memory usage

## Next Steps
1. Expand to work with more data types including arrays and floating point
2. Implement multiple LED outputs to visualize different variables
3. Add more complex conditional logic for a state machine
4. Optimize the code further to increase cycles per second
5. Explore using PROGMEM for storing larger constant data

## References
1. Arduino Reference for data types: https://www.arduino.cc/reference/en/
2. Free RAM measurement technique: https://playground.arduino.cc/Code/AvailableMemory/
3. F() macro documentation: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
