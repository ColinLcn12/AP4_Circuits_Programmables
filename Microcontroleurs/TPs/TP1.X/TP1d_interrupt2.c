#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

/*LEDS
 D1-4 - PORTB 0x0F
 D5-8 - PORTD 0x0F 
 */

void __interrupt() isr (void);


//the loop of leds modification is close to one second but not perfect
void main(void) {
    /*Closest setup to 8 loops
        Prescaler	64
        Postscaler	16
        loops: 7.971938776
        time: 0.12544
        pr2: 244
     */

    //Set LED 1-8 to output
    TRISB &= ~0x0F;
    TRISD &= ~0x0F;

    //Set prescaller to 64 and enable timer and postscaler 16
    T2CON |= 0xEF;

    //Turn off all leds except D0
    LATD |= 0x01;
    LATD &= ~0x0E;
    LATB &= ~0x0F;

    //Enable Peripheral interrupt enable bit and global
    INTCON |= 0xC0;

    //Enable timer2 interrupt
    PIE1 |= 0x02;

    PR2 = 244;
    PIR1 &= ~0x02;

    while(1){ }
}

void __interrupt() isr (void) {
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
    PIR1 &= ~0x02;
}