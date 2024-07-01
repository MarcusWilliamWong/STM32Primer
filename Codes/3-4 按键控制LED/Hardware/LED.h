#ifndef __LED_H
#define __LED_H

#include "Common_types.h"

void LED_Init(void);
void GPIOA_setLEDx(uint16_t GPIO_Pin, LedState NewState);
void GPIOA_ToggleLEDx(uint16_t GPIO_Pin);

#endif
