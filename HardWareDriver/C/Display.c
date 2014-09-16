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
1.�ⲿ�ִ��룬����������汾����ʾ�������ʱ�õģ���ʱ�õ���ŵ����5110����Ļ���ⲿ�ִ����ǿ����õģ����Һܺ���
2.��ҿ���ȥ�о���5110����������Դ�ļ����棬û�м���ù��̶��ѣ���������ߵĹ����ļ���������
------------------------------------
*/

/*****************************************************************
 * �ļ���   ��Display.c
 * ����     : ��Ļ��ʾ����
 * ʵ��ƽ̨ ��STM32f103T8U6 
 * ��汾   ��ST3.5.0
 * ����     ��MJ
 * ʱ��     ��2014-2-18 0:47:33
 * ���     ������ʹ��
 * ����     ������鵽���гɼ�����  ���ű���д�ų���
 ******************************************************************/

 
#include "adc.h"

    int Throttle;
    int Roll;
    int Pitch;
    int Yaw;
    int Battery;//�������ʾ��


char Throttle_Offest=0;
char Pitch_Offest=0;
char Roll_Offest=0;
char Yaw_Offest=0;//ң��΢��

    
/*
ҡ�����ݲɼ�
�������Ϊ�����ֺ��ձ���
*/
void GetAD(unsigned char RomoteMode)
{

  switch(RomoteMode)
  {
    /*����Ϊ�����ֵĶ�Ӧ��ϵ*/
 case America:
                
      Throttle=Throttle_Offest+99-(100*Get_Adc_Average(3,15))/4096;//�ɼ�����ҡ�˵�λ�ã�����Ӳ��ԭ����Ҫ��100-�ɼ�ֵ
      Throttle=(Throttle<=0)?0:Throttle;                 //Խ���ж�
      Throttle=(Throttle>=99)?99:Throttle;               //Խ���ж�

      Pitch=Pitch_Offest+(100*Get_Adc_Average(1,15))/4096;//�ɼ�����ҡ�˵�λ�ã���ֵ����Ӧ�ĸ�������
      Pitch=(Pitch<=0)?0:Pitch;                 //Խ���ж�
      Pitch=(Pitch>=99)?99:Pitch;               //Խ���ж�

      Roll=Roll_Offest+(100*Get_Adc_Average(0,15))/4096;//�ɼ����ҡ��λ�ã���ֵ����Ӧ�ĺ������
      Roll=(Roll<=0)?0:Roll;                //Խ���ж�
      Roll=(Roll>=99)?99:Roll;              //Խ���ж�

      Yaw=Yaw_Offest+(100*Get_Adc_Average(2,15))/4096;//�ɼ����ҡ��λ�ã���ֵ����Ӧ��ƫ����
      Yaw=(Yaw<=0)?0:Yaw;                //Խ���ж�
      Yaw=(Yaw>=99)?99:Yaw;              //Խ���ж�

      Battery=(100*Get_Adc_Average(8,15))/2600;//�ɼ�ң�ص�ص�ѹ����ֵ�ɶ�Ӧ�ĵ�ر���
      Battery=(Battery>=99)?99:Battery;               //Խ���ж�
   
          break;
    /*����Ϊ�ձ��ֵĶ�Ӧ��ϵ*/
 case Japan:
      Throttle=Throttle_Offest+(100*Get_Adc_Average(1,15))/4096;//�ɼ�����ҡ�˵�λ�ã�����Ӳ��ԭ����Ҫ��100-�ɼ�ֵ
      Throttle=(Throttle<=0)?0:Throttle;                 //Խ���ж�
      Throttle=(Throttle>=99)?99:Throttle;               //Խ���ж�

      Pitch=Pitch_Offest+100-(100*Get_Adc_Average(3,15))/4096;//�ɼ�����ҡ�˵�λ�ã���ֵ����Ӧ�ĸ�������
      Pitch=(Pitch<=0)?0:Pitch;                 //Խ���ж�
      Pitch=(Pitch>=99)?99:Pitch;               //Խ���ж�

      Roll=Roll_Offest+(100*Get_Adc_Average(0,15))/4096;//�ɼ����ҡ��λ�ã���ֵ����Ӧ�ĺ������
      Roll=(Roll<=0)?0:Roll;                //Խ���ж�
      Roll=(Roll>=99)?99:Roll;              //Խ���ж�

      Yaw=Yaw_Offest+(100*Get_Adc_Average(2,15))/4096;//�ɼ����ҡ��λ�ã���ֵ����Ӧ��ƫ����
      Yaw=(Yaw<=0)?0:Yaw;                //Խ���ж�
      Yaw=(Yaw>=99)?99:Yaw;              //Խ���ж�

      Battery=(100*Get_Adc_Average(8,15))/2600;//�ɼ�ң�ص�ص�ѹ����ֵ�ɶ�Ӧ�ĵ�ر���
      Battery=(Battery>=99)?99:Battery;               //Խ���ж�
  
          break;
    
    
    
  }

  

}





