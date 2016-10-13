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

//<FUN> ��ͨ���豸
//<INP> tCommType		:   ͨ���豸  (NET_SYNC_MODEM��NET_ASYN_MODEM��NET_GPRS_MODEM)
//<RET> RET_TYPE		:   ������ 
int API_NetOpen(int tCommType)
{
	return RET_SUCCESS;
}


//<FUN> �ر�ͨ���豸
//<RET> RET_TYPE		:   ������
int API_NetClose(void)
{
	return RET_SUCCESS;
}


//<FUN> ����ѡ�����
//<INP> tOption			:   ��������(OPT_TYPE)
//<INP> pVal			:   ����������
//<INP> tValSize		:   ��������������
//<RET> RET_TYPE		:   ������
int API_NetSetOpt(int tOption, void *pVal, int tValSize)
{
	return RET_SUCCESS;
	switch(tOption)
	{
		case NOPT_TST:			//
                
		case NOPT_APN:			//S����APN�����		pVal(char*)ΪAPN			tValSizeδʹ��
			break;
		case NOPT_USERNAME:		//S����APN�û���		pVal(char*)ΪUSERNAME	tValSizeδʹ��
			break;
		case NOPT_PASSWORD:		//S����APN����		pVal(char*)ΪPASSWORD	tValSizeδʹ��
			break;
		case NOPT_REGISTER:		//S����ע��			pValδʹ��				tValSizeΪ��ʱʱ��(��λ:����)
			break;
		case NOPT_UART_BAUD:	//Gͨ�Ų�����		pVal(int*)Ϊͨ�Ų�����	tValSizeδʹ��
			break;
		case NOPT_RESET:		//Sģ�鸴λ			pValδʹ��				tValSizeΪ��ʱʱ��(��λ:����)
			break;
		case NOPT_INFO:			//Gģ����Ϣ			pVal(char*)Ϊģ����Ϣ	tValSizeδʹ��
			break;
		case NOPT_PWRSWITCH:	//S��Դ����			pVal(int*)Ϊ��Դ����[1Ϊ��,0Ϊ��]	tValSizeδʹ��
			break;
		case NOPT_ISCONNECT:	//G��ѯ����״̬		pVal(int*)Ϊ�Ƿ�����[1������,0δ����]	tValSizeδʹ��
			break;
		case NOPT_SETLINKAT:	//S���������		pVal(char**)Ϊ�����	tValSizeΪ��������
			break;		                
		case NOPT_ESN:			//G��ȡESN          pVal(char*)ΪESN			tValSizeδʹ��
			break;
		case NOPT_IMEI:			//G��ȡIMEI         pVal(char*)ΪIMEI		tValSizeδʹ��
			break;
		case NOPT_IMSI:			//G��ȡIMSI         pVal(char*)ΪIMSI		tValSizeδʹ��
			break;
		case NOPT_CCID:			//G��ȡCCID         pVal(char*)ΪCCID		tValSizeδʹ��
			break;
		case NOPT_OPNAME:		//G��������			pVal(char*)Ϊ��������	tValSizeδʹ��
			break;
		case NOPT_READY:		//G�������״̬  	pVal(int*)Ϊ����״̬[1����,0δ����]	tValSizeδʹ��
			break;
		case NOPT_SIGNL:		//G�����źż���  	pVal(int*)Ϊ�źż���[0-100]			tValSizeδʹ��
		    break;
		case NOPT_CMD:			//Sִ��ģ������		pVal(char*)Ϊ���͵������Ӧ��		tValSizeΪ��ʱʱ��(��λ:����)	
			break;
			
		default:
            break;
		
	}
	
	return RET_SUCCESS;
}


//<FUN> ��ȡѡ�����
//<INP> tOption			:   Ϊ��������(OPT_TYPE)
//<INP> pVal			:   Ϊ����������
//<INP> tValSize		:   Ϊ��������������
//<RET> RET_TYPE		:   ������
int API_NetGetOpt(int tOption, void* pVal, int tValSize)
{
	return RET_SUCCESS;
	switch(tOption)
	{
		case NOPT_TST:			//
                
		case NOPT_APN:			//S����APN�����		pVal(char*)ΪAPN			tValSizeδʹ��
			break;
		case NOPT_USERNAME:		//S����APN�û���		pVal(char*)ΪUSERNAME	tValSizeδʹ��
			break;
		case NOPT_PASSWORD:		//S����APN����		pVal(char*)ΪPASSWORD	tValSizeδʹ��
			break;
		case NOPT_REGISTER:		//S����ע��			pValδʹ��				tValSizeΪ��ʱʱ��(��λ:����)
			break;
		case NOPT_UART_BAUD:	//Gͨ�Ų�����		pVal(int*)Ϊͨ�Ų�����	tValSizeδʹ��
			break;
		case NOPT_RESET:		//Sģ�鸴λ			pValδʹ��				tValSizeΪ��ʱʱ��(��λ:����)
			break;
		case NOPT_INFO:			//Gģ����Ϣ			pVal(char*)Ϊģ����Ϣ	tValSizeδʹ��
			break;
		case NOPT_PWRSWITCH:	//S��Դ����			pVal(int*)Ϊ��Դ����[1Ϊ��,0Ϊ��]	tValSizeδʹ��
			break;
		case NOPT_ISCONNECT:	//G��ѯ����״̬		pVal(int*)Ϊ�Ƿ�����[1������,0δ����]	tValSizeδʹ��
			break;
		case NOPT_SETLINKAT:	//S���������		pVal(char**)Ϊ�����	tValSizeΪ��������
			break;		                
		case NOPT_ESN:			//G��ȡESN          pVal(char*)ΪESN			tValSizeδʹ��
			break;
		case NOPT_IMEI:			//G��ȡIMEI         pVal(char*)ΪIMEI		tValSizeδʹ��
			break;
		case NOPT_IMSI:			//G��ȡIMSI         pVal(char*)ΪIMSI		tValSizeδʹ��
			break;
		case NOPT_CCID:			//G��ȡCCID         pVal(char*)ΪCCID		tValSizeδʹ��
			break;
		case NOPT_OPNAME:		//G��������			pVal(char*)Ϊ��������	tValSizeδʹ��
			break;
		case NOPT_READY:		//G�������״̬  	pVal(int*)Ϊ����״̬[1����,0δ����]	tValSizeδʹ��
			break;
		case NOPT_SIGNL:		//G�����źż���  	pVal(int*)Ϊ�źż���[0-100]			tValSizeδʹ��
		    break;
		case NOPT_CMD:			//Sִ��ģ������		pVal(char*)Ϊ���͵������Ӧ��		tValSizeΪ��ʱʱ��(��λ:����)	
			break;
			
		default:
            break;
		
	}
	
	return RET_SUCCESS;
}

