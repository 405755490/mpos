#ifndef _COMM_HEADFILES_
#define _COMM_HEADFILES_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/ioctl.h>
#include <assert.h>
#include <sys/mman.h>
#include <pthread.h>
#include <sys/msg.h>
#include <linux/input.h>
#include "std_head.h"
#include "ks_stdlib.h"
#include "ks_sdk.h"
#include "ks_gui.h"
#include "global.h"

#if 0
	//����ΪĸPOS
	#ifndef ONELEVELMPOS   
	#define ONELEVELMPOS
	#undef  TWOLEVELMPOS
	#endif
#else 
	//����Ϊ����POS
	#undef  ONELEVELMPOS
	#ifndef TWOLEVELMPOS   
	#define TWOLEVELMPOS
	#endif
#endif

#ifndef DEBUG  //����ģʽ��
#define DEBUG
#endif



typedef 	float  				FLOAT;
typedef 	double  			DOUBLE;
typedef     unsigned long       u_long;
typedef     unsigned char       u_char;
typedef unsigned char  uchar    ;

#ifndef TRUE   
#define TRUE   1
#endif
#ifndef FALSE   
#define FALSE   0
#endif
#ifndef APP_SUCC   
#define APP_SUCC   1
#endif
#ifndef APP_FAIL 
#define APP_FAIL   0
#endif



#define  CCR			0x0D	//ȷ�ϼ�
#define  ENTER		CCR
#define  ESC		0x1B
#define NEXT_PAGE     0X43  //�·�ҳ��
#define HEAD_PAGE     0X42  //�Ϸ�ҳ��
#define LEFT_PAGE     0X41  //��ҳ��
#define RIGHT_PAGE     0X44  //�ҷ�ҳ��


#define   	DISCONNECT	      0          	/*δ����            */
#define   	CONNECT		1          	/*������            */

#define QUIT (-6)
#define TRANSTIMEOUT -3



#define ENUMPASSKEY_LEN   200   //���͸�����POS����Կ����
typedef struct
{
	char Areacode[2] ;
	char AreacodeName[10];
	char b_tek[17];
	char r_tek[17];
	char mingwenkey[ENUMPASSKEY_LEN];
	char miwenkey[10][16];
	char mingwenkeyChk[10][8] ;
}MPOS_ONE_LEVEL_KEY;


#endif
