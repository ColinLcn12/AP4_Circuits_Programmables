
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef CONFIG_POTENTIOMETER_H
#define	CONFIG_POTENTIOMETER_H

#include <xc.h>

void setupPotentiometer(void);
void configPortA(void);
void configADCModule(void);
void configADCInterrup(void);
void resetInterrupt(void);

#endif

