#include "stm32f10x.h"  // Device Header
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "LED.h"

/**
	* @brief  初始化LED
	* @param  无
	* @retval 无
	*/
void LED_Init(void)
{
	/* 使能GPIOA的高级外设总线2外设时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/* 初始化GPIO输出模式 */
	GPIO_InitTypeDef GPIOA_InitStruct = 
	{
		GPIO_Pin_1 | GPIO_Pin_2,
		GPIO_Speed_50MHz,
		GPIO_Mode_Out_PP, /* 推挽输出 */
	};
	GPIO_Init(GPIOA, &GPIOA_InitStruct);
	
	/* 配置GPIO输出为高电平，LED 正极一端接 3V3，负极接GPIO引脚，所以一开始让LED灭 */
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
}

/**
  * @brief  点亮/关闭 GPIOA 的 LEDx
  * @param  NewState: LED_DISABLE, LED_ENABLE
  * @retval 无
  */
void GPIOA_setLEDx(uint16_t GPIO_Pin, LedState NewState)
{
	if (LED_ENABLE == NewState)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin);
	}
	else
	{
		GPIO_SetBits(GPIOA, GPIO_Pin);
	}
}

/**
  * @brief  取反 GPIOA 的 LEDx 输出电平
  * @param  NewState: LED_DISABLE, LED_ENABLE
  * @retval 无
  */
void GPIOA_ToggleLEDx(uint16_t GPIO_Pin)
{
	if (Bit_SET == GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin))
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin);
	}
	else
	{
		GPIO_SetBits(GPIOA, GPIO_Pin);
	}
}
