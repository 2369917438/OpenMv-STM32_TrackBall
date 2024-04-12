#include "stm32f10x.h"
#include "LED.h"
#include "delay.h"

void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitTypeSTR;
	GPIO_InitTypeSTR.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitTypeSTR.GPIO_Pin   = GPIO_Pin_13;
	GPIO_InitTypeSTR.GPIO_Speed = GPIO_Speed_50MHz;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_Init(GPIOC,&GPIO_InitTypeSTR);
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}

void LED_flash()
{
	LED=1;
	delay_ms(500);
	LED=0;	
	delay_ms(500);
}
