#include "stm32f10x.h"  // Device Header
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

/**
	* @brief  初始化LED
  * @param  无
  * @retval 无
  */
void LED_Init(void)
{
	// 使能高级外设总线2的外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);


	// 配置GPIO输出模式
	GPIO_InitTypeDef GPIOA_InitStruct = 
	{
		GPIO_Pin_1 | GPIO_Pin_2,
		GPIO_Speed_50MHz,
		GPIO_Mode_Out_PP,
	};
	GPIO_Init(GPIOA, &GPIOA_InitStruct);
	
	// 配置默认输出为高电平，一开始让LED灭
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
}

/**
  * @brief  点亮LED1
  * @param  无
  * @retval 无
  */
void GPIOA_LEDx_ON(uint16_t GPIO_Pin)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin);
}

void GPIOA_LEDx_OFF(uint16_t GPIO_Pin)
{
	GPIO_SetBits(GPIOA, GPIO_Pin);
}
