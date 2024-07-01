#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "Delay.h"

int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出，50MHZ
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开启外设时钟控制函数
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// GPIO_SetBits(GPIOA, GPIO_Pin_0); // 将指定端口设置为高电平
	// GPIO_ResetBits(GPIOA, GPIO_Pin_0); // 将指定端口设置为低电平
	
	// GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET); // 写入GPIO的某个端口为高/低电平
	
	// LED闪烁功能
	while(1)
	{
		//GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
		Delay_ms(0x1f4u);
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
		Delay_ms(0x7d0u);
	}
}
