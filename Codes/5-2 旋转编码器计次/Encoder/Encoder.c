/********************************************************************************************************************************* 
 * @Author: Eureke
 * @Date: 2024-07-01 02:27:49
 * @LastEditTime: 2024-07-01 04:09:29
 * @Description: 
 * @FilePath: \5-2 旋转编码器计次\Encoder\Encoder.c
 **********************************************************************************************************************************/ 
#include "stm32f10x.h"
#include "Encoder.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "misc.h"

/*********************************************** Global Variable *****************************************************************/
int32_t Encoder_Count = 0;

/********************************************************************************************************************************* 
 * @description: 旋转编码器初始化函数
 * @return {*}
 **********************************************************************************************************************************/ 
void Encoder_Init(void)
{
	/* Init RCC */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );
	/* Init GPIOB0, GPIOB1 */
	GPIO_InitTypeDef GPIO_InitStructure =
	{
		.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_IPU,
	};
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Init AFIO 0, 1 */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0 | GPIO_PinSource1);

	/* Init EXTI */
	EXTI_InitTypeDef EXTI_InitStructure =
	{
		.EXTI_Line = EXTI_Line0 | EXTI_Line1,
		.EXTI_Mode = EXTI_Mode_Interrupt,
		.EXTI_Trigger = EXTI_Trigger_Falling,
		.EXTI_LineCmd = ENABLE,
	};
	EXTI_Init(&EXTI_InitStructure);

	/* Init NVIC */
	NVIC_InitTypeDef NVIC_InitStructure_Exti0 =
	{
		.NVIC_IRQChannel = EXTI0_IRQn,
		.NVIC_IRQChannelPreemptionPriority = 1,
		.NVIC_IRQChannelSubPriority = 1,
		.NVIC_IRQChannelCmd = ENABLE
	};

	NVIC_InitTypeDef NVIC_InitStructure_Exti1 =
	{
		.NVIC_IRQChannel = EXTI1_IRQn,
		.NVIC_IRQChannelPreemptionPriority = 1,
		.NVIC_IRQChannelSubPriority = 2,
		.NVIC_IRQChannelCmd = ENABLE
	};
	NVIC_Init(&NVIC_InitStructure_Exti0);
	NVIC_Init(&NVIC_InitStructure_Exti1);
}

/********************************************************************************************************************************* 
 * @description: 实现中断函数EXTI0，首先判断是否中断请求EXTI0
 * 	当旋转编码器逆时针旋转时，A端口的下降沿先于B端口的下降沿产生，即判断A端口下降沿产生时，B端口应为高电平，此时计数-1；

 * @return {*}
 **********************************************************************************************************************************/ 
void EXTI0_IRQHandler(void)
{
	if (SET == EXTI_GetITStatus(EXTI_Line0)) /* 触发中断 EXTI0*/
	{
		if (SET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)) /* 顺时针 */
		{
			--Encoder_Count;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

/********************************************************************************************************************************* 
 * @description: 实现中断函数EXTI1，首先判断是否中断请求EXTI1
 *  当旋转编码器顺时针旋转时，A端口的下降沿后于B端口的下降沿产生，即判断B端口下降沿产生时，A端口应为高电平，此时计数+1。
 * @return {*}
 **********************************************************************************************************************************/ 
void EXTI1_IRQHandler(void)
{
	if (SET == EXTI_GetITStatus(EXTI_Line1)) /* 触发中断 EXTI1*/
	{
		if (SET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)) /* 逆时针 */
		{
			++Encoder_Count;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

/********************************************************************************************************************************* 
 * @description: 获取旋转编码器的计数次数的变化值
 * @return {*}
 **********************************************************************************************************************************/ 
int32_t Encoder_GetDeltCount(void)
{
	int32_t temp = Encoder_Count;
	Encoder_Count = 0;
	return temp;
}
