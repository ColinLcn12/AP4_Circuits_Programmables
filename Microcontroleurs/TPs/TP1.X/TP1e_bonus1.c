#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

/*LEDS
 D1-4 - PORTB 0x0F
 D5-8 - PORTD 0x0F 
 */

void __interrupt() isr (void);
void delai_approx(int);

void main(void) {
    /*
        Prescaler	16
        Postscaler	1
        PR2 = 124
     */
    
    TRISB &= ~0x0F;
    TRISD &= ~0x0F;
   
    //Set prescaller to 64 and enable timer and postscaler 16
    T2CON |= 0xEF;
    
    //Turn off all leds except D0
    LATD |= 0x01;
    LATB |= 0x08;
    LATD &= ~0x0E;
    LATB &= ~0x07;
    
    //Enable Peripheral interrupt enable bit and global
    INTCON |= 0xC0;
    
    //Enable timer2 interrupt
    PIE1 |= 0x02;
    
    PR2 = 244;
    PIR1 &= ~0x02;
    
    while(1){
        if((LATB & 0x0F) == 0x01)
        {
            LATB &= ~0x07;
            LATB |= 0x08;
        }
        //If D1-3
        else
        {
            char lb = (LATB & 0x0F);
            LATB &= 0xF0;
            LATB += lb/2;
        }
        delai_approx(125);
    }
}

void __interrupt() isr (void) {
    //If D4
    if((LATD & 0x0F) == 0x08)
    {
        LATD &= ~0x0F;
        LATD |= 0x01;
    }
    //If D1-3
    else
        LATD += (LATD & 0x0F); 
    PIR1 &= ~0x02;
}

//Wait ~ x millisecond
void delai_approx(int milSec) {
    for(int i=0; i<milSec; i++)
        __delay_ms(1);
}
