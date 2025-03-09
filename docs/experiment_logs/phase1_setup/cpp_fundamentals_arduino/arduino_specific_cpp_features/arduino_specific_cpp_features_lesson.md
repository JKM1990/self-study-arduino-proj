# Arduino-Specific C++ Features

Let's dive into the more Arduino-specific C++ features, starting with pointers and references.

## Pointers and References

Pointers are one of the most powerful but potentially confusing features of C++. For Arduino programming, understanding the basics of pointers will help you write more efficient code.

### What Are Pointers?

A pointer is a variable that stores a memory address. Think of memory as a huge array of numbered storage boxes - a pointer simply contains the number (address) of one of these boxes.

```cpp
int temperature = 22;      // A regular variable storing the value 22
int* tempPtr = &temperature;  // A pointer storing the memory address of temperature
                           // The & operator gets the address of a variable
```

In this example, `tempPtr` doesn't contain 22; it contains the memory location where 22 is stored.

### Why Are Pointers Useful?

1. **Pass-by-reference**: Allows functions to modify the original variables
2. **Working with arrays**: Arrays are actually pointers under the hood
3. **Memory efficiency**: Share data without making copies
4. **Dynamic memory**: Create and destroy variables as needed (though this is less common on Arduino)

### Dereferencing Pointers

To access the value stored at the address in a pointer, you use the dereference operator `*`:

```cpp
int temperature = 22;
int* tempPtr = &temperature;

Serial.println(temperature);  // Prints 22
Serial.println(*tempPtr);     // Also prints 22 - the * gets the value at the address

*tempPtr = 25;                // Changes the value at the address
Serial.println(temperature);  // Now prints 25
```

### Practical Example: Modifying Variables Through Functions

One of the most common uses of pointers in Arduino programming is to allow functions to modify variables:

```cpp
// Without pointers (pass by value):
void addFive(int value) {
  value = value + 5;  // Only modifies the local copy
}

// With pointers (pass by reference):
void addFiveWithPointer(int* valuePtr) {
  *valuePtr = *valuePtr + 5;  // Modifies the original variable
}

void setup() {
  Serial.begin(9600);
  
  int number = 10;
  
  addFive(number);
  Serial.print("After addFive: ");
  Serial.println(number);  // Still 10! The function didn't change the original
  
  addFiveWithPointer(&number);
  Serial.print("After addFiveWithPointer: ");
  Serial.println(number);  // Now 15, because the function modified the original
}
```

### Arrays and Pointers

In C++, arrays and pointers are closely related. When you declare an array, its name effectively becomes a pointer to its first element:

```cpp
int sensorValues[3] = {345, 567, 789};
int* firstValuePtr = sensorValues;  // No & needed - array name is already a pointer

Serial.println(*firstValuePtr);    // Prints 345 (first element)
Serial.println(*(firstValuePtr+1)); // Prints 567 (second element)
Serial.println(*(firstValuePtr+2)); // Prints 789 (third element)
```

This relationship makes it easy to pass arrays to functions:

```cpp
// Function that calculates average of an array
float calculateAverage(int* values, int size) {
  long sum = 0;
  for(int i = 0; i < size; i++) {
    sum += values[i];  // values[i] is the same as *(values+i)
  }
  return (float)sum / size;
}

// Using the function
int readings[] = {102, 96, 105, 98};
float average = calculateAverage(readings, 4);
```

### Real-World Application: Sensor Reading System

Here's a more practical example that uses pointers to build a reusable sensor reading system:

