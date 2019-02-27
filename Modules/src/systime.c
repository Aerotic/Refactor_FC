/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-27 11:17:09 am
 * @copyright APPI SASU
 */
#include "systime.h"

volatile float SysT[TIME_ITEM_NUM][3];
#define NOW 0
#define OLD 1
#define NEW 2

void initTimeIntervals(void)
{
    uint8_t i;
    for( i = 0; i < TIME_ITEM_NUM; i++) getTimeInterval(i);
}

void initSysTime(void)
{
    initTimeIntervals();
}

// 获取自上电起系统运行的时间，以微秒为单位
uint32_t getSysTime_us(void)
{
    register uint32_t ms;
    uint32_t value;
    ms = SysTickUptime;
    value = ms * TICK_US + (SysTick->LOAD - SysTick->VAL) * TICK_US / SysTick->LOAD;
    return value;
}

// 阻塞式等待，以微秒为单位
void delay_us(uint32_t us)
{
    uint32_t now = getSysTime_us();
    while (getSysTime_us() - now < us)
        ;
}

// 阻塞式等待，以毫秒为单位
void delay_ms(uint32_t ms)
{
    /*错误实例：此种延时会概率性出错
    **可能会产生delayus(1000)失效引起的delayms()失效
    **		uint32_t tmp = ms * 1000 ;
    **    DelayUs(tmp);
    **		tmp = 0;
    */
    while (ms--)
        delay_us(1000);
}

void getTimeInterval(uint8_t item)
{
    SysT[item][OLD] = SysT[item][NOW];                       //上一次的时间
    SysT[item][NOW] = GetSysTime_us() / 1000000.0f;          //本次的时间
    SysT[item][NEW] = ((SysT[item][NOW] - SysT[item][OLD])); //时间间隔
    return SysT[item][NEW];
}