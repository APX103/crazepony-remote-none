#include "Key.h"
/*    
      ____                      _____                  +---+
     / ___\                     / __ \                 | R |
    / /                        / /_/ /                 +---+
   / /   ________  ____  ___  / ____/___  ____  __   __
  / /  / ___/ __ `/_  / / _ \/ /   / __ \/ _  \/ /  / /
 / /__/ /  / /_/ / / /_/  __/ /   / /_/ / / / / /__/ /
 \___/_/   \__,_/ /___/\___/_/    \___ /_/ /_/____  /
                                                 / /
                                            ____/ /
                                           /_____/
Tim.c file
��д�ߣ�С��  (Camel)
����E-mail��375836945@qq.com
���뻷����MDK-Lite  Version: 4.23
����ʱ��: 2014-01-28
���ܣ�
1.����IO�ڳ�ʼ��
2.�ⲿ�ְ����Ĺ����Ƕ��⿪�ŵģ���û�ж��� �书�ܣ�������ɷ��Ӱ�
------------------------------------
*/

/********************************************
              Key��ʼ������
���ܣ�
1.����Key�ӿ�IO���뷽��

������
Key�ӿڣ�
Key1-->PB2
Key2-->PB1
Key3-->PB3
********************************************/
void KeyInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	/* config the extiline(PB1) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);

	/* config the NVIC(PB1) */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Configure PB1 as output push-pull */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;            //�趨�ⲿ�ж�1
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  //�趨�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�趨�½��ش���ģʽ
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
}

void EXTI1_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line1) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	{
		printf("hello");
		EXTI_ClearITPendingBit(EXTI_Line1);     //����жϱ�־λ
	}
}


char KeyScan(void)
{
 if(Key2 == kPress) return kSet_Mode_Choose;
 if(Key3 == kPress) return kValueinc;
 if(Key4 == kPress) return kValuedec;
 
 return 0x15;
}





