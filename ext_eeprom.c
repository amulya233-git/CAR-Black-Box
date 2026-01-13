#include "main.h"

/* 
 * Function to write a byte to external EEPROM using I2C
 * address: memory location in EEPROM
 * data   : byte to write
 */
void write_ext_eeprom(unsigned char address, unsigned char data)
{
    i2c_start();          // Send I2C start condition
    i2c_write(SLAVE_WRITE); // Send EEPROM slave address with write bit (D0 = 0)
    i2c_write(address);     // Send memory address in EEPROM where data will be written
    i2c_write(data);        // Send the actual data byte
    i2c_stop();             // Send I2C stop condition to end transmission
    for(unsigned int i=3000;i--;) ; // Small delay to ensure EEPROM write completes
}

/* 
 * Function to read a byte from external EEPROM using I2C
 * address: memory location in EEPROM to read from
 * Returns the byte read from EEPROM
 */
unsigned char read_ext_eeprom(unsigned char address)
{
    unsigned char data;

    i2c_start();             // Send I2C start condition
    i2c_write(SLAVE_WRITE);  // Send EEPROM slave address with write bit to set memory address
    i2c_write(address);      // Send memory address to read
    i2c_rep_start();         // Send repeated start condition (switch to read mode)
    i2c_write(SLAVE_READ);   // Send EEPROM slave address with read bit (D1 = 1)
    data = i2c_read();       // Read the data byte from EEPROM
    i2c_stop();              // Send I2C stop condition

    return data;             // Return the read data
}
