#ifndef ADC_H           // Header guard start: Check if ADC_H is not defined
#define ADC_H           // Define ADC_H to prevent multiple inclusion

// Define ADC channels with readable names
#define CHANNEL0		0x00   // ADC channel 0
#define CHANNEL1		0x01   // ADC channel 1
#define CHANNEL2		0x02   // ADC channel 2
#define CHANNEL3		0x03   // ADC channel 3
#define CHANNEL4		0x04   // ADC channel 4
#define CHANNEL5		0x05   // ADC channel 5
#define CHANNEL6		0x06   // ADC channel 6
#define CHANNEL7		0x07   // ADC channel 7
#define CHANNEL8		0x08   // ADC channel 8
#define CHANNEL9		0x09   // ADC channel 9
#define CHANNEL10		0x0A   // ADC channel 10

// Function prototype to initialize ADC hardware
void init_adc(void);    // No input, sets up ADC registers, reference voltage, etc.

// Function prototype to read ADC value from a given channel
unsigned short read_adc(unsigned char channel);  
// Input: channel (0-10), Output: ADC digital value (e.g., 0-1023 for 10-bit ADC)

#endif   // End of header guard
