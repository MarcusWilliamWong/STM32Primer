/****************************************************************
 * - Author: Eureke
 * - Date: 2024-08-01 00:14:49
 * - LastEditTime: 2024-08-01 02:21:06
 * - Description: 
 * - FilePath: \8-1 DMA数据转运\Dma\src\Dma.c
 *****************************************************************/
#define DMA_SOURCE

/*********************************************************
 * Include Files
 *********************************************************/
#include "stm32f10x_rcc.h"
#include "Dma.h"
#include "stm32f10x_dma.h"

/*********************************************************
 * Global Variables
 *********************************************************/
uint8_t Dma_ArrayA[DMA_ARRAYSIZE] = {0};
uint8_t Dma_ArrayB[DMA_ARRAYSIZE] = {0};

/*********************************************************
 * Global Function
 *********************************************************/
/****************************************************************
 * - Description: 
 * - return {*}
 *****************************************************************/
void Dma_Init(void)
{
	/* 外设开启必须要开启其所需的时钟 */
	/* DMA属于AHB总线上的外设。需要开启AHB外设时钟 */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	/* 初始化DMA相关寄存器 */
	DMA_InitTypeDef DMA_InitStruct = 
	{
		.DMA_PeripheralBaseAddr = (uint32_t)DMA_DSTADDR,
		.DMA_MemoryBaseAddr	= (uint32_t)DMA_SRCADDR,	
		.DMA_DIR = DMA_DIR_PeripheralDST,
		.DMA_BufferSize = DMA_ARRAYSIZE,
		.DMA_PeripheralInc = DMA_PeripheralInc_Enable,
		.DMA_MemoryInc = DMA_MemoryInc_Enable,
		.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,
		.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte,
		.DMA_Mode = DMA_Mode_Normal,
		.DMA_Priority = DMA_Priority_Medium,
		.DMA_M2M = DMA_M2M_Enable,
	};

	DMA_Init(DMA1_Channel1, &DMA_InitStruct);
}

/****************************************************************
 * - Description: 
 * - param {uint8_t} *DstAddr
 * - param {uint8_t} *SrcAddr
 * - return {*}
 *****************************************************************/
void Dma_TranscationDataM2M(void)
{
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, DMA_ARRAYSIZE);
	DMA_Cmd(DMA1_Channel1, ENABLE);
}
