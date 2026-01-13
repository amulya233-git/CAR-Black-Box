#include "main.h"

/* Function to read a byte from the internal EEPROM */
unsigned char read_internal_eeprom(unsigned char addr)
{
    EEADR = addr;       // Load the EEPROM address to read from

    EEPGD = 0;          // Select EEPROM memory (0 = Data EEPROM, 1 = Program memory)
    CFGS = 0;           // Access EEPROM, not configuration registers
    WREN = 0;           // Ensure write is disabled (read operation)
    RD   = 1;           // Start EEPROM read
    return EEDATA;      // Return the data read from EEPROM
}

/* Function to write a byte to the internal EEPROM */
void write_internal_eeprom(unsigned char addr, unsigned char data)
{
    EEADR = addr;       // Load the EEPROM address to write to
    EEDATA = data;      // Load the data to write

    EEPGD = 0;          // Select EEPROM memory
    CFGS = 0;           // Access EEPROM, not configuration registers
    WREN = 1;           // Enable write to EEPROM

    GIE = 0;            // Disable global interrupts during write sequence

    EECON2 = 0x55;      // Required unlock sequence step 1
    EECON2 = 0xAA;      // Required unlock sequence step 2
    WR = 1;             // Start write operation

    GIE = 1;            // Re-enable global interrupts

    while(WR);          // Wait until write completes (WR bit clears)
}
