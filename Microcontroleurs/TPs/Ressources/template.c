#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

/*LEDS
 D1-4 - PORTB 0x0F
 D5-8 - PORTD 0x0F 
 */

void delai_approx(int);
void delai_timer0_500milSec(void);

void main(void) {
    /* Code d'initialisation */
    //Set LED 1-8 to output
    TRISB &= ~0x0F;
    TRISD &= ~0x0F;
    
    while(1){
        //Turn on Led D1-4, turn off led D5-8
        LATB |= 0x0F;
        LATD &= ~0x0F;
        //Wait ~ one second
        delai_timer0_500milSec();
        //Turn off Led D1-4, turn on led D5-8
        LATB &= ~0x0F;
        LATD |= 0x0F;
        //Wait ~ one second
        delai_timer0_500milSec();
        /* Code a executer dans une boucle infinie */
    }
}

//Wait ~ x millisecondes
void delai_approx(int milSec) {
    for(int i=0; i<milSec; i++)
        __delay_ms(1);
}

void delai_timer0_500milSec(void) {
    //Set Prescaler to 16
    //Fclk to 2MHz
    //Set TMR0 to 56
    // 1 / ( ( 256 - TMR0 ) * ( Prescaler / Fclk ) ) = 625 
    
    //OPTION REG PSA to 1, TMR0CS to 0
    
    OPTION_REG |= 0x0A;
    OPTION_REG &= ~0x20;
        
    for(int i = 0; i<625; i++)
    {
        TMR0 = 0x38;
        INTCON &= ~0x04;
        while(!(INTCON & 0x04)){}
    }
}