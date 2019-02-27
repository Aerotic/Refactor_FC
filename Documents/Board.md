---
 Author: Aero
 Description: 此为407FCB2.0飞控板的板上资源介绍
---

- 1. USART1
    USART1-RX PA10
    USART1-TX PA9
    用以对外USB-TTL通信，可用作下载口

- 2. USART2
    USART2-RX PA3
    USART2-TX PA2
    用以备用串口，可外接GPS或者其他基于串口的无线模块

- 3. USART3
    USART3-RX PD9
    用以S.Bus协议接口

- 4. SPI1
    SPI1-MOSI PA7 ---> W25Q-DI
    SPI1-MISO PB4 ---> W25Q-DO
    SPI1-SCK  PA5 ---> W25Q-CLK
    SPI1-NSS  PA4 ---> W25Q-nCS
    W25Q-nWP  PA1
    W25Q-nRST PA0
    外部Flash通信接口

- 5. TIM3
    TIM3-CH1 PA6
    TIM3-CH2 PC7
    TIM3-CH3 PC8
    TIM3-CH4 PB1
    用以输出PWM

- 6. LED
    LED0 PC14
    LED1 PE6
    LED2 PC13
    LED3 PC15
