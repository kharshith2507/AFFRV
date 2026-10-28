
# AFFRV | Autonomous Fire Fighting Robotic Vehicle

An ESP32-based autonomous fire-fighting robotic vehicle developed as part of the Engineering Clinics (ECS2003) course at VIT-AP University.

## Project Overview

AFFRV is a four-wheel robotic prototype designed to detect flames, respond through programmed motor movements, activate a water pump, and support manual operation through Bluetooth.

## Hardware Components

- ESP32 DevKit
- 3 IR Flame Sensor Modules
- 2 L298N Motor Driver Modules
- 4 DC Gear Motors
- MQ-2 Gas Sensor
- DHT11 Temperature and Humidity Sensor
- Water Pump and Water Container
- Buzzer
- Separate ESP32-CAM Board
- 18650 Battery Holder

## Implemented Features

- Three-direction flame detection
- Automatic fire-response sequence
- Buzzer alert
- Bluetooth-based manual control
- Motor movement and pump control
- Gas and temperature monitoring through Serial Monitor
- Separate ESP32-CAM video streaming program

## Repository Structure

- `Main_ESP32_Controller/` - Main robot firmware
- `ESP32_CAM/` - Separate camera streaming firmware

## Bluetooth Commands

| Command | Function |
|---|---|
| 1 | Automatic Mode |
| 2 | Manual Mode |
| 3 | Forward |
| 4 | Reverse |
| 5 | Left |
| 6 | Right |
| 7 | Stop |
| 8 | Pump ON |
| 9 | Pump OFF |

## Development Team

1. Kandregula Harshith
2. Jonnalagadda Pragneswar
3. Kolisetty Sai Sathvik
4. Tavva Jaasmitha Sree
5. Mandadi Hima Bhargavi
6. Lokavarapu Keerthana

## Institution

VIT-AP University  
School of Engineering  
Course: Engineering Clinics (ECS2003)  
Project ID: AFFRV

## Important Note

This project is an academic engineering prototype developed for laboratory demonstration. It is not a certified fire-safety or industrial fire-fighting system.
