#include "com.h"
#include "string.h"
#include "app.h"
#include "displayMidware.h"
#include "multi_com.h"

uint16_t getUint16(uint8_t *buf)
{
    return (((uint16_t)buf[1]) << 8) + buf[0];
}

uint16_t getChecksum(uint8_t *buf,uint16_t len)
{
    uint16_t checksum = 0;
	int i;
    for(i = 0; i < len; i++)
    {
        checksum += buf[i];
    }
    return checksum;
}

int comDeal(uint8_t* buf,uint16_t len)
{
    Cmd* cmd = (Cmd*)buf;
    if(buf[0] != CMD_HEAD)return -1;
    if(buf[len - 1] != CMD_END)return -1;
    if(len < sizeof(Cmd))return -1;
    if(getUint16(cmd->len) > 1024)return -1;
    if(getChecksum(buf,len-4) != buf[len-4] + (((uint16_t)buf[len-3])<<8))return -1;
    if(memcmp(cmd->ID,appVar.ID,sizeof(appVar.ID)) != 0)return -1;

    if(cmd->cmd == CMD_SENDINFO)
    {
        int contentLen  = 0;
        ParaSendInfo* para = (ParaSendInfo*)&cmd->para;
        contentLen = getUint16(para->contentLen);
        //Todo 检查contentLen是否合法
        if(para->contentType == CONTENT_IDLE)
        {
            setIdleString(&buf[16 + 32],contentLen);
        }
        else if(para->contentType == CONTENT_EMERGENT)
        {

            setEmergentString(&buf[16 + 32],contentLen,getUint16(para->StayTime));
        }
    }
	else if(cmd->cmd == CMD_IO)
	{
		appVar.relay1output = cmd->para[0];
		appVar.relay2output = cmd->para[1];
	}
	else if(cmd->cmd == CMD_SET_LED_HARDWARE)
    {
        memcpy((void*)(&appVar.LED_HardInfo),cmd->para,16);
    }
    else if(cmd->cmd == CMD_GET_LED_HARDWARE)
    {
        memcpy(cmd->para,(void*)(&appVar.LED_HardInfo),16);
    }
	else if(cmd->cmd == CMD_SPK)
	{
		multi_com_send(COM_SPK,&(cmd->para[1]),cmd->para[0]);
		return -1;
	}
	else
	{
		return -1;
	}
    cmd->head = BACK_HEAD;
    cmd->reserve3 = 0;
    {
        uint16_t checksum = getChecksum(buf,48);
        cmd->checksum[0] = checksum;
        cmd->checksum[1] = checksum>>1;
    }
    cmd->end = BACK_END;
	return 0;
}
