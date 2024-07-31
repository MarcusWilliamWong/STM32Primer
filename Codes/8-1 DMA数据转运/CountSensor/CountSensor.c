/********************************************************************************************************************************* 
 * @Author: Eureke
 * @Date: 2024-06-30 19:27:40
 * @LastEditTime: 2024-07-01 01:42:12
 * @Description: 
 * @FilePath: \5-1 对射式红外传感器计次\CountSensor\CountSensor.c
 *********************************************************************************************************************************/ 
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "CountSensor.h"

/*********************************************** Global Variable *****************************************************************/
uint32_t CountSensor_Count = 0;

/********************************************************************************************************************************* 
 * @description: CountSensor 初始化函数，配置GPIO外设，AFIO外设，EWXTI外设，NVIC内核外设打通整个中断道路
 * @return {*}
 *********************************************************************************************************************************/ 
void CountSensor_Init(void)
{
	/* 开启GPIOB和AFIO的外设时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	/* 初始化 GPIO外设 */
	GPIO_InitTypeDef GPIO_InitStructure =
	{
		.GPIO_Pin = GPIO_Pin_14,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_IPU
	};

	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* 初始化 AFIO外设，打通从GPIO外设由AFIO进入到EXTI电路*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14); /* 连接GPIOB的第14条线路，AFIO同一时间只能选择连接某一个GPIO外设的0-15号的同名端口 */

	/* 初始化 EXTI外设 */
	EXTI_InitTypeDef EXTI_InitStructure =
	{
		.EXTI_Line = EXTI_Line14,
		.EXTI_Mode = EXTI_Mode_Interrupt,
		/* EXTI_Trigger_Rising 上升沿触发计数中断，被挡时触发计数；
		EXTI_Trigger_Falling 下降沿触发计数中断，移开挡板时触发计数
		EXTI_Trigger_Rising_Falling 上升下降沿均触发计数中断，被挡和移开挡板时均触发计数*/
		.EXTI_Trigger = EXTI_Trigger_Rising_Falling,
		.EXTI_LineCmd = ENABLE
	};
	EXTI_Init(&EXTI_InitStructure);

	/* EXTI外设通向NVIC内核外设，需要配置NVIC，配置中断分组 */
	NVIC_InitTypeDef NVIC_InitStructure = 
	{
		.NVIC_IRQChannel = EXTI15_10_IRQn,
		.NVIC_IRQChannelPreemptionPriority = 1,
		.NVIC_IRQChannelSubPriority = 1,
		.NVIC_IRQChannelCmd = ENABLE
	};
	NVIC_Init(&NVIC_InitStructure);
	/* only call once */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); /* To write to this register, you must write 0x5FA to the VECTKEY field, otherwise the
processor ignores the write */
	
	/* 至此打通了 NVIC，最后实现一下对应的中断函数 */
}

/*********************************************************************************************************************************
 * @description: 实现 EXTI14的中断函数
 * @return {*}
 *********************************************************************************************************************************/ 
void EXTI15_10_IRQHandler(void)
{	
	/* 判断 EXTI14是否有中断信号进入 */
	if (SET == EXTI_GetITStatus(EXTI_Line14))
	{
		++CountSensor_Count;
		/* 每次进入中断后，都要记得清除挂起标志位，便于下次中断进入 */
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}

/********************************************************************************************************************************* 
 * @description: 获取当前累计的计数值
 * @return {*}
 **********************************************************************************************************************************/ 
uint32_t CountSensor_GetCount(void)
{
	return CountSensor_Count;
}
