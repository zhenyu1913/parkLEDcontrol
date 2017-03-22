#ifndef COM_H
#define COM_H

#include "stdint.h"

#define CMD_HEAD 0xA0
#define CMD_END 0x50

#define BACK_HEAD 0xAF
#define BACK_END 0x5F

enum CmdType{
    CMD_SENDINFO = 0x03,
	CMD_IO = 0x04,
    CMD_SET_LED_HARDWARE = 0x23,
    CMD_GET_LED_HARDWARE = 0x24,
    CMD_SPK = 0xA0,
};

enum ContentType{
    CONTENT_IDLE = 0,
    CONTENT_EMERGENT = 0x80,
};

typedef struct{
    uint8_t infoIndex[2];
    uint8_t animationStyle;
    uint8_t stayStyle;
    uint8_t moveSpeed;
    uint8_t pageStayTime;
    uint8_t fontSize;
    uint8_t reserve4[6];
    uint8_t reserve5[8];
    uint8_t StayTime[2];
    uint8_t encodeType;
    uint8_t fontColor;
    uint8_t contentType;
    uint8_t currentSessionNum;
    uint8_t maxSessionNum;
    uint8_t contentLen[2];
    uint8_t currentArea;
    uint8_t reserve6;
}ParaSendInfo;

typedef struct{
    uint8_t head;
    uint8_t len[2];
    uint8_t ID[2];
    uint8_t reserve[8];
    uint8_t cmd;
    uint8_t reserve2[2];

    uint8_t para[32];

    uint8_t checksum[2];
    uint8_t reserve3;
    uint8_t end;
}Cmd;

int comDeal(uint8_t* buf,uint16_t len);

#endif
