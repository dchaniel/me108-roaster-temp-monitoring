# Coffee Roaster Temperature Monitoring

## Overview

This is a projectdesigned for ME108 (Making and Breaking) at Stanford to monitor and display the temperature of a coffee roaster using a PT100 RTD sensor. The system uses an Adafruit MAX31865 RTD-to-Digital converter and a TM1637-based 4-digit 7-segment display to show the temperature of the sensor. Makes roasting to your desired temp easy!

## Table of Contents

- [Components](#components)
- [Circuit Diagram](#circuit-diagram)
- [Installation](#installation)
- [Usage](#usage)
- [Code Structure](#code-structure)
  - [Setup](#setup)
  - [Loop](#loop)
- [Troubleshooting](#troubleshooting)
- [Future Improvements](#future-improvements-ideation)
- [License](#license)

## Components

- **Arduino Nano**: The brains of the operation.
- **Adafruit MAX31865**: An RTD-to-Digital converter specifically designed for PT100 and PT1000 sensors.
- **PT100 RTD Sensor**: A temperature sensor used to measure the roaster's temperature.
- **TM1637 Display Module**: A 4-digit 7-segment display for visual temperature output.
- **110V AC to 5V DC Converter**: Converts the roaster's power to a safe voltage for the Arduino.

## Circuit Diagram

<img width="1284" alt="image" src="https://github.com/user-attachments/assets/46e57e3c-6c4c-499b-9ebc-b56c31d10f10">

## Installation

1. **Clone the Repository**
    ```bash
    git clone https://github.com/dchaniel/me108-roaster-temp-monitoring.git
    ```
2. **Install Arduino IDE**  
   Download and install the [Arduino IDE](https://www.arduino.cc/en/software) if you haven't already.

3. **Install Required Libraries**
    - **Adafruit MAX31865 Library**
        - Open Arduino IDE.
        - Navigate to `Sketch` > `Include Library` > `Manage Libraries`.
        - Search for `Adafruit MAX31865` and install it.
    - **TM1637 Display Library**
        - Similarly, search for `TM1637` and install the library by Avishay Orpaz.

4. **Connect the Hardware**
    - Follow the [circuit diagram](#circuit-diagram) to connect the PT100 sensor, MAX31865, TM1637 display, and Arduino board.

5. **Upload the Code**
    - Open the `roaster_temp_monitoring.ino` file in Arduino IDE.
    - Select the appropriate board and port from `Tools` > `Board` and `Tools` > `Port`.
    - Click the upload button to transfer the code to the Arduino.

## Usage

Once the system is powered and the code is uploaded:

- **Temperature Display**: The TM1637 display will alternately show the current roaster temperature in Celsius and Fahrenheit.
- **Serial Monitor**: Open the Arduino Serial Monitor (baud rate: 9600) to view detailed temperature readings, resistance values, and any fault information.
- **Fault Indicators**: If a fault is detected (e.g., sensor disconnection, exceeding temperature thresholds), the display will show `ERR`, and detailed fault codes will appear in the Serial Monitor.

## Code Structure

The primary code resides in the `roaster_temp_monitoring.ino` file. Below is an overview of its structure and functionality.


### Setup

- **Serial Communication**: Initiates at 9600 baud to facilitate debugging and data logging via the Serial Monitor.
- **Display Initialization**: Sets the brightness of the TM1637 display.
- **MAX31865 Initialization**: Configures the MAX31865 for a 3-wire PT100 sensor. If initialization fails, an error message is printed to the Serial Monitor.

### Loop

- **Temperature Reading**: Continuously reads the temperature from the PT100 sensor using the MAX31865.
- **Debugging Information**: Outputs raw RTD values, resistance calculations, and temperature readings in both Celsius and Fahrenheit to the Serial Monitor.
- **Fault Detection**: Checks for any faults reported by the MAX31865. If a fault is detected, detailed information is printed, and the fault is cleared.
- **Display Logic**:
  - **Normal Operation**: Alternates displaying the temperature in Celsius and Fahrenheit on the 4-digit display.
  - **Fault Condition**: Displays `ERR` on the display to indicate an error.

## Troubleshooting

- **Inaccurate Temperature Readings**
  - **Cause**: Calibration issues or sensor inaccuracies.
  - **Solution**: Adjust the `RNOMINAL` value in the code based on the specific RTD used. Ensure the sensor is properly connected.

## Future Improvements Ideation

- **Data Logging**: Integrate an SD card module to log temperature data over time for analysis.
- **Wireless Monitoring**: Add Bluetooth or Wi-Fi capabilities to monitor temperatures remotely via a smartphone or computer.
- **Enhanced UI**: Upgrade to a larger display or incorporate an OLED screen for more detailed information.
- **Alarm System**: Implement audible or visual alarms for critical temperature thresholds or fault conditions.

## License

This project is licensed under the [MIT License](LICENSE).

---

*Happy Roasting!*
