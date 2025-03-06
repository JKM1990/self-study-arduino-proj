# Component: Arduino UNO R3 (ELEGOO)

## Specifications
- **Type:** Microcontroller Board
- **Model:** UNO R3
- **Manufacturer:** ELEGOO (based on Arduino design)
- **Microcontroller:** ATmega328P
- **Operating Voltage:** 5V
- **Input Voltage:** 7-12V (recommended)
- **Digital I/O Pins:** 14 (6 provide PWM output)
- **Analog Input Pins:** 6
- **DC Current per I/O Pin:** 20 mA
- **Flash Memory:** 32 KB (0.5 KB used by bootloader)
- **SRAM:** 2 KB
- **EEPROM:** 1 KB
- **Clock Speed:** 16 MHz

## Purpose in Project
Primary microcontroller for the 2D plotter system. Handles all control logic, motor driving, and user interface.

## Connection Details
- **Power:** Via USB (for programming and low-power operation) or external power supply (7-12V)
- **Digital Pins:** Used for controlling stepper motor drivers, buttons, and status LEDs
- **PWM Pins (3, 5, 6, 9, 10, 11):** Used for servo control and variable output
- **Serial Communication:** Via USB or pins 0 (RX) and 1 (TX)
- **I2C Communication:** Via pins A4 (SDA) and A5 (SCL)
- **SPI Communication:** Via pins 10 (SS), 11 (MOSI), 12 (MISO), 13 (SCK)

## Configuration
- Jumper selection for power source (USB/External)
- ATmega16U2 programmed as a USB-to-serial converter

## Usage Notes
- Avoid drawing more than 20mA from any I/O pin
- Don't exceed 5V on any input pin
- Total current from 3.3V pin should not exceed 50mA
- External power supply should not exceed 12V

## Code Example
```cpp
// Basic program structure
void setup() {
  // Initialization code runs once
  Serial.begin(9600);  // Initialize serial communication
  pinMode(13, OUTPUT); // Set pin 13 as output
}

void loop() {
  // Main code runs repeatedly
  digitalWrite(13, HIGH);  // Turn on the LED
  delay(1000);             // Wait for a second
  digitalWrite(13, LOW);   // Turn off the LED
  delay(1000);             // Wait for a second
}
```

## Images
Reference images will be added to media/photos folder

## Troubleshooting
- **Board not recognized by computer**
  - Check USB cable (data+power, not charge-only)
  - Install correct drivers
  - Select correct board and port in Arduino IDE

- **Program won't upload**
  - Verify board selection in Arduino IDE
  - Check if another program is using the serial port
  - Try pressing reset button right before upload

## Resources
- [ELEGOO UNO R3 Documentation](https://www.elegoo.com/)
- [Arduino UNO Official Reference](https://docs.arduino.cc/hardware/uno-rev3)
- [ATmega328P Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
