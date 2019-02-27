/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-27 11:20:17 am
 * @copyright APPI SASU
 */
#ifndef _SYSTIME_H_
#define _SYSTIME_H_
#include "bsp.h"
void initSysTime(void);
uint32_t getSysTime_us(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
float getTimeInterval(uint8_t item);
#endif