/********************************************************************************************************************************* 
 * @Author: Eureke
 * @Date: 2024-07-01 02:12:50
 * - LastEditTime: 2024-07-06 21:49:03
 * @Description: 
 * - FilePath: \6-2 定时器定时中断与定时器外部时钟\User\main.c
 **********************************************************************************************************************************/ 
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint8_t keyNum = 0;

int main(void)
{
	/* Hardware Init */
	Timer_Init();
	OLED_Init();
	OLED_ShowString(1, 1,"Cnt:");
	while(1)
	{	
		OLED_ShowNum(2, 1, Timer_Count, 5);
		OLED_ShowNum(3, 1, TIM_GetCounter(TIM2), 5);
	}
}
