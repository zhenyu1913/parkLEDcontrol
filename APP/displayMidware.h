#ifndef DISPLAYMIDWARE_H
#define DISPLAYMIDWARE_H

#include "stdint.h"

void setIdleString(uint8_t *s,uint16_t len);
void setEmergentString(uint8_t *s,uint16_t len,uint16_t second);
void updateDisplayString(void);

#endif
