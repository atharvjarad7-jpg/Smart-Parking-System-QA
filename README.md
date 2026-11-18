# Smart Parking System Using Arduino UNO and ESP32

## 1. Project Overview
The Smart Parking System is an IoT-based project designed to monitor parking slot availability using ultrasonic sensors and an ESP32 microcontroller.

## 2. Objectives
- Detect vehicle presence in parking slots.
- Monitor available parking slots.
- Display real-time parking status using Blynk IoT.

## 3. Hardware Components
- Arduino UNO
- ESP32 Wi-Fi Microcontroller
- HC-SR04 Ultrasonic Sensors (2)
- Breadboard
- Jumper Wires
- Power Supply

## 4. Software and Tools
- Arduino IDE
- Blynk IoT Platform
- GitHub

## 5. Working Principle
The ultrasonic sensors measure the distance between the sensor and the vehicle. If the distance is less than 7 cm, the slot is considered occupied. The ESP32 sends parking status to the Blynk dashboard through Wi-Fi.

## 6. Quality Assurance
The project will be tested for:
- Incorrect vehicle detection
- Sensor reading errors
- Wi-Fi connectivity problems
- Incorrect Blynk dashboard updates

## 7. Project Documentation
This repository contains source code, QA issues, testing details and project planning information.
