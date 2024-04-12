#include "SG90.h"
#include "stm32f10x.h"
#include "delay.h"
#define time1 10
#define time2 15
#define stop_time 20


//水平转向控制
void Right_turn_Horizontal(int i)
{
	TIM_SetCompare4(TIM1,5);
	while(i--)
	{
	delay_ms(1);
	}
	TIM_SetCompare4(TIM1,15);
	delay_ms(stop_time);
}

void Left_turn_Horizontal(int i)
{
	TIM_SetCompare4(TIM1,25);
	while(i--)
	{
	delay_ms(1);
	}
	TIM_SetCompare4(TIM1,15);
	delay_ms(stop_time);
}
//上下转向控制
void Up_turn_Vertical(int i)
{
	TIM_SetCompare1(TIM1,5);
	while(i--)
	{
	delay_ms(1);
	}
	TIM_SetCompare1(TIM1,15);
	delay_ms(stop_time);
}

void Down_turn_Vertical(int i)
{
	TIM_SetCompare1(TIM1,25);
	while(i--)
	{
	delay_ms(2);
	}
	TIM_SetCompare1(TIM1,15);
	delay_ms(stop_time);
}

void SGtrack(u8 res)
{
switch(res)
		{
			case '1':
			{
				Down_turn_Vertical(time2);
				Left_turn_Horizontal(time1);
			}
			case '2':
			{
				Down_turn_Vertical(time2);
			}
			case '3':
			{
				Down_turn_Vertical(time2);
				Right_turn_Horizontal(time1);
			}
			case '4':
			{
				Left_turn_Horizontal(time1);
			}
			case '5':
			{
			}
			case '6':
			{
				Right_turn_Horizontal(time1);
			}
			case '7':
			{
				Up_turn_Vertical(time1);
				Left_turn_Horizontal(time1);
			}
			case '8':
			{
				Up_turn_Vertical(time1);
			}
			case '9':
			{
				Up_turn_Vertical(time1);
				Right_turn_Horizontal(time1);
			}
		}
}
