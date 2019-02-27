---
    Title: README.MD
    Author: Aeroman
---
## 名词解释
- 1. 外设 Peripheral 
    指的是STM32芯片片上除了Cortex-M4核心(Core)的部分，例如usart/uart(异步串行通信接口，简称串口)、spi(串行外设通信接口)、rng(随机数生成器)等等
- 2. 模块 Module 
    指的是STM32芯片之外的IC等模块，可以实现一定的功能，比如MPU6050模块





### 关于各种外设如usart的相关设置
在[Drivers](../Drivers)文件夹下，进入相应的头文件下修好
#### 例子
需要修改usart2的波特率，进入[Drivers/usart2.h]()，修改宏USART2_BAUDRATE即可

### 关于引入新外设相关头文件的设置
在经过[bsp.h]()进入[stm32f4xx_conf.h]()去掉相应的外设头文件即可