```cpp
#include <Arduino.h>

// Struct to hold sensor configuration
struct SensorConfig {
  byte pin;             // Analog pin number
  int minValue;         // Minimum expected value
  int maxValue;         // Maximum expected value
  float calibration;    // Calibration factor
};

// Function to read and process multiple sensors
void readSensors(SensorConfig* configs, int numSensors, int* results) {
  for (int i = 0; i < numSensors; i++) {
    // Read raw value
    int rawValue = analogRead(configs[i].pin);
    
    // Apply calibration and mapping
    float calibratedValue = rawValue * configs[i].calibration;
    int mappedValue = map(calibratedValue, configs[i].minValue, 
                         configs[i].maxValue, 0, 100);
    
    // Store processed result
    results[i] = constrain(mappedValue, 0, 100);
  }
}

void setup() {
  Serial.begin(9600);
  
  // Configure three sensors
  SensorConfig sensors[3] = {
    {A0, 0, 1023, 1.0},   // Temperature sensor
    {A1, 100, 900, 1.2},  // Light sensor with calibration
    {A2, 200, 800, 0.8}   // Humidity sensor with different calibration
  };
  
  // Array to hold results
  int readings[3];
  
  // Read all sensors
  readSensors(sensors, 3, readings);
  
  // Display results
  Serial.println("Sensor readings (0-100 scale):");
  for (int i = 0; i < 3; i++) {
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(readings[i]);
  }
}

void loop() {
  // Just a demonstration in setup()
}
```

## Memory Management on Arduino

Arduino has three types of memory, each with different characteristics:

### 1. Flash Memory (Program Memory)

- Size: 32KB on Arduino Uno
- Used for: Storing your compiled program and constant data
- Characteristics: Non-volatile (persists when power is off), read-only during operation

### 2. SRAM (Static RAM)

- Size: 2KB on Arduino Uno
- Used for: Variables, call stack, heap (dynamic memory)
- Characteristics: Volatile (lost when power is off), read-write, very limited

### 3. EEPROM

- Size: 1KB on Arduino Uno
- Used for: Long-term data storage that needs to persist between power cycles
- Characteristics: Non-volatile, read-write, but limited write cycles (100,000)

### PROGMEM: Storing Data in Flash

One of the most important memory techniques in Arduino programming is using the `PROGMEM` keyword to store constants in flash memory instead of SRAM:

```cpp
#include <avr/pgmspace.h>

// Without PROGMEM - uses 27 bytes of SRAM
const char message[] = "Sensor reading complete";

// With PROGMEM - uses 27 bytes of flash, not SRAM
const char message2[] PROGMEM = "Sensor reading complete";

// Large lookup table stored in flash instead of SRAM
const PROGMEM int sineTable[360] = {
  0, 17, 35, 52, 70, 87, 105, 122, 139, 156, 
  174, 191, 208, 225, 242, 259, 276, 292, 309, 326, 
  // ... (more values)
};

void setup() {
  Serial.begin(9600);
  
  // Reading from PROGMEM requires special functions
  char buffer[30];
  strcpy_P(buffer, message2);  // Copy from PROGMEM to SRAM
  
  Serial.println(buffer);
  
  // Reading a value from the PROGMEM table
  int sinValue = pgm_read_word_near(sineTable + 90);
  Serial.print("Sine of 90 degrees: ");
  Serial.println(sinValue);
}
```

### The F() Macro for Strings

For strings sent to `Serial.print()` or similar functions, Arduino provides the convenient `F()` macro:

```cpp
// Bad: Uses SRAM
Serial.println("This is a long message that uses up valuable SRAM");

// Good: Uses flash memory instead
Serial.println(F("This is a long message stored in flash memory"));
```

This is one of the easiest and most effective ways to save SRAM.

### Manual Memory Management

Unlike modern languages with garbage collection, C++ requires manual memory management if you use dynamic memory:

```cpp
// Allocate memory dynamically
int* data = new int[50];  // Allocates 100 bytes on the heap

// Use the memory
for (int i = 0; i < 50; i++) {
  data[i] = i * 2;
}

// IMPORTANT: Free the memory when done
delete[] data;
```

However, dynamic memory allocation is generally discouraged on Arduino due to the limited SRAM and potential for fragmentation. It's better to use fixed-size arrays where possible.

