/*
 * File:   main.c
 * Author: hirosuke1214
 *
 * Created on 2025/09/24, 12:26
 */

// PIC12F683 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Detect (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 8000000 // Xtal frequency for __delta_ms(x).

void initializeGPIO()
{
    GPIO = 0;   // Clear GPIO register.
    CMCON0 = 0b111;  // GP0-2 use I/O.
    ANSEL = 0;  // AN0-2 use digital I/O.
    TRISIO = 0b00001000; // GP0-5 use output. GP3 only input.
    OSCCON = 0b01110000;    // Clock Frequency is 8MHz. Clock source configured FOSC register.
}

void main(void)
{
    initializeGPIO();
    
    while(1)
    {
        GP2 = !GP2;
        __delay_ms(300);
    }
    
    return;
}