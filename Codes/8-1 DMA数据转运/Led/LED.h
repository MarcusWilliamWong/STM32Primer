#ifndef __LED_H
#define __LED_H

typedef enum 
{
	LED_DISABLE = 0U, 
	LED_ENABLE = !LED_DISABLE
} LedState;

void LED_Init(void);
void GPIOA_setLEDx(uint16_t GPIO_Pin, LedState NewState);
void GPIOA_ToggleLEDx(uint16_t GPIO_Pin);

#endif /* __LED_H */
