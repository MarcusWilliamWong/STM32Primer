#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"

uint8_t keyNum = 0;

int main(void)
{
	LED_Init();
	Key_Init();

	while(1)
	{	
		/* Q1：原版代码按下按键后LED会闪烁 */
		/* Q2：持久按下按键，LED闪烁 */
		keyNum = Key_GetNum();
		if (keyNum == 1) 
		{
			// GPIOA_setLEDx(GPIO_Pin_1, LED_ENABLE);
			GPIOA_ToggleLEDx(GPIO_Pin_1);
			Delay_ms(100); /* A1：在切换后添加100ms延迟，让用户使用体验更优 */
		}
		if (keyNum == 2)
		{
			// GPIOA_setLEDx(GPIO_Pin_2, LED_ENABLE);
			GPIOA_ToggleLEDx(GPIO_Pin_2);
			Delay_ms(100); /* 切换后添加100ms延迟，用户使用体验更优 */
		}
		keyNum = 0;
	}
	
}
