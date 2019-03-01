/**
 * @author Firstname Lastname <firstname.lastname@example.com>
 * @file Description
 * @desc Created on 2019-02-25 9:00:06 pm
 * @copyright APPI SASU
 */
#include "usart3.h"
uint8_t USART3_Rx_Buffer[USART3RXBUF_SIZE];
void USART3_Init(void){
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//时钟配置
	RCC_AHB1PeriphClockCmd(USART3_RCC_AHB, ENABLE); //配置GPIOD和DMA1的时钟
	RCC_APB1PeriphClockCmd(USART3_RCC_APB, ENABLE); //配置USART3的时钟

	//GPIO配置
	GPIO_PinAFConfig(USART3_GPIO_PORT, USART3_GPIO_RXSRC, GPIO_AF_USART3); //使能该引脚的第二功能
	GPIO_InitStructure.GPIO_Pin = USART3_PIN_RX;		   //选择要配置的引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;						   //开启第二功能模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;						   //设置输出模式为推挽模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;					   //设置引脚的速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;					   //设置引脚的上下拉模式
	GPIO_Init(USART3_GPIO_PORT, &GPIO_InitStructure);					   //生效GPIO的设置
	//USART配置
	USART_Cmd(USART3, DISABLE);										   //关闭USART
	USART_InitStructure.USART_BaudRate = USART3_BAUDRATE;			   //设置波特率
	USART_InitStructure.USART_WordLength = USART3_WORDLEN;			   //设置数据位长度
	USART_InitStructure.USART_StopBits = USART3_STOPBIT;			   //设置停止位长度
	USART_InitStructure.USART_Parity = USART3_PARITY;				   //设置
	USART_InitStructure.USART_Mode = USART3_MODE;					   //设置通信模式
	USART_InitStructure.USART_HardwareFlowControl = USART3_HWFLOWCTRL; //设置硬件流控制
	USART_Init(USART3, &USART_InitStructure);						   //生效USART的配置

	//数据接收DMA配置
	DMA_DeInit(DMA1_Stream1);												//关闭DMA
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;							//设置DMA的通道
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (USART3->DR);   //设置片上外设即USART数据寄存器的基址
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)USART3_Rx_Buffer;		//设置内存的基址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;					//设置DMA的传输方向
	DMA_InitStructure.DMA_BufferSize = USART3RXBUF_SIZE;									//设置DMA的数据缓存区的长度----最长可接收128byte的数据
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
	DMA_Init(DMA1_Stream1, &DMA_InitStructure);							//使能DMA
	
	//数据发送DMA中断配置
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream1_IRQn;   //设置中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //设置中断优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		  //设置中断次优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //开启中断通道
	NVIC_Init(&NVIC_InitStructure);							  //生效配置
	DMA_ITConfig(DMA1_Stream1, DMA_IT_TC, ENABLE);			  //设置DMA的中断模式并开启中断

	//开启传输
	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);
	DMA_Cmd(DMA1_Stream1, ENABLE);  //开启接收DMA
	//DMA_Cmd(DMA1_Stream1, DISABLE);
	/**
	此处若关闭DMA会一直异常触发DMA中断
	*/
	USART_Cmd(USART3, ENABLE);		//开启USART
}

void DMA1_Stream1_IRQHandler(void){
	if (DMA_GetITStatus(DMA1_Stream1, DMA_IT_TCIF1)){
		DMA_ClearFlag(DMA1_Stream1, DMA_FLAG_TCIF1);
		DMA_ClearITPendingBit(DMA1_Stream1, DMA_IT_TCIF1);
	}
}