/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-26 2:52:33 pm
 */

#ifndef _USART2_H_
#define _USART2_H_
#include "bsp.h"


void USART2_Init(void);
void USART2_WriteByte(uint8_t b);
void DMA1_Stream6_IRQHandler(void);
void USART2_IRQHandler(void);//USART2中断
void USART2_StartTxDMA(void);
#endif 

