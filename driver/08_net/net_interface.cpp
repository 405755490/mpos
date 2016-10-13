#include "net_interface.h"
#include "csocket.h"

#include <stdio.h>
#include <string.h>


CSocket g_socket;
int  g_iNetType = 0;
char g_caBuffer[4096]={0};


bool socket_connected()
{
	return g_socket.connected();
}

bool socket_connect_srv(char *p_caHost, char *p_caPort)
{
	return g_socket.connect_srv(p_caHost, p_caPort);
}

void socket_disconnect_srv()
{
	g_socket.disconnect_srv();
}

int socket_read(char *p_caOutstr, int p_iReadln, int p_iTimeout)
{
	return g_socket.read(p_caOutstr, p_iReadln, p_iTimeout);
}

int socket_write(char *p_caInstr, int p_iWriteln)
{
	return g_socket.write(p_caInstr, p_iWriteln);
}

//<FUN> 打开通信设备
//<INP> tCommType		:   通信设备  (NET_SYNC_MODEM、NET_ASYN_MODEM、NET_GPRS_MODEM)
//<RET> RET_TYPE		:   错误码 
int API_NetOpen(int tCommType)
{
	return RET_SUCCESS;
}


//<FUN> 关闭通信设备
//<RET> RET_TYPE		:   错误码
int API_NetClose(void)
{
	return RET_SUCCESS;
}


//<FUN> 设置选项参数
//<INP> tOption			:   参数类型(OPT_TYPE)
//<INP> pVal			:   参数缓冲区
//<INP> tValSize		:   参数缓冲区长度
//<RET> RET_TYPE		:   错误码
int API_NetSetOpt(int tOption, void *pVal, int tValSize)
{
	return RET_SUCCESS;
	switch(tOption)
	{
		case NOPT_TST:			//
                
		case NOPT_APN:			//S设置APN接入点		pVal(char*)为APN			tValSize未使用
			break;
		case NOPT_USERNAME:		//S设置APN用户名		pVal(char*)为USERNAME	tValSize未使用
			break;
		case NOPT_PASSWORD:		//S设置APN密码		pVal(char*)为PASSWORD	tValSize未使用
			break;
		case NOPT_REGISTER:		//S网络注册			pVal未使用				tValSize为超时时间(单位:毫秒)
			break;
		case NOPT_UART_BAUD:	//G通信波特率		pVal(int*)为通信波特率	tValSize未使用
			break;
		case NOPT_RESET:		//S模块复位			pVal未使用				tValSize为超时时间(单位:毫秒)
			break;
		case NOPT_INFO:			//G模块信息			pVal(char*)为模块信息	tValSize未使用
			break;
		case NOPT_PWRSWITCH:	//S电源开关			pVal(int*)为电源开关[1为开,0为关]	tValSize未使用
			break;
		case NOPT_ISCONNECT:	//G查询连接状态		pVal(int*)为是否连接[1已连接,0未连接]	tValSize未使用
			break;
		case NOPT_SETLINKAT:	//S连接命令集合		pVal(char**)为命令集合	tValSize为命令总数
			break;		                
		case NOPT_ESN:			//G获取ESN          pVal(char*)为ESN			tValSize未使用
			break;
		case NOPT_IMEI:			//G获取IMEI         pVal(char*)为IMEI		tValSize未使用
			break;
		case NOPT_IMSI:			//G获取IMSI         pVal(char*)为IMSI		tValSize未使用
			break;
		case NOPT_CCID:			//G获取CCID         pVal(char*)为CCID		tValSize未使用
			break;
		case NOPT_OPNAME:		//G网络名称			pVal(char*)为网络名称	tValSize未使用
			break;
		case NOPT_READY:		//G网络就绪状态  	pVal(int*)为就绪状态[1就绪,0未就绪]	tValSize未使用
			break;
		case NOPT_SIGNL:		//G网络信号级别  	pVal(int*)为信号级别[0-100]			tValSize未使用
		    break;
		case NOPT_CMD:			//S执行模块命令		pVal(char*)为发送的命令和应答		tValSize为超时时间(单位:毫秒)	
			break;
			
		default:
            break;
		
	}
	
	return RET_SUCCESS;
}


//<FUN> 获取选项参数
//<INP> tOption			:   为参数类型(OPT_TYPE)
//<INP> pVal			:   为参数缓冲区
//<INP> tValSize		:   为参数缓冲区长度
//<RET> RET_TYPE		:   错误码
int API_NetGetOpt(int tOption, void* pVal, int tValSize)
{
	return RET_SUCCESS;
	switch(tOption)
	{
		case NOPT_TST:			//
                
		case NOPT_APN:			//S设置APN接入点		pVal(char*)为APN			tValSize未使用
			break;
		case NOPT_USERNAME:		//S设置APN用户名		pVal(char*)为USERNAME	tValSize未使用
			break;
		case NOPT_PASSWORD:		//S设置APN密码		pVal(char*)为PASSWORD	tValSize未使用
			break;
		case NOPT_REGISTER:		//S网络注册			pVal未使用				tValSize为超时时间(单位:毫秒)
			break;
		case NOPT_UART_BAUD:	//G通信波特率		pVal(int*)为通信波特率	tValSize未使用
			break;
		case NOPT_RESET:		//S模块复位			pVal未使用				tValSize为超时时间(单位:毫秒)
			break;
		case NOPT_INFO:			//G模块信息			pVal(char*)为模块信息	tValSize未使用
			break;
		case NOPT_PWRSWITCH:	//S电源开关			pVal(int*)为电源开关[1为开,0为关]	tValSize未使用
			break;
		case NOPT_ISCONNECT:	//G查询连接状态		pVal(int*)为是否连接[1已连接,0未连接]	tValSize未使用
			break;
		case NOPT_SETLINKAT:	//S连接命令集合		pVal(char**)为命令集合	tValSize为命令总数
			break;		                
		case NOPT_ESN:			//G获取ESN          pVal(char*)为ESN			tValSize未使用
			break;
		case NOPT_IMEI:			//G获取IMEI         pVal(char*)为IMEI		tValSize未使用
			break;
		case NOPT_IMSI:			//G获取IMSI         pVal(char*)为IMSI		tValSize未使用
			break;
		case NOPT_CCID:			//G获取CCID         pVal(char*)为CCID		tValSize未使用
			break;
		case NOPT_OPNAME:		//G网络名称			pVal(char*)为网络名称	tValSize未使用
			break;
		case NOPT_READY:		//G网络就绪状态  	pVal(int*)为就绪状态[1就绪,0未就绪]	tValSize未使用
			break;
		case NOPT_SIGNL:		//G网络信号级别  	pVal(int*)为信号级别[0-100]			tValSize未使用
		    break;
		case NOPT_CMD:			//S执行模块命令		pVal(char*)为发送的命令和应答		tValSize为超时时间(单位:毫秒)	
			break;
			
		default:
            break;
		
	}
	
	return RET_SUCCESS;
}

