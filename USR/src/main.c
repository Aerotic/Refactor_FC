/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-27 11:06:16 am
 * @copyright APPI SASU
 */

#include "bsp.h"

int main(void)
{
	initPeriphals();
	initModules();
	printf("HelloWorld!");
	//USART_SendData(USART2,0xaa);

	while (1)
	{
	}
}