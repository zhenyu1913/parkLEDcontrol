#include "multi_com.h"
#include "timer.h"
#include "sys.h"
#include "app.h"

com_t com_list[COM_NUM];

void multi_com_port_fram_rev(com_chn_t com_chn,uint8_t *buf,
       uint16_t len)
{
    if(com_chn == COM_485)
    {
        set_timer(rs485RevTask,0,0);
    }
    if(com_chn == COM_SPK)
    {
        set_timer(SPK_RevTask,0,0);
    }
}

void multi_com_port_send_char(com_chn_t com_chn,uint8_t c)
{
    if(com_chn == COM_485)
    {
        USART_SendData(USART1, c);
    }
	if(com_chn == COM_SPK)
	{
        USART_SendData(USART2, c);
	}
}

void multi_com_port_tr_control(com_chn_t com_chn,tr_t tr)
{
    if(com_chn == COM_485)
    {
        if(tr == TR_TX)
        {
            GPIO_SetBits(GPIOA,GPIO_Pin_8);
        }
        else
        {
            GPIO_ResetBits(GPIOA,GPIO_Pin_8);
        }
    }
}
