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

//◎数据通信接口

enum NET_OPT
{
	NOPT_TST			=0,		//
	
	NOPT_APN			=1,		//S设置接入点		pVal(char*)为APN						tValSize未使用
	NOPT_USERNAME		=2,		//S设置用户名       pVal(char*)为USERNAME					tValSize未使用
	NOPT_PASSWORD		=3,		//S设置密码         pVal(char*)为PASSWORD					tValSize未使用
	
	NOPT_REGISTER		=4,		//S网络注册			pVal未使用								tValSize为超时时间(单位:毫秒)
	NOPT_UART_BAUD		=5,		//G通信波特率       pVal(int*)为通信波特率					tValSize未使用
	NOPT_RESET			=6,		//S模块复位			pVal未使用								tValSize为超时时间(单位:毫秒)
	NOPT_INFO			=7,		//G模块信息			pVal(char*)为模块信息					tValSize未使用
	NOPT_PWRSWITCH		=8,		//S电源开关         pVal(int*)为电源开关[1为开,0为关]		tValSize未使用
	NOPT_ISCONNECT		=9,		//G查询连接状态		pVal(int*)为是否连接[1已连接,0未连接]	tValSize未使用
	NOPT_SETLINKAT		=10,	//S连接命令集合		pVal(char**)为命令集合					tValSize为命令总数

	NOPT_ESN			=11,	//G获取ESN          pVal(char*)为ESN						tValSize未使用
	NOPT_IMEI			=12,	//G获取IMEI         pVal(char*)为IMEI						tValSize未使用
	NOPT_IMSI			=13,	//G获取IMSI         pVal(char*)为IMSI						tValSize未使用
	NOPT_CCID			=14,	//G获取CCID         pVal(char*)为CCID						tValSize未使用
	NOPT_OPNAME			=15,	//G网络名称			pVal(char*)为网络名称					tValSize未使用
	
	NOPT_READY			=21,	//G网络就绪状态  	pVal(int*)为就绪状态[1就绪,0未就绪]		tValSize未使用
	NOPT_SIGNL			=22,	//G网络信号级别  	pVal(int*)为信号级别[0-100]				tValSize未使用
	
	NOPT_CMD			=31,	//S执行模块命令		pVal(char*)为发送的命令和应答			tValSize为超时时间(单位:毫秒)	
	
	NOPT_MAX					
};		

enum NET_EVENT
{
	NET_ERR				=0,		//
	NET_AT				=1,		//AT命令
	NET_STATE			=2,		//网络状态
	NET_ACTIVE			=3,		//激活网络		
	NET_DEACTIVE		=4,		//去激活网络
	NET_CONNECT			=5,		//连接网络		
	NET_DISCONNECT		=6,		//断开网络连接  
	NET_SEND			=7,		//发送数据      
	NET_RECV			=8,		//接收数据      
	NET_EXIT			=9,		//服务退出
	NET_REGISTER		=10,	//网络注册
	NET_RESET			=11,	//网络复位
	NET_WAITCONNECT		=12,	//等待客户端连接	
};		


#ifdef __cplusplus
extern "C"
{
#endif

	///私有接口///
	bool  socket_connected();
	bool  socket_connect_srv(char *p_caHost, char *p_caPort);
	void  socket_disconnect_srv();
	int   socket_read(char *p_caOutstr, int p_iReadln, int p_iTimeout);
	int   socket_write(char *p_caInstr, int p_iWriteln);
	/////////////


    //<FUN> 打开通信设备
	//<INP> tCommType		:   通信设备  (NET_SYNC_MODEM、NET_ASYN_MODEM、NET_GPRS_MODEM)
	//<RET> RET_TYPE		:   错误码 
	int API_NetOpen(int tCommType);
	
	//<FUN> 关闭通信设备
	//<RET> RET_TYPE		:   错误码
	int API_NetClose(void);

	//<FUN> 设置选项参数
	//<INP> tOption			:   为参数类型(OPT_TYPE)
	//<INP> pVal			:   为参数缓冲区
	//<INP> tValSize		:   为参数缓冲区长度
	//<RET> RET_TYPE		:   错误码
	int API_NetSetOpt(int tOption, void* pVal, int  tValSize);

	//<FUN> 获取选项参数
	//<INP> tOption			:   为参数类型(OPT_TYPE)
	//<INP> pVal			:   为参数缓冲区
	//<INP> tValSize		:   为参数缓冲区长度
	//<RET> RET_TYPE		:   错误码
	int API_NetGetOpt(int tOption, void* pVal, int  tValSize);

	int API_NetActive(int tTimeOutMs);
	int API_NetDeActive(int tTimeOutMs);

	//<FUN> 连接服务
	//<INP> pAddr			:   服务器地址
	//<INP> tPort			:   服务器端口
	//<INP> tTimeOutMs		:	处理超时时间,单位:毫秒
	//<RET> RET_TYPE		:   错误码
	int API_NetConnect(char* pAddr,int tPort,int tTimeOutMs);

	//<FUN> 断开连接
	//<INP> tTimeOutMs		:	处理超时时间,单位:毫秒
	//<RET> RET_TYPE		:   错误码
	int API_NetDisConnect(int tTimeOutMs);

	//<FUN> 发送数据
	//<INP> pSendBuf		:   要发送的数据缓冲区
	//<INP> tSendLen		:   要发送的数据长度
	//<INP> tTimeOutMs		:	处理超时时间,单位:毫秒
	//<RET> RET_TYPE		:   错误码
	int API_NetSend(u8* pSendBuf,int  tSendLen,int tTimeOutMs);

	//<FUN> 接收数据
	//<INP> pRecvBuf		:   接收数据缓冲区
	//<INP> tRecvLen		:   接收数据缓冲区长度
	//<INP> tTimeOutMs		:	处理超时时间,单位:毫秒
	//<RET> RET_TYPE		:   实际收到的数据长度
	int API_NetRecv(u8* pRecvBuf,int tRecvLen,int tTimeOutMs);

	int API_NetEvent(int* pRet);


#ifdef __cplusplus
}
#endif

#endif // GUI_INTERFACE_H
