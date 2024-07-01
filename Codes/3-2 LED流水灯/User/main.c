#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "Delay.h"
#include "LED_Cfg.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); /* 开启APB2总线的外设时钟控制 RCC_APB2Periph_GPIOA */ 
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  /* 推挽输出，50MHZ */
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// GPIO_SetBits(GPIOA, GPIO_Pin_0); /* 将指定端口设置为高电平 */ 
	// GPIO_ResetBits(GPIOA, GPIO_Pin_0); /* 将指定端口设置为低电平 */ 
	
	// GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET); /* 写入GPIO的某个端口为高/低电平 */ 
	uint16_t led_pin = LED_START_PIN;
	/* LED闪烁功能 */
	while(1)
	{
		for (uint32_t i = 0; i < LED_NUM; ++i) {
			GPIO_Write(GPIOA, 0x0u);
			GPIO_Write(GPIOA, led_pin);

			if (led_pin == (uint16_t)0x0010) 
			{
				// led_pin >>= 0x0001u;
				led_pin = LED_START_PIN;
				continue;
			}
			
			led_pin <<= 0x0001u;
			Delay_ms(0x1f4u); /* 500ms */
		}
	}
}
