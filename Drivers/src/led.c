/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-27 9:52:10 am
 * @copyright APPI SASU
 */
#include "led.h"

void cfgLED(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_AHB1PeriphClockCmd(LED_RCC_AHB , ENABLE );
	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN0 | LED_GPIO_PIN2 | LED_GPIO_PIN3 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(LED_GPIO_PORT0,&GPIO_InitStructure);

    RCC_AHB1PeriphClockCmd(LED_RCC_AHB , ENABLE );
	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(LED_GPIO_PORT1,&GPIO_InitStructure);

    LED0_OFF;
    LED1_OFF;
    LED2_OFF;
    LED3_OFF;

}
void runLEDs(uint8_t times){
    uint8_t i;
    for( i = 0; i < times; i++)
    {
        LED0_ON;
        LED1_OFF;
        LED2_OFF;
        LED3_OFF;

        LED0_OFF;
        LED1_ON;
        LED2_OFF;
        LED3_OFF;

        LED0_OFF;
        LED1_OFF;
        LED2_ON;
        LED3_OFF;

        LED0_OFF;
        LED1_OFF;
        LED2_OFF;
        LED3_ON;        
    }
    
}