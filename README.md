# atmega32-smart_home_project
Independently designed and developed a smart home system using AVR Atmega32 microcontroller and C programming language

Integrated various smart devices, including light bulbs, and thermostats, into a single system

Implemented a UART protocol using an HC-05 Bluetooth module for remote control of the system

Built two different modes for the system:

ADMIN MODE: Allows the administrator to control all system functions including controlling floor LEDs, dimmer circuits, DC motor for ceiling fan rotation, and servo motor for opening/closing the door. Additionally, the admin can add or drop users from the system and store user data in EEPROM to prevent data loss during system restarts.

USER MODE: Allows users to control all system functions except for opening/closing the door and adding themselves to the system.

Used an ADC and PWM to control the dimmer circuit and a temperature sensor to automatically turn on/off the DC motor for ceiling fan rotation based on room temperature.

Conducted testing and debugging to ensure proper functionality of the system.
