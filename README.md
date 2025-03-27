# Arduino 2D Plotter Project

## Project Overview
Self-directed learning project to build a two-axis drawing system using Arduino and stepper motors (January - April 2025). In Preparation for my upcoming work placement with Cripps & Sons, where I will be coding a double-headed drilling machine for drawers and cabinets.

### Goals
- Learn Arduino programming and electronics fundamentals
- Develop skills in stepper motor control and coordination
- Build a functional 2D plotter capable of drawing basic shapes
- Prepare for work experience at Cripps and Sons automated drill system

## Project Timeline
- **Total Duration:** 16 weeks
- **Total Story Points:** 84 across 4 phases
<<<<<<< HEAD
=======
- **Current Progress:** Phase 1 (8/16 points completed)
>>>>>>> phase1/cpp_fundamentals_arduino

## Project Phases
1. **Setup and Basics (16 points)**
   - Arduino IDE setup ✓
   - Basic LED circuit ✓
<<<<<<< HEAD
   - Button input with debouncing ✓
   - C++ fundamentals ✓
   - Technical diagrams ✓
   - Breadboard prototyping ✓
=======
   - C++ fundamentals ✓
   - Button input with debouncing ✓
   - Technical diagrams
   - Breadboard prototyping
>>>>>>> phase1/cpp_fundamentals_arduino

2. **Motor Control (21 points)**
   - Wire up stepper motor
   - Configure A4988 driver
   - Basic motor movement
   - Position tracking
   - Acceleration control

3. **Dual-Axis System (34 points)**
   - Design mechanical frame
   - Coordinate dual motor movement
   - Implement coordinate system
   - User input system
   - Basic shape drawing

4. **System Assembly and Testing (13 points)**
   - System assembly
   - Calibration routine
   - Error handling
   - Final testing and documentation

## Current Development Status
- Completed Arduino IDE setup and transitioned to PlatformIO in VS Code
- Implemented basic LED circuits with current-limiting resistors
- Successfully implemented button input with two different debouncing techniques:
  - Time-based debouncing with millis() (50ms debounce delay)
  - Counter-based debouncing requiring multiple consistent readings
- Created bounce simulation code to demonstrate debouncing principles
- Documented hardware specifications for Arduino UNO R3
- Acquired fundamental C++ skills for Arduino development:
  - Arduino-specific functions and programming patterns
  - Timing operations with millis() for non-blocking code
  - Variable scoping and state management
  - Digital input/output manipulation
  - Control structures and functions

## Equipment

### Core Components
- **Arduino UNO R3 (ELEGOO)**
  - Microcontroller: ATmega328P
  - Operating Voltage: 5V
  - Digital I/O Pins: 14 (6 with PWM)
  - Analog Input Pins: 6
  - Flash Memory: 32 KB
  - Clock Speed: 16 MHz

### Stepper Motor System
- **NEMA 17 Stepper Motors (2×)**
  - Current: 2A
  - Holding Torque: 45Ncm/63.74oz.in
  - 1.8° step angle (200 steps/revolution)

- **A4988 Stepper Motor Drivers (5×)**
  - DAOKI brand with heatsinks
  - Microstepping: Full, 1/2, 1/4, 1/8, 1/16
  - Current control with trim potentiometer
  - Logic voltage: 3-5.5V
  - Motor voltage: 8-35V

### Power Supply
- **Facmogu 12V 5A Power Supply**
  - Input: AC 100-240V 50/60Hz
  - Output: DC 12V 5A (60W)
  - 2.1×5.5mm barrel connector

### Mechanical Components
- **Houkr GT2 Timing Belt/Pulley Kit**
  - 2× GT2 20-tooth pulleys (5mm bore)
  - 2m GT2 timing belt (6mm width)
  - Mounting hardware

- **Linear Motion Components**
  - 300mm & 200mm linear rods
  - Linear bearings
  - Mounting hardware

### Additional Components
- **SG90 Servo Motor** for pen lift mechanism
- **Breadboard** for prototyping
- **Tactile push buttons** (4-pin)
- **LEDs** for status indication
- **Jumper wires**
- **Resistors** (various values)
- **Capacitors** for motor noise suppression

## Repository Structure
<<<<<<< HEAD
- **/docs/** - Documentation, experiment logs, progress tracking
  - **/docs/experiment_logs/** - Detailed documentation of experiments
  - **/docs/progress/** - Phase-based progress documentation
  - **/docs/skills_progress/** - Skills development tracking
- **/src/** - All Arduino code organized by project phase
  - **/src/phase1_setup/** - Initial Arduino and button debouncing code
  - **/src/libraries/** - Custom libraries
  - **/src/main/** - Production code
- **/hardware/** - Hardware documentation (components, schematics, assembly)
- **/media/** - Photos and videos of progress
=======
- **/docs/** - Detailed logs of experiments and learning
- **/docs/progress/** - Phase progress reports for all subtasks in current phase, extensive documentation.
- **/src/** - All Arduino code (Phase experiments, libraries, main project)
- **/hardware/** - Hardware documentation (components, schematics, assembly)
- **/media/** - Videos of progress linked to my Youtube channel (private videos)
>>>>>>> phase1/cpp_fundamentals_arduino

## Learning Resources
- Arduino Project Hub
- Arduino Official Documentation
- Component Datasheets
- Claude AI (primary learning companion)
- Youtube

## Safety Protocols
Safety guidelines are being followed at all stages of development to ensure proper handling of electronic components and mechanical systems.

## Contact
Jeff Manser - Second-year programming student\
E-mail:\
jeffkmanser@gmail.com (Personal)\
w0194127@nscc.ca (NSCC account)