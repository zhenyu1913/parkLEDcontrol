#include "string.h"
#include "hub08.h"
#include "ziku.h"
#include "displayMidware.h"

#define STRING_BUF_LEN MAX_LED_UNIT_NUM*8

char bufString[STRING_BUF_LEN];
char idleString[STRING_BUF_LEN];
char emergentString[STRING_BUF_LEN];

unsigned int emergentCount;

void setBufString(char* s)
{
	int i = 0;
	if(memcmp(s,bufString,STRING_BUF_LEN) == 0)return;
	memcpy(bufString,s,STRING_BUF_LEN);
	memset(displayBuf,0,sizeof(displayBuf));
	while(s[i] != 0 && i < STRING_BUF_LEN)
	{
		int j;
		for(j = 0; j < TableIndexLen; j++)
		{
			if((unsigned char)s[i] < 0x80)
			{
				if(TableIndex[j] == s[i])
				{
					memcpy(displayBuf[i],Table[j],16);
					break;
				}
			}
			else
			{
				if(TableIndex[j] == s[i] && TableIndex[j+1] == s[i+1])
				{
					memcpy(displayBuf[i],Table[j],16);
					memcpy(displayBuf[i+1],Table[j+1],16);
					break;
				}
			}
		}
		if((unsigned char)s[i] < 0x80)
		{
			i+=1;
		}
		else
		{
			i+=2;
		}
	}
}

void setIdleString(uint8_t *s,uint16_t len)
{
	if(len > STRING_BUF_LEN)return;
	memset(idleString,0,sizeof(idleString));
	memcpy(idleString,s,len);
	if(emergentCount == 0)
	{
		setBufString(idleString);
	}
}

void setEmergentString(uint8_t *s,uint16_t len,uint16_t second)
{
	if(len > STRING_BUF_LEN)return;
	memset(emergentString,0,sizeof(emergentString));
	memcpy(emergentString,s,len);
	emergentCount = second;
	if(emergentCount)
	{
		setBufString(emergentString);
	}
	else
	{
		setBufString(idleString);
	}
}

void updateDisplayString()
{
	if(emergentCount)
	{
		setBufString(emergentString);
		emergentCount--;
	}
	else
	{
		setBufString(idleString);
	}
}
