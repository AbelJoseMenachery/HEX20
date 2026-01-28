📘 README.md
Timer-Based Multi-Channel ADC Data Acquisition (Arduino)
🧠 Overview

This project demonstrates periodic ADC sampling using a hardware timer interrupt on an Arduino (ATmega328P).
Four analog channels are sampled at fixed time intervals, timestamped, and transmitted as a structured data packet over UART.

The implementation avoids delay() and polling-based timing, focusing instead on deterministic, interrupt-driven embedded design.
