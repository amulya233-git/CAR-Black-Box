#ifndef MAIN_H
#define MAIN_H

#include <xc.h>           // Include PIC microcontroller specific definitions
#include "clcd.h"         // Include LCD driver header
#include "mkp.h"          // Include matrix keypad driver
#include "adc.h"          // Include ADC module driver
#include "eeprom.h"       // Include internal EEPROM read/write functions
#include "ds1307.h"       // Include DS1307 RTC driver
#include "ext_eeprom.h"   // Include external EEPROM read/write functions
#include "i2c.h"          // Include I2C communication driver
#include "uart.h"         // Include UART serial communication driver

// Define all possible states/modes of the system
enum mode
{
    e_view,       // State to view logs on LCD
    e_download,   // State to download logs to serial console
    e_clear,      // State to clear logs
    e_set_time,   // State to set RTC time
    e_Dashboard,  // State for the car dashboard display
    e_menu        // State to display the main menu
};

// Function prototypes for all main functionalities
void dashboard(void);       // Display current speed, gear, EV status
void view(void);            // View logs on CLCD
void download_log(void);    // Download logs to UART
void clear_log(void);       // Clear logs in EEPROM
void set_time(void);        // Set RTC time
void menu(void);            // Display main menu and handle input
void get_time(void);        // Read time from RTC
void display_time(void);    // Display time on CLCD

#endif  /* MAIN_H */
