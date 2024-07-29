/********************************************************************************************************************************* 
 * @Author: Eureke
 * @Date: 2024-06-30 19:27:51
 * @LastEditTime: 2024-06-30 20:44:23
 * @Description: 
 * @FilePath: \5-1 对射式红外传感器计次\CountSensor\CountSensor.h
 *********************************************************************************************************************************/ 
#ifndef __COUNTSENSOR_H
#define __COUNTSENSOR_H

extern uint32_t CountSensor_Count;

extern void CountSensor_Init(void);
extern uint32_t CountSensor_GetCount(void);

#endif /* __COUNTSENSOR */