#include "stm32f10x.h"
#include "usart.h"
#include "SG90.h"
#include "delay.h"
#include "main.h"


	
void MyUART_Init(void)
{
	//第一步初始化复用的GPIO口,RX对应的复用IO口PA5和PA10，运用GPIO口的知识
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitTypeSTU;
	USART_InitTypeDef USART_InitTypeSTU; //定义要放在开头
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING;//TXDPA10,设置为浮空模式
	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;//RXDPA9,设置为复用推挽
	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_9;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	//第二步，串口复位（选做）
	//USART_DeInit(USART1);
	
	
	//第三步串口时钟使能以及串口参数模式等设置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	
	USART_InitTypeSTU.USART_BaudRate           =115200;
	USART_InitTypeSTU.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitTypeSTU.USART_Mode               =USART_Mode_Rx|USART_Mode_Tx;
	USART_InitTypeSTU.USART_Parity             =USART_Parity_No;
	USART_InitTypeSTU.USART_StopBits           =USART_StopBits_1;
	USART_InitTypeSTU.USART_WordLength         =USART_WordLength_8b;
	USART_Init(USART1,&USART_InitTypeSTU);
	
	USART_Cmd(USART1,ENABLE);//不要忘记最后的使能函数
	
	
	//第四步，关于中断的设置（包括中断优先级，中断开启）
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//开启中断，并且定义为接收中断
	
	
	NVIC_InitTypeSTU.NVIC_IRQChannel                    =USART1_IRQn;//在启动文件定义
	NVIC_InitTypeSTU.NVIC_IRQChannelCmd                 =ENABLE;
	NVIC_InitTypeSTU.NVIC_IRQChannelPreemptionPriority  =3;//设置的是抢占优先级
	NVIC_InitTypeSTU.NVIC_IRQChannelSubPriority         =3;//设置的是子优先级
	NVIC_Init(&NVIC_InitTypeSTU);
  
}





void USART1_IRQHandler(void) //设置中断函数
{
	u8 res = 0;
	if(USART_GetITStatus(USART1, USART_IT_RXNE))//判断是否是接收中断，此函数用于判断中断类型
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		res = USART_ReceiveData(USART1); //接受数据函数
		SGtrack(res);
	}
}