//��ʱ��֪����ʲô��
int API_NetActive(int tTimeOutMs)
{
	return RET_SUCCESS;	
}

//��ʱ��֪����ʲô��
int API_NetDeActive(int tTimeOutMs)
{
	return RET_SUCCESS;	
}


//<FUN> ���ӷ���
//<INP> pAddr			:   ��������ַ
//<INP> tPort			:   �������˿�
//<INP> tTimeOutMs		:	����ʱʱ��,��λ:����	����������Ӵ���
//<RET> RET_TYPE		:   ������
int API_NetConnect(char* pAddr, int tPort, int tTimeOutMs)
{
	printf("API_NetConnect: pAddr[%s] tPort[%d] tTimeOutMs[%d]\n", pAddr, tPort, tTimeOutMs);
	/*
	if(socket_connected())//��������״̬
	{
		printf("API_NetConnect:��������״̬,ֱ�ӷ���RET_SUCCESS\n");
		return RET_SUCCESS;	
	}
	*/
	socket_disconnect_srv();
	
	char caPort[8]={0};
	sprintf(caPort, "%d", tPort);
	
	if(socket_connect_srv(pAddr, caPort))
	{
		printf("API_NetConnect:���ӳɹ�������RET_SUCCESS\n");
		return RET_SUCCESS;
	}
	else
		return RET_ERR;
	/*
	//��������������ʽ
	if(tTimeOutMs < 1)
		tTimeOutMs = 1;
	int iCount=0;
	while(1==1)
	{
		iCount += 1;
		if(iCount > tTimeOutMs)
		{
			printf("API_NetConnect:���ӳ�����������RET_TIMEOUT\n");
			return RET_TIMEOUT;	
		}
		printf("API_NetConnect:pAddr[%s] caPort[%s]\n", pAddr, caPort);
		if(socket_connect_srv(pAddr, caPort))
		{
			printf("API_NetConnect:���ӳɹ�������RET_SUCCESS\n");
			return RET_SUCCESS;
		}
	}
	*/
	/*//�����ǳ�ʱд��
	time_t begin;
	begin = time(NULL);
	while(1==1)
	{
		tTimeOutMs = 9000;
		if( (time(NULL)-begin) >= tTimeOutMs/1000) 
		{
			printf("API_NetConnect:���ӳ�ʱ������RET_TIMEOUT\n");
			return RET_TIMEOUT;	
		}
		printf("API_NetConnect:pAddr[%s] caPort[%s]\n", pAddr, caPort);
		if(socket_connect_srv(pAddr, caPort))
		{
			printf("API_NetConnect:���ӳɹ�������RET_SUCCESS\n");
			return RET_SUCCESS;
		}
	}
	*/
	return RET_ERR;
}


//<FUN> �Ͽ�����
//<INP> tTimeOutMs		:	����ʱʱ��,��λ:����
//<RET> RET_TYPE		:   ������
int API_NetDisConnect(int tTimeOutMs)
{
	socket_disconnect_srv();
	return 0;
}


//<FUN> ��������
//<INP> pSendBuf		:   Ҫ���͵����ݻ�����
//<INP> tSendLen		:   Ҫ���͵����ݳ���
//<INP> tTimeOutMs		:	����ʱʱ��,��λ:����
//<RET> RET_TYPE		:   ������
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




//<FUN> ��������
//<INP> pRecvBuf		:   �������ݻ�����
//<INP> tRecvLen		:   �������ݻ���������
//<INP> tTimeOutMs		:	����ʱʱ��,��λ:����
//<RET> RET_TYPE		:   ʵ���յ������ݳ���
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
		return iRet;//ʵ�ʽӵ����ݳ���
	}
		
}


//��ʱ��֪����ʲô
int API_NetEvent(int* pRet)
{
	return RET_SUCCESS;
}



