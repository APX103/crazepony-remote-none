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
main.c file
��д�ߣ�С��  (Camel)
����E-mail��375836945@qq.com
���뻷����MDK-Lite  Version: 4.23
����ʱ��: 2014-03-28
���ܣ�
1.ң�����������
2.ң�ط��棬��û�л������ʱ��ȥ�������ֻ�ǹ涨�����ݸ�ʽ
3.��ҿ������Ż����޸�~��~
------------------------------------
*/

#include      "Config.h"			 //ͷ�ļ�����

#define  R_Mode  America  //�޸ĺ궨�壬�л�ң�ز�����ʽΪ�����ֻ����ձ���

extern int offset_flag;
extern int  Pitch_Offest;
extern int  Roll_Offest;

int main(void)
{
	u16 offset_value;
	u16 buffer[2];
    int i = 0;
	
	SystemClock_HSI(9);    //ϵͳʱ������,9��Ƶ��36M
    NVIC_INIT();	                //�жϳ�ʼ��
    UART1_init(SysClock,115200);
    STMFLASH_Unlock();            //�ڲ�flash����
    LedInit();						 //LED ��ʼ��	
    Adc_Init();            //ҡ��AD��ʼ��
    NRF24L01_Init();       //����ģ���ʼ��
		TX_Mode();						 //����ģʽ
    TIM4_Init(SysClock,1000);           //��ʱ����ʼ��,��ʱ����Ϊ1ms��1ms����һ��ҡ��ADֵ
    TIM3_Init(SysClock,5000);           //��ӡ������Ϣ
    KeyInit();             //������ʼ��
    TxBuf[30]=Syn_byte;    //��Ӧң��������λд0xA5,��֤�ɻ����ڿ�����ʱ�����յ�һ��������32�ֽڵ����ݰ�
    GetAD(R_Mode);          
/*******************************************************/
//����Ϊң�ؽ�����         
/*******************************************************/
     while((Throttle>5)||(Roll>5))//��������������������ͣ�������������
     GetAD(R_Mode);//�õ���·ADֵ����ʾ
    
     TxBuf[28]=ignore_parWrite;     //��Ӧң���������ֽ�д0��ʹ�ɻ�����д������һ��
     TxBuf[27]=Unlock;              //�����ɻ�
     TxBuf[31]=EnableAircraft;      //�����ɹ���ʹ�ܷɿ�
/*******************************************************/
//�������
/*******************************************************/
    
	Led1=0;
	Led2=0;
	Led3=0;
	Led4=0;
	Led5=0;

	//flash�ж�ȡң��΢��ֵ
	STMFLASH_Read_INT(STM32_FLASH_BASE+STM32_FLASH_OFFEST+0,&Pitch_Offest);
	STMFLASH_Read_INT(STM32_FLASH_BASE+STM32_FLASH_OFFEST+4,&Roll_Offest);
	if((Pitch_Offest < -100)||(Pitch_Offest > 100)){
		Pitch_Offest = -50;
	}
	if((Roll_Offest < -100)||(Roll_Offest > 100)){
		Roll_Offest = -50;
	}
	 													   
 	while(1)
	{  
      
	    GetAD(R_Mode);    //�õ���·AD���жϷ���
	
		if((1 == offset_flag) && (i > 20)){
			//ң��΢��ֵ���ı䣬д��flash
			offset_flag = 0;
			i = 0;

			printf("Pitch_Offest:%d\r\n",Pitch_Offest);
		   	printf("Roll_Offest:%d\r\n",Roll_Offest);

			buffer[0] =  (u16)Pitch_Offest;
			buffer[0] =  (u16)(Pitch_Offest>>8);
			STMFLASH_Write(STM32_FLASH_BASE+STM32_FLASH_OFFEST+0,buffer,4);
			buffer[0] =  (u16)Roll_Offest;
			buffer[0] =  (u16)(Roll_Offest>>8);
			STMFLASH_Write(STM32_FLASH_BASE+STM32_FLASH_OFFEST+4,buffer,4);
		}
		i++;
 
//       
//    
// //���Ի��λ��������ã��������ӻ���ֱ��ע�͵�����ע��Ҳ��Ӱ�����
//     printf("\r\n�յ�����[%d] = %d\r\n",i,rx_buffer[i++]);
//     printf("��ָ�� = %d\r\n",UartRxbuf.Rd_Indx & UartRxbuf.Mask);
//     printf("дָ�� = %d\r\n",UartRxbuf.Wd_Indx & UartRxbuf.Mask);
//     printf("����%d�ֽ�\r\n",UartBuf_Cnt(&UartRxbuf));
//     if(i>UartRxbuf.Mask){
//     i=0;
//     //UartBuf_RD(&UartRxbuf);
//     printf("*********************\r\n");
//     }
// /////////////////////////////////////////////////////////////////   
//       
//       
     
		}
}





