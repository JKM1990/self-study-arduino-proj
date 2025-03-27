# Component: SG90 Servo Motor

## Specifications
- **Type:** Micro Servo Motor
- **Model:** SG90
- **Weight:** 9g
- **Size:** Compact miniature design

## Electrical Characteristics
- **Operating Voltage:** 4.8V - 6V DC
- **Current Draw:** 
  - Idle: ~10 mA
  - Active: 100-250 mA
  - Max (Stall): 360 mA
- **Operating Frequency:** 50 Hz
- **Pulse Width:** 1520 μs

## Purpose in Project
Pen lift/lower mechanism for 2D plotter:
- Precise vertical positioning
- Quick response
- Low power consumption

## Mechanical Details
- **Torque:** 
  - 1.2 kg/cm @ 4.8V
  - 1.6 kg/cm @ 6V
- **Speed:** 0.15 sec/60 degrees
- **Rotation:** 180 degrees
- **Gear Material:** Nylon

## Pin Configuration
- **Red Wire:** Positive Power (5V)
- **Brown Wire:** Ground
- **Orange/Yellow Wire:** PWM Signal Control

## Control Interface
- Requires PWM (Pulse Width Modulation)
- Standard servo control protocol
- Compatible with Arduino servo libraries

## Installation Notes
- Secure mounting
- Avoid excessive load
- Use appropriate power supply
- Implement soft start/stop

## Potential Issues
- Overloading can cause premature failure
- Continuous rotation may damage gears
- Requires precise pulse width control

## Troubleshooting
- Check power connections
- Verify PWM signal
- Listen for unusual sounds
- Monitor for jerky or inconsistent movement

## Recommended Practices
- Use external power for multiple servos
- Implement current limiting
- Add soft start/stop in control code
- Avoid stalling the motor

## Thermal Considerations
- Monitor temperature during operation
- Provide adequate cooling if needed
- Avoid continuous high-load conditions

## Resources
- Servo motor control tutorials
- Arduino servo library documentation
- Microcontroller interfacing guides
