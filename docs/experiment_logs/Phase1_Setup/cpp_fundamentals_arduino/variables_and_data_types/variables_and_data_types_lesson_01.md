# C++ Basics for Arduino: Variables and Data Types

Let's begin with the fundamentals of C++ variables and data types as they apply specifically to Arduino programming.

## Static Typing in C++

Coming from languages like JavaScript, Python, PHP, and Java, you're already familiar with variables, but C++ has some important differences:

C++ uses **static typing**, which means you must declare the type of each variable when you create it, and that type cannot change during the program's execution. This is similar to Java but differs from JavaScript, Python, and PHP which use dynamic typing.

```cpp
// In C++, you must specify the data type
int motorSpeed = 255;
float temperature = 22.5;

// This won't work in C++:
motorSpeed = "fast"; // Error: can't assign string to int
```

This static typing helps catch errors at compile time rather than runtime, and it makes your code more efficient because the compiler knows exactly how much memory to allocate.

## Arduino Memory Constraints

One of the biggest differences when programming Arduino compared to web development is the extremely limited resources. Your Arduino Uno has:

- Only 2KB of RAM (that's 2,048 bytes, not megabytes!)
- 32KB of program memory (flash)
- 1KB of EEPROM

For comparison, even a simple webpage might use several megabytes of memory. This constraint makes memory management critical for Arduino projects.

## C++ Data Types on Arduino

Let's explore the most common data types you'll use and their memory footprint:

```cpp
// Integer types
byte sensorValue = 127;        // 8-bit unsigned (0 to 255) - uses 1 byte
int position = 1500;           // 16-bit signed (-32,768 to 32,767) - uses 2 bytes
unsigned int steps = 45000;    // 16-bit unsigned (0 to 65,535) - uses 2 bytes
long distance = 1000000;       // 32-bit signed (-2 billion to +2 billion) - uses 4 bytes
unsigned long runTime = 3600000; // 32-bit unsigned (0 to 4+ billion) - uses 4 bytes

// Floating-point types
float voltage = 3.3;           // 32-bit floating point - uses 4 bytes

// Character and Boolean types
char direction = 'N';          // Single character - uses 1 byte
bool isRunning = true;         // Boolean (true/false) - uses 1 byte on Arduino
```

### Key Memory Considerations:

1. **Choose the smallest type that will fit your data**
   
   For example, if you're counting button presses and know the value will never exceed 255, use `byte` instead of `int` to save memory.

2. **Avoid floating-point when possible**
   
   Floating-point operations are much slower on Arduino's 8-bit processor and use more memory. Try to use integers when possible.

   ```cpp
   // Instead of this:
   float temperature = 22.5;
   
   // Consider this (storing tenths of degrees):
   int temperatureInTenths = 225; // 22.5 degrees
   ```

3. **Watch out for string memory usage**
   
   Strings can quickly consume your precious RAM. For constant strings, use the F() macro to store them in flash memory instead:
   
   ```cpp
   // Bad: Uses RAM
   Serial.println("Motor starting");
   
   // Good: Uses flash memory instead
   Serial.println(F("Motor starting"));
   ```

## A Practical Example

Let's look at a practical example that demonstrates variable types in an Arduino context:

```cpp
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
  
  // Track performance 
  cycleCount++;
  
  // Every second, print status
  if (currentTime % 1000 < 10) {  // Check if we just crossed a second boundary
    Serial.print(F("Uptime: "));
    Serial.print((currentTime - startTime) / 1000);  // Convert to seconds
    Serial.print(F(" seconds, cycles: "));
    Serial.println(cycleCount);
    
    // Reset cycle counter
    cycleCount = 0;
  }
}

// Function to check available RAM
int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
```

In this example, we've:
- Used appropriate data types for different values
- Demonstrated how to track time with `millis()`
- Added a function to check available RAM
- Used the F() macro to save memory by keeping strings in flash

## An Interesting Fact: Memory Size Differences by Architecture

One surprising thing for many beginners is that the size of data types can vary across different platforms. The sizes I've listed are specific to Arduino's AVR architecture (like the Uno). 

For example, on some other platforms:
- `int` might be 4 bytes instead of 2 bytes
- `long` might be 8 bytes instead of 4 bytes

This is why it's good practice to use explicitly sized types if you need guaranteed sizes across platforms:

```cpp
#include <stdint.h>

uint8_t  tinyNumber = 42;    // Exactly 8 bits (1 byte)
int16_t  smallNumber = 1000; // Exactly 16 bits (2 bytes) 
uint32_t bigNumber = 100000; // Exactly 32 bits (4 bytes)
```

## Exercise: Analyzing Memory Usage

Let's analyze memory usage for a typical sensor-based project:

```cpp
#include <Arduino.h>

// Using different data types
byte sensorReading = 0;           // 1 byte
int sensorValues[10];             // 20 bytes (10 × 2 bytes)
float temperatureC = 0.0;         // 4 bytes
char deviceID[10] = "ARDUINO01";  // 10 bytes 
bool isActivated = false;         // 1 byte
unsigned long lastUpdateTime = 0; // 4 bytes

// TOTAL: 40 bytes of RAM used just for these variables
```

When you consider that an Arduino Uno only has 2,048 bytes of RAM total, you can see why choosing the right data types matters.