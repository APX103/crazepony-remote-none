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

extern int  Pitch_Offest;
extern int  Roll_Offest;

int main(void)
{

	int key_mode = 0;	//��ʾ���ڰ�������ģʽ����key2�����л���0��΢��pitchģʽ��1��΢��rollģʽ
  
   // int i;
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
     
 	while(1)
	{  
      
    GetAD(R_Mode);    //�õ���·AD���жϷ���
    
    if(KeyScan() == kSet_Mode_Choose){
		if(0 == key_mode){
			key_mode = 1;
			Led2 = 1;	//Led2�����ʾ������΢��roll��ģʽ
		}else{
			key_mode = 0;
			Led2 = 0;	//Led2�����ʾ������΢��pitch��ģʽ
		}
	}
       
    if(KeyScan() == kValueinc){
		if(0 == key_mode)	//΢��pitch
		{
			Pitch_Offest++;
		}else{	//΢��roll
			Roll_Offest++;
		}

	 	Led3 = 1;
	}
      
    if(KeyScan() == kValuedec){
		if(0 == key_mode)	//΢��pitch
		{
			Pitch_Offest--;
		}else{	//΢��roll
			Roll_Offest--;
		}

	 	Led4 = 1;
	}

	printf("pitch offset %d\r\n",(int) Pitch_Offest);
	printf("roll offset %d\r\n",(int) Roll_Offest);
    
	
	//ң���ϵ�Key1��ʱ���ã����µ����������Զ��壬��������Ϊƫ�����ڣ�һ�������ȵ�
      
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





