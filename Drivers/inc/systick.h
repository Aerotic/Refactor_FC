/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-27 10:23:01 am
 * @copyright APPI SASU
 */
#ifndef _SYSTICK_H_
#define _SYSTICK_H_
#include "bsp.h"

extern volatile uint32_t SysTickUptime;
#define TICK_PER_SECOND 1000 
#define TICK_US	(1000000/TICK_PER_SECOND)

void SysTick_Init(void);
void SysTick_Handler(void);
#endif