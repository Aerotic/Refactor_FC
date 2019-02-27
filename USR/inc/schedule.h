/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-27 9:51:30 am
 * @copyright APPI SASU
 */
#ifndef _SCHEDULE_H
#define _SCHEDULE_H
#include <stdint.h>

struct _SCHEDULE
{
	uint16_t cnt_1ms;
	uint16_t cnt_2ms;
	uint16_t cnt_5ms;
	uint16_t cnt_10ms;
	uint16_t cnt_20ms;
	uint16_t cnt_50ms;
};

void Loop_1000Hz(void); //1ms执行一次
void Loop_500Hz(void);  //2ms执行一次
void Loop_200Hz(void);  //5ms执行一次
void Loop_100Hz(void);  //10ms执行一次
void Loop_50Hz(void);   //20ms执行一次
void Loop_20Hz(void);   //50ms执行一次

void Loop(void);

extern struct _SCHEDULE mSCH;

#endif