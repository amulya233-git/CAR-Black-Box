#ifndef SCI_H
#define SCI_H

// UART pins
#define RX_PIN      TRISC7   // UART receive pin (RC7) configured via TRISC
#define TX_PIN      TRISC6   // UART transmit pin (RC6) configured via TRISC

// Function prototypes

void init_uart(void); // Initialize UART module (baud rate, TX/RX enable, etc.)

void putch(unsigned char byte); 
// Send a single byte over UART

int puts(const char *s); 
// Send a null-terminated string over UART

unsigned char getch(void); 
// Receive a single byte from UART (blocking)

unsigned char getch_with_timeout(unsigned short max_time); 
// Receive a single byte with a timeout; returns after max_time if no data

unsigned char getche(void); 
// Receive a single byte and echo it back via UART

#endif
