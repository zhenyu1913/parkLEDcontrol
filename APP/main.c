#include "sys.h"
#include "hardware.h"
#include "timer.h"
#include "delay.h"
#include "displayMidware.h"
#include "hub08.h"
#include "multi_com.h"
#include "app.h"
#include "com.h"

void LED_task()
{
    static int count = 0;
    count++;
    if(count %2 == 0)
    {
        GPIO_ResetBits(GPIOC,GPIO_Pin_14);
        GPIO_SetBits(GPIOC,GPIO_Pin_15);
    }
    else
    {
        GPIO_SetBits(GPIOC,GPIO_Pin_14);
        GPIO_ResetBits(GPIOC,GPIO_Pin_15);
    }
}

void SPK_RevTask()
{
    uint16_t len;
    len = com_list[COM_SPK].rev_index;
    multi_com_send(COM_485,com_list[COM_SPK].buf,len);
}
void rs485RevTask()
{
	uint16_t len;
	len = com_list[COM_485].rev_index;
	if(comDeal(com_list[COM_485].buf,len) == 0)
	{
		multi_com_send(COM_485,com_list[COM_485].buf,52);
	}
//	multi_com_send(COM_SPK,com_list[COM_485].buf,len);
}

void updateID()
{
	appVar.ID[0] = 0;
	appVar.ID[0] += PAin(4);
	appVar.ID[0] <<= 1;
	appVar.ID[0] += PAin(5);
	appVar.ID[0] <<= 1;
	appVar.ID[0] += PAin(6);
	appVar.ID[0] <<= 1;
	appVar.ID[0] += PAin(7);
}

void updateRelayOutput()
{
	if(appVar.relay1output)
	{
		PBout(11) = 1;
	}
	else 
	{
		PBout(11) = 0;
	}
	if(appVar.relay2output)
	{
		PBout(12) = 1;
	}
	else 
	{
		PBout(12) = 0;
	}
}

void rountineTask1s()
{
	updateDisplayString();
	updateID();
	updateRelayOutput();
}

int main(void)
{
	uint8_t str[] = {0xBB ,0xB6 ,0xBB ,0xB6 ,0xBB ,0xB6 ,0xBB ,0xB6 ,0xD3 ,0xAD ,0xD3 ,0xAD ,0xD3 ,0xAD ,0xD3 ,0xAD ,0xB9 ,0xE2 ,0xB9 ,0xE2 ,0xB9 ,0xE2 ,0xB9 ,0xE2 ,0xC1 ,0xD9 ,0xC1 
	,0xD9 ,0xC1 ,0xD9 ,0xC1 ,0xD9};
    hardware_init();
    appInit();
	setIdleString(str,sizeof(str));
    set_timer(LED_task,500,1);
	set_timer(LED_run,3,1);
	set_timer(rountineTask1s,1000,1);
    while(1)
    {
        timer_run_task();
    }
}
