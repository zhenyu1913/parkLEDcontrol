#include "stdint.h"
#include "multi_com.h"
#include "string.h"

void isr_multi_com_timer()
{
    int i;
    for (i = 0; i < COM_NUM; i++)
    {
        if (com_list[i].timerout_count > 0)
        {
            com_list[i].timerout_count--;
        }
        else
        {
            if (com_list[i].status == RXING)
            {
                com_list[i].status = RX_FINISHED;
                multi_com_port_fram_rev((com_chn_t)i, com_list[i].buf,
                        com_list[i].rev_index);
                com_list[i].status = RX_IDLE;
            }
        }
    }
}

int multi_com_rev_char(com_chn_t com_chn, uint8_t c)
{
    com_t* l_com;
    l_com = &com_list[com_chn];

    com_list[COM_485].timeout = 5;

    switch (l_com->status)
    {
        case RX_IDLE:

            l_com->rev_index = 0;
            memset(l_com->buf, 0, BUF_LEN);
            l_com->status = RXING;

            l_com->buf[l_com->rev_index] = c;
            l_com->rev_index++;
            l_com->timerout_count = l_com->timeout;

            break;

        case RXING:

            if (l_com->rev_index < BUF_LEN)
            {
                l_com->buf[l_com->rev_index] = c;
                l_com->rev_index++;
            }
            l_com->timerout_count = l_com->timeout;
            break;

        case RX_FINISHED:
            break;

        default:
            break;
    }
    return 0;
}

int multi_com_send_char(com_chn_t com_chn)
{
    com_t* l_com;
    l_com = &com_list[com_chn];
    if (l_com->send_index < l_com->send_len)
    {
        multi_com_port_send_char(com_chn,l_com->buf[l_com->send_index]);
        l_com->send_index++;
    }
    else
    {
        multi_com_port_tr_control(com_chn,TR_RX);
        l_com->status = RX_IDLE;
    }
    return 0;
}

int multi_com_send(com_chn_t com_chn, uint8_t* send_buf, uint16_t len)
{
    com_t* l_com;
    l_com = &com_list[com_chn];
    if (len > BUF_LEN)
    {
        return -1;
    }
    l_com->status = TXING;
    multi_com_port_tr_control(com_chn,TR_TX);
    memcpy(&l_com->buf, send_buf, len);
    l_com->send_index = 0;
    l_com->send_len = len;
    multi_com_send_char(com_chn);
    return 0;
}

int isr_multi_com_send_char(com_chn_t com_chn)
{
    multi_com_send_char(com_chn);
    return 0;
}

int isr_multi_com_rev_char(com_chn_t com_chn, uint8_t c)
{
    multi_com_rev_char(com_chn, c);
    return 0;
}

