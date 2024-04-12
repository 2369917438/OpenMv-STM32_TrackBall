#include "stm32f10x.h"
#include "usart.h"
#include "SG90.h"
#include "delay.h"
#include "main.h"


	
void MyUART_Init(void)
{
	//��һ����ʼ�����õ�GPIO��,RX��Ӧ�ĸ���IO��PA5��PA10������GPIO�ڵ�֪ʶ
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitTypeSTU;
	USART_InitTypeDef USART_InitTypeSTU; //����Ҫ���ڿ�ͷ
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING;//TXDPA10,����Ϊ����ģʽ
	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;//RXDPA9,����Ϊ��������
	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_9;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	//�ڶ��������ڸ�λ��ѡ����
	//USART_DeInit(USART1);
	
	
	//����������ʱ��ʹ���Լ����ڲ���ģʽ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	
	USART_InitTypeSTU.USART_BaudRate           =115200;
	USART_InitTypeSTU.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitTypeSTU.USART_Mode               =USART_Mode_Rx|USART_Mode_Tx;
	USART_InitTypeSTU.USART_Parity             =USART_Parity_No;
	USART_InitTypeSTU.USART_StopBits           =USART_StopBits_1;
	USART_InitTypeSTU.USART_WordLength         =USART_WordLength_8b;
	USART_Init(USART1,&USART_InitTypeSTU);
	
	USART_Cmd(USART1,ENABLE);//��Ҫ��������ʹ�ܺ���
	
	
	//���Ĳ��������жϵ����ã������ж����ȼ����жϿ�����
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//�����жϣ����Ҷ���Ϊ�����ж�
	
	
	NVIC_InitTypeSTU.NVIC_IRQChannel                    =USART1_IRQn;//�������ļ�����
	NVIC_InitTypeSTU.NVIC_IRQChannelCmd                 =ENABLE;
	NVIC_InitTypeSTU.NVIC_IRQChannelPreemptionPriority  =3;//���õ�����ռ���ȼ�
	NVIC_InitTypeSTU.NVIC_IRQChannelSubPriority         =3;//���õ��������ȼ�
	NVIC_Init(&NVIC_InitTypeSTU);
  
}





void USART1_IRQHandler(void) //�����жϺ���
{
	u8 res = 0;
	if(USART_GetITStatus(USART1, USART_IT_RXNE))//�ж��Ƿ��ǽ����жϣ��˺��������ж��ж�����
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		res = USART_ReceiveData(USART1); //�������ݺ���
		SGtrack(res);
	}
}
