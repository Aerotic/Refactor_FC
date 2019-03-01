/**
 * @author Aero <neuhutao@gmail.com>
 * @file Description: USART2配置
 * @desc Created on 2019-02-26 2:51:25 pm
 */
#include "usart2.h"

uint8_t USART2_Rx_Buffer[USART2RXBUF_SIZE];
uint8_t USART2_Tx_Buffer[USART2RXBUF_SIZE];

void USART2_Init(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//时钟配置
	RCC_AHB1PeriphClockCmd(USART2_RCC_AHB, ENABLE); //配置GPIOA和DMA1的时钟
	RCC_APB1PeriphClockCmd(USART2_RCC_APB, ENABLE); //配置USART2的时钟

	//GPIO配置
	GPIO_PinAFConfig(USART2_GPIO_PORT, USART2_GPIO_TXSRC, GPIO_AF_USART2); //使能该引脚的第二功能
	GPIO_PinAFConfig(USART2_GPIO_PORT, USART2_GPIO_RXSRC, GPIO_AF_USART2); //使能该引脚的第二功能
	GPIO_InitStructure.GPIO_Pin = USART2_PIN_TX | USART2_PIN_RX;		   //选择要配置的引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;						   //开启第二功能模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;						   //设置输出模式为推挽模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;					   //设置引脚的速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;					   //设置引脚的上下拉模式
	GPIO_Init(USART2_GPIO_PORT, &GPIO_InitStructure);					   //生效GPIO的设置

	//USART配置
	USART_DeInit(USART2);
	// USART_Cmd(USART2, DISABLE);										   //关闭USART
	USART_InitStructure.USART_BaudRate = USART2_BAUDRATE;			   //设置波特率
	USART_InitStructure.USART_WordLength = USART2_WORDLEN;			   //设置数据位长度
	USART_InitStructure.USART_StopBits = USART2_STOPBIT;			   //设置停止位长度
	USART_InitStructure.USART_Parity = USART2_PARITY;				   //设置
	USART_InitStructure.USART_Mode = USART2_MODE;					   //设置通信模式
	USART_InitStructure.USART_HardwareFlowControl = USART2_HWFLOWCTRL; //设置硬件流控制
	USART_Init(USART2, &USART_InitStructure);						   //生效USART的配置

	//数据接收DMA配置---不定长数据接收模式
	DMA_DeInit(DMA1_Stream5);												//失效DMA配置
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;							//设置DMA的通道
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (USART2->DR);   //设置片上外设即USART数据寄存器的基址
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)USART2_Rx_Buffer;		//设置内存的基址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;					//设置DMA的传输方向
	DMA_InitStructure.DMA_BufferSize = 128;									//设置DMA的数据缓存区的长度----最长可接收128byte的数据
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//设置DMA的外设递增模式,若是该DMA所在channel下仅一个相关外设则可设置为DISABLE
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//设置DMA的内存递增模式,若是该DMA所在channel下仅一段相关内存则可设置为DISABLE
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //设置DMA访问片上外设时操作的的数据的长度
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//设置DMA访问内存时操作的的数据的长度
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							//设置DMA传输模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;					//设置DMA优先级
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;					//设置是否开启FIFO
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;   //设置FIFO的深度
	DMA_InitStructure.DMA_MemoryBurst = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; //设置burst相关
	DMA_Init(DMA1_Stream5, &DMA_InitStructure);							//使能DMA

	//数据接收DMA中断配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;		  //设置中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //设置中断优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		  //设置中断次优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //开启中断通道
	NVIC_Init(&NVIC_InitStructure);							  //生效配置
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);			  //设置USART的中断模式
	//数据发送DMA配置
	DMA_DeInit(DMA1_Stream6);												//失效DMA配置
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;							//设置DMA的通道
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (USART2->DR);   //设置片上外设即USART数据寄存器的基址
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)USART2_Tx_Buffer;		//设置内存的基址
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;					//设置DMA的传输方向
	DMA_InitStructure.DMA_BufferSize = USART2RXBUF_SIZE;					//设置DMA的数据缓存区的长度
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//设置DMA的外设递增模式,若是该DMA所在channel下仅一个相关外设则可设置为DISABLE
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//设置DMA的内存递增模式,若是该DMA所在channel下仅一段相关内存则可设置为DISABLE
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //设置DMA访问片上外设时操作的的数据的长度
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//设置DMA访问内存时操作的的数据的长度
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							//设置DMA传输模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;					//设置DMA优先级
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;					//设置是否开启FIFO
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;   //设置FIFO的深度
	DMA_InitStructure.DMA_MemoryBurst = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; //设置burst相关
	DMA_Init(DMA1_Stream6, &DMA_InitStructure);							//使能DMA

	//数据发送DMA中断配置
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;   //设置中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //设置中断优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		  //设置中断次优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //开启中断通道
	NVIC_Init(&NVIC_InitStructure);							  //生效配置
	DMA_ITConfig(DMA1_Stream6, DMA_IT_TC, ENABLE);			  //设置DMA的中断模式并开启中断

	//开启传输
	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
	USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);
	DMA_Cmd(DMA1_Stream5, ENABLE);  //开启接收DMA
	DMA_Cmd(DMA1_Stream6, DISABLE); //关闭发送DMA流,待发送时开启
	USART_Cmd(USART2, ENABLE);		//开启USART

}

void USART2_WriteByte(uint8_t txbyte)
{
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	USART_SendData(USART2, txbyte);
}
void USART2_StartTxDMA(void)
{
	DMA_SetCurrDataCounter(DMA1_Stream6, USART2TXBUF_SIZE);
	DMA_Cmd(DMA1_Stream6, ENABLE);
}

void USART2_IRQHandler(void)
{
	uint8_t num_1;
	uint16_t data_len_1;
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		data_len_1 = 128 - DMA_GetCurrDataCounter(DMA1_Stream5);
		num_1 = USART2->SR;
		num_1 = USART2->DR;
		DMA_Cmd(DMA1_Stream5, DISABLE);
		DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TEIF5 | DMA_FLAG_TCIF5 | DMA_FLAG_DMEIF5 | DMA_FLAG_HTIF5 | DMA_FLAG_FEIF5);//清除标志
		DMA_SetCurrDataCounter(DMA1_Stream5, 128);//设置DMA数据计数器为buffsize以开始下一轮接收
		//do sth
		printf("Received!");
		USART_ClearITPendingBit(USART2, USART_IT_IDLE);//清除挂起标志位
	}
}

void DMA1_Stream6_IRQHandler(void)
{
	if (DMA_GetITStatus(DMA1_Stream6, DMA_IT_TCIF6))
	{
		DMA_ClearFlag(DMA1_Stream6, DMA_FLAG_TCIF6);
		DMA_ClearITPendingBit(DMA1_Stream6, DMA_IT_TCIF6);
		DMA_Cmd(DMA1_Stream6, DISABLE);
	}
}