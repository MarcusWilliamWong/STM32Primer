# ST32的RCC模块

## 简介

RCC（Reset & Colock Control），即复位和时钟控制模块，包括时钟设置，外设复位和时钟管理。

RCC_APB2Periph_GPIO()

APB2 是 Advanced Peripheral Bus 2 高级外设总线2 的缩写。

STM32中有三个常见外设总线：APB1，APB2，AHB。STM核心控制芯片通过外设总线，与各个外设模块相连接，各个外设模块有自己的寄存器，数据缓冲区，时钟控制逻辑等等。

AHB是 Advanced High-performance Bus，是STM32微控制器中速度最快的外设总线，一般连接速度要求较高的外设，如存储器控制器，DMA控制器等。

APB1和APB2总线连接速度较低的外设，相比APB1总线，APB2总线的时钟频率更高，一般是APB1的两倍。