#ifndef EEPROM_H
#define EEPROM_H

/* Function to read a byte from internal EEPROM at a given address */
unsigned char read_internal_eeprom(unsigned char addr);

/* Function to write a byte to internal EEPROM at a given address */
void write_internal_eeprom(unsigned char addr, unsigned char data);

#endif  /* EEPROM_H */
