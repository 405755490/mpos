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
	pthread_t show_time=0;//显示时间线程 
	
	pthread_t gthread_id = 0;
	
	pthread_attr_t attr1;
	pthread_t show_ui1=0;
	//初始化SDK的运行环境
	if(0 != (ret = SDK_Init(argc, argv)))
	{
		API_Trace(0, "SDK_Init failed!");    
		return -1;
	}

	//由于ZT8225的显示API是用QT开发的，主程序main必须由QT的
	//QApplication接管，所以业务流程函数CtlTask必须运行在线程中
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&gthread_id, &attr, CtlTask, NULL);


	//SDK_Exit调用后，主线程由QT的QApplication接管，直到
	//按下程序终止时，SDK_Exit才会返回
	SDK_Exit();
	//取消业务线程    
	pthread_cancel(gthread_id);
	//取消显示时间线程    
	pthread_cancel(show_time);
	//清除线程使用环境
	pthread_attr_destroy(&attr);
	return 0;
}

