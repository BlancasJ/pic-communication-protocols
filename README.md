# PIC Microcontroller Communication Protocols

Collection of inter-microcontroller communication implementations using I2C, UART, and WiFi (ESP8266). Each subfolder demonstrates a different protocol with sender-receiver pairs. Proteus simulation files allow testing without hardware.

## Context
- **Date:** 2018
- **Institution:** Universidad Politecnica de Yucatan (UPY)
- **Course/Event:** Microcontrollers
- **Type:** University Project

## What It Does
Implements multiple communication protocols between PIC18F4550 microcontrollers. Each example includes separate sender and receiver code designed to run on two PICs connected via I2C bus or UART serial. The WiFi example bridges a PIC to an ESP8266 module using AT commands.

## Hardware Components

| Component | Purpose |
|-----------|---------|
| PIC18F4550 (x2) | Master and slave microcontrollers |
| LCD 16x2 | Displays received data on the slave side |
| LM35 temperature sensor | Temperature source for I2C/UART temperature examples |
| 4x4 matrix keyboard | Input device for multi-slave keyboard example |
| ESP8266 WiFi module | WiFi bridge via UART AT commands |

## Tech Stack
- CCS C compiler (ccsinfo.com)
- PIC18F4550 (8MHz internal oscillator)
- I2C (SDA=B0, SCL=B1, slow mode)
- UART (9600 baud)
- Proteus (circuit simulation)

## How to Run
Compile `.c` files with CCS C compiler. Load the generated `.hex` to each PIC via PIC programmer (PICkit 3). For simulation, open `.pdsprj` files in Proteus.

## Files

### `i2c/` — I2C Communication

| Subfolder | Master does | Slave does |
|-----------|------------|------------|
| `temperature/` (v1) | Reads LM35 every 20ms via timer, sends to slave (addr 0xa0) | Receives ADC value, converts to Celsius (x0.4882), displays on LCD |
| `temperature/` (v2) | Polls 6 buttons (RA0-RA5), queries 6 temperature slaves | 6 slaves each read LM35 and respond with temperature |
| `temperature/` (v3) | PIC16F877 master writes/reads 7-byte buffer at 100kHz fast I2C | PIC16F877 slave with buffered transmission |
| `multi-slave-keyboard/` | Reads 4x4 keyboard, queries different slaves (0xa0-0xc0) based on key pressed | Slave1 returns temperature, Slave2 uses SSP interrupt with buffer management |
| `letter-exchange/` | Sends letters A-Z cyclically every 20ms | Receives letter and displays on LCD |
| `button-query/` | Button B6 queries slave 0xa0 (temperature), button B7 queries slave 0xb0 | Returns sensor data on request |

### `uart/` — UART Serial Communication

| Subfolder | Sender does | Receiver does |
|-----------|------------|--------------|
| `temperature/` | Reads LM35 every ~800ms, sends formatted temperature float at 9600 baud | Displays received temperature on LCD |
| `word/` | Sends multi-character strings via UART | Reconstructs strings and validates with strcmp |
| `password/` | Sends 10 fake passwords + correct one ("5897") via timer interrupts | Validates with switch statement, displays "Correct"/"Incorrect" on LCD |
| `letter/` | Sends A-Z every 100ms | Displays received letter on LCD |
| `single-char-echo/` | Sends A-Z cyclically, also receives and displays | Bidirectional character exchange |
| `string-compare/` | Compares strings via timer interrupt using strcmp | Displays comparison result on LCD |
| `usb-echo/` | — | Receives characters from PC via RS232, echoes them back |
| `greeting/` | Sends "Que onda?" and "What's up?" alternating | Receives and displays on LCD |
| `port-monitor/` | Reads 4 bits from Port A, sends via UART with Timer3 | — |
| `command-parser/` | — | Parses serial commands, controls pin A4 |
| `basic-toggle/` | Timer3-driven UART test with pin D1 toggle | — |
| `rs232-transceiver/` | RS232 test with USB bootloader, temperature + WiFi attempt | — |

### `wifi/` — WiFi Communication

| File | What it does |
|------|-------------|
| `esp8266-at-commands.c` | Sends AT commands to ESP8266 via UART, searches for "OK" response using custom substring search function. Proof-of-concept for PIC-to-WiFi bridge |

### `proteus/` — Circuit Simulations

| Subfolder | Simulates |
|-----------|-----------|
| `i2c/` | Basic I2C master-slave communication |
| `i2c-multi-slave/` | I2C with multiple slave addresses |
| `i2c-six-slave/` | I2C with 6 temperature slaves |
| `temperature/` | I2C temperature sensor reading |
| `uart-temperature/` | UART temperature send/receive pair |
| `read-period/` | AC period measurement |
