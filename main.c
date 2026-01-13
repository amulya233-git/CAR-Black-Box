#include "main.h"

// Initialize global time string
char time[9] = "00:00:00"; // default time at startup

// Function to initialize all peripherals
void init_config()
{
    init_clcd();      // initialize character LCD
    init_adc();       // initialize ADC module
    init_mkp();       // initialize matrix keypad
    init_uart();      // initialize UART for serial communication
    init_i2c();       // initialize I2C for RTC & EEPROM
    init_ds1307();    // initialize DS1307 RTC
}

// Global state and key variables
char state = e_Dashboard;  // initial state is dashboard
char key;                   // stores pressed key

// Main program
void main(void) 
{  
    init_config(); // initialize all hardware modules
    
    while(1) // infinite loop for main program
    {
        key = read_matrix_keypad(STATE); // read the current key pressed
        
        // Execute functionality based on current state
        switch(state)
        {
            case e_Dashboard : 
                dashboard(); // show dashboard with speed, gear, and EV
                break;

            case e_menu : 
                menu();      // show main menu options
                break; 

            case e_view : 
                view();      // view stored logs
                break;

            case e_download : 
                download_log(); // download logs to console
                break;

            case e_clear : 
                clear_log(); // clear all logs from EEPROM
                break;

            case e_set_time : 
                set_time();  // set RTC time
                break;
        }
    }
}
