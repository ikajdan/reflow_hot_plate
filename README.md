<h1 align="center">
  <img src="https://github.com/ikajdan/reflow_hot_plate/assets/28950897/c3468495-384c-4000-b4db-6c9cec08a22f" alt="Reflow Hot Plate" width="300" height="auto"/>
  <br><br>
  Reflow Hot Plate
  <br><br>
</h1>

<p align="center">
  <a href="#features">Features</a> •
  <a href="#hardware">Hardware</a> •
  <a href="#software">Software</a> •
  <a href="#usage">Usage</a> •
  <a href="#gallery">Gallery</a> •
  <a href="#license">License</a>
</p>

The STM32-Based Reflow Hot Plate Project is an open-source initiative aimed at creating a reflow soldering hot plate using the STM32 microcontroller. This project provides an affordable and customizable solution for hobbyists looking to solder surface-mount components onto printed circuit boards with precision and control.

## Features

- **Precise temperature control:** The STM32 microcontroller provides accurate temperature control, ensuring optimal soldering results for a wide range of solder pastes and components.
- **User-friendly interface:** A user-friendly interface, featuring an OLED display and tactile buttons, allows you to easily set and monitor reflow profiles.
- **Customizable reflow profiles:** Create, edit, and save reflow profiles tailored to your specific soldering requirements.
- **Safety mechanisms:** Built-in safety features, such as over-temperature protection and emergency shut-off, ensure a secure soldering environment.
- **Open-source:** The entire project, including schematics, PCB layouts, and firmware is open-source and available for improvement and customization.

## Hardware

The electronic hardware is designed using KiCad. It includes the following components:

- STM32 microcontroller (STM32F103 series)
- N-Channel Power MOSFET for controlling the heating element
- Thermocouple and PT100 sensor for temperature measurement
- OLED display for real-time temperature and soldering progress information
- Buttons for user interaction
- USB-C connector for communication
- Power supply circuitry

The mechanical hardware is designed using FreeCAD. It includes the following components:

- Front panel mask
- Front panel brackets
- Gooseneck mounting

These components are designed to be 3D printed and assembled together to create a complete device.

For detailed hardware schematics, PCB layout and CAD models, please refer to the [Hardware](hardware/) directory.

## Software

The software for the reflow hot plate is developed using the STM32CubeIDE. It includes:

- Temperature control algorithm
- User interface logic
- Reflow profile management
- Safety and emergency handling

The Cube project can be found in the [Software](software/) directory.

## Usage

1. Power on the reflow hot plate and wait for it to initialize.
1. Place your PCB with solder paste and components onto the hot plate.
1. Use the tactile buttons and OLED display to navigate through the user interface and select a reflow profile.
1. The hot plate will execute the selected reflow profile, precisely controlling the temperature to solder the components onto the PCB.
1. Once the reflow process is complete, allow the PCB to cool before removing it from the hot plate.

## Gallery

<img src="https://github.com/ikajdan/reflow_hot_plate/assets/28950897/f0e61aaf-80ff-4ed2-aad6-bbd336b23196" width="30%"></img>
<img src="https://github.com/ikajdan/reflow_hot_plate/assets/28950897/86b3246f-bf8c-475d-af1c-53e835ec0c3f" width="30%"></img>
<img src="https://github.com/ikajdan/reflow_hot_plate/assets/28950897/a9347d3d-248d-4953-bed5-8ff7e9e12626" width="30%"></img>
<img src="https://github.com/ikajdan/reflow_hot_plate/assets/28950897/901e2f82-cec4-45c8-be06-c0374f554270" width="30%"></img>
<img src="https://github.com/ikajdan/reflow_hot_plate/assets/28950897/b9648db5-6c5c-4180-8398-41f9e938b2ea" width="30%"></img>
<img src="https://github.com/ikajdan/reflow_hot_plate/assets/28950897/4947a20e-c97b-49a8-8e7f-02202b682c66" width="30%"></img>

## License

This project is licensed under the [MIT License](LICENSE.md), which means you are free to use, modify, and distribute the project's source code and documentation for both commercial and non-commercial purposes.
