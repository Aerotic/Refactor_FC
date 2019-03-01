/**
 * @author Firstname Lastname <firstname.lastname@example.com>
 * @file Description
 * @desc Created on 2019-02-26 2:48:39 pm
 * @copyright APPI SASU
 */
#include "bsp.h"

void initPeriphals(void)
{

  // 中断优先级组别设置为3
  // 即抢占式优先级分为8级，次优先级分为2级
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);

  // USART1 settings
  // 波特率512k 停止位1 无校验 无流控 全双工 且DMA buff长为14
  // 用以与Android通信
  // 且用于串口打印
  USART1_Init();

  // USART2 settings
  // 波特率115.2k 停止位1 无校验 无流控 全双工 且DMA buff长为14
  // 用以备用
  USART2_Init();

  // USART3 settings
  // 波特率100k 停止位2 偶校验 无流控 仅接收数据 且DMA buff长为25
  // 用以配合使用s.Bus通信协议
  USART3_Init();

  // LED settings
  LED_Init();

  // SysTick settings
  // 用以系统计时
  SysTick_Init();

  // Soft I2C settings
  initSoftI2C();
}

void initModules(void)
{
  // 设置USART2为串口打印口
  setSerialPrintPort(USART2);
  initSysTime();
  
}
