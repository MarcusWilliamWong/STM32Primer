/****************************************************************
 * - Author: Eureke
 * - Date: 2024-08-01 00:14:39
 * - LastEditTime: 2024-08-01 02:07:24
 * - Description: 
 * - FilePath: \8-1 DMA数据转运\Dma\inc\Dma.h
 *****************************************************************/
#if !defined (__DMA_H)
#define __DMA_H
/*********************************************************
 * Include Files
 *********************************************************/
#include <stdint.h>
/*********************************************************
 * Macros
 *********************************************************/
#define DMA_DSTADDR Dma_ArrayB
#define DMA_SRCADDR Dma_ArrayA
#define DMA_ARRAYSIZE 4u
/*********************************************************
 * Global Variables
 *********************************************************/
extern uint8_t Dma_ArrayA[DMA_ARRAYSIZE];
extern uint8_t Dma_ArrayB[DMA_ARRAYSIZE];

/*********************************************************
 * Global Function
 *********************************************************/
extern void Dma_Init(void);

extern void Dma_TranscationDataM2M(void);

#endif /* __DMA_H */
