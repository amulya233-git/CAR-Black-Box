// Detection modes
#define LEVEL           0   // LEVEL detection: key is read continuously while pressed
#define STATE           1   // STATE detection: key is read once per press until released

// Keypad row pins (outputs)
#define R1              RB5  // Row 1 connected to PORTB pin 5
#define R2              RB6  // Row 2 connected to PORTB pin 6
#define R3              RB7  // Row 3 connected to PORTB pin 7

// Keypad column pins (inputs)
#define C1              RB1  // Column 1 connected to PORTB pin 1
#define C2              RB2  // Column 2 connected to PORTB pin 2
#define C3              RB3  // Column 3 connected to PORTB pin 3
#define C4              RB4  // Column 4 connected to PORTB pin 4

// No key pressed
#define ALL_RELEASED    0x00  // Returned by scan_key() when no key is pressed

// Key definitions (mapping of keys to SW1–SW12)
#define SW1             1
#define SW2             2
#define SW3             3
#define SW4             4
#define SW5             5
#define SW6             6
#define SW7             7
#define SW8             8
#define SW9             9
#define SW10            10
#define SW11            11
#define SW12            12

// Function prototypes
void init_mkp(void);   // Initialize the keypad pins (rows as output, columns as input)
unsigned char read_matrix_keypad(unsigned char detection_type); // Read key based on detection type
unsigned char scan_key(void);  // Scan the keypad and return which key is pressed
