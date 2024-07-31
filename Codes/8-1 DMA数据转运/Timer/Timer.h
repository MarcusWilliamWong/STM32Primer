/********************************************************************************************************************************* 
 * - Author: Eureke
 * - Date: 2024-08-01 00:10:16
 * - LastEditTime: 2024-08-01 00:25:50
 * - Description: 
 * - FilePath: \8-1 DMA数据转运\Timer\Timer.h
 **********************************************************************************************************************************/ 
#if !defined (__TIMER_H)
#define __TIMER_H
/**************************************************************** 
 * Include files
 ****************************************************************/ 
#include <stdint.h>
/***************************************************************
 * Global Function
 ***************************************************************/ 
extern uint32_t Timer_Count;

/*************************************************************** 
 * @description: 定时器初始化函数
 * @return {*}
 **************************************************************/ 
extern void Timer_Init(void);

/************************************************************** 
 * @description: 
 * @return {*}
 **************************************************************/ 

#endif /* __TIMER_H */
