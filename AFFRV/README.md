# AFFRV-01 | Autonomous Fire Fighting Robotic Vehicle

An ESP32-based academic fire-fighting robot prototype developed for Engineering Clinics (ECS2003), VIT-AP University.

## Firmware files

This repository contains **two separate Arduino sketches**. They run on separate boards and must be uploaded independently.

### 1. Main ESP32 controller
Path: `Main_ESP32_Controller/AFFRV_Main.ino`

Controls the robot's three flame sensors, four-wheel motor drive through two L298N modules, buzzer, water-pump output, Bluetooth manual commands, and MQ-2/DHT11 monitoring.

### 2. ESP32-CAM
Path: `ESP32_CAM/AFFRV_CAM.ino`

Runs independently on an AI-Thinker ESP32-CAM board. It creates its own Wi-Fi access point and serves an MJPEG camera stream. As described in the project report, it is **not connected to or communicating with the main ESP32 controller**.

## Hardware

**Main controller**
- ESP32 DevKit
- 3 IR flame sensor modules
- 2 L298N motor-driver modules
- 4 DC gear motors
- MQ-2 gas sensor
- DHT11 temperature/humidity sensor
- Water pump, container and delivery tube
- Buzzer

**Camera unit**
- AI-Thinker ESP32-CAM board

## Main ESP32 GPIO mapping

| Function | GPIO |
|---|---:|
| Flame Sensor 1 | 15 |
| Flame Sensor 2 | 4 |
| Flame Sensor 3 | 17 |
| DHT11 data | 16 |
| MQ-2 analog output | 32 |
| Motor direction outputs | 19, 21, 22, 23 |
| Water pump control | 25 |
| Buzzer | 26 |

## Bluetooth commands

| Command | Function |
|---|---|
| 1 | Automatic mode |
| 2 | Manual mode |
| 3 | Forward |
| 4 | Reverse |
| 5 | Left |
| 6 | Right |
| 7 | Stop |
| 8 | Pump ON |
| 9 | Pump OFF |

Bluetooth device name: `ESP32_Fire_Robot`

## Upload instructions

### Main ESP32
1. Open `Main_ESP32_Controller/AFFRV_Main.ino` in Arduino IDE.
2. Select the correct ESP32 DevKit board and COM port.
3. Install the `DHT sensor library` dependency.
4. Verify the wiring and power arrangement, then compile and upload.

### ESP32-CAM
1. Open `ESP32_CAM/AFFRV_CAM.ino` in Arduino IDE.
2. Select the AI Thinker ESP32-CAM board (and the appropriate upload settings).
3. Set `ap_password` to your own Wi-Fi access-point password (at least 8 characters).
4. Upload using the appropriate ESP32-CAM programming arrangement.
5. Open Serial Monitor at 115200 baud, connect your phone/computer to the camera access point, and open the IP address printed in Serial Monitor.

## Project team

1. Kandregula Harshith
2. Jonnalagadda Pragneswar
3. Kolisetty Sai Sathvik
4. Tavva Jaasmitha Sree
5. Mandadi Hima Bhargavi
6. Lokavarapu Keerthana

## Institution

VIT-AP University  
School of Engineering  
Engineering Clinics (ECS2003)  
Project ID: AFFRV-01

## Scope and safety

This is an academic laboratory prototype, not a certified fire-safety or industrial fire-fighting system. The main firmware uses fixed-duration movement and pump operation; it does not verify extinguishment or provide obstacle avoidance or safe-distance control. The ESP32-CAM sketch is a separate video-streaming program and does not perform fire detection.

## Source note

The two sketches were transcribed from Appendices A and B of the team's supplied final project report. PDF text extraction can introduce formatting issues; compare both files with the original working sketches and compile them for the exact target boards before submission. The camera access-point password is a placeholder and must be configured by the team.
