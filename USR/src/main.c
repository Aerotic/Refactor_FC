/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-27 11:06:16 am
 * @copyright APPI SASU
 */

#include "bsp.h"

uint32_t tmp = 0xffffff;
u32 DeviceID;
int main(void)
{
	initPeriphals();
	initModules();
	printf("\nHelloWorld!\n");
//	//USART_SendData(USART2,0xaa);
//	W25X_Flash_WAKEUP();
//	tmp = W25X_FLASH_ReadWriteByte(W25X_Cmd_DeviceID);
//	printf("Flash ID is 0x%6X",W25X_FLASH_ReadDeviceID());
	//SPI_FLASH_Init();
	DeviceID = W25x_FLASH_Check();
	if (!DeviceID) {
		printf("\nError W25x Series Flash not detected\n");
	}
	else
	{
		printf("\nW25Q%d detected!\n",(int16_t)(DeviceID + 1));
	}
	
	
	while (1)
	{
	}
}