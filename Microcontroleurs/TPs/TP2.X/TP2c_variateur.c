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
void timer2();
void setPWMLed0();
void __interrupt() isr (void);

void main(void) {
    setupLeds();
    configPortA();
    configADCModule();
    configADCInterrup();
    //Wait 1 ms for acquisition time
    delai_approx(1);
    resetInterrupt();
    timer2();
    setPWMLed0();
    while(1) {}
}

void setupLeds(void) {
    //Set led 0 input
    TRISD &= ~0x01;
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

void timer2() {
    //Set prescaller to 16 and enable timer and postscaler 1 but it's useless for PWM
    T2CON |= 0x06;
    
    //Set timer 2 interrupt
    PIR1 &= ~0x02;
    
    //Set timer2 PR2
    PR2 = 255;
}

void setPWMLed0() {
    //Set led for PWM
    RD0PPS = 0x0F;
    
    //Enable PWM
    PWM4CON = 0x80;
    
    //Set value to 0
    PWM4DCH = 0;
    PWM4DCL &= ~0xC0;
}

void __interrupt() isr (void) {
    //Check only ADC interrupt
    if(PIR1 & 0x40) {
        //PR2 is only 8 bits long, so we have to ignore the two last bits to fit it
        PWM4DCH = ((ADRESH & 0x03) << 6) + (ADRESL / 4);
        
        resetInterrupt();
    }
}