/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-28 6:07:06 pm
 * @copyright APPI SASU
 */
#ifndef _BSP_H_
#define _BSP_H_
#include "stdint.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

// USART1 settings
// 波特率512k 停止位1 无校验 无流控 全双工 且DMA buff长为14
// 功能1: 用以与Android通信 
// 功能2: 用于串口打印
// 功能3: 串口下载(待定)
#define USART1_BAUDRATE 115200
#define USART1_WORDLEN USART_WordLength_8b
#define USART1_STOPBIT USART_StopBits_1
#define USART1_PARITY USART_Parity_No
#define USART1_HWFLOWCTRL USART_HardwareFlowControl_None
#define USART1_MODE USART_Mode_Tx | USART_Mode_Rx
#define USART1_RCC_AHB RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_DMA2
#define USART1_RCC_APB RCC_APB2Periph_USART1
#define USART1_GPIO_PORT GPIOA
#define USART1_PIN_TX GPIO_Pin_9
#define USART1_PIN_RX GPIO_Pin_10
#define USART1_GPIO_TXSRC GPIO_PinSource9
#define USART1_GPIO_RXSRC GPIO_PinSource10
#define USART1RXBUF_SIZE 14
#define USART1TXBUF_SIZE 14

// USART2 settings
// 波特率115.2k 停止位1 无校验 无流控 全双工 且DMA buff长为14
// 功能1: 备用 可接GPS
#define USART2_BAUDRATE 115000
#define USART2_WORDLEN USART_WordLength_8b
#define USART2_STOPBIT USART_StopBits_1
#define USART2_PARITY USART_Parity_No
#define USART2_HWFLOWCTRL USART_HardwareFlowControl_None
#define USART2_MODE USART_Mode_Rx | USART_Mode_Tx
#define USART2_RCC_AHB RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_DMA1
#define USART2_RCC_APB RCC_APB1Periph_USART2
#define USART2_GPIO_PORT GPIOA
#define USART2_PIN_TX GPIO_Pin_2
#define USART2_PIN_RX GPIO_Pin_3
#define USART2_GPIO_TXSRC GPIO_PinSource2
#define USART2_GPIO_RXSRC GPIO_PinSource3
#define USART2RXBUF_SIZE 2
#define USART2TXBUF_SIZE 2

// USART3 settings
// 波特率100k 停止位2 偶校验 无流控 仅接收数据 且DMA buff长为25
//功能1: 用以配合使用s.Bus通信协议 
#define USART3_BAUDRATE 100000
#define USART3_WORDLEN USART_WordLength_8b
#define USART3_STOPBIT USART_StopBits_2
#define USART3_PARITY USART_Parity_Even
#define USART3_HWFLOWCTRL USART_HardwareFlowControl_None
#define USART3_MODE USART_Mode_Rx
#define USART3_RCC_AHB RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_DMA1
#define USART3_RCC_APB RCC_APB1Periph_USART3
#define USART3_GPIO_PORT GPIOD
#define USART3_PIN_TX GPIO_Pin_8
#define USART3_PIN_RX GPIO_Pin_9
#define USART3_GPIO_TXSRC GPIO_PinSource8
#define USART3_GPIO_RXSRC GPIO_PinSource9
#define USART3RXBUF_SIZE 2
#define USART3TXBUF_SIZE

// LED settings
#define LED_RCC_AHB RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE
#define LED_GPIO_PORT0 GPIOC
#define LED_GPIO_PORT1 GPIOE
#define LED_GPIO_PIN0 GPIO_Pin_14 //PC14
#define LED_GPIO_PIN1 GPIO_Pin_6  //PE6
#define LED_GPIO_PIN2 GPIO_Pin_13 //PC13
#define LED_GPIO_PIN3 GPIO_Pin_15 //PC15

//SoftI2C settings
#define SOFTI2C_RCC_AHB	      RCC_AHB1Periph_GPIOB
#define SOFTI2C_GPIO_PORT      GPIOB
#define SOFTI2C_PIN_SCL   GPIO_Pin_13
#define SOFTI2C_PIN_SDA   GPIO_Pin_12

// SystemTime settings
#define TIMEINTERVAL_DBUS       0
#define TIMEINTERVAL_TASK500HZ  1
#define TIMEINTERVAL_TASK200HZ  2
#define TIMEINTERVAL_TASK100HZ  3
#define TIMEINTERVAL_TASK50HZ   4
#define TIMEINTERVAL_TASK20HZ   5
#define TIME_ITEM_NUM           6

// SPI1 settings
#define SPI1_RCC_APB2   RCC_APB2Periph_SPI1
#define SPI1_RCC_AHB1   RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB
#define SPI1_GPIO_PORT0 GPIOA
#define SPI1_GPIO_PORT1 GPIOB
#define SPI1_PIN_MOSI   GPIO_Pin_7  //PA7
#define SPI1_SRC_MOSI   GPIO_PinSource7
#define SPI1_PIN_MISO   GPIO_Pin_4  //PB4
#define SPI1_SRC_MISO   GPIO_PinSource4
#define SPI1_PIN_SCK    GPIO_Pin_5  //PA5
#define SPI1_SRC_SCK    GPIO_PinSource5
#define SPI1_PIN_NSS    GPIO_Pin_4  //PA4 用以片选W25Q128
#define SPI1_DIRECTION  SPI_Direction_2Lines_FullDuplex
#define SPI1_MODE       SPI_Mode_Master
#define SPI1_DATASIZE   SPI_DataSize_8b
#define SPI1_CPOL       SPI_CPOL_High
#define SPI1_CPHA       SPI_CPHA_2Edge
#define SPI1_NSS        SPI_NSS_Soft
#define SPI1_BAUDRATEPS SPI_BaudRatePrescaler_4
#define SPI1_FIRSTBIT   SPI_FirstBit_MSB
#define SPI1_CRCPOLY    7
#define SPI1_NSS_SELECT_W25FLASH    SPI1_GPIO_PORT0->BSRRH = SPI1_PIN_NSS
#define SPI1_NSS_notSELECT_W25FLASH     SPI1_GPIO_PORT0->BSRRL = SPI1_PIN_NSS


// W25x_flash settings
#define W25x_RCC_AHB1       RCC_AHB1Periph_GPIOA
#define W25x_GPIO_PORT      GPIOA
#define W25x_PIN_NWP        GPIO_Pin_1 //PA1
#define W25x_PIN_NRST       GPIO_Pin_0 //PA0
#define W25x_FLASH_SPI      SPI1



/******Drivers*******/
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "led.h"
#include "systick.h"
#include "softi2c.h"
#include "spi1.h"

/******Modules*******/
#include "serialprint.h"
#include "systime.h"
#include "w25x_flash.h"


void initPeriphals(void);
void initModules(void);
#endif
// #error '\n'*******BSP'\n'*******
