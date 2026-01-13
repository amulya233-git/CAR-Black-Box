#ifndef Ds1307_H
#define Ds1307_H

/* I2C Slave addresses for DS1307 */
#define SLAVE_READ      0xD1    // Slave address + Read bit (1)
#define SLAVE_WRITE     0xD0    // Slave address + Write bit (0)

/* DS1307 Register Addresses */
#define SEC_ADDR        0x00    // Seconds register
#define MIN_ADDR        0x01    // Minutes register
#define HOUR_ADDR       0x02    // Hours register
#define DAY_ADDR        0x03    // Day of the week register
#define DATE_ADDR       0x04    // Date of the month register
#define MONTH_ADDR      0x05    // Month register
#define YEAR_ADDR       0x06    // Year register
#define CNTL_ADDR       0x07    // Control register (for square wave, etc.)

/* Function prototypes */

/* Initialize the DS1307 RTC */
void init_ds1307(void);

/* Write a value to a specific register of DS1307 */
void write_ds1307(unsigned char address1, unsigned char data);

/* Read a value from a specific register of DS1307 */
unsigned char read_ds1307(unsigned char address1);

#endif
