/**
 * @author Firstname Lastname <firstname.lastname@example.com>
 * @file Description
 * @desc Created on 2019-02-25 8:59:22 pm
 * @copyright APPI SASU
 */


#ifndef _USART3_H_
#define _USART3_H_


#include "bsp.h"
extern uint8_t USART3_Rx_Buffer[USART3RXBUF_SIZE];
void cfgUSART3(void);
void DMA1_Stream1_IRQHandler(void);
#endif
