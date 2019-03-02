/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-28 5:49:20 pm
 * @copyright APPI SASU
 */
#include "spi1.h"

void SPI1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	RCC_AHB1PeriphClockCmd(SPI1_RCC_AHB1, ENABLE);
	RCC_APB2PeriphClockCmd(SPI1_RCC_APB2, ENABLE);

	GPIO_PinAFConfig(SPI1_GPIO_PORT0, SPI1_SRC_SCK, GPIO_AF_SPI1);	//PA5	SPI1  SCLK
	GPIO_PinAFConfig(SPI1_GPIO_PORT1, SPI1_SRC_MISO, GPIO_AF_SPI1); //PB4	SPI1  MISO
	GPIO_PinAFConfig(SPI1_GPIO_PORT0, SPI1_SRC_MOSI, GPIO_AF_SPI1); //PA7	SPI1  MOSI
	GPIO_InitStructure.GPIO_Pin = SPI1_PIN_SCK | SPI1_PIN_MOSI;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(SPI1_GPIO_PORT0, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SPI1_PIN_MISO;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(SPI1_GPIO_PORT1, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SPI1_PIN_NSS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(SPI1_GPIO_PORT0, &GPIO_InitStructure);

	SPI1_NSS_notSELECT_W25FLASH;



	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);	// 复位SPI1
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE); // 停止复位SPI1

	SPI_InitStructure.SPI_Direction = SPI1_DIRECTION;
	SPI_InitStructure.SPI_Mode = SPI1_MODE;
	SPI_InitStructure.SPI_DataSize = SPI1_DATASIZE;
	SPI_InitStructure.SPI_CPOL = SPI1_CPOL;
	SPI_InitStructure.SPI_CPHA = SPI1_CPHA;
	SPI_InitStructure.SPI_NSS = SPI1_NSS;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI1_BAUDRATEPS;
	SPI_InitStructure.SPI_FirstBit = SPI1_FIRSTBIT;
	SPI_InitStructure.SPI_CRCPolynomial = SPI1_CRCPOLY;
	SPI_Init(SPI1, &SPI_InitStructure);

	SPI_Cmd(SPI1, ENABLE);
}
//SPI1速度设置
//SPI速度=fAPB2/分频系数
//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256
//fAPB2一般为8MHz
void SPI1_SetSpeed(uint8_t spi_brps)
{
	assert_param(IS_SPI_BAUDRATE_PRESCALER(spi_brps)); //判断参数是否正确
	SPI_Cmd(SPI1, DISABLE);
	SPI1->CR1 &= 0XFFC7;																						//复位bit3到bit5，以设置波特率
	SPI1->CR1 |= spi_brps;															//设置速度
	SPI_Cmd(SPI1, ENABLE);
}
//SPI1 读写一个byte
uint8_t SPI1_ReadWriteByte(uint8_t txbyte)
{

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
	{
	} //等待发送区空

	SPI_I2S_SendData(SPI1, txbyte); //发送一个byte

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
	{
	} //等待接收完一个byte

	return SPI_I2S_ReceiveData(SPI1); 
}