//暂时不知道干什么的
int API_NetActive(int tTimeOutMs)
{
	return RET_SUCCESS;	
}

//暂时不知道干什么的
int API_NetDeActive(int tTimeOutMs)
{
	return RET_SUCCESS;	
}


//<FUN> 连接服务
//<INP> pAddr			:   服务器地址
//<INP> tPort			:   服务器端口
//<INP> tTimeOutMs		:	处理超时时间,单位:毫秒	或者最大连接次数
//<RET> RET_TYPE		:   错误码
int API_NetConnect(char* pAddr, int tPort, int tTimeOutMs)
{
	printf("API_NetConnect: pAddr[%s] tPort[%d] tTimeOutMs[%d]\n", pAddr, tPort, tTimeOutMs);
	/*
	if(socket_connected())//处于连接状态
	{
		printf("API_NetConnect:处于连接状态,直接返回RET_SUCCESS\n");
		return RET_SUCCESS;	
	}
	*/
	socket_disconnect_srv();
	
	char caPort[8]={0};
	sprintf(caPort, "%d", tPort);
	
	if(socket_connect_srv(pAddr, caPort))
	{
		printf("API_NetConnect:连接成功，返回RET_SUCCESS\n");
		return RET_SUCCESS;
	}
	else
		return RET_ERR;
	/*
	//设置重连次数方式
	if(tTimeOutMs < 1)
		tTimeOutMs = 1;
	int iCount=0;
	while(1==1)
	{
		iCount += 1;
		if(iCount > tTimeOutMs)
		{
			printf("API_NetConnect:连接超次数，返回RET_TIMEOUT\n");
			return RET_TIMEOUT;	
		}
		printf("API_NetConnect:pAddr[%s] caPort[%s]\n", pAddr, caPort);
		if(socket_connect_srv(pAddr, caPort))
		{
			printf("API_NetConnect:连接成功，返回RET_SUCCESS\n");
			return RET_SUCCESS;
		}
	}
	*/
	/*//下面是超时写法
	time_t begin;
	begin = time(NULL);
	while(1==1)
	{
		tTimeOutMs = 9000;
		if( (time(NULL)-begin) >= tTimeOutMs/1000) 
		{
			printf("API_NetConnect:连接超时，返回RET_TIMEOUT\n");
			return RET_TIMEOUT;	
		}
		printf("API_NetConnect:pAddr[%s] caPort[%s]\n", pAddr, caPort);
		if(socket_connect_srv(pAddr, caPort))
		{
			printf("API_NetConnect:连接成功，返回RET_SUCCESS\n");
			return RET_SUCCESS;
		}
	}
	*/
	return RET_ERR;
}


//<FUN> 断开连接
//<INP> tTimeOutMs		:	处理超时时间,单位:毫秒
//<RET> RET_TYPE		:   错误码
int API_NetDisConnect(int tTimeOutMs)
{
	socket_disconnect_srv();
	return 0;
}


//<FUN> 发送数据
//<INP> pSendBuf		:   要发送的数据缓冲区
//<INP> tSendLen		:   要发送的数据长度
//<INP> tTimeOutMs		:	处理超时时间,单位:毫秒
//<RET> RET_TYPE		:   错误码
int API_NetSend(u8* pSendBuf, int tSendLen, int tTimeOutMs)
{
	char caTmp[4096]={0};
	memcpy(caTmp, pSendBuf, tSendLen);
	int iRet = socket_write(caTmp, tSendLen);
	if(iRet < 0)
	{
		return -1;
	}
	else
	{
		return RET_SUCCESS;
	}
}




//<FUN> 接收数据
//<INP> pRecvBuf		:   接收数据缓冲区
//<INP> tRecvLen		:   接收数据缓冲区长度
//<INP> tTimeOutMs		:	处理超时时间,单位:毫秒
//<RET> RET_TYPE		:   实际收到的数据长度
int API_NetRecv(u8* pRecvBuf, int tRecvLen, int tTimeOutMs)
{
	char caTmp[4096]={0};
	memcpy(caTmp, pRecvBuf, tRecvLen);
	int iRet = socket_read(caTmp, tRecvLen, tTimeOutMs);
	
	if(-2 == iRet)
		return -2;
	else if(-1 == iRet || -3 == iRet)
		return -1;
	else
	{
		memcpy(pRecvBuf, caTmp, iRet);
		return iRet;//实际接到数据长度
	}
		
}


//暂时不知道干什么
int API_NetEvent(int* pRet)
{
	return RET_SUCCESS;
}



