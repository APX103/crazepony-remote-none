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
����ʱ��: 2014-01-28
���ܣ�
------------------------------------
*/
#include "config.h"             //�������е�����ͷ�ļ�

// uint32_t startTime[5],execTime[5];
// uint32_t realExecPrd[5];

#define debugprint



/*****Remote mode switch define******/
#define AmericaMode  

	
// uint32_t t0,t1;


extern char IMUcalibratflag;
extern u8  TX_ADDRESS[TX_ADR_WIDTH];
extern char Lockflag;


int main(void)
{
	static char ledsta;
	/*************remote tx addr*******/
	RemoteTxaddr = 0xd3;
 /***********************************/
	SystemClock_HSI(9);           //ϵͳʱ�ӳ�ʼ����ʱ��Դ�ڲ�HSI
	cycleCounterInit();				    // Init cycle counter
	SysTick_Config(SystemCoreClock / 1000);	//SysTick����ϵͳtick��ʱ������ʼ�����жϣ�1ms
	UART1_init(SysClock,uart1baudSet); //����1��ʼ��
  NVIC_INIT();	                //�жϳ�ʼ��
  STMFLASH_Unlock();            //�ڲ�flash����
  LoadParamsFromEEPROM();				//����ϵͳ�������ñ�
  LedInit();	                  //IO��ʼ��
  Adc_Init();										//ҡ��AD��ʼ��
	KeyInit();										//������ʼ��
 	NRF24L01_INIT();              //NRF24L01��ʼ��
  SetTX_Mode();                 //������ģ��Ϊ����ģʽ
  controlClibra();							//ң��ҡ��У׼  
	TIM4_Init(SysClock,TIME4_Preiod);	  //��ʱ��4��ʼ������ʱʱ�䵥λ��(TIME4_Preiod)΢��
	
	LedSet(led2,1);
	LedSet(led3,1);
	
	LoadRCdata();                //ҡ�˸�ֵ
	RockerUnlockcrazepony();		 //�ڸ�����
  Lockflag = 1;								 //������־
	
  LedSet(led2,0);
	LedSet(led3,0);
	 
  while (1)             
	{ 
		
if(flag10Hz == 1)  //10Hz 
		{		
			flag10Hz = 0;
			 /*status led*/
			ledsta = !ledsta;
			LedSet(signalLED,ledsta);				        
		  /*crazepony Lock*/
	    KeyLockcrazepony();
		  /*IMUcalibrate  */
			IMUcalibrate();
			/*remote calibrate*/
		  Remotecalibrate();
			
			
			
      #ifdef debugprint
				printf("thr -->%d\r\n",Throttle);
				printf("pitch -->%d\r\n",Pitch);
				printf("roll -->%d\r\n",Roll);
				printf("yaw -->%d\r\n",Yaw);
			  printf("remote addr -->0x%x\r\n",TX_ADDRESS[4]);// tx addr
				printf("-------------\r\n");
			#endif
			
		}

if(flag50Hz == 1)//
		{	
// 			t1 = micros() - t0; 
// 			t0 = micros();
			
			flag50Hz = 0;
			CommUAVUpload(MSP_SET_4CON);
		}
		
if(flag80Hz)// 80Hz 12.5ms
		{
			flag80Hz = 0;
			LoadRCdata();   
		}
	}
}

