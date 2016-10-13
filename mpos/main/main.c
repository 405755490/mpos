#if	0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/ioctl.h>
#include <assert.h>
#include <sys/mman.h>
#include "comm.h"
#include "ks_sdk.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include <sys/time.h>
#include <unistd.h>
#include "comm.h"
#include <ctype.h>


#ifndef NEWLCD
#define NEWLCD
#endif
#define AP_SUCCESS          0

#include "maxq_server.h"
#include "CSerial.h"

const static char *gstrSerialPortDevice = "/dev/ttySAC0";
const int gnSerialPortBaudrate = 460800;

extern void * CtlTask(void * pBuf);



int main(int argc, char * argv[])
{	

	char tmp[100]={0};
	memset(tmp,0,sizeof(tmp));
	int ret = 0;
	pthread_attr_t attr;
	pthread_t show_time=0;//��ʾʱ���߳� 
	
	pthread_t gthread_id = 0;
	
	pthread_attr_t attr1;
	pthread_t show_ui1=0;
	//��ʼ��SDK�����л���
	if(0 != (ret = SDK_Init(argc, argv)))
	{
		API_Trace(0, "SDK_Init failed!");    
		return -1;
	}

	//����ZT8225����ʾAPI����QT�����ģ�������main������QT��
	//QApplication�ӹܣ�����ҵ�����̺���CtlTask�����������߳���
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&gthread_id, &attr, CtlTask, NULL);


	//SDK_Exit���ú����߳���QT��QApplication�ӹܣ�ֱ��
	//���³�����ֹʱ��SDK_Exit�Ż᷵��
	SDK_Exit();
	//ȡ��ҵ���߳�    
	pthread_cancel(gthread_id);
	//ȡ����ʾʱ���߳�    
	pthread_cancel(show_time);
	//����߳�ʹ�û���
	pthread_attr_destroy(&attr);
	return 0;
}

