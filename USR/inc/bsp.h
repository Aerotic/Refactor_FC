/**
 * @author Firstname Lastname <firstname.lastname@example.com>
 * @file Description
 * @desc Created on 2019-02-25 9:10:49 pm
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

/******Drivers*******/
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "led.h"
#include "systick.h"

/******Modules*******/
#include "serialprint.h"


void initPeriphals(void);
void initModules(void);
#endif
// #error '\n'*******BSP'\n'*******
