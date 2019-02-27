#ifndef __USART1_H
#define	__USART1_H

#include "bsp.h"
#include "stdio.h"

extern uint8_t USART1_Rx_Buffer[USART1RXBUF_SIZE];
extern uint8_t USART1_Tx_Buffer[USART1TXBUF_SIZE];
// #define USART1_START_TXDMA DMA_Cmd DMA_SetCurrDataCounter(DMA1_Stream6,9);\(DMA2_Stream7, ENABLE)


void cfgUSART1(void);
void writeByteUSART1(uint8_t b);
void DMA2_Stream5_IRQHandler(void);
void USART1_IRQHandler(void);//USART1中断
void startTxDMA(void);


#endif /* __USART1_H */
