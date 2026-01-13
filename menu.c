#include "main.h"

// External variables to track system state and key press
extern char state = e_Dashboard, key;  
char j, s_f;  // j = menu index (0..3), s_f = selector flag for top/bottom line

void menu()
{
    // Menu text options, each string fits 16 characters for CLCD
    char menu[][17] = {"View log    ", "Download log", "Clear log   ", "Set time    "};

    // Display two menu items at a time
    if(j < 3)
    {
        clcd_print(menu[j], LINE1(2));      // Print current menu item on line1 starting at pos 2
        clcd_print(menu[j+1], LINE2(2));    // Print next menu item on line2 starting at pos 2
    }

    // Display selector '*' to show which menu item is currently selected
    if(s_f == 0)
    {
        clcd_print("*", LINE1(0));  // Top line selected
        clcd_print(" ", LINE2(0));  // Clear selector on bottom line
    }
    else
    {
        clcd_print(" ", LINE1(0));  // Clear selector on top line
        clcd_print("*", LINE2(0));  // Bottom line selected
    }

    // Navigate menu with SW1 (up) and SW2 (down)
    if(key == SW2)  // Down pressed
    {
        if(s_f == 0)
            s_f = 1;     // Move selector to bottom line
        else if(j < 2)
            j++;         // Scroll menu down if possible
    }
    else if(key == SW1) // Up pressed
    {
        if(s_f == 1)
            s_f = 0;     // Move selector to top line
        else if(j > 0)
            j--;         // Scroll menu up if possible
    }

    // Confirm selection with SW4
    if(key == SW4)
    {
        CLEAR_DISP_SCREEN;               // Clear CLCD
        // Change state based on selected menu item
        if(j + s_f == 0) state = e_view;
        else if(j + s_f == 1) state = e_download;
        else if(j + s_f == 2) state = e_clear;
        else if(j + s_f == 3) state = e_set_time;
    }
    else if(key == SW5)  // Cancel/Exit menu
    {
        CLEAR_DISP_SCREEN;
        state = e_Dashboard;  // Return to dashboard display
    }
}
