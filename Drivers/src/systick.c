/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-26 3:07:40 pm
 */
#include "systick.h"

volatile uint32_t SysTickUptime=0;


void cfgSysTick(){
    RCC_ClocksTypeDef RCC_ClocksInitStructure;
    uint32_t cnts;

    RCC_GetClocksFreq(&RCC_ClocksInitStructure);
    cnts = (uint32_t)RCC_ClocksInitStructure.HCLK_Frequency / TICK_PER_SECOND; //cnts=HCLK
    cnts = cnts / 8;                                              //cnts=HCLK/8
    SysTick_Config(cnts);
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); //HCLK/8  set freq divider
}

void SysTick_Handler(void)
{
	SysTickUptime++;
}

