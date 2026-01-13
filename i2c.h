#ifndef I2C_H
#define I2C_H

/* Initialize I2C module in Master Mode */
void init_i2c(void);

/* Generate a Start condition on I2C bus */
void i2c_start(void);

/* Generate a Repeated Start condition on I2C bus */
void i2c_rep_start(void);

/* Generate a Stop condition on I2C bus */
void i2c_stop(void);

/* Write a byte of data on I2C bus */
void i2c_write(unsigned char data);

/* Read a byte of data from I2C bus */
unsigned char i2c_read(void);

#endif
