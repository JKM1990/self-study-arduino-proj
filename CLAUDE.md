# CLAUDE.md - Guidelines for Arduino 2D Plotter Project

## Agent Workflow
- ALWAYS ask user before writing any files or performing build commands
- DO NOT upload code to Arduino board - user will handle this manually
- Present code for review before implementing in project files

## Development Environment
- WSL: Ubuntu 24.04
- Editor: VS Code with WSL extension
- Build System: PlatformIO IDE extension installed on WSL
- Target: Arduino UNO R3 board

## Project Context
- 2D plotter using Arduino UNO R3 with NEMA 17 stepper motors
- Currently in Phase 1: Setup and Basics (C++ fundamentals, input handling)

## Build Commands
- Build: `pio run`
- Clean: `pio run --target clean`
- Monitor serial: `pio device monitor`
- Test: `pio test`

## Code Style Guidelines
- **Formatting**: 2-space indentation, 80-char line limit
- **Naming**: camelCase for variables/functions, PascalCase for classes
- **Pin Variables**: Use const int with pin_ prefix (e.g., `const int pin_led = 13;`)
- **Documentation**: Comment all functions with purpose, parameters, returns
- **Error Handling**: Use status codes for Arduino functions
- **Libraries**: Prefer Arduino standard libraries, document external deps
- **Functions**: Keep functions small (<50 lines), single responsibility

## Project Organization
- `/src/main` - Production code for current phase
- `/src/experiments` - Experimental sketches
- `/src/libraries` - Custom libraries
- `/docs` - Documentation and experiment logs