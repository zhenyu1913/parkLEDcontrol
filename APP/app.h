#ifndef APP_H
#define APP_H

#include "stdint.h"

typedef struct{
    uint8_t width;
    uint8_t heigh;
    uint8_t colorType;
    uint8_t dataPolarity;
    uint8_t OE_Palarity;
    int8_t  lineOrder;
    uint8_t scanType;
    uint8_t isSwapRedAndGreen;
    uint8_t null[2];
    uint8_t isSwapData;
    uint8_t scanFrequency;
    uint8_t isWithout138;
    uint8_t null2[3];
}LED_HardInfo_t;

typedef struct{
    LED_HardInfo_t LED_HardInfo;
    uint8_t ID[2];
	uint8_t isStopLEDscan;
	uint8_t relay1output;
	uint8_t relay2output;
}AppVar;

extern AppVar appVar;
void appInit(void);
void rs485RevTask(void);
void SPK_RevTask(void);

#endif
