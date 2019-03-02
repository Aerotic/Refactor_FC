/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-27 10:58:23 am
 * @copyright APPI SASU
 */
#include "serialprint.h"

USART_TypeDef* SerialPrintPort;
#if 1
#pragma import(__use_no_semihosting)                             
struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;
int fputc(int ch, FILE *f)
{      
	while((SerialPrintPort->SR&0X40)==0);  
    SerialPrintPort->DR = (u8) ch;      
	return ch;
}

void setSerialPrintPort(USART_TypeDef* USARTx){
	SerialPrintPort = USARTx;
}
#endif