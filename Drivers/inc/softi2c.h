/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-27 4:56:15 pm
 * @copyright APPI SASU
 */
#ifndef _SOFTI2C_H_
#define _SOFTI2C_H_
#include "bsp.h"
#define SCL_H SOFTI2C_GPIO_PORT->BSRRL = SOFTI2C_PIN_SCL
#define SCL_L SOFTI2C_GPIO_PORT->BSRRH = SOFTI2C_PIN_SCL
#define SDA_H SOFTI2C_GPIO_PORT->BSRRL = SOFTI2C_PIN_SDA
#define SDA_L SOFTI2C_GPIO_PORT->BSRRH = SOFTI2C_PIN_SDA
#define SDA_READ SOFTI2C_GPIO_PORT->IDR &SOFTI2C_PIN_SDA

void initSoftI2C(void);
void SoftI2C_Delay(void);
int SoftI2C_Start(void);
void SoftI2C_Stop(void);
void SoftI2C_Ack(void);
void SoftI2C_NoAck(void);
int SoftI2C_WaitAck(void);
void SoftI2C_SendByte(uint8_t SendByte);
uint8_t SoftI2C_ReadByte(void);

int SoftI2C_SingleByte_Write(uint8_t SlaveAddress, uint8_t REG_Address, uint8_t REG_data);
int SoftI2C_SingleByte_Read(uint8_t SlaveAddress, uint8_t REG_Address);
int SoftI2C_MultiByte_Read(uint8_t SlaveAddress, uint8_t REG_Address, uint8_t *ptChar, uint8_t size);

extern uint8_t I2C_FastMode;
#endif