### Stack vs Heap

Arduino's memory is divided into:

- **Stack**: Used for function calls, local variables, and control flow
- **Heap**: Used for dynamically allocated memory (with `new` and `delete`)

If your program uses too much stack (deep function calls, large local variables), or too much heap (unfreed allocations), you might encounter a **stack overflow**. This can cause your Arduino to behave unpredictably or crash.

### Checking Available Memory

This handy function helps you monitor free memory:

```cpp
int freeMemory() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void setup() {
  Serial.begin(9600);
  
  Serial.print("Free memory: ");
  Serial.print(freeMemory());
  Serial.println(" bytes");
  
  // Use this throughout your program to track memory usage
}
```

## Bit Manipulation

Bit manipulation is crucial for Arduino programming, especially when working directly with hardware or optimizing memory usage.

### Binary Basics

In C++, you can write binary literals with the `0b` prefix:

```cpp
byte value = 0b00101010;  // 42 in decimal
```

The bits in a byte are numbered from 0 (rightmost, least significant) to 7 (leftmost, most significant).

### Bitwise Operators

C++ provides several operators for manipulating individual bits:

#### Bitwise AND (`&`)

Used to check if specific bits are set, or to clear bits:

```cpp
byte value = 0b10101010;  // 170 in decimal
byte mask  = 0b00001111;  // 15 in decimal

byte result = value & mask;  // 0b00001010 (10 in decimal)
```

Here, the `&` operator keeps only the bits that are 1 in both value and mask.

#### Bitwise OR (`|`)

Used to set specific bits:

```cpp
byte value = 0b10100000;  // 160 in decimal
byte mask  = 0b00001111;  // 15 in decimal

byte result = value | mask;  // 0b10101111 (175 in decimal)
```

The `|` operator sets bits to 1 if they are 1 in either value or mask.

#### Bitwise XOR (`^`)

Used to toggle bits:

```cpp
byte value = 0b10101010;  // 170 in decimal
byte mask  = 0b00001111;  // 15 in decimal

byte result = value ^ mask;  // 0b10100101 (165 in decimal)
```

The `^` operator toggles bits that are 1 in the mask (0→1, 1→0).

#### Bitwise NOT (`~`)

Inverts all bits:

```cpp
byte value = 0b10101010;  // 170 in decimal
byte result = ~value;      // 0b01010101 (85 in decimal)
```

#### Shift Operators (`<<` and `>>`)

Shift bits left or right:

```cpp
byte value = 0b00000001;  // 1 in decimal

byte shifted_left = value << 3;  // 0b00001000 (8 in decimal)
byte shifted_right = shifted_left >> 2;  // 0b00000010 (2 in decimal)
```

Left shifting by 1 doubles the value; right shifting by 1 halves it (for unsigned types).

### Practical Bit Manipulation Techniques

#### Reading a Specific Bit

```cpp
byte value = 0b10101010;  // 170 in decimal
byte bitNumber = 3;  // We want to check bit #3 (0-indexed from right)

// Method 1: Using bitwise AND with a mask
byte mask = (1 << bitNumber);  // 0b00001000
bool isBitSet = (value & mask) != 0;  // true if bit is 1

// Method 2: Shift and check least significant bit
bool isBitSet2 = ((value >> bitNumber) & 1) == 1;

// Both give the same result
```

#### Setting a Specific Bit

```cpp
byte value = 0b10100000;  // 160 in decimal
byte bitNumber = 2;  // We want to set bit #2 (0-indexed from right)

// Create a mask with only that bit set to 1
byte mask = (1 << bitNumber);  // 0b00000100

// Set the bit using OR
value |= mask;  // Now value is 0b10100100 (164)
```

#### Clearing a Specific Bit

```cpp
byte value = 0b10101010;  // 170 in decimal
byte bitNumber = 3;  // We want to clear bit #3 (0-indexed from right)

// Create a mask with that bit set to 0 and all others to 1
byte mask = ~(1 << bitNumber);  // 0b11110111

// Clear the bit using AND
value &= mask;  // Now value is 0b10100010 (162)
```

