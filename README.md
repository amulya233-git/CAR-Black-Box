## Car Black Box

📌 **Description**
The Car Black Box is an embedded systems project developed in C that records and monitors critical vehicle parameters such as speed, gear position, and time. It logs events into EEPROM, displays real-time data on an LCD, and allows viewing, clearing, and downloading logs for analysis.

⚙️ **Features**

* Real-time speed measurement using ADC
* Time tracking using RTC (DS1307)
* Event and gear change logging
* Log storage in internal/external EEPROM
* View, clear, and download logs via UART
* LCD-based menu-driven interface

🛠 **Technologies Used**

* Language: Embedded C
* Microcontroller: PIC (XC8)
* Concepts: ADC, I2C, UART, EEPROM, RTC
* Tools: MPLAB X IDE, XC8 Compiler

📂 **Project Structure**
CarBlackBox/
├── main.c – Application control
├── *.c / *.h – Drivers and modules
├── README.md – Documentation

▶️ **Usage**

* Power on the system to start monitoring
* Use keypad to navigate menu options
* View, download, or clear stored logs

📚 **Learning Outcomes**

* Embedded peripheral interfacing
* EEPROM data logging techniques
* Menu-driven UI implementation
* Real-time system design

🚧 **Limitations**

* Console/LCD-based interface only
* Designed for educational use

👨‍💻 **Author**
Amulya M

📜 **License**
Open-source for educational use
