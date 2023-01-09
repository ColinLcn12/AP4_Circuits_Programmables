#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

/*LEDS
 D1-4 - PORTB 0x0F
 D5-8 - PORTD 0x0F 
 */

void exerice_a (void);
void exerice_b (void);
void exerice_c (void);
void delai_approx(int);
void delai_timer0(void);


void main(void) {
    
}

void exerice_a (void) {
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

void exerice_b (void) {
    //Set LED 1-8 to output
    TRISB &= ~0x0F;
    TRISD &= ~0x0F;
    
    while(1){
        //Turn on Led D1-4, turn off led D5-8
        LATB |= 0x0F;
        LATD &= ~0x0F;
        //Wait ~ 500 millisecond
        delai_timer0(500);
        //Turn off Led D1-4, turn on led D5-8
        LATB &= ~0x0F;
        LATD |= 0x0F;
        //Wait ~ 500 millisecond
        delai_timer0(500);
    }
}

void exerice_b (void) {
    
}

//Wait ~ x millisecond
void delai_approx(int milSec) {
    for(int i=0; i<milSec; i++)
        __delay_ms(1);
}

//Wait ~ x millisecond
void delai_timer0(int milsecond) {
    //Set Prescaler to 8   
    //Fclk to 2MHz
    //Set TMR0 to 6
    //Setup to wait 1 millisecond
    
    //Prescaler to 8
    OPTION_REG |= 0x02;
    //OPTION REG PSA to 0, TMR0CS to 0
    OPTION_REG &= ~0x28;
    
    for(int i = 0; i<milsecond; i++)
    {
        //Set TMR0 to 6
        TMR0 = 6;
        //Set Flag to 0
        INTCON &= ~0x04;
        while(!(INTCON & 0x04)){}
    }
}