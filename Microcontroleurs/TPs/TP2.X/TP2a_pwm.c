#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

/*LEDS
 D1-4 - PORTD 0x0F
*/

/*Switch
 S2 - PORTA 0x20
*/

/*
 Duty cycle ration
 PR2 = 249
 
 0% -> TMPR2 = 0
 25% -> TMR2 = 250
 50% -> TMR2 = 500
 75% -> TMR2 = 750
 100% -> TMR2 = 1000 
*/

void __interrupt() isr (void);
void timer2(void);
void led_D_0(void);
void buttonS2(void);

int etat = 0;

void main(void) {
    led_D_0();
    buttonS2();
    
    //Enable Peripheral interrupt enable bit and global interrupt enable bit and on change interrupt
    INTCON |= 0xC8;
    
    //Set timer2 PR2
    PR2 = 249;
    
    timer2();
    
    //Set led for PWM
    RD0PPS = 0x0F;
    
    //Enable PWM
    PWM4CON = 0x80;
    
    //Set value to 0
    PWM4DCH = 0;
    PWM4DCL &= ~0xC0;
    
    while(1) {}
}

void timer2() {
    //Set prescaller to 16 and enable timer and postscaler 1 but it's useless for PWM
    T2CON |= 0x06;
    
    //Set timer 2 interrupt
    PIR1 &= ~0x02;
}

void led_D_0(void) {
    //Set LED 1 to output
    TRISD &= ~0x01;
}

void buttonS2(void) {
    //Set button as input and set it as digital
    TRISA |= 0x20;
    ANSELA &= ~0x20;
    
    //Reset button interrupt just in case
    IOCAF &= ~0x20;
    
    //Enable interrupt on change control on button S2
    IOCAN |= 0x20;
}

void __interrupt() isr (void) {
    if(INTCON & 0x01)
    {        
        if(IOCAF & 0x20)
        {
            /*//Value are changing from 0,250,500,750 and 1000
            //Manage the 2 first bits
            if(PWM4DCL & 0x80)
                PWM4DCL &= ~0x80;
            else
                PWM4DCL |= 0x80;
            
            //Manage the bits 3 from 10
            if(PWM4DCH >= 250)
            {
                PWM4DCH = 0;
                PWM4DCL &= ~0x80;
            }
            else if(PWM4DCH & 0x01 || PWM4DCH == 0)
                PWM4DCH+=62;
            else
                PWM4DCH+=63;*/          
            
            switch(etat)
            {
                case 0:
                    PWM4DCH=62;
                    PWM4DCL |= 0x80;
                    break;
                case 1:
                    PWM4DCH=125;
                    PWM4DCL &= ~0x80;
                    break;
                case 2:
                    PWM4DCH=187;
                    PWM4DCL |= 0x80;
                    break;
                case 3:
                    PWM4DCH=250;
                    PWM4DCL &= ~0x80;
                    break;
                case 4:
                    PWM4DCH=0;
                    break;
            }
            
            if(etat >= 4)
                etat = 0;
            else
                etat++;
            
            //Reset button interrupt
            IOCAF &= ~0x20;
        }
    }
}