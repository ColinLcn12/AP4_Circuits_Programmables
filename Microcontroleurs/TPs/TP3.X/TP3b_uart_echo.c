/*
 * File:   TP3b_uart_echo.c
 * Author: Colin
 *
 * Created on January 31, 2023, 12:01 PM
 */

#include "configbits.h"
#include <xc.h>
#include "config_EUSART.h"

void configInterruption(void);
void __interrupt() isr (void);

void main(void) {
    setup();
    configInterruption();
    writeString("Start\n\r");
    while(1) {}
}

void configInterruption(void) {
    // Enable Peripheral interrupt enable bit and global interrupt enable bit
    INTCON |= 0xC0;
    // Enable USART receive interrupt
    PIE1 |= 0x20;
    // Set interrupt flag to 0
    PIR1 &= ~0x20;
}

void __interrupt() isr (void) {
    if(PIR1 & 0x20){
        write(RC1REG);
        PIR1 &= ~0x20;
    }
}