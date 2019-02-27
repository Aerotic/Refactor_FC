/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-27 11:17:09 am
 * @copyright APPI SASU
 */
#include "systime.h"

void initTimeIntervals(void)
{
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
    while (getSysTime_us() - now < us);
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