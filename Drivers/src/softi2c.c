/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description
 * @desc Created on 2019-02-27 4:53:12 pm
 * @copyright APPI SASU
 */
#include "softi2c.h"

uint8_t I2C_FastMode;

void initSoftI2C(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(SOFTI2C_RCC_AHB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = SOFTI2C_PIN_SCL | SOFTI2C_PIN_SDA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(SOFTI2C_GPIO_PORT, &GPIO_InitStructure);
}

void SoftI2C_Delay(void)
{
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();

    if (!I2C_FastMode)
    {
        uint8_t i = 15;
        while (i--)
            ;
    }
}

int SoftI2C_Start(void)
{
    SDA_H;
    SCL_H;
    SoftI2C_Delay();
    if (!SDA_READ)
        return 0; //SDA为低电平则总线忙，退出
    SDA_L;
    SoftI2C_Delay();
    if (SDA_READ)
        return 0; //SDA为高电平则总线出错，退出
    SDA_L;
    SoftI2C_Delay();
    return 1;
}

void SoftI2C_Stop(void)
{
    SCL_L;
    SoftI2C_Delay();
    SDA_L;
    SoftI2C_Delay();
    SCL_H;
    SoftI2C_Delay();
    SDA_H;
    SoftI2C_Delay();
}

void SoftI2C_Ack(void)
{
    SCL_L;
    SoftI2C_Delay();
    SDA_L;
    SoftI2C_Delay();
    SCL_H;
    SoftI2C_Delay();
    SCL_L;
    SoftI2C_Delay();
}

void SoftI2C_NoAck(void)
{
    SCL_L;
    SoftI2C_Delay();
    SDA_H;
    SoftI2C_Delay();
    SCL_H;
    SoftI2C_Delay();
    SCL_L;
    SoftI2C_Delay();
}

// 返回为1则有ACK,为0则无ACK
int SoftI2C_WaitAck(void)
{
    SCL_L;
    SoftI2C_Delay();
    SDA_H;
    SoftI2C_Delay();
    SCL_H;
    SoftI2C_Delay();
    if (SDA_READ)
    {
        SCL_L;
        SoftI2C_Delay();
        return 0;
    }
    SCL_L;
    SoftI2C_Delay();
    return 1;
}

//数据由高位到低位
void SoftI2C_SendByte(uint8_t sendbyte)
{
    uint8_t i = 8;
    while (i--)
    {
        SCL_L;
        SoftI2C_Delay();
        if (sendbyte & 0x80)
            SDA_H;
        else
            SDA_L;
        sendbyte <<= 1;
        SoftI2C_Delay();
        SCL_H;
        SoftI2C_Delay();
    }
    SCL_L;
}

//数据由高位到低位
uint8_t SoftI2C_ReadByte(void) 
{
    uint8_t i = 8;
    uint8_t receivebyte = 0;

    SDA_H;
    while (i--)
    {
        receivebyte <<= 1;
        SCL_L;
        SoftI2C_Delay();
        SCL_H;
        SoftI2C_Delay();
        if (SDA_READ)
        {
            receivebyte |= 0x01;
        }
    }
    SCL_L;
    return receivebyte;
}

//单字节写入
int SoftI2C_SingleByte_Write(uint8_t slave_address, uint8_t reg_address, uint8_t reg_data)
{
    if (!SoftI2C_Start())
        return 0;
    SoftI2C_SendByte(slave_address); //·¢ËÍÉè±¸µØÖ·+Ð´ÐÅºÅ//I2C_SendByte(((reg_address & 0x0700) >>7) | slave_address & 0xFFFE);//ÉèÖÃ¸ßÆðÊ¼µØÖ·+Æ÷¼þµØÖ·
    if (!SoftI2C_WaitAck())
    {
        SoftI2C_Stop();
        return 0;
    }
    SoftI2C_SendByte(reg_address); //ÉèÖÃµÍÆðÊ¼µØÖ·
    SoftI2C_WaitAck();
    SoftI2C_SendByte(reg_data);
    SoftI2C_WaitAck();
    SoftI2C_Stop();
    return 1;
}

//单字节读取
int SoftI2C_SingleByte_Read(uint8_t slave_address, uint8_t reg_address)
{
    unsigned char reg_data;
    if (!SoftI2C_Start())
        return 0;
    SoftI2C_SendByte(slave_address); //I2C_SendByte(((reg_address & 0x0700) >>7) | reg_address & 0xFFFE);//设置高起始地址
    if (!SoftI2C_WaitAck())
    {
        SoftI2C_Stop();
        return 0;
    }
    SoftI2C_SendByte((uint8_t)reg_address); //设置低起始地址
    SoftI2C_WaitAck();
    SoftI2C_Start();
    SoftI2C_SendByte(slave_address + 1);
    SoftI2C_WaitAck();

    reg_data = SoftI2C_ReadByte();
    SoftI2C_NoAck();
    SoftI2C_Stop();
    return reg_data;
}

//多字节读取
int SoftI2C_MultiByte_Read(uint8_t slave_address, uint8_t reg_address, uint8_t *ptchar, uint8_t size)
{
    uint8_t i;

    if (size < 1)
        return 0;
    if (!SoftI2C_Start())
        return 0;
    SoftI2C_SendByte(slave_address);
    if (!SoftI2C_WaitAck())
    {
        SoftI2C_Stop();
        return 0;
    }
    SoftI2C_SendByte(reg_address);
    SoftI2C_WaitAck();

    SoftI2C_Start();
    SoftI2C_SendByte(slave_address + 1);
    SoftI2C_WaitAck();

    for (i = 1; i < size; i++)
    {
        *ptchar++ = SoftI2C_ReadByte();
        SoftI2C_Ack();
    }
    *ptchar++ = SoftI2C_ReadByte();
    SoftI2C_NoAck();
    SoftI2C_Stop();
    return 1;
}
