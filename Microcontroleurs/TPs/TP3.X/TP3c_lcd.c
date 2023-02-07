/*
 * File:   TP3c_lcd.c
 * Author: Colin
 *
 * Created on February 7, 2023, 1:37 PM
 */

#include "configbits.h"
#include <xc.h>
#include "config_EUSART.h"
#include "lcd.h"
#include "spi.h"

void main(void) {
    SPI_InitializePins();
    LCD_InitializePins();
    SPI_Initialize();
    LCD_Initialize();
    LCD_Clear();
    LCD_GoTo(0,0);
    LCD_WriteString("Hello, world !");
    
    while(1) {}
}
