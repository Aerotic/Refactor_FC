#include "spi1.h"

void SPI1_Init(void)
{	 
    GPIO_InitTypeDef  GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//PB5~7¸´ÓÃ¹¦ÄÜÊä³ö	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//¸´ÓÃ¹¦ÄÜ
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//ÍÆÍìÊä³ö
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//ÉÏÀ­
    GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»¯
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1); //PA5¸´ÓÃÎª SPI1  CLK
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_SPI1); //PA6¸´ÓÃÎª SPI1  MISO
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1); //PA7¸´ÓÃÎª SPI1  MOSI

	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);//Í£Ö¹¸´Î»SPI1

	SPI_InitStructure.SPI_Direction = SPI1_DIRECTION;
	SPI_InitStructure.SPI_Mode = SPI1_MODE;		
	SPI_InitStructure.SPI_DataSize = SPI1_DATASIZE;
	SPI_InitStructure.SPI_CPOL = SPI1_CPOL;	
	SPI_InitStructure.SPI_CPHA = SPI1_CPHA;	
	SPI_InitStructure.SPI_NSS = SPI1_NSS;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI1_BRPS;
	SPI_InitStructure.SPI_FirstBit = SPI1_FIRSTBIT;
	SPI_InitStructure.SPI_CRCPolynomial = SPI1_CRCPOLY;
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
}   
//SPI1ËÙ¶ÈÉèÖÃº¯Êý
//SPIËÙ¶È=fAPB2/·ÖÆµÏµÊý
//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
//fAPB2Ê±ÖÓÒ»°ãÎª84Mhz£º
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//ÅÐ¶ÏÓÐÐ§ÐÔ
	SPI1->CR1&=0XFFC7;//Î»3-5ÇåÁã£¬ÓÃÀ´ÉèÖÃ²¨ÌØÂÊ
	SPI1->CR1|=SPI_BaudRatePrescaler;	//ÉèÖÃSPI1ËÙ¶È 
	SPI_Cmd(SPI1,ENABLE); //Ê¹ÄÜSPI1
} 
//SPI1 ¶ÁÐ´Ò»¸ö×Ö½Ú
//TxData:ÒªÐ´ÈëµÄ×Ö½Ú
//·µ»ØÖµ:¶ÁÈ¡µ½µÄ×Ö½Ú
u8 SPI1_ReadWriteByte(u8 TxData)
{		 			 
 
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}//µÈ´ý·¢ËÍÇø¿Õ  
	
	SPI_I2S_SendData(SPI1, TxData); //Í¨¹ýÍâÉèSPIx·¢ËÍÒ»¸öbyte  Êý¾Ý
		
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){} //µÈ´ý½ÓÊÕÍêÒ»¸öbyte  
 
	return SPI_I2S_ReceiveData(SPI1); //·µ»ØÍ¨¹ýSPIx×î½ü½ÓÊÕµÄÊý¾Ý	
 		    
}
