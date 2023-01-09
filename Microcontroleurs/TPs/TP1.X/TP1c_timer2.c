#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

/*LEDS
 D1-4 - PORTB 0x0F
 D5-8 - PORTD 0x0F 
 */

void delai_timer2(void);

void main(void) {
    //Set LED 1-8 to output
    TRISB &= ~0x0F;
    TRISD &= ~0x0F;
    
    //Default config turn off all LEDs except D1
    LATB |= 0x01;
    LATB &= ~0x0E;
    LATD &= ~0x0F;
    
    while(1){
        //Wait 125 ms
        delai_timer2(125);
        
        //If D4
        if(LATB & 0x0F == 0x08)
        {
            LATB &= ~0x0F;
            LATD |= 0x01;
        }
        //If D8
        else if(LATD & 0x0F == 0x08)
        {
            LATD &= ~0x0F;
            LATB |= 0x01;
        }
        //If D1-3
        else if(LATD & 0x0F == 0x00)
            LATB = LATB << 1;
        //IF D5-7
        else
            LATD = LATD << 1;
    }
}

//Wait ~ x millisecond
void delai_timer2(int milsecond) {
    /*1 milliSecond	per flag with setup :	
        PR2	124
        pre	16
        post 1
     8 steps needed -> 125 loop each
     */
    
    //Set postscaller to 1
    T2CON &= ~0x78;
    
    //Set prescaller to 16
    T2CON |= 0x02;
    
    //Enable timer 2
    T2CON |= 0x04;
    
    for(int i = 0; i< milsecond; i++)
    {
        //Set PR2 to 124
        PR2 = 124;
        //Set Flag to 0
        PIR1 &= ~0x02;
        while(!(PIR1 & 0x02)){}
    }
}