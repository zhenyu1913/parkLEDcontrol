#include "sys.h"
#include "delay.h"
#include "hub08.h"
#include "app.h"

#define SDAR1 PBout(7) //红色数据1
#define SDAR2 PBout(6) //红色数据2
#define SDAG1 PBout(5) //绿色数据1
#define SDAG2 PBout(4) //绿色数据2
#define CLK PBout(8)   //74HC595的时钟
#define STB PBout(15)   //输出锁存
#define OE  PBout(9)   //74HC138的使能
#define LED_A  PBout(14)   //74HC138的使能
#define LED_B  PBout(13)   //74HC138的使能
#define LED_C  PAout(15)   //74HC138的使能
#define LED_D  PBout(3)   //74HC138的使能
 //74HC595串行数据输入
void SendDate(unsigned char DataR1,unsigned char DataR2)
{
    unsigned char i;
	if(appVar.LED_HardInfo.dataPolarity == 0)
	{
		DataR1=~DataR1;
		DataR2=~DataR2;
	}
    for(i = 0; i < 8; i++)
    {
		SDAR1=DataR1 & 1;
		SDAR2=DataR2 & 1;
        CLK = 0;
        CLK = 1;
        DataR1 >>= 1;
        DataR2 >>= 1;
    }
}

unsigned char displayBuf[MAX_LED_UNIT_NUM*8][16];

#define OE_ON() OE = appVar.LED_HardInfo.OE_Palarity
#define OE_OFF() OE = !appVar.LED_HardInfo.OE_Palarity

//主函数入口
void LED_run()
{
    unsigned int num;
	if(appVar.isStopLEDscan)return;
    for(num=0;num<16;num++)
    {
        int i = 0;
		int maxCharNum = appVar.LED_HardInfo.width * appVar.LED_HardInfo.heigh/2;
        for(i = 0; i < maxCharNum/4; i++)
        {
            SendDate(displayBuf[i][num],displayBuf[i+maxCharNum/4][num]);
        }
        for(i = 0; i < maxCharNum/4; i++)
        {
            SendDate(displayBuf[i+maxCharNum*2/4][num],displayBuf[i+maxCharNum*3/4][num]);
        }
        STB=0;
        STB=1;     //输出锁存
        LED_A = num & 1;
        LED_B = num>>1 & 1;
        LED_C = num>>2 & 1;
        LED_D = num>>3 & 1;
        OE_ON();
		delay_us(70);
        OE_OFF();
    }
//	delay_us(70);
//	OE_OFF();
}
