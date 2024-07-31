/****************************************************************
 * - Author: Eureke
 * - Date: 2024-08-01 00:10:16
 * - LastEditTime: 2024-08-01 01:42:38
 * - Description: 
 * - FilePath: \8-1 DMA数据转运\CountSensor\CountSensor.h
 *****************************************************************/
#ifndef __COUNTSENSOR_H
#define __COUNTSENSOR_H

extern uint32_t CountSensor_Count;

extern void CountSensor_Init(void);
extern uint32_t CountSensor_GetCount(void);

#endif /* __COUNTSENSOR */
