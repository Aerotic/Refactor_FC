/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-28 5:40:09 pm
 * @copyright APPI SASU
 */
#ifndef _W25x_FLASH_H_
#define _W25x_FLASH_H_
#include "bsp.h"

#define W25x_FLASH_ID_X16 0xEF3015  //W25X16
#define W25x_FLASH_ID_Q16 0xEF4015  //W25Q16
#define W25x_FLASH_ID_Q64 0XEF4017  //W25Q64
#define W25x_FLASH_ID_Q128 0XEF4018 //W25Q128

//#define W25x_FLASH_PageSize            4096
#define W25x_FLASH_PageSize 256
#define W25x_FLASH_PerWritePageSize 256

/*命令定义-开头************以字母表排序*************/
#define W25x_Cmd_BlockErase 0xD8
#define W25x_Cmd_ChipErase 0xC7
#define W25x_Cmd_DeviceID 0xAB
#define W25x_Cmd_Dummy_Byte 0xFF
#define W25x_Cmd_FastReadData 0x0B
#define W25x_Cmd_FastReadDual 0x3B
#define W25x_Cmd_JedecDeviceID 0x9F
#define W25x_Cmd_PageProgram 0x02
#define W25x_Cmd_PowerDown 0xB9
#define W25x_Cmd_ReadData 0x03
#define W25x_Cmd_ReadStatusReg 0x05
#define W25x_Cmd_ReleasePowerDown 0xAB
#define W25x_Cmd_SectorErase 0x20
#define W25x_Cmd_WriteDisable 0x04
#define W25x_Cmd_WriteEnable 0x06
#define W25x_Cmd_WriteStatusReg 0x01
#define W25x_WIP_Flag 0x01 /* Write In Progress (WIP) flag */

/*命令定义-结尾*******************************/

#define W25x_TIMEOUT_THREHOLD ((uint32_t)0x1000)
#define W25x_TIMEOUT_LONG_THREHOLD ((uint32_t)(10 * W25x_TIMEOUT_THREHOLD))

void W25x_FLASH_Init(void);
uint8_t W25x_FLASH_Check(void);
uint8_t W25x_FLASH_ReadWriteByte(uint8_t txbyte);
void W25x_FLASH_SectorErase(uint32_t SectorAddr);
void W25x_FLASH_BulkErase(void);
void W25x_FLASH_PageWrite(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void W25x_FLASH_BufferWrite(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void W25x_FLASH_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint32_t W25x_FLASH_ReadID(void);
uint32_t W25x_FLASH_ReadDeviceID(void);
void W25x_FLASH_StartReadSequence(uint32_t ReadAddr);
void W25x_Flash_PowerDown(void);
void W25x_Flash_WAKEUP(void);
void W25x_FLASH_WaitForWriteEnd(void);
uint8_t W25x_FLASH_ReadByte(void);
uint16_t W25x_FLASH_SendHalfWord(uint16_t HalfWord);
static uint8_t W25x_SPI_TIMEOUT_UserCallback(uint8_t errorCode);

#define W25x_FLASH_ERROR(fmt, arg...) printf("<<-FLASH-ERROR->> " fmt "\n", ##arg)

#endif