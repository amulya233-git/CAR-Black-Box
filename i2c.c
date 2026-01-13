#include "main.h"

/* Initialize I2C in Master Mode */
void init_i2c(void)
{
    /* Set SCL (RC3) and SDA (RC4) pins as inputs */
    TRISC3 = 1;  
    TRISC4 = 1;  

    /* Configure SSP module for I2C Master mode */
    SSPCON1 = 0x28;  

    /* Set the clock frequency (depends on Fosc) */
    SSPADD = 0x31;  

    /* Disable slew rate control for standard speed */
    CKE = 0;  

    /* Enable SMP for standard speed sampling */
    SMP = 1;  

    /* Clear SSP interrupt flag */
    SSPIF = 0;  

    /* Clear bus collision interrupt flag */
    BCLIF = 0;  
}

/* Wait for I2C operation to complete */
void i2c_idle(void)
{
    while (!SSPIF);  // Wait until SSPIF is set
    SSPIF = 0;       // Clear the flag
}

/* Check acknowledge after write */
void i2c_ack(void)
{
    if (ACKSTAT)  // If ACK not received
    {
        // Optional: print error/debug message
    }
}

/* Generate Start condition */
void i2c_start(void)
{
    SEN = 1;      // Start condition enabled
    i2c_idle();   // Wait for completion
}

/* Generate Stop condition */
void i2c_stop(void)
{
    PEN = 1;      // Stop condition enabled
    i2c_idle();   // Wait for completion
}

/* Generate Repeated Start condition */
void i2c_rep_start(void)
{
    RSEN = 1;     // Repeated start enabled
    i2c_idle();   // Wait for completion
}

/* Write a byte on I2C bus */
void i2c_write(unsigned char data)
{
    SSPBUF = data;  // Load data into SSPBUF
    i2c_idle();     // Wait until transmission is complete
}

/* Enable Receive mode */
void i2c_rx_mode(void)
{
    RCEN = 1;      // Enable receive mode
    i2c_idle();    // Wait for reception
}

/* Send No-Acknowledge after read */
void i2c_no_ack(void)
{
    ACKDT = 1;     // 1 = NACK, 0 = ACK
    ACKEN = 1;     // Enable acknowledge sequence
}

/* Read a byte from I2C bus */
unsigned char i2c_read(void)
{
    i2c_rx_mode(); // Enable receive mode
    i2c_no_ack();  // Send NACK after reading last byte

    return SSPBUF; // Return received byte
}
