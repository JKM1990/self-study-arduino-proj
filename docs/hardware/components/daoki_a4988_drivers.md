# Component: DAOKI A4988 Stepper Motor Drivers

## Specifications
- **Type:** Stepper Motor Driver Module
- **Manufacturer:** DAOKI
- **Compatible Motors:** Bipolar Stepper Motors
- **Package:** 5x Driver Modules with Heatsinks

## Electrical Characteristics
- **Input Voltage:** 8-35V
- **Max Current:** 2A per phase
- **Logic Voltage:** 5V
- **Microstepping Modes:** Full, Half, 1/4, 1/8, 1/16 step

## Purpose in Project
Precise motor control for 2D plotter axes:
- Current regulation
- Microstepping support
- Thermal management via integrated heatsinks

## Key Features
- Simple step and direction control interface
- Adjustable current output
- Overcurrent protection
- Thermal shutdown capability
- Compatible with NEMA 17 stepper motors

## Pin Configuration
- STEP: Pulse input for motor movement
- DIR: Direction control
- EN: Enable/disable motor
- MS1, MS2, MS3: Microstepping mode selection
- RESET: Motor driver reset
- SLEEP: Low-power mode control

## Microstepping Modes
- Full Step: 200 steps/revolution
- Half Step: 400 steps/revolution
- 1/4 Step: 800 steps/revolution
- 1/8 Step: 1600 steps/revolution
- 1/16 Step: 3200 steps/revolution

## Installation Notes
- Securely mount with included heatsinks
- Ensure proper thermal dissipation
- Match motor current ratings
- Use appropriate power supply

## Troubleshooting
- Check wiring connections
- Verify current limit potentiometer
- Monitor for overheating
- Ensure proper microstepping configuration

## Potential Issues
- Incorrect wiring can damage driver
- Excess current may cause thermal shutdown
- Improper grounding can cause erratic behavior

## Recommended Practices
- Use separate power supply for motors
- Implement current limiting
- Add additional cooling if operating at max current

## Resources
- Manufacturer datasheet
- A4988 technical documentation
- Arduino stepper motor control guides
