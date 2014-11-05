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
    RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ��
    GPIOB->CRL&=0XFFFF0F0F;  //PB1,2,3����
    GPIOB->CRL|=0X00008080;
    GPIOB->ODR|=7<<1;        //PB1,2,3����
    
    RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��
    GPIOB->CRH&=0XFFFFFFF0;  //PA8����
    GPIOB->CRH|=0X00000008;
    GPIOB->ODR|=1<<8;        //PA8����
}


char KeyScan(void)
{
 if(Key2 == kPress) return kSet_Mode_Choose;
 if(Key3 == kPress) return kValueinc;
 if(Key4 == kPress) return kValuedec;
 
 return 0x15;
}





