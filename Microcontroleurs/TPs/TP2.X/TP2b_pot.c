/*
 * File:   TP2b_pot.c
 * Author: Colin
 *
 * Created on January 24, 2023, 3:05 PM
 */

#include <xc.h>
#include "configbits.h"

void setupLeds(void);
void configPortA(void);
void configADCModule(void);
void configADCInterrup(void);
void delai_approx(int);
void resetInterrupt(void);
void activateLed(int led);
void __interrupt() isr (void);

void main(void) {
    setupLeds();
    configPortA();
    configADCModule();
    configADCInterrup();
    //Wait 1 ms for acquisition time
    delai_approx(1);
    resetInterrupt();
    
    while(1) {}
}

void setupLeds(void) {
    //Set led 0-7 to inputs
    TRISD &= ~0x0F;
    TRISB &= ~0x0F;
}

void configPortA(void) {
    //Set as output potentiometer
    TRISA |= 0x01;
    //Set as analog
    ANSELA |= 0x01;
    //Disable all weak pull-ups
    OPTION_REG |= 0x80;
}

void configADCModule(void) {
    //Set input channel, GO/!Done and enable ADC
    ADCON0 = 0x03;
    //Set right jutify, Fosc/4, VDD and VSS
    ADCON1 = 0xC0;
    
}

void configADCInterrup(void) {
    //Enable Peripheral interrupt enable bit and global interrupt enable bit
    INTCON |= 0xC0;
    //Enable ADC Interrupt
    PIE1 |= 0x40;
    //Clear ADC INterrupt bit
    PIR1 &= ~0x40;
}

//Wait ~ x millisecond
void delai_approx(int milSec) {
    for(int i=0; i<milSec; i++)
        __delay_ms(1);
}

void resetInterrupt(void) {
    //Set Go/!Done to 1
    ADCON0 |= 0x02;
    //Clear ADC INterrupt bit
    PIR1 &= ~0x40;  
}

void activateLed(int led) {
    //Reset all leds
    LATD &= ~0x0F;
    LATB &= ~0x0F;
    
    switch(led) {
        case 0:
            LATD |= 0x01;
            break;
        case 1:
            LATD |= 0x02;
            break;
        case 2:
            LATD |= 0x04;
            break;
        case 3:
            LATD |= 0x08;
            break;
        case 4:
            LATB |= 0x01;
            break;
        case 5:
            LATB |= 0x02;
            break;
        case 6:
            LATB |= 0x04;
            break;
        case 7:
            LATB |= 0x08;
            break;
    }
}

void __interrupt() isr (void) {
    //Check only ADC interrupt
    if(PIR1 & 0x40) {
        //Just in case take only the 2 last bit of ADRESH
        signed int aDCVal = ((ADRESH & 0x03) << 8) + ADRESL;
        
        // 1024/8 for each led
        activateLed(aDCVal/128);
        
        resetInterrupt();
    }
}