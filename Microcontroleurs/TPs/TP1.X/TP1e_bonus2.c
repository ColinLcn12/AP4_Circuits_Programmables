#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

/*LEDS
 D1-4 - PORTB 0x0F
 D5-8 - PORTD 0x0F 
 */

void __interrupt() isr (void);
int count = 0;

void main(void) {
    /*
        Prescaler	16
        Postscaler	1
        PR2 = 124
     */
    
    //Set LED 1-8 to output
    TRISB &= ~0x0F;
    TRISD &= ~0x0F;
    
    //Set button as input
    TRISA |= 0x20;
   
    //Enable interrupt on button positive edge register
    IOCAP |= 0x20;
    
    //Set prescaller to 16 and enable timer and postscaler 1
    T2CON |= 0x06;
    
    //Turn off all leds except D0
    LATD |= 0x01;
    LATD &= ~0x0E;
    LATB &= ~0x0F;
    
    //Enable Peripheral interrupt enable bit and global interrupt enable bit and on change interrupt
    INTCON |= 0xC9;
    
    //Enable timer2 interrupt
    PIE1 |= 0x02;
    
    PR2 = 124;
    PIR1 &= ~0x02;
    
    while(1){ }
}

void __interrupt() isr (void) {
    if(count == 125)
    {
    //If D4
    if((LATB & 0x0F) == 0x08)
    {
        LATB &= ~0x0F;
        LATD |= 0x01;
    }
    //If D8
    else if((LATD & 0x0F) == 0x08)
    {
        LATD &= ~0x0F;
        LATB |= 0x01;
    }
    //If D1-3
    else if((LATD & 0x0F) == 0x00)
        LATB += (LATB & 0x0F);
    //IF D5-7
    else if((LATB & 0x0F) == 0x00)
        LATD += (LATD & 0x0F); 
    count = 0;
    }
    else
        count+=1;
    PIR1 &= ~0x02;
    if((INTCON & 0x01) == 0x01)
    {
        if(T2CON & 0x04)
            T2CON &= ~0x04;
        else
            T2CON |= 0x04;
    }
}