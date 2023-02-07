    /*
 * File:   config_EUSART.c
 * Author: Colin
 *
 * Created on January 31, 2023, 9:23 AM
 */

#include "config_EUSART.h"

void setup(void) {
    registerConfig();
    inputOutput();
    configTerminal();
    activateUART();
}

void registerConfig(void) {
    // Connect RC6 to TX/CK
    RC6PPS = 0x14; 
    // Connect RC7 to RX
    RXPPS = 0x17;
}

void inputOutput(void) {
    // RC6 output
    TRISC &= ~0x40;
    // RC7 digital input
    TRISC |= 0x80;
    ANSELC &= ~0x80;
}

void configTerminal(void) {
    // Asynchronous mode and set BRGH to 0
    TX1STA &= ~0x14;
    TX1STA |= 0x20;
    // Set 16-bit rate
    BAUD1CON = 0x08;
    // Set SP1BR to 119 for 18.432 MHz
    SP1BRGH = 0;
    SP1BRGL = 51;
}

void activateUART(void) {
    // Enable serial port and enable receiver
    RC1STA |= 0x90;
    // Transmit enable bit
    TX1STA |= 0x20;
}

void write(char data) {
    TX1REG = data;
}

void writeString(const char* string) {
    int i = 0;
    while(string[i] != '\0') {
        write(string[i]);
        delai_approx(3); // Wait 3 ms
        i++;
    }
    // Does work
    /*for(int i = 0; i < sizeof(string); i++) {
        write(string[i]);
        delai_approx(100); // Wait 3 ms
    }*/
}

char read(void) {
    return RC1REG;
}

//Wait ~ x millisecond
void delai_approx(int milSec) {
    for(int i=0; i<milSec; i++)
        __delay_ms(1);
}