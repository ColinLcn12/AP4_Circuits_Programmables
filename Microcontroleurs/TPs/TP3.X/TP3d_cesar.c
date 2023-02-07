/*
 * File:   TP3d_cesar.c
 * Author: Colin
 *
 * Created on February 7, 2023, 1:48 PM
 */

#include "configbits.h"
#include <xc.h>
#include "config_EUSART.h"
#include "config_potentiometer.h"
#include "lcd.h"
#include "spi.h"

const char* alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";
int offset = 0;

void initLCD(void);
void writeLCD(char val);
void changeLCD(int led);
void configInterruptionEcho(void);
void __interrupt() isr (void);

void main(void) {
    initLCD();
    writeLCD('d');
    
    setup();
    configInterruptionEcho();
    writeString("Start\n\r");
    
    setupPotentiometer();
    delai_approx(1);
    //Wait 1 ms for acquisition time
    resetInterrupt();
    while(1) {}
}

void initLCD(void) {
    SPI_InitializePins();
    LCD_InitializePins();
    SPI_Initialize();
    LCD_Initialize();
    LCD_Clear();
}

void writeLCD(char val) {
    LCD_GoTo(0,0);
    LCD_WriteString("Offset : ");
    LCD_WriteByte(val);
}

void changeLCD(int val) {
    // I wasn't able to find a way to convert int to char
    offset = val+1;
    switch(val) {
        case 0:
            writeLCD('1');
            break;
        case 1:
            writeLCD('2');
            break;
        case 2:
            writeLCD('3');
            break;
        case 3:
            writeLCD('4');
            break;
        case 4:
            writeLCD('5');
            break;
        case 5:
            writeLCD('6');
            break;
        case 6:
            writeLCD('7');
            break;
        case 7:
            writeLCD('8');
            break;
    }
}

void configInterruptionEcho(void) {
    // Enable Peripheral interrupt enable bit and global interrupt enable bit
    INTCON |= 0xC0;
    // Enable USART receive interrupt
    PIE1 |= 0x20;
    // Set interrupt flag to 0
    PIR1 &= ~0x20;
}

void __interrupt() isr (void) {
    //Check only ADC interrupt
    if(PIR1 & 0x40) {       
        //Just in case take only the 2 last bit of ADRESH
        int aDCVal = ((ADRESH & 0x03) << 8) + ADRESL;
        
        // 1024/8 for each led
        changeLCD(aDCVal/128);
        
        resetInterrupt();
    }
    if(PIR1 & 0x20){
        if(RC1REG == '\r')
        {
            write('\n');
            write('\r');
        }
        else {
            int i = 0;
            while(alphabet[i] != RC1REG) {
                i++;
            }
            write(alphabet[i + offset]);
            PIR1 &= ~0x20;
        }
    }
}