#### Toggling a Specific Bit

```cpp
byte value = 0b10101010;  // 170 in decimal
byte bitNumber = 1;  // We want to toggle bit #1 (0-indexed from right)

// Create a mask with only that bit set to 1
byte mask = (1 << bitNumber);  // 0b00000010

// Toggle the bit using XOR
value ^= mask;  // Now value is 0b10101000 (168)
```

### Direct Port Manipulation

For Arduino, one of the most powerful applications of bit manipulation is direct port manipulation, which is much faster than `digitalWrite()`:

```cpp
// Standard Arduino functions
pinMode(13, OUTPUT);
digitalWrite(13, HIGH);
digitalWrite(13, LOW);

// Equivalent direct port manipulation (much faster)
// For pin 13 on Arduino Uno (which is PORTB, bit 5)
DDRB |= 0b00100000;    // Set pin as output (same as pinMode(13, OUTPUT))
PORTB |= 0b00100000;   // Set pin HIGH
PORTB &= ~0b00100000;  // Set pin LOW
```

Direct port manipulation is 3-5x faster than `digitalWrite()`, which matters for timing-critical applications.

### Real-World Example: LED Control with Bit Manipulation

Here's a practical example using bit manipulation to control multiple LEDs efficiently:

```cpp
#include <Arduino.h>

// We'll control 8 LEDs connected to pins 2-9
// Instead of treating them individually, we'll treat them as a single byte
// where each bit corresponds to one LED

void setup() {
  // Set all pins 2-9 as outputs
  DDRD |= 0b11111100;  // Pins 2-7 are on PORTD
  DDRB |= 0b00000011;  // Pins 8-9 are on PORTB
  
  Serial.begin(9600);
  Serial.println(F("LED Bit Manipulation Demo"));
}

// Function to set the LED states using a single byte
void setLeds(byte pattern) {
  // Lower 6 bits go to PORTD bits 2-7
  PORTD = (PORTD & 0b00000011) | ((pattern << 2) & 0b11111100);
  
  // Upper 2 bits go to PORTB bits 0-1
  PORTB = (PORTB & 0b11111100) | (pattern >> 6);
}

void loop() {
  // Binary counter pattern
  for (byte i = 0; i < 255; i++) {
    setLeds(i);
    delay(100);
  }
  
  // Knight Rider/KITT pattern (bouncing light)
  byte pattern = 0b00000001;
  for (int i = 0; i < 14; i++) {
    if (i < 7) {
      // Shift left for first half
      setLeds(pattern);
      pattern = pattern << 1;
    } else {
      // Shift right for second half
      pattern = pattern >> 1;
      setLeds(pattern);
    }
    delay(100);
  }
  
  // Random pattern
  for (int i = 0; i < 20; i++) {
    setLeds(random(255));
    delay(100);
  }
}
```

This example shows how you can control 8 LEDs simultaneously with just a few operations, which is much more efficient than calling `digitalWrite()` 8 times.

## Summary of Hour 2: Arduino-Specific C++ Features

We've covered:

1. **Pointers and References**
   - What pointers are and how to use them
   - Passing by reference for modifying variables
   - Array-pointer relationship
   - Practical applications for Arduino

2. **Memory Management**
   - The three types of Arduino memory
   - Using PROGMEM and F() to save SRAM
   - Avoiding dynamic memory allocation
   - Checking available memory

3. **Bit Manipulation**
   - Bitwise operators (AND, OR, XOR, NOT, shifts)
   - Techniques for reading, setting, clearing, and toggling bits
   - Direct port manipulation for speed
   - Practical applications for LED control

These concepts form the foundation for more advanced Arduino programming techniques, especially when it comes to optimizing your code for the limited resources of the Arduino platform.