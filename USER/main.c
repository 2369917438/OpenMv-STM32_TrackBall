#include "stm32f10x.h"
#include "LED.h"
#include "delay.h"
#include "PWM.h"
#include "SG90.h"
#include "usart.h"
#include "main.h"


#define time 30

 int main(void)
 {	
   SystemInit();
	 delay_init();
	 Led_Init();
	 TIM1_PWM_Init();
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级
	 MyUART_Init();
//对舵机的调试部分
	 Down_turn_Vertical(30);
	 while(1)
	 {
//	 Down_turn_Vertical(time);
//	 delay_ms(1000);
//	 Up_turn_Vertical(time);
//	 delay_ms(1000);
	 }

 }
