#ifndef EXT_EEPROM_H
#define EXT_EEPROM_H

// I2C EEPROM slave address with R/W bits
#define SLAVE_READ      0xA1   // EEPROM read mode (D0 = 1)
#define SLAVE_WRITE     0xA0   // EEPROM write mode (D0 = 0)

// Function prototype to write a byte to external EEPROM
// address1 : EEPROM memory location
// data     : byte to write
void write_ext_eeprom(unsigned char address1,  unsigned char data);

// Function prototype to read a byte from external EEPROM
// address1 : EEPROM memory location
// Returns the byte read from EEPROM
unsigned char read_ext_eeprom(unsigned char address1);

#endif
