#include "tim.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "NRF24L01.h"
#include "Led.h"
#include "misc.h" 
#include "Display.h"
#include "stdio.h"
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
1.��ʼ����ʱ��4������ң������
2.��ʼ����ʱ��3����ӡ��Ϣ
------------------------------------
*/



	

int Ledcounter;

//��ʱ��������ں���
//��ʱ����Ϊ1ms
//���߼�����������ʾң���źŵ�ǿ�ȣ�ң���ϵ�����Խ�죬�ź�Խ��
//��Ϊ���ͺ��������и�����ط����������ղ���Ӧ���ź�ʱ���ڷ��ͺ��������ʱ���ط�����Խ��
//��ʱԽ�࣬LED�ͻ��������Խ����������

void TIM4_IRQHandler(void)		//1ms�ж�һ��,���ڳ����ȡ6050��
{
    if( TIM_GetITStatus(TIM4 , TIM_IT_Update) != RESET ) 
    {     
     Ledcounter++;
      
     if(Ledcounter==59)Led1=1;
     if(Ledcounter==60){Led1=0;Ledcounter=0;}

      TxBuf[0]=(Throttle*10)&0xff;
      TxBuf[1]=((Throttle*10)>>8);     //������װ������������ǰ�����ֽ�
      TxBuf[2]=Pitch;                  //������װ���3���ֽ�
      TxBuf[3]=Roll;                   //�����ת���4���ֽ�
      TxBuf[4]=Yaw;                    //ƫ����װ���5���ֽ�
      TxBuf[31]=(Throttle<=5) ? 0:0xA5;//����Ϩ���־�ֽڿ���     
      NRF24L01_TxPacket(TxBuf);	       //���ݰ����ͣ�����ط�����15��
      TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update);   //����жϱ�־  
    } 
}



int DebugCounter;             //��ӡ��Ϣ���ʱ��������ֵ

#define Debug

void TIM3_IRQHandler(void)		//��ӡ�жϷ������
{
    if( TIM_GetITStatus(TIM3 , TIM_IT_Update) != RESET ) 
    {     
#ifdef Debug
      DebugCounter++;
      if( DebugCounter==200)
            {
            DebugCounter=0;
//             printf(" ******************************************************************\r\n");
//             printf(" *       ____                      _____                  +---+   *\r\n");
//             printf(" *      / ___\\                     / __ \\                 | R |   *\r\n");
//             printf(" *     / /                        / /_/ /                 +---+   *\r\n");
//             printf(" *    / /   ________  ____  ___  / ____/___  ____  __   __        *\r\n");
//             printf(" *   / /  / ___/ __ `/_  / / _ \\/ /   / __ \\/ _  \\/ /  / /        *\r\n");
//             printf(" *  / /__/ /  / /_/ / / /_/  __/ /   / /_/ / / / / /__/ /         *\r\n");
//             printf(" *  \\___/_/   \\__,_/ /___/\\___/_/    \\___ /_/ /_/____  /          *\r\n");
//             printf(" *                                                  / /           *\r\n");
//             printf(" *                                             ____/ /            *\r\n");
//             printf(" *                                            /_____/             *\r\n");
//             printf(" ******************************************************************\r\n");
           // printf("\r\n");
            printf(" Crazepony-II���棺ϵͳ��������...\r\n"); 
            printf("\r\n--->ң��ʵʱ����<---\r\n");
            printf("���ŵ�ǰֵ---> %d\r\n",(int) Throttle);
            printf("������ǰֵ---> %d\r\n",(int) Pitch);
            printf("�����ǰֵ---> %d\r\n",(int) Roll);
            printf("ƫ����ǰֵ---> %d\r\n",(int) Yaw);
            


        }
#else      
             
#endif
        
        TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);   //����жϱ�־   
    }
}








//��ʱ��4��ʼ���������жϴ���PID
void TIM4_Init(char clock,int Preiod)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  //��ʱ��
    
    TIM_DeInit(TIM4);

    TIM_TimeBaseStructure.TIM_Period = Preiod;
    TIM_TimeBaseStructure.TIM_Prescaler = clock-1;//��ʱ1ms
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM4,TIM_FLAG_Update);

    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM4,ENABLE);
    //printf("��ʱ��4��ʼ�����...\r\n");
    
}	


//��ʱ��3��ʼ��
void TIM3_Init(char clock,int Preiod)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  //��ʱ��
    
    TIM_DeInit(TIM3);

    TIM_TimeBaseStructure.TIM_Period = Preiod;
    TIM_TimeBaseStructure.TIM_Prescaler = clock-1;//��ʱ1ms
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM3,TIM_FLAG_Update);

    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM3,ENABLE);
  
    //printf("��ʱ��3��ʼ�����...\r\n");
}		


void TimerNVIC_Configuration()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /* NVIC_PriorityGroup 2 */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //TIM3
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//��ʱ��3��Ϊ���ڴ�ӡ��ʱ��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //TIM4
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

} 




