/********************************************************************************************************************************* 
 * - Author: Eureke
 * - Date: 2024-07-04 01:42:05
 * - LastEditTime: 2024-08-01 00:22:41
 * - Description: 定时器驱动程序
 * - FilePath: \8-1 DMA数据转运\Timer\Timer.c
 **********************************************************************************************************************************/ 
#include "Timer.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "Dma.h"
/********************************************************************************************************************************* 
 * Global Variable
 **********************************************************************************************************************************/ 
uint32_t Timer_Count = 0;

/********************************************************************************************************************************* 
 * Global Function
 **********************************************************************************************************************************/ 

/********************************************************************************************************************************** 
 * - Timer_Init()
 * - description: 
 * - parameters:
 * - return {*}
 **********************************************************************************************************************************/ 
void Timer_Init(void)
{
	/* 参见STM32F10xx参考手册.pdf RM0008 P366*/
	/* 开启RCC总线时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/* 开启内部时钟，作为TIM2定时器的输入时钟信号，默认上电后使用内部时钟为 72M*/
	TIM_InternalClockConfig(TIM2);
	/* 初始化定时器的时基单元 */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure =
	{
		.TIM_Prescaler = 7200 - 1, /* 时基单元的预分频器的值，对输入的时钟信号CK_PSC(72MHz)进行7200分频，定时器时钟CK_CNT为即每秒 72M / 7200 = 10000 个周期信号方波 */
		.TIM_CounterMode = TIM_CounterMode_Up, /* 计数方式，向上\下\中央对齐 */
		.TIM_Period = 10000 - 1, /* ARR自动重装器的值，即计数器目标数值为10000，也就是说使用1M的频率，计数10000个，也就是定时为1s*/
		.TIM_ClockDivision = TIM_CKD_DIV1, /* 时钟分频，用于调整外部时钟信号的滤波器采样频率 */
		.TIM_RepetitionCounter = 0/* 重复计数器，属于高级定时器的特性，此处不需要直接赋0 */
	};
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	/* TIM_TimeBaseInit 最后会手动生成更新时间。当更新事件、触发时间、输入捕获、输出比较时，会产生中断/DMA请求*/
	/* 所以会出现现象上电后，计数器值直接从1开始计数，解决方法是：清除上电后的中断挂起位 */
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	/* 定时器模块的中断输出控制：因为定时器触发中断情况较为复杂，所以设计了一个中断输出控制电路，用于使能各个定时器触发的中断请求信号 */
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	/* 中断优先级分组 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/* 配置 NVIC 注册TIM2中断 */
	NVIC_InitTypeDef NVIC_InitStructure = 
	{
		.NVIC_IRQChannel = TIM2_IRQn,
		.NVIC_IRQChannelPreemptionPriority = 2,
		.NVIC_IRQChannelSubPriority = 1,
		.NVIC_IRQChannelCmd = ENABLE,

	};
	NVIC_Init(&NVIC_InitStructure);

	/* 使能定时器的计数器 */
	TIM_Cmd(TIM2, ENABLE);
}

/********************************************************************************************************************************* 
 * - Description: 实现TIM2中断处理逻辑
 * - return {*}
 **********************************************************************************************************************************/ 
void TIM2_IRQHandler(void)
{
	/* 查看定时器TIM2的更新中断挂起状态 */
	if (SET == TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		if (!(Timer_Count % 2) )
		{
			/* 当计数器为偶数时，更新数组A的值 */
			for (int i = 0; i < DMA_ARRAYSIZE; ++i)
			{
				++Dma_ArrayA[i];
			}
		}
		else
		{
			/* 当计数器为奇数时，使用DMA将数据A的值转运到数组B的位置 */
			Dma_TranscationDataM2M();
		}
		++Timer_Count;
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
