/********************************************************************************************************************************* 
 * - Author: Eureke
 * - Date: 2024-07-02 02:10:18
 * - LastEditTime: 2024-07-04 02:07:22
 * - Description: 
 * - FilePath: \6-2 定时器定时中断与定时器外部时钟\Oled\OLED.h
 **********************************************************************************************************************************/ 
#ifndef __OLED_H
#define __OLED_H

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

#endif /* __OLED_H */
