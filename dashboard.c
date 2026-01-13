#include "main.h"

// External variables from other modules
extern char time[9]; // Stores current time as string "HH:MM:SS"
extern char key;     // Stores the key pressed
char gear, address;  // Current gear and EEPROM address pointer
int count;           // Counter for storing data periodically
extern char state;   // Current state of the dashboard/menu

void dashboard()
{
    get_time();  // Function to update 'time' variable with current time

    // Event labels for different gear/states
    char ev[9][3] = {"ON","GR","GN","G1","G2","G3","G4","G5","CO"};

    char data[10];               // Array to store data to write to EEPROM
    unsigned short adc_reg_val;  // ADC value from speed sensor
    char speed, flag = 0;        // Calculated speed and flag to indicate gear change

    // Display headers on CLCD
    clcd_print("Time     EV   SP", LINE1(0));
    clcd_print(time, LINE2(0));  // Display current time on second line

    // Read ADC from channel 4 (speed sensor)
    adc_reg_val = read_adc(CHANNEL4);

    // Convert ADC value to speed (assumes scaling factor 10.33)
    speed = adc_reg_val / 10.33;

    // Display speed on CLCD (tens and units separately)
    clcd_putch((speed % 10) + '0', LINE2(15)); // Units place
    clcd_putch((speed / 10) + '0', LINE2(14)); // Tens place

    // Gear control using keys
    if (key == SW3)          // SW3 -> ignition or neutral
    {
        gear = 8;            // Set gear to "CO" or ignition ON
        flag++;
    }
    else if (key == SW1 && gear < 7) // SW1 -> increase gear
    {
        gear++;
        flag++;
    }
    else if (key == SW2 && (gear > 1 && gear < 8)) // SW2 -> decrease gear
    {
        gear--;
        flag++;
    }

    // Prevent illegal gear change beyond limits
    if (gear == 8 && (key == SW1 || key == SW2))
    {
        gear = 2; // Reset to first gear if trying to go beyond
    }

    // Display current event/gear on CLCD
    clcd_print(ev[gear], LINE2(9));

    // If gear was changed
    if (flag)
    {
        if (count < 10)
        {
            count++; // Increment counter
        }

        // Prepare data to store in EEPROM: HHMMSS + gear + speed
        data[0] = time[0]; data[1] = time[1];
        data[2] = time[3]; data[3] = time[4];
        data[4] = time[6]; data[5] = time[7];
        data[6] = ev[gear][0]; data[7] = ev[gear][1];
        data[8] = (speed / 10) + '0'; data[9] = (speed % 10) + '0';

        // Every 10th entry, shift EEPROM data to free space
        if (count == 10)
        {
            for (char i = 0; i < 90; i++)
            {
                write_ext_eeprom(i, read_ext_eeprom(i + 10));
            }
            address = 90; // Start writing new data at address 90
        }

        // Write new data to EEPROM
        for (char i = 0; i < 10; i++)
        {
            write_ext_eeprom(address++, data[i]);
        }
    }

    // If SW4 pressed, go to menu state
    if (key == SW4)
    {
        CLEAR_DISP_SCREEN;  // Clear CLCD
        state = e_menu;     // Change state to menu
    }
}
