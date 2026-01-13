#include "main.h"

void init_mkp(void)
{
    // Configure rows (RB0-RB2) as output (R1-R3)
    TRISB = TRISB & 0x1F;  // 0b00011111 -> RB0-RB4 output, others keep original (RB3-RB7 inputs)

    // Configure columns (RB1-RB4) as input (C1-C4)
    TRISB = TRISB | 0x1E;  // 0b00011110 -> set RB1-RB4 as inputs

    // Enable PORTB internal pull-ups
    RBPU = 0;
}

// Scan the keypad and return which key is pressed
unsigned char scan_key(void)
{
    // Scan first row (R1=0, R2=R3=1)
    R1 = 0;
    R2 = 1;
    R3 = 1;

    if(C1 == 0) return SW1;   // first column low -> SW1 pressed
    if(C2 == 0) return SW4;
    if(C3 == 0) return SW7;
    if(C4 == 0) return SW10;

    // Scan second row (R2=0, R1=R3=1)
    R1 = 1;
    R2 = 0;
    R3 = 1;

    if(C1 == 0) return SW2;
    if(C2 == 0) return SW5;
    if(C3 == 0) return SW8;
    if(C4 == 0) return SW11;

    // Scan third row (R3=0, R1=R2=1)
    R1 = 1;
    R2 = 1;
    R3 = 0;
    R3 = 0; // Give sufficient time for row to settle

    if(C1 == 0) return SW3;
    if(C2 == 0) return SW6;
    if(C3 == 0) return SW9;
    if(C4 == 0) return SW12;

    // If no key pressed, return ALL_RELEASED
    return ALL_RELEASED;
}

// Read the keypad based on detection type
unsigned char read_matrix_keypad(unsigned char detection_type)
{
    static int once = 1;  // Ensure single detection for STATE detection
    unsigned char key;

    if(detection_type == LEVEL)
    {
        // LEVEL detection: continuously return the key as long as pressed
        return scan_key();
    }
    else if(detection_type == STATE)
    {
        // STATE detection: return key only once per press
        key = scan_key();
        if( key != ALL_RELEASED && once)
        {
            once = 0;  // Key has been detected, block repeated detection
            return key;
        }
        if(key == ALL_RELEASED)
            once = 1;  // Reset for next key press
    }

    // If no key or already returned in STATE detection
    return ALL_RELEASED;
}
