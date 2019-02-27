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
  // 用以与Android通信
  // 且用于串口打印
  // 波特率512k 停止位1 无校验 无流控 全双工 且DMA buff长为14
  cfgUSART1();

  // USART2 settings
  // 用以备用
  // 波特率115.2k 停止位1 无校验 无流控 全双工 且DMA buff长为14
  cfgUSART2();

  // USART3 settings
  // 用以配合使用s.Bus通信协议
  // 波特率100k 停止位2 偶校验 无流控 仅接收数据 且DMA buff长为25
  cfgUSART3();

  // LED settings
  cfgLED();

  // SysTick settings
  // 用以系统计时
  cfgSysTick();
}

void initModules(void)
{
  // 设置USART2为串口打印口
  setSerialPrintPort(USART2);
}
