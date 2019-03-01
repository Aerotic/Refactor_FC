/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-27 9:45:37 am
 * @copyright APPI SASU
 */
#ifndef _LED_H_
#define _LED_H_
#include "bsp.h"

#define LED0_OFF    LED_GPIO_PORT0->BSRRL = LED_GPIO_PIN0
#define LED0_ON     LED_GPIO_PORT0->BSRRH = LED_GPIO_PIN0
#define LED0_TOGGLE LED_GPIO_PORT0->ODR  ^= LED_GPIO_PIN0

#define LED1_OFF    LED_GPIO_PORT1->BSRRL = LED_GPIO_PIN1
#define LED1_ON	    LED_GPIO_PORT1->BSRRH = LED_GPIO_PIN1
#define LED1_TOGGLE LED_GPIO_PORT1->ODR  ^= LED_GPIO_PIN1

#define LED2_OFF    LED_GPIO_PORT0->BSRRL = LED_GPIO_PIN2
#define LED2_ON     LED_GPIO_PORT0->BSRRH = LED_GPIO_PIN2
#define LED2_TOGGLE LED_GPIO_PORT0->ODR  ^= LED_GPIO_PIN2

#define LED3_OFF    LED_GPIO_PORT0->BSRRL = LED_GPIO_PIN3
#define LED3_ON     LED_GPIO_PORT0->BSRRH = LED_GPIO_PIN3
#define LED3_TOGGLE LED_GPIO_PORT0->ODR  ^= LED_GPIO_PIN3

void LED_Config(void);
void runLEDs(uint8_t times);
void blinkLEDs(void);
#endif