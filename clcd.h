#ifndef LCD_H
#define LCD_H

/* Define the port and pins connected to the CLCD */
#define CLCD_PORT       PORTD   // Data port connected to LCD
#define CLCD_EN         RC2     // Enable pin
#define CLCD_RS         RC1     // Register select (0=command, 1=data)
#define CLCD_RW         RC0     // Read/Write pin (0=write, 1=read)
#define CLCD_BUSY       RD7     // Busy flag pin (reads if LCD is busy)
#define PORT_DIR        TRISD7  // Direction control for the port (input/output)

/* Define logic levels for convenience */
#define HI              1       // Logic high
#define LO              0       // Logic low

/* Define port directions */
#define INPUT           0xFF    // All bits input
#define OUTPUT          0x00    // All bits output

/* Define command/data selection */
#define DATA_COMMAND        1   // When RS=1, sending data
#define INSTRUCTION_COMMAND 0   // When RS=0, sending command

/* Define oscillator frequency for delay calculations */
#define _XTAL_FREQ      20000000    // 20 MHz crystal frequency

/* LCD line addresses */
#define LINE1(x)        (0x80 + (x)) // Address for 1st line + offset
#define LINE2(x)        (0xC0 + (x)) // Address for 2nd line + offset

/* LCD command macros for convenience */
#define TWO_LINE_5x8_MATRIX_8_BIT   clcd_write(0x38, INSTRUCTION_COMMAND) // Function set: 2 lines, 5x8 font, 8-bit mode
#define CLEAR_DISP_SCREEN            clcd_write(0x01, INSTRUCTION_COMMAND) // Clear display
#define CURSOR_HOME                  clcd_write(0x02, INSTRUCTION_COMMAND) // Move cursor to home position
#define DISP_ON_AND_CURSOR_OFF       clcd_write(0x0C, INSTRUCTION_COMMAND) // Display ON, cursor OFF
#define EIGHT_BIT_MODE               0x33 // Initialization sequence value for 8-bit mode

/* Function prototypes */
void init_clcd(void);                                       // Initialize the CLCD
void clcd_print(const unsigned char *data, unsigned char addr); // Print a string at given address
void clcd_putch(const unsigned char data, unsigned char addr);  // Print a single character at given address
void clcd_write(unsigned char bit_values, unsigned char control_bit); // Write a byte to CLCD

#endif
