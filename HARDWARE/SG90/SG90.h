#ifndef _SG90_
#define _SG90_
#endif

#include "stm32f10x.h"
//void SG901_Init(void);
//void SG901_OnMove(void);
//void SG901_DownMove(void);
//void SG901_StopMove(void);

void Server_360_Forward(void);
void Server_180_Angle(void);
void Left_turn_Horizontal(int i);
void Right_turn_Horizontal(int i);
void Down_turn_Vertical(int i);
void Up_turn_Vertical(int i);
void SGtrack(u8 res);
