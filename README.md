# Microcontroller Stopwatch Project

## Overview

This project implements a stopwatch application using an ARM microprocessor Tiva-C Series TM4C123GH6PM. The stopwatch is controlled through switch inputs and displayed on an LCD screen. It was developed using Code Composer Studio and created as a hands-on project for EME Egypt's Make Electronics course to demonstrate interfacing with LCD and using the timers module on the microprocessor. 🕒

## Features

Start, pause, and reset the stopwatch using physical buttons. 🚀

Display the elapsed time in the format "HH:MM:SS.m" on an LCD screen. 🕐

## Hardware Requirements

Tiva-C Series TM4C123GH6PM microprocessor board. 🛠️

LCD display. 🖥️

Connecting wires. 🔌

## Project Demo

Check out the project in action! Watch the demo video: [Demo Video](Demo/demo.mp4) 📽️

## Getting Started

### Hardware Setup

1. Connect the LCD display to the microprocessor's GPIO pins.

2. Double-check your connections and ensure everything is properly wired before proceeding.

### Software Compilation

1. Install Code Composer Studio (IDE) for programming the microprocessor.

2. Clone or download this repository to your local machine.

3. Open the project in Code Composer Studio.

4. Compile the source code to generate the binary file.

### Upload the Code

1. Connect your microprocessor board to your computer.

2. Use Code Composer Studio to upload the compiled binary to the microprocessor.

### Power Up

1. Power on your microprocessor.

2. The LCD display will show "00:00:00.0".

## Usage

1. Press Switch 2 to start the stopwatch. Press it again to reset the stopwatch.

2. Press Switch 1 to pause/resume the stopwatch.

## Future Work

Add lap time functionality. 🔮

Implement a countdown timer mode. ⏱️

## Contributing

Contributions are welcome! Here's how you can contribute: 🤝

1. Fork this repository.

2. Create a new branch: `git checkout -b feature/new-feature`.

3. Make your changes and commit them: `git commit -m "Add new feature"`.

4. Push to the branch: `git push origin feature/new-feature`.

5. Open a pull request.

## Acknowledgments

This project draws inspiration from educational resources provided by Egypt Make Electronics (EME). 🙌

## Contact

 For inquiries, please contact [e.roshdy97@gmail.com](mailto:e.roshdy97@gmail.com). 📧
