# PlatformIO Commands Reference

## Basic Commands

| Command | Description |
|---------|-------------|
| `pio run` | Build the project (compile and verify) |
| `pio run -t upload` | Build and upload to target device |
| `pio run -t clean` | Clean build files |
| `pio device monitor` | Open serial monitor |
| `pio test` | Run unit tests |
| `pio check` | Static code analysis |

## Working with Sub-projects

| Command | Description |
|---------|-------------|
| `pio run -d [directory]` | Build a specific project in subdirectory |
| `pio run -d [directory] -t upload` | Build and upload a specific project |
| `pio device monitor -d [directory]` | Open serial monitor for a specific project |
| `pio test -d [directory]` | Run tests for a specific project |

## Project Management

| Command | Description |
|---------|-------------|
| `pio project init` | Initialize a new project |
| `pio project config` | Show project configuration |
| `pio lib list` | List installed libraries |
| `pio lib install [library]` | Install a library |
| `pio lib update` | Update installed libraries |
| `pio lib uninstall [library]` | Uninstall a library |

## Board & Platform Management

| Command | Description |
|---------|-------------|
| `pio boards` | List all supported boards |
| `pio boards [query]` | Search for specific boards |
| `pio platform list` | List installed platforms |
| `pio platform install [platform]` | Install a platform |
| `pio platform update` | Update installed platforms |
| `pio platform uninstall [platform]` | Uninstall a platform |

## Advanced Usage

| Command | Description |
|---------|-------------|
| `pio run -t upload --upload-port [port]` | Upload using specific port |
| `pio run -e [environment]` | Build for specific environment |
| `pio run -v` | Verbose output for debugging |
| `pio run -j [jobs]` | Set number of concurrent build jobs |
| `pio run --silent` | Suppress output except errors |

## Examples for Arduino 2D Plotter Project

| Command | Example |
|---------|---------|
| `pio run -d src/phase1_setup/button_debouncing` | Build the button debouncing project |
| `pio run -d src/phase1_setup/button_debouncing -t upload` | Upload the button debouncing project |
| `pio device monitor -d src/phase1_setup/button_debouncing` | Monitor output from button debouncing project |
| `pio test -d src/phase1_setup/button_debouncing` | Run tests for button debouncing project |