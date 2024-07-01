#include "stm32f10x.h"  // Device Header
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "Key.h"
#include "Delay.h"
/**
	* @brief  初始化按键
  * @param  无
  * @retval 无
  */
void Key_Init(void)
{
	/* 开启外设总线2上的GPIOB外设 */ 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIOB_InitStruct = 
	{
		GPIO_Pin_1 | GPIO_Pin_11,
		GPIO_Speed_50MHz,
		GPIO_Mode_IPU,  /* 上拉输入模式，按键另一端接地；按下GPIO口为低电平，松开GPIO口为高电平 */
	};
	GPIO_Init(GPIOB, &GPIOB_InitStruct);
}

uint8_t Key_GetNum(void)
{
	uint8_t keyNum = 0;
	if (Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
	{
		Delay_ms(20);
		while (Bit_RESET == GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_1));
		Delay_ms(20);
		keyNum = 1;
	}
	
	if (Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11))
	{
		Delay_ms(20);
		while (Bit_RESET == GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_11));
		Delay_ms(20);
		keyNum = 2;
	}

	return keyNum;
}

