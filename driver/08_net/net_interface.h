#ifndef NET_INTERFACE_H
#define NET_INTERFACE_H

typedef		unsigned char	u8;

enum NET_TYPE
{
	NET_SYNC_MODEM	= 0,
	NET_ASYN_MODEM	= 1,
	NET_GPRS_MODEM	= 2,
};

enum RET_TYPE
{
	RET_SUCCESS	= 0,
	RET_ERR		= 1,
	RET_TIMEOUT	= 2,
};

//������ͨ�Žӿ�

enum NET_OPT
{
	NOPT_TST			=0,		//
	
	NOPT_APN			=1,		//S���ý����		pVal(char*)ΪAPN						tValSizeδʹ��
	NOPT_USERNAME		=2,		//S�����û���       pVal(char*)ΪUSERNAME					tValSizeδʹ��
	NOPT_PASSWORD		=3,		//S��������         pVal(char*)ΪPASSWORD					tValSizeδʹ��
	
	NOPT_REGISTER		=4,		//S����ע��			pValδʹ��								tValSizeΪ��ʱʱ��(��λ:����)
	NOPT_UART_BAUD		=5,		//Gͨ�Ų�����       pVal(int*)Ϊͨ�Ų�����					tValSizeδʹ��
	NOPT_RESET			=6,		//Sģ�鸴λ			pValδʹ��								tValSizeΪ��ʱʱ��(��λ:����)
	NOPT_INFO			=7,		//Gģ����Ϣ			pVal(char*)Ϊģ����Ϣ					tValSizeδʹ��
	NOPT_PWRSWITCH		=8,		//S��Դ����         pVal(int*)Ϊ��Դ����[1Ϊ��,0Ϊ��]		tValSizeδʹ��
	NOPT_ISCONNECT		=9,		//G��ѯ����״̬		pVal(int*)Ϊ�Ƿ�����[1������,0δ����]	tValSizeδʹ��
	NOPT_SETLINKAT		=10,	//S���������		pVal(char**)Ϊ�����					tValSizeΪ��������

	NOPT_ESN			=11,	//G��ȡESN          pVal(char*)ΪESN						tValSizeδʹ��
	NOPT_IMEI			=12,	//G��ȡIMEI         pVal(char*)ΪIMEI						tValSizeδʹ��
	NOPT_IMSI			=13,	//G��ȡIMSI         pVal(char*)ΪIMSI						tValSizeδʹ��
	NOPT_CCID			=14,	//G��ȡCCID         pVal(char*)ΪCCID						tValSizeδʹ��
	NOPT_OPNAME			=15,	//G��������			pVal(char*)Ϊ��������					tValSizeδʹ��
	
	NOPT_READY			=21,	//G�������״̬  	pVal(int*)Ϊ����״̬[1����,0δ����]		tValSizeδʹ��
	NOPT_SIGNL			=22,	//G�����źż���  	pVal(int*)Ϊ�źż���[0-100]				tValSizeδʹ��
	
	NOPT_CMD			=31,	//Sִ��ģ������		pVal(char*)Ϊ���͵������Ӧ��			tValSizeΪ��ʱʱ��(��λ:����)	
	
	NOPT_MAX					
};		

enum NET_EVENT
{
	NET_ERR				=0,		//
	NET_AT				=1,		//AT����
	NET_STATE			=2,		//����״̬
	NET_ACTIVE			=3,		//��������		
	NET_DEACTIVE		=4,		//ȥ��������
	NET_CONNECT			=5,		//��������		
	NET_DISCONNECT		=6,		//�Ͽ���������  
	NET_SEND			=7,		//��������      
	NET_RECV			=8,		//��������      
	NET_EXIT			=9,		//�����˳�
	NET_REGISTER		=10,	//����ע��
	NET_RESET			=11,	//���縴λ
	NET_WAITCONNECT		=12,	//�ȴ��ͻ�������	
};		


#ifdef __cplusplus
extern "C"
{
#endif

	///˽�нӿ�///
	bool  socket_connected();
	bool  socket_connect_srv(char *p_caHost, char *p_caPort);
	void  socket_disconnect_srv();
	int   socket_read(char *p_caOutstr, int p_iReadln, int p_iTimeout);
	int   socket_write(char *p_caInstr, int p_iWriteln);
	/////////////


    //<FUN> ��ͨ���豸
	//<INP> tCommType		:   ͨ���豸  (NET_SYNC_MODEM��NET_ASYN_MODEM��NET_GPRS_MODEM)
	//<RET> RET_TYPE		:   ������ 
	int API_NetOpen(int tCommType);
	
	//<FUN> �ر�ͨ���豸
	//<RET> RET_TYPE		:   ������
	int API_NetClose(void);

	//<FUN> ����ѡ�����
	//<INP> tOption			:   Ϊ��������(OPT_TYPE)
	//<INP> pVal			:   Ϊ����������
	//<INP> tValSize		:   Ϊ��������������
	//<RET> RET_TYPE		:   ������
	int API_NetSetOpt(int tOption, void* pVal, int  tValSize);

	//<FUN> ��ȡѡ�����
	//<INP> tOption			:   Ϊ��������(OPT_TYPE)
	//<INP> pVal			:   Ϊ����������
	//<INP> tValSize		:   Ϊ��������������
	//<RET> RET_TYPE		:   ������
	int API_NetGetOpt(int tOption, void* pVal, int  tValSize);

	int API_NetActive(int tTimeOutMs);
	int API_NetDeActive(int tTimeOutMs);

	//<FUN> ���ӷ���
	//<INP> pAddr			:   ��������ַ
	//<INP> tPort			:   �������˿�
	//<INP> tTimeOutMs		:	����ʱʱ��,��λ:����
	//<RET> RET_TYPE		:   ������
	int API_NetConnect(char* pAddr,int tPort,int tTimeOutMs);

	//<FUN> �Ͽ�����
	//<INP> tTimeOutMs		:	����ʱʱ��,��λ:����
	//<RET> RET_TYPE		:   ������
	int API_NetDisConnect(int tTimeOutMs);

	//<FUN> ��������
	//<INP> pSendBuf		:   Ҫ���͵����ݻ�����
	//<INP> tSendLen		:   Ҫ���͵����ݳ���
	//<INP> tTimeOutMs		:	����ʱʱ��,��λ:����
	//<RET> RET_TYPE		:   ������
	int API_NetSend(u8* pSendBuf,int  tSendLen,int tTimeOutMs);

	//<FUN> ��������
	//<INP> pRecvBuf		:   �������ݻ�����
	//<INP> tRecvLen		:   �������ݻ���������
	//<INP> tTimeOutMs		:	����ʱʱ��,��λ:����
	//<RET> RET_TYPE		:   ʵ���յ������ݳ���
	int API_NetRecv(u8* pRecvBuf,int tRecvLen,int tTimeOutMs);

	int API_NetEvent(int* pRet);


#ifdef __cplusplus
}
#endif

#endif // GUI_INTERFACE_H
