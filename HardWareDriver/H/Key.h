#ifndef _Key_H_
#define _Key_H_

#include "sys.h"



//#define Key1     PBin(2)//PB2��BOOT1���ţ�����
#define kSet_Mode_Choose         0x12
#define kValueinc                0x13
#define kValuedec                0x14

#define Key2         PBin(1)
#define Key3         PBin(3)
#define Key4         PAin(8)



#define kPress       0
#define kRelease     !kPress




void KeyInit(void);   //Key��ʼ�������ⲿ����
char KeyScan(void);   //����ɨ�躯��


#endif

