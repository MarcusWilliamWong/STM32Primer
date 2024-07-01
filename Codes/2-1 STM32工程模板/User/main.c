#include "stm32f10x.h"

int main(void) 
{
	// 1. 使用直接配置寄存器方法编程
	// APB2外设时钟使能寄存器RCC_APB2ENR
	// RCC->APB2ENR = 0x00000010;
	// GPIOC->CRH = 0x00300000; // 亮
	// GPIOC->ODR = 0x00002000; //0x00002000 灭
	
	
	// 2. 使用库函数方法编程
	/*
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // RCC外设时钟控制
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	// GPIO_SetBits(GPIOC, GPIO_Pin_13); // GPIO_SetBits函数将PC13号口置为高电平
	GPIO_ResetBits(GPIOC, GPIO_Pin_13); // GPIO_ResetBits函数将pin置为低电平，低电平亮灯
	*/
	while (1)
	{
		
	}
}
