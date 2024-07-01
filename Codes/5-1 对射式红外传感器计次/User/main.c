#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "CountSensor.h"

uint8_t keyNum = 0;

int main(void)
{
	/* Hardware Init */
	OLED_Init();
	CountSensor_Init();

	OLED_ShowString(1, 1,"Count:");

	
	while(1)
	{	
		OLED_ShowNum(1, 7, CountSensor_GetCount(), 5);
	}
	
}
