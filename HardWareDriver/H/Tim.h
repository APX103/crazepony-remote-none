#ifndef _DELAY_H_
#define _DELAY_H
#include "stm32f10x.h"



void TIM4_Init(char clock,int Preiod);//���ڼ��ϵͳ
void TIM3_Init(char clock,int Preiod);//��ʱ��3�ĳ�ʼ��
void TimerNVIC_Configuration(void);//��ʱ���ж�����������

#endif

