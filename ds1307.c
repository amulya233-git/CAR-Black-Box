#include "main.h"

/* 
 * DS1307 Slave address modes
 * D0  - Write Mode
 * D1  - Read Mode
 */

void init_ds1307(void)
{
    unsigned char dummy;

    /* Stop the clock by setting CH (Clock Halt) bit in seconds register */
    dummy = read_ds1307(SEC_ADDR);          // Read current seconds register
    write_ds1307(SEC_ADDR, dummy | 0x80);  // Set CH bit (MSB) to 1 -> Stop clock

    /* Set 12-hour format by setting 12/24 hr bit in hour register */
    dummy = read_ds1307(HOUR_ADDR);        // Read current hour register
    write_ds1307(HOUR_ADDR, dummy | 0x40); // Set 12-hour mode (bit 6)

    /* 
     * Configure Control Register of DS1307:
     * Bit 7 - OUT
     * Bit 6 - 0
     * Bit 5 - OSF (Oscillator Stop Flag)
     * Bit 4 - SQWE (Square Wave Enable)
     * Bit 3 - 0
     * Bit 2 - 0
     * Bit 1 - RS1
     * Bit 0 - RS0
     * 
     * Set RS1 and RS0 = 11 to output square wave at 32.768 KHz
     */ 
    write_ds1307(CNTL_ADDR, 0x93); // 0x93 sets SQWE and RS1/RS0 as 11

    /* Start the clock by clearing the CH bit */
    dummy = read_ds1307(SEC_ADDR);         // Read seconds register
    write_ds1307(SEC_ADDR, dummy & 0x7F); // Clear CH bit (MSB) -> Start clock
}

/* Write data to DS1307 register */
void write_ds1307(unsigned char address, unsigned char data)
{
    i2c_start();            // Send I2C start condition
    i2c_write(SLAVE_WRITE); // Send DS1307 slave address with Write bit
    i2c_write(address);     // Send register address to write to
    i2c_write(data);        // Send data to the register
    i2c_stop();             // Send I2C stop condition
}

/* Read data from DS1307 register */
unsigned char read_ds1307(unsigned char address)
{
    unsigned char data;

    i2c_start();             // Start I2C
    i2c_write(SLAVE_WRITE);  // Send DS1307 slave address with Write bit
    i2c_write(address);      // Send register address to read from
    i2c_rep_start();         // Send repeated start for read operation
    i2c_write(SLAVE_READ);   // Send DS1307 slave address with Read bit
    data = i2c_read();       // Read data from register
    i2c_stop();              // Stop I2C

    return data;             // Return read value
}
