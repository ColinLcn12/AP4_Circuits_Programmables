/*
 * File:   TP3a_uart_tx.c
 * Author: Colin
 *
 * Created on January 31, 2023, 10:18 AM
 */

#include "configbits.h"
#include <xc.h>
#include "config_EUSART.h"

void main(void) {
    setup();
    writeString("Hello, World !\n\r");
    while(1) { }
}
