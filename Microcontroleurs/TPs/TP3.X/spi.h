/* Explorer 8 SPI Module APIs Header File

 * File originally generated by Microchip for the Explorer 8 (Device : PIC16F1719)
 * File amended (01/2023) by AP for JUNIA ISEN AP4

 */

#ifndef _SPI_H
#define _SPI_H

/**
  Section: Macro Declarations
*/

#define DUMMY_DATA 0x0

/**
  Section: SPI Module APIs
*/
void SPI_InitializePins(void);
void SPI_Initialize(void);
char SPI_Exchange8bit(char data);
char SPI_Exchange8bitBuffer(char *dataIn, char bufLen, char *dataOut);
char SPI_IsBufferFull(void);
char SPI_HasWriteCollisionOccured(void);
void SPI_ClearWriteCollisionStatus(void);


#endif // _SPI_H
