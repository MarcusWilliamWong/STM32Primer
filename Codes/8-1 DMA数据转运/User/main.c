/****************************************************************
 * - Author: Eureke
 * - Date: 2024-08-01 00:10:16
 * - LastEditTime: 2024-08-01 01:56:40
 * - Description: 
 * - FilePath: \8-1 DMA数据转运\User\main.c
 *****************************************************************/
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "OLED.h"
#include "Timer.h"
#include "Dma.h"

int main(void)
{
	/* Hardware Init */
	Timer_Init();
	Dma_Init();
	OLED_Init();
	while(1)
	{	
		OLED_ShowString(1, 1, "Dma_ArrayA:");
		OLED_ShowNum(2, 1, Dma_ArrayA[0], 2);
		OLED_ShowNum(2, 4, Dma_ArrayA[0], 2);
		OLED_ShowNum(2, 7, Dma_ArrayA[0], 2);
		OLED_ShowNum(2, 10, Dma_ArrayA[0], 2);

		OLED_ShowString(3, 1, "Dma_ArrayB:");
		OLED_ShowNum(4, 1, Dma_ArrayB[0], 2);
		OLED_ShowNum(4, 4, Dma_ArrayB[0], 2);
		OLED_ShowNum(4, 7, Dma_ArrayB[0], 2);
		OLED_ShowNum(4, 10, Dma_ArrayB[0], 2);
	}
}
