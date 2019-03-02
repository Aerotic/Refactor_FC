/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-28 6:22:05 pm
 * @copyright APPI SASU
 */
#ifndef _SPI1_H_
#define _SPI1_H_
#include "bsp.h"

void SPI1_Init(void);// SPI1配置
uint8_t SPI1_ReadWriteByte(uint8_t txbyte);//SPI1 读写一个byte
void SPI1_SetSpeed(uint8_t spi_brps);


#endif