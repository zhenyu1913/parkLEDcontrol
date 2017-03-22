#ifndef MULTI_UART_H
#define MULTI_UART_H

#include "stdint.h"

#define MC_TIMEOUT     5

#define BUF_LEN     256

typedef enum
{
    RX_IDLE,
    RXING,
    RX_FINISHED,
    TXING,
    TX_FINISHED,
}com_status_t;

typedef enum tr_t
{
    TR_RX,
    TR_TX,
}tr_t;

typedef struct
{
    com_status_t status;
    uint8_t buf[BUF_LEN];
    uint16_t rev_index;
    uint16_t send_index;
    uint16_t send_len;
    uint16_t timerout_count;
    uint16_t timeout;
}com_t;

#include "multi_com_port.h"

int multi_com_send(com_chn_t com_chn, uint8_t* send_buf, uint16_t len);
int isr_multi_com_send_char(com_chn_t com_chn);
int isr_multi_com_rev_char(com_chn_t com_chn, uint8_t c);
void isr_multi_com_timer(void);
void rs485RevTask(void);

#endif
