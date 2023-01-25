/*
 * File:   TP2b_pot.c
 * Author: Colin
 *
 * Created on January 24, 2023, 3:05 PM
 */

#include <xc.h>
#include "configbits.h"

void setupLeds(void);
void configTimer2Interrup(void);
void delai_approx(int);
void timer2();
void setPWMLed0();
void __interrupt() isr (void);
int inc = 1;

void main(void) {
    setupLeds();
    configTimer2Interrup();
    //Wait 1 ms for acquisition time
    delai_approx(1);
    timer2();
    setPWMLed0();
    while(1) {}
}

void setupLeds(void) {
    //Set led 0 input
    TRISD &= ~0x0F;
    TRISB &= ~0x0F;
}

void configTimer2Interrup(void) {
    //Enable Peripheral interrupt enable bit and global interrupt enable bit
    INTCON |= 0xC0;
}

//Wait ~ x millisecond
void delai_approx(int milSec) {
    for(int i=0; i<milSec; i++)
        __delay_ms(1);
}

void timer2() {
    //Set time2 to interrupt after 1ms
    //Set prescaller to 16 and enable timer and postscaler 1
    T2CON |= 0x06;
    
    //Enable timer2 interrupt
    PIE1 |= 0x02;
    
    //Set timer 2 interrupt
    PIR1 &= ~0x02;
    
    //Set timer2 PR2
    PR2 = 249;
}

void setPWMLed0() {
    //Set led for PWM
    RD0PPS = 0x0F;
    RD1PPS = 0x0F;
    RD2PPS = 0x0F;
    RD3PPS = 0x0F;
    RB0PPS = 0x0F;
    RB1PPS = 0x0F;
    RB2PPS = 0x0F;
    RB3PPS = 0x0F;
    
    //Enable PWM
    PWM4CON = 0x80;
    
    //Set value to 0
    PWM4DCH = 0;
    PWM4DCL &= ~0xC0;
}

void __interrupt() isr (void) {
    if(PIR1 & 0x02)
    {
        if(PWM4DCH == 250)
            inc = 0;
        if(PWM4DCH == 0 && PWM4DCL == 0)
            inc = 1;
        
        if(inc)
            if(PWM4DCL & 0x80)
            {
                PWM4DCL &= ~0xC0;
                PWM4DCH++;
            }
            else
                PWM4DCL+=0x80;
        else
            if(PWM4DCL == 0)
            {
                PWM4DCH--;
                PWM4DCL |= 0x80;
            }
            else
                PWM4DCL-=0x80;
        PIR1 &= ~0x02;
    }
}