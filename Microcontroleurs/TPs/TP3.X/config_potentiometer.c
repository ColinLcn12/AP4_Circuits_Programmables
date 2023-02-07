/*
 * File:   config_variator.c
 * Author: Colin
 *
 * Created on February 7, 2023, 2:15 PM
 */

#include "config_potentiometer.h"

void setupPotentiometer(void) {
    configPortA();
    configADCModule();
    configADCInterrup();
}

void configPortA(void) {
    //Set as output potentiometer
    TRISA |= 0x01;
    //Set as analog
    ANSELA |= 0x01;
    //Disable all weak pull-ups
    //OPTION_REG |= 0x80;
    WPUA &= ~0x01;
}

void configADCModule(void) {
    //Set input channel, GO/!Done and enable ADC
    ADCON0 = 0x03;
    //Set right jutify, Fosc/4, VDD and VSS
    ADCON1 = 0xC0; 
}

void configADCInterrup(void) {
    //Enable Peripheral interrupt enable bit and global interrupt enable bit
    INTCON |= 0xC0;
    //Enable ADC Interrupt
    PIE1 |= 0x40;
    //Clear ADC INterrupt bit
    PIR1 &= ~0x40;
}

void resetInterrupt(void) {
    //Set Go/!Done to 1
    ADCON0 |= 0x02;
    //Clear ADC INterrupt bit
    PIR1 &= ~0x40;  
}