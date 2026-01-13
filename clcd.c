#include "main.h"

// Function to write a byte to the CLCD
void clcd_write(unsigned char byte, unsigned char control_bit)
{
    CLCD_RS = control_bit;      // Set RS: 0=Instruction, 1=Data
    CLCD_PORT = byte;           // Put data/command on CLCD data port

    /* Enable pulse should be at least 200ns */
    CLCD_EN = HI;               // Set EN high to latch data
    CLCD_EN = LO;               // Set EN low to complete the write

    PORT_DIR = INPUT;            // Set port direction to input for busy flag reading
    CLCD_RW = HI;               // Set RW high to read busy flag
    CLCD_RS = INSTRUCTION_COMMAND; // RS = 0 to read instruction

    do
    {
        CLCD_EN = HI;           // Pulse EN to read busy flag
        CLCD_EN = LO;
    } while (CLCD_BUSY);         // Wait until CLCD is ready

    CLCD_RW = LO;               // Set RW low back to write mode
    PORT_DIR = OUTPUT;           // Set port direction back to output
}

// Function to initialize the CLCD
void init_clcd()
{
    TRISD = 0x00;               // Set PortD as output for CLCD data
    TRISC = TRISC & 0xF8;       // Set first 3 bits of PortC as output for control

    CLCD_RW = LO;               // Set RW low (write mode)

    /* Startup delay for CLCD controller */
    __delay_ms(30);

    /* CLCD startup sequence - 8-bit mode initialization */
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND);
    __delay_us(4100);           // Wait 4.1 ms
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND);
    __delay_us(100);            // Wait 100 us
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND);
    __delay_us(1);              // Wait 1 us

    CURSOR_HOME;                // Move cursor to home
    __delay_us(100);
    TWO_LINE_5x8_MATRIX_8_BIT; // Set 2 lines, 5x8 font
    __delay_us(100);
    CLEAR_DISP_SCREEN;          // Clear display
    __delay_us(500);
    DISP_ON_AND_CURSOR_OFF;     // Display ON, cursor OFF
    __delay_us(100);
}

// Function to print a string at a specific address on CLCD
void clcd_print(const unsigned char *data, unsigned char addr)
{
    clcd_write(addr, INSTRUCTION_COMMAND); // Move cursor to address
    while (*data != '\0')
    {
        clcd_write(*data++, DATA_COMMAND); // Write characters one by one
    }
}

// Function to print a single character at a specific address
void clcd_putch(const unsigned char data, unsigned char addr)
{
    clcd_write(addr, INSTRUCTION_COMMAND); // Move cursor to address
    clcd_write(data, DATA_COMMAND);        // Write single character
}
