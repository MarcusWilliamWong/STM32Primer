/********************************************************************************************************************************* 
 * @Author: Eureke
 * @Date: 2024-07-01 02:12:50
 * @LastEditTime: 2024-07-01 04:02:07
 * @Description: 
 * @FilePath: \5-2 旋转编码器计次\User\main.c
 **********************************************************************************************************************************/ 
#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"
#include "Encoder.h"

uint8_t keyNum = 0;

int main(void)
{
	int32_t G_Num = 0; /* 编码器计数 */
	/* Hardware Init */
	OLED_Init();
	CountSensor_Init();
	Encoder_Init();
	OLED_ShowString(1, 1,"Cnt1:");
	OLED_ShowString(2, 1,"Cnt2:");

	while(1)
	{	
		OLED_ShowSignedNum(1, 6, CountSensor_GetCount(), 5);
		G_Num += Encoder_GetDeltCount();
		OLED_ShowSignedNum(2, 6, G_Num, 5);
	}
}
