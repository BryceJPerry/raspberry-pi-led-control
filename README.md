# raspberry-pi-led-control
Raspberry Pi LED Control Program: A C++ application that demonstrates GPIO control by blinking an LED with clean exit handling. Features include thread-safe keyboard input for graceful termination, signal handling for Ctrl+C interrupts, and real-time status output. The program uses the pigpio library for GPIO control. 

```markdown
# Raspberry Pi LED Blink with Thread-Safe Termination

This program demonstrates GPIO control on a Raspberry Pi, implementing a clean shutdown mechanism and thread-safe input handling.

## Hardware Requirements
- Raspberry Pi (any model)
- LED
- 220Ω resistor
- Breadboard and jumper wires

## Circuit Setup
1. Connect the LED's anode (longer leg) to GPIO18 through a 220Ω resistor
2. Connect the LED's cathode (shorter leg) to any ground (GND) pin

## Software Prerequisites

### Update System
```bash
sudo apt update
sudo apt upgrade
```

### Install Required Packages
```bash
# Install C++ compiler and build tools
sudo apt install build-essential

# Install pigpio library
sudo apt install pigpio

# Start pigpio daemon
sudo pigpiod

# Enable pigpio daemon at boot
sudo systemctl enable pigpiod
```

## Building the Program

1. Clone this repository.

2. Compile the program:
```bash
g++ -o led_blink led_blink.cpp -lpigpio -lpthread
```

## Running the Program
```bash
sudo ./led_blink
```

## Usage
- The LED will blink continuously with 1-second intervals
- Press 'q' to quit the program
- Press Ctrl+C for emergency stop

## Troubleshooting

If you get "can't lock /var/run/pigpio.pid":
```bash
sudo killall pigpiod
sudo pigpiod
```

## Notes
- The program must be run with sudo due to GPIO access requirements
- Make sure the pigpiod daemon is running before starting the program
- The program uses GPIO18 by default (can be changed in LED_PIN define)

## License
MIT
```

Would you like me to add any additional sections to the README or expand on any part of the documentation?
