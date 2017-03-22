#ifndef MULTI_COM_PORT_H
#define MULTI_COM_PORT_H

#include "multi_com.h"


typedef enum com_chn_t
{
    COM_485 = 0,
    COM_SPK,
    COM_NUM,
}com_chn_t;

extern com_t com_list[COM_NUM];

void multi_com_port_fram_rev(com_chn_t com_chn,uint8_t *buf,uint16_t len);
void multi_com_port_send_char(com_chn_t com_chn,uint8_t c);
void multi_com_port_tr_control(com_chn_t com_chn,tr_t tr);

uint8_t get_rs485_rev_flag(void);
uint8_t clr_rs485_rev_flag(void);

#endif
