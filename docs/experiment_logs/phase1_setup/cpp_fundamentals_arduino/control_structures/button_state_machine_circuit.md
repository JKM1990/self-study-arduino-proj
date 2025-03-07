# Setting Up the Button State Machine Circuit

Let me guide you through setting up your breadboard circuit for the button state machine example. I'll make this practical and hands-on.

## Components Needed

First, gather these components from your ELEGOO UNO R3 starter kit:
- Your Arduino UNO board
- Breadboard
- 1 pushbutton (tactile switch)
- 3 LEDs (red, green, and blue)
- 3 resistors (220Ω) for the LEDs
- 1 resistor (10kΩ) for the button (optional, since we'll use internal pull-up)
- Jumper wires (various colors will help keep track of connections)

## Step-by-Step Breadboard Setup

### 1. Position Your Components

First, let's place everything on the breadboard:

1. **Place the pushbutton** across the center gap of your breadboard (it should straddle the gap with legs in different rows).
   - Tactile buttons have 4 pins arranged in a square
   - Note that the internal connections are diagonal (pins 1-3 and 2-4 are connected)

2. **Place the LEDs** in the breadboard:
   - Red LED: place in an empty row
   - Green LED: place in a different empty row
   - Blue LED: place in another empty row
   - Remember that LEDs are polarized! The longer leg is the anode (+), and the shorter leg is the cathode (-)

3. **Place the current-limiting resistors** (220Ω) for each LED:
   - Connect one end to the cathode (shorter leg) of each LED
   - Connect the other end to an empty row

### 2. Wire Up the Circuit

Now let's connect everything:

#### For the Button:
1. Connect one side of the button (pin 1) to digital pin 2 on the Arduino
2. Connect the diagonal pin (pin 3) to GND on the Arduino
   - We're using the internal pull-up resistor, so no external resistor is needed
   - With this configuration, the button will read LOW when pressed

#### For the LEDs:
1. **Red LED:**
   - Connect the anode (longer leg) to digital pin 9 on the Arduino
   - Connect the 220Ω resistor from the cathode to GND

2. **Green LED:**
   - Connect the anode to digital pin 10 on the Arduino
   - Connect the 220Ω resistor from the cathode to GND

3. **Blue LED:**
   - Connect the anode to digital pin 11 on the Arduino
   - Connect the 220Ω resistor from the cathode to GND

### 3. Power Connections
1. Connect the Arduino GND to the breadboard's negative power rail
2. Use this negative rail for all GND connections (resistors)

## Visual Representation of the Circuit

Here's a text-based representation of how your circuit should look:

```
Arduino            Breadboard
+-------+          +----------------+
|       |          |                |
|     D2|--------->|Button (Pin 1)  |
|       |          |     |          |
|       |          |     |          |
|       |          |Button (Pin 3)  |
|       |          |     |          |
|       |          |     v          |
|    GND|--------->|GROUND RAIL     |
|       |          |                |
|     D9|--------->|LED R(+)        |
|       |          |    |           |
|       |          |    v           |
|       |          |   220Ω         |
|       |          |    |           |
|       |          |    v           |
|       |          |GROUND RAIL     |
|       |          |                |
|    D10|--------->|LED G(+)        |
|       |          |    |           |
|       |          |    v           |
|       |          |   220Ω         |
|       |          |    |           |
|       |          |    v           |
|       |          |GROUND RAIL     |
|       |          |                |
|    D11|--------->|LED B(+)        |
|       |          |    |           |
|       |          |    v           |
|       |          |   220Ω         |
|       |          |    |           |
|       |          |    v           |
|       |          |GROUND RAIL     |
+-------+          +----------------+
```

## Troubleshooting Tips

If your circuit doesn't work as expected:

1. **Button Not Responding:**
   - Verify the button orientation - remember the internal connections are diagonal
   - Make sure pin 1 connects to Arduino pin 2 and pin 3 to GND
   - Test the button with a simple sketch that just prints values to Serial

2. **LEDs Not Lighting:**
   - Check LED polarity - longer leg should connect to the Arduino pins
   - Verify your resistors are the correct value (220Ω: red-red-brown)
   - Make sure the pins in the code match your physical connections

3. **Dim LEDs:**
   - The code uses `analogWrite()` for PWM (brightness control) - this is intentional
   - The initial state (STATE_OFF) will have the LEDs off (brightness[0] = 0)

## Creating Your Code

1. Create a new PlatformIO project named "button_state_machine" in your Phase 1 section
2. Use the full code example I provided earlier in your main.cpp file
3. Verify that your pin definitions match your physical connections:
   ```cpp
   const byte BUTTON_PIN = 2;
   const byte RED_LED = 9;
   const byte GREEN_LED = 10;
   const byte BLUE_LED = 11;
   ```

## What to Expect When Running

When you upload and run the code:

1. Initially, all LEDs will be OFF (STATE_OFF)
2. Each time you press the button, the system cycles to the next state:
   - STATE_OFF: All LEDs off
   - STATE_LOW: All LEDs dimly lit (PWM value 64)
   - STATE_MEDIUM: All LEDs at medium brightness (PWM value 150)
   - STATE_HIGH: All LEDs at full brightness (PWM value 255)
3. The serial monitor will show messages about state changes

The code uses non-blocking button debouncing, so it will handle button presses reliably without using `delay()`.