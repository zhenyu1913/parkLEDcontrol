#ifndef HUB08_H
#define HUB08_H

#define MAX_LED_UNIT_NUM 12

extern unsigned char displayBuf[MAX_LED_UNIT_NUM*8][16];
void LED_run(void);

#endif
