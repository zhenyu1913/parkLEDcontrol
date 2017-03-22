#include "app.h"

AppVar appVar;

void appInit()
{
    appVar.LED_HardInfo.width = 16;
    appVar.LED_HardInfo.heigh = 4;
    appVar.LED_HardInfo.dataPolarity = 1;
    appVar.LED_HardInfo.OE_Palarity = 0;
	appVar.relay1output = 1;
	appVar.relay2output = 1;
};
