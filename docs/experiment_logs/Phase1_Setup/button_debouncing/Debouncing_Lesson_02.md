I'll help you set up the button debouncing circuit on your breadboard. Let me walk you through this step-by-step with the ELEGOO Uno R3 starter kit components.

# Setting Up Your Button Debouncing Circuit

## Components You'll Need

From your ELEGOO starter kit, gather:
- Your Arduino Uno R3 board
- Breadboard
- 1 small tactile push button (4 pins)
- Jumper wires (at least 3: 1 red, 1 black, 1 other color)
- You won't need an external resistor since we're using the Arduino's internal pull-up resistor

## Understanding Your Button

The tactile button in your kit has 4 pins, but it's important to understand how they're connected internally:

```
    1 o---o 2
      |   |
      |   |
    3 o---o 4
```

Pins 1 and 2 are connected to each other internally, and pins 3 and 4 are connected to each other. The button works by connecting the top pair to the bottom pair when pressed.

## Step-by-Step Assembly

1. **Place the Button on the Breadboard**:
   - Position your breadboard with the center gap running horizontally
   - Place the tactile button so it straddles the center gap of the breadboard
   - The button should be oriented so that its 4 pins go into 4 different rows

2. **Connect the Arduino Ground to the Button**:
   - Take a black jumper wire
   - Connect one end to any GND pin on the Arduino
   - Connect the other end to the same row as one of the button's pins (let's say pin 3)
   - This will be one side of the button circuit

3. **Connect the Arduino Input Pin to the Button**:
   - Take a colored jumper wire (not red or black)
   - Connect one end to digital pin 2 on the Arduino
   - Connect the other end to a row with another button pin that is NOT directly connected to your ground pin (let's say pin 1)
   - This will be the input pin that reads the button state

4. **Power and Built-in LED**:
   - You don't need to connect the 5V since we're using the internal pull-up resistor
   - The built-in LED on pin 13 is already connected internally to the Arduino

## Visual Diagram of the Circuit

```
   Arduino Uno                 Breadboard
   ___________                 __________
  |           |               |          |
  |        5V o                          |
  |           |                          |
  |       GND o---------[black]----------o Row A
  |           |                          |
  |        D2 o--------[color]----------o Row B
  |           |                   |      |
  |        D13|                   |      |
  |___________|                  [BTN]   |
                                  |      |
                                  |      |
                                 Row C----o Row A (GND)
                                  |      |
                                  |      |
                                 Row D----o Row B (D2)
                                          |
                                          |
                                 __________
```

## How This Connects to Your Code

Your code uses `pinMode(pin_button, INPUT_PULLUP)` which activates an internal pull-up resistor on pin 2. Here's what happens electrically:

1. **When Button is NOT Pressed**:
   - The internal pull-up resistor pulls pin 2 HIGH (to 5V)
   - `digitalRead(pin_button)` returns HIGH
   - LED is OFF (following your code's logic)

2. **When Button is Pressed**:
   - The button connects pin 2 to GND
   - This creates a direct path to ground, overpowering the pull-up
   - `digitalRead(pin_button)` returns LOW
   - LED turns ON

The debouncing happens in software exactly as your code describes, smoothing out the electrical noise when the button contacts connect and disconnect.

## Verification Steps

After you've connected everything:

1. **Visual Check**:
   - Button straddles the center gap of the breadboard
   - One side of the button connects to GND
   - The other side connects to pin 2
   - No loose connections or unintended shorts

2. **Power Up**:
   - Connect your Arduino to your computer via USB
   - Upload your code if you haven't already
   - Open the Serial Monitor at 9600 baud

3. **Testing**:
   - Press the button and notice the built-in LED should light up
   - Release and it should turn off
   - Check the Serial Monitor to see both raw and debounced state changes
   - Notice how multiple raw state changes might occur, but only one debounced change

## Troubleshooting Tips

If things aren't working as expected:

- **LED Doesn't Respond**: Check your code upload status and that you're using the correct pin numbers
- **Button Always Reads as Pressed**: Double-check your button orientation; you might have connected across the wrong pins
- **Button Never Registers as Pressed**: Ensure the connections to pin 2 and GND are secure
- **Inconsistent Behavior**: Make sure the button is properly seated in the breadboard