#ifndef _SPI1_H_
#define _SPI1_H_
#include "bsp.h"

    /*
     * SPI1 settings
     * 
    */
    #define SPI1_DIRECTION  SPI_Direction_2Lines_FullDuplex
    #define SPI1_MODE       SPI_Mode_Master
    #define SPI1_DATASIZE   SPI_DataSize_8b
    #define SPI1_CPOL       SPI_CPOL_Low
    #define SPI1_CPHA       SPI_CPHA_1Edge
    #define SPI1_NSS        SPI_NSS_Soft
    #define SPI1_BRPS       SPI_BaudRatePrescaler_8
    #define SPI1_FIRSTBIT   SPI_FirstBit_MSB
    #define SPI1_CRCPOLY    7


    /*
    **RCC settings
    */
	#define SPI1_RCC_AHB			RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_DMA2
	#define SPI1_RCC_APB			RCC_APB2Periph_SPI1


	/*
     * GPIO settings
	*/
	#define SPI1_GPIO_PORT1		GPIOA
	#define SPI1_GPIO_PORT2		GPIOB
	#define SPI1_PIN_MOSI		GPIO_Pin_7          //PA7
	#define SPI1_PIN_MISO		GPIO_Pin_4          //PB4
    #define SPI1_PIN_SCK   		GPIO_Pin_5          //PA5
	#define SPI1_PIN_NSS		GPIO_Pin_4          //PA4
	#define SPI1_GPIOSRC_MOSI	GPIO_PinSource7
	#define SPI1_GPIOSRC_MISO	GPIO_PinSource4
    #define SPI1_GPIOSRC_SCK	GPIO_PinSource5
	#define SPI1_GPIOSRC_NSS	GPIO_PinSource4


#endif