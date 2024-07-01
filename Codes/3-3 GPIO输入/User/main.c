#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "Delay.h"
#include "LED.h"

int main(void)
{
	LED_Init();

	while(1)
	{
		GPIOA_LEDx_ON(GPIO_Pin_1);
		Delay_s(1);
		GPIOA_LEDx_OFF(GPIO_Pin_1);
		Delay_s(1);
		GPIOA_LEDx_ON(GPIO_Pin_2);
		Delay_s(1);
		GPIOA_LEDx_OFF(GPIO_Pin_2);
		Delay_s(1);
	}
	
}
