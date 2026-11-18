# Smart Parking System Using ESP32

## 1. Project Overview
The Smart Parking System is an embedded system designed to detect vehicle presence in parking slots using an ESP32 microcontroller and ultrasonic sensors.

## 2. Objectives
- Detect vehicle presence in parking slots.
- Monitor parking slot availability.
- Identify occupied and empty parking slots.

## 3. Hardware Components
- ESP32 Wi-Fi Microcontroller
- HC-SR04 Ultrasonic Sensors (2)
- Jumper Wires
- Breadboard
- Power Supply

## 4. Software and Tools
- Arduino IDE
- GitHub

## 5. Working Principle
The HC-SR04 ultrasonic sensors measure the distance between the sensor and the vehicle. If the measured distance is less than 7 cm, the parking slot is considered occupied. Otherwise, the slot is considered empty.

## 6. Quality Assurance
The system will be tested for:
- Incorrect vehicle detection
- Sensor reading errors
- Incorrect parking slot status
- ESP32 connection problems

## 7. Project Documentation
This repository contains ESP32 source code, circuit diagram, QA issues, testing details and project planning information.
