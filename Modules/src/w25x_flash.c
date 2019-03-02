/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-03-01 4:31:50 pm
 * @copyright APPI SASU
 */
#include "w25x_flash.h"

static __IO uint32_t W25x_SPI_TimeOut = W25x_TIMEOUT_LONG_THREHOLD;

void W25x_FLASH_Init(void)
{
}

uint8_t W25x_FLASH_Check(void){
    uint32_t device_id;
    uint8_t device_flag;
    device_id = W25x_FLASH_ReadID();
    switch (device_id)
    {
        case W25x_FLASH_ID_X16:
            device_flag = 16;
            break;
        case W25x_FLASH_ID_Q16:
            device_flag = 15;
            break;
        case W25x_FLASH_ID_Q64:
            device_flag = 63;
            break;
        case W25x_FLASH_ID_Q128:
            device_flag = 127;
            break;
        default:
            device_flag = 0;
            break;
    }
    return device_flag;

}

/**
  * @brief  通过连接FLASH的SPI读写一个byte
  * @param  要发送的byte.
  * @retval 接收到的byte
  */
uint8_t W25x_FLASH_ReadWriteByte(uint8_t txbyte)
{
    W25x_SPI_TimeOut = W25x_TIMEOUT_THREHOLD;

    /* Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(W25x_FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET)
    {
        if ((W25x_SPI_TimeOut--) == 0)
            return W25x_SPI_TIMEOUT_UserCallback(0);
    }

    /* Send byte through the W25x_FLASH_SPI peripheral */
    SPI_I2S_SendData(W25x_FLASH_SPI, txbyte);

    W25x_SPI_TimeOut = W25x_TIMEOUT_THREHOLD;

    /* Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(W25x_FLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET)
    {
        if ((W25x_SPI_TimeOut--) == 0)
            return W25x_SPI_TIMEOUT_UserCallback(0); //超时返回0
    }

    /* Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData(W25x_FLASH_SPI);
}

/*******************************************************************************
* Function Name  : SPI_FLASH_SendHalfWord
* Description    : Sends a Half Word through the SPI interface and return the
*                  Half Word received from the SPI bus.
* Input          : Half Word : Half Word to send.
* Output         : None
* Return         : The value of the received Half Word.
*******************************************************************************/
uint16_t W25x_FLASH_SendHalfWord(uint16_t HalfWord)
{

    W25x_SPI_TimeOut = W25x_TIMEOUT_THREHOLD;

    /* Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(W25x_FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET)
    {
        if ((W25x_SPI_TimeOut--) == 0)
            return W25x_SPI_TIMEOUT_UserCallback(2);
    }

    /* Send Half Word through the FLASH_SPI peripheral */
    SPI_I2S_SendData(W25x_FLASH_SPI, HalfWord);

    W25x_SPI_TimeOut = W25x_TIMEOUT_THREHOLD;

    /* Wait to receive a Half Word */
    while (SPI_I2S_GetFlagStatus(W25x_FLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET)
    {
        if ((W25x_SPI_TimeOut--) == 0)
            return W25x_SPI_TIMEOUT_UserCallback(3);
    }
    /* Return the Half Word read from the SPI bus */
    return SPI_I2S_ReceiveData(W25x_FLASH_SPI);
}

/**
* @brief    : Reads a byte from the SPI Flash.
*                  This function must be used only if the Start_Read_Sequence
*                  function has been previously called.
* Input          : None
* Output         : None
* Return         : Byte Read from the SPI Flash.
*******************************************************************************/
uint8_t W25x_FLASH_ReadByte(void)
{
    return (W25x_FLASH_ReadWriteByte(W25x_Cmd_Dummy_Byte));
}

/**
* @brief    : Enables the write access to the FLASH.
* Input          : None
* Output         : None
* Return         : None
**/
void W25x_FLASH_WriteEnable(void)
{
    /* Select the FLASH: Chip Select low */
    SPI1_NSS_SELECT_W25FLASH;

    /* Send "Write Enable" instruction */
    W25x_FLASH_ReadWriteByte(W25x_Cmd_WriteEnable);

    /* Deselect the FLASH: Chip Select high */
    SPI1_NSS_notSELECT_W25FLASH;
}

/*******************************************************************************
* Function Name  : SPI_FLASH_WaitForWriteEnd
* Description    : Polls the status of the Write In Progress (WIP) flag in the
*                  FLASH's status  register  and  loop  until write  opertaion
*                  has completed.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void W25x_FLASH_WaitForWriteEnd(void)
{
    uint8_t FLASH_Status = 0;

    /* 选择 FLASH: CS 低 */
    SPI1_NSS_SELECT_W25FLASH;

    /* 发送 读状态寄存器 命令 */
    W25x_FLASH_ReadWriteByte(W25x_Cmd_ReadStatusReg);

    W25x_SPI_TimeOut = W25x_TIMEOUT_THREHOLD;

    /* 若FLASH忙碌，则等待 */
    do
    {
        /* Send a dummy byte to generate the clock needed by the FLASH
    and put the value of the status register in FLASH_Status variable */
        FLASH_Status = W25x_FLASH_ReadWriteByte(W25x_Cmd_Dummy_Byte);

        {
            if ((W25x_SPI_TimeOut--) == 0)
            {
                W25x_SPI_TIMEOUT_UserCallback(4);
                return;
            }
        }
    } while ((FLASH_Status & W25x_WIP_Flag) == SET); /* 正在写入标志 */

    /* 取选  FLASH: CS 高 */
    SPI1_NSS_notSELECT_W25FLASH;
}

//进入掉电模式
void W25x_Flash_PowerDown(void)
{
    /* 选择 FLASH: CS 低 */
    SPI1_NSS_SELECT_W25FLASH;

    /* 发送 掉电 命令 */
    W25x_FLASH_ReadWriteByte(W25x_Cmd_PowerDown);

    /* 取选  FLASH: CS 高 */
    SPI1_NSS_notSELECT_W25FLASH;
}

/**
  * @brief  读取FLASH ID
  * @param 	无
  * @retval FLASH ID
  */
uint32_t W25x_FLASH_ReadID(void)
{
    uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

    /* Select the FLASH: Chip Select low */
    SPI1_NSS_SELECT_W25FLASH;

    /* Send "RDID " instruction */
    W25x_FLASH_ReadWriteByte(W25x_Cmd_JedecDeviceID);

    /* Read a byte from the FLASH */
    Temp0 = W25x_FLASH_ReadWriteByte(W25x_Cmd_Dummy_Byte);

    /* Read a byte from the FLASH */
    Temp1 = W25x_FLASH_ReadWriteByte(W25x_Cmd_Dummy_Byte);

    /* Read a byte from the FLASH */
    Temp2 = W25x_FLASH_ReadWriteByte(W25x_Cmd_Dummy_Byte);

    /* Deselect the FLASH: Chip Select high */
    SPI1_NSS_notSELECT_W25FLASH;

    Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

    return Temp;
}

/**
  * @brief  读取FLASH Device ID
  * @param 	无
  * @retval FLASH Device ID
  */
uint32_t W25x_FLASH_ReadDeviceID(void)
{
    uint32_t Temp = 0;

    /* Select the FLASH: Chip Select low */
    SPI1_NSS_SELECT_W25FLASH;

    /* Send "RDID " instruction */
    W25x_FLASH_ReadWriteByte(W25x_Cmd_DeviceID);
    W25x_FLASH_ReadWriteByte(W25x_Cmd_Dummy_Byte);
    W25x_FLASH_ReadWriteByte(W25x_Cmd_Dummy_Byte);
    W25x_FLASH_ReadWriteByte(W25x_Cmd_Dummy_Byte);

    /* Read a byte from the FLASH */
    Temp = W25x_FLASH_ReadWriteByte(W25x_Cmd_Dummy_Byte);

    /* Deselect the FLASH: Chip Select high */
    SPI1_NSS_notSELECT_W25FLASH;

    return Temp;
}
/*******************************************************************************
* Function Name  : SPI_FLASH_StartReadSequence
* Description    : Initiates a read data byte (READ) sequence from the Flash.
*                  This is done by driving the /CS line low to select the device,
*                  then the READ instruction is transmitted followed by 3 bytes
*                  address. This function exit and keep the /CS line low, so the
*                  Flash still being selected. With this technique the whole
*                  content of the Flash is read with a single READ instruction.
* Input          : - ReadAddr : FLASH's internal address to read from.
* Output         : None
* Return         : None
*******************************************************************************/
void W25x_FLASH_StartReadSequence(uint32_t ReadAddr)
{
    /* Select the FLASH: Chip Select low */
    SPI1_NSS_SELECT_W25FLASH;

    /* Send "Read from Memory " instruction */
    W25x_FLASH_ReadWriteByte(W25x_Cmd_ReadData);

    /* Send the 24-bit address of the address to read from -----------------------*/
    /* Send ReadAddr high nibble address byte */
    W25x_FLASH_ReadWriteByte((ReadAddr & 0xFF0000) >> 16);
    /* Send ReadAddr medium nibble address byte */
    W25x_FLASH_ReadWriteByte((ReadAddr & 0xFF00) >> 8);
    /* Send ReadAddr low nibble address byte */
    W25x_FLASH_ReadWriteByte(ReadAddr & 0xFF);
}

//唤醒
void W25x_Flash_WAKEUP(void)
{
    /*选择 FLASH: CS 低 */
    SPI1_NSS_SELECT_W25FLASH;

    /* 发上 上电 命令 */
    W25x_FLASH_ReadWriteByte(W25x_Cmd_ReleasePowerDown);

    /* 取选 FLASH: CS 高 */
    SPI1_NSS_notSELECT_W25FLASH; //等待TRES1
}

/**
  * @brief  擦除FLASH扇区
  * @param  SectorAddr：要擦除的扇区地址
  * @retval 无
  */
void W25x_FLASH_SectorErase(uint32_t SectorAddr)
{
    /* 发送FLASH写使能命令 */
    W25x_FLASH_WriteEnable();
    W25x_FLASH_WaitForWriteEnd();
    /* 擦除扇区 */
    /* 选择FLASH: CS低电平 */
    SPI1_NSS_SELECT_W25FLASH;
    /* 发送扇区擦除指令*/
    W25x_FLASH_ReadWriteByte(W25x_Cmd_SectorErase);
    /*发送擦除扇区地址的高位*/
    W25x_FLASH_ReadWriteByte((SectorAddr & 0xFF0000) >> 16);
    /* 发送擦除扇区地址的中位 */
    W25x_FLASH_ReadWriteByte((SectorAddr & 0xFF00) >> 8);
    /* 发送擦除扇区地址的低位 */
    W25x_FLASH_ReadWriteByte(SectorAddr & 0xFF);
    /* 取选 FLASH: CS 高电平 */
    SPI1_NSS_notSELECT_W25FLASH;
    /* 等待擦除完毕*/
    W25x_FLASH_WaitForWriteEnd();
}
/**
  * @brief  对FLASH按页写入数据，调用本函数写入数据前需要先擦除扇区
  * @param 
			@arg	pBuffer，要写入数据的指针
	*		@arg  WriteAddr，写入地址
	*		@arg  NumByteToWrite，写入数据长度，必须小于等于SPI_FLASH_PerWritePageSize
  * @retval 无
  */
void W25x_FLASH_PageWrite(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    /* 发送FLASH写使能命令 */
    W25x_FLASH_WriteEnable();

    /* 选择FLASH: CS低电平 */
    SPI1_NSS_SELECT_W25FLASH;
    /* 写送写指令*/
    W25x_FLASH_ReadWriteByte(W25x_Cmd_PageProgram);
    /*发送写地址的高位*/
    W25x_FLASH_ReadWriteByte((WriteAddr & 0xFF0000) >> 16);
    /*发送写地址的中位*/
    W25x_FLASH_ReadWriteByte((WriteAddr & 0xFF00) >> 8);
    /*发送写地址的低位*/
    W25x_FLASH_ReadWriteByte(WriteAddr & 0xFF);

    if (NumByteToWrite > W25x_FLASH_PerWritePageSize)
    {
        NumByteToWrite = W25x_FLASH_PerWritePageSize;
        W25x_FLASH_ERROR("W25x_FLASH_PageWrite too large!");
    }

    /* 写入数据*/
    while (NumByteToWrite--)
    {
        /* 发送当前要写入的字节数据 */
        W25x_FLASH_ReadWriteByte(*pBuffer);
        /* 指向下一字节数据 */
        pBuffer++;
    }

    /* 取选 FLASH: CS 高电平 */
    SPI1_NSS_notSELECT_W25FLASH;

    /* 等待写入完毕*/
    W25x_FLASH_WaitForWriteEnd();
}

/**
  * @brief  对FLASH写入数据，调用本函数写入数据前需要先擦除扇区
  * @param 
			@arg	pBuffer，要写入数据的指针
	*		@arg  WriteAddr，写入地址
	*		@arg  NumByteToWrite，写入数据长度
  * @retval 无
  */
void W25x_FLASH_BufferWrite(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    Addr = WriteAddr % W25x_FLASH_PageSize;
    count = W25x_FLASH_PageSize - Addr;
    NumOfPage = NumByteToWrite / W25x_FLASH_PageSize;
    NumOfSingle = NumByteToWrite % W25x_FLASH_PageSize;

    if (Addr == 0) /* 若地址与 W25x_FLASH_PageSize 对齐  */
    {
        if (NumOfPage == 0) /* NumByteToWrite < W25x_FLASH_PageSize */
        {
            W25x_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
        }
        else /* NumByteToWrite > W25x_FLASH_PageSize */
        {
            while (NumOfPage--)
            {
                W25x_FLASH_PageWrite(pBuffer, WriteAddr, W25x_FLASH_PageSize);
                WriteAddr += W25x_FLASH_PageSize;
                pBuffer += W25x_FLASH_PageSize;
            }

            W25x_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else /* 若地址与 W25x_FLASH_PageSize 不对齐  */
    {
        if (NumOfPage == 0) /* NumByteToWrite < W25x_FLASH_PageSize */
        {
            if (NumOfSingle > count) /* (NumByteToWrite + WriteAddr) > W25x_FLASH_PageSize */
            {
                temp = NumOfSingle - count;

                W25x_FLASH_PageWrite(pBuffer, WriteAddr, count);
                WriteAddr += count;
                pBuffer += count;

                W25x_FLASH_PageWrite(pBuffer, WriteAddr, temp);
            }
            else
            {
                W25x_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else /* NumByteToWrite > W25x_FLASH_PageSize */
        {
            NumByteToWrite -= count;
            NumOfPage = NumByteToWrite / W25x_FLASH_PageSize;
            NumOfSingle = NumByteToWrite % W25x_FLASH_PageSize;

            W25x_FLASH_PageWrite(pBuffer, WriteAddr, count);
            WriteAddr += count;
            pBuffer += count;

            while (NumOfPage--)
            {
                W25x_FLASH_PageWrite(pBuffer, WriteAddr, W25x_FLASH_PageSize);
                WriteAddr += W25x_FLASH_PageSize;
                pBuffer += W25x_FLASH_PageSize;
            }

            if (NumOfSingle != 0)
            {
                W25x_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

/**
  * @brief  读取FLASH数据
  * @param 
			@arg	pBuffer，存储读出数据的指针
	*		@arg  ReadAddr，读取地址
	*		@arg  NumByteToRead，读取数据长度
  * @retval 无
  */
void W25x_FLASH_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    /* 选择FLASH: CS低电平 */
    SPI1_NSS_SELECT_W25FLASH;

    /* 发送 读 指令 */
    W25x_FLASH_ReadWriteByte(W25x_Cmd_ReadData);

    /* 发送 读 地址高位 */
    W25x_FLASH_ReadWriteByte((ReadAddr & 0xFF0000) >> 16);
    /* 发送 读 地址中位 */
    W25x_FLASH_ReadWriteByte((ReadAddr & 0xFF00) >> 8);
    /* 发送 读 地址低位 */
    W25x_FLASH_ReadWriteByte(ReadAddr & 0xFF);

    /* 读取数据 */
    while (NumByteToRead--)
    {
        /* 读取一个字节*/
        *pBuffer = W25x_FLASH_ReadWriteByte(W25x_Cmd_Dummy_Byte);
        /* 指向下一个字节缓冲区 */
        pBuffer++;
    }

    /* 取选 FLASH: CS 高电平 */
    SPI1_NSS_notSELECT_W25FLASH;
}

/**
  * @brief  擦除FLASH扇区，整片擦除
  * @param  无
  * @retval 无
  */
void W25x_FLASH_BulkErase(void)
{
    /* 发送FLASH写使能命令 */
    W25x_FLASH_WriteEnable();

    /* 整块 Erase */
    /* 选择FLASH: CS低电平 */
    SPI1_NSS_SELECT_W25FLASH;
    /* 发送整块擦除指令*/
    W25x_FLASH_ReadWriteByte(W25x_Cmd_ChipErase);
    /* 取选 FLASH: CS 高电平 */
    SPI1_NSS_notSELECT_W25FLASH;

    /* 等待擦除完毕*/
    W25x_FLASH_WaitForWriteEnd();
}

/**
  * @brief  等待超时回调函数
  * @param  None.
  * @retval None.
  */
static uint8_t W25x_SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
    /* 等待超时后的处理,输出错误信息 */
    W25x_FLASH_ERROR("SPI Time out! ErrorCode = %d", errorCode);
    return 0;
}