#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

/*LEDS
 D1-4 - PORTB 0x0F
 D5-8 - PORTD 0x0F 
 */

void delai_approx(int);


void main(void) {
    //Set LED 1-8 to output
    TRISB &= ~0x0F;
    TRISD &= ~0x0F;
    
    while(1){
        //Turn on Led D1-4, turn off led D5-8
        LATB |= 0x0F;
        LATD &= ~0x0F;
        //Wait ~ 500 millisecond
        delai_approx(500);
        //Turn off Led D1-4, turn on led D5-8
        LATB &= ~0x0F;
        LATD |= 0x0F;
        //Wait ~ 500 millisecond
        delai_approx(500);
    }
}

//Wait ~ x millisecond
void delai_approx(int milSec) {
    for(int i=0; i<milSec; i++)
        __delay_ms(1);
}