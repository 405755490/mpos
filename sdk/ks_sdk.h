
#ifndef _KS_SDK_H_
#define _KS_SDK_H_

//#include "stdafx.h"
#include "ks_gui.h"
//-----------------------------------------------------------------------------------------------------------------------

enum TRACE_MODE
{    
    TRACE_TO_NULL =         0x00,   //不输出调试信息
    TRACE_TO_CONSOLE =		0x01,	//调试信息输出到终端显示中
    TRACE_TO_FILE =			0x02	//调试信息输出到文件中
};
//-----------------------------------------------------------------------------------------------------------------------
enum INIT_MODULE
{
	M_SYS				=0x00000001,		//系统
	M_DISPLAY			=0x00000002,		//输出显示
	M_INPUT				=0x00000004,		//输入系统
	M_UI_CFG			=0x00000008,		//加载UI配置
	
	M_CARD				=0x00000010,		//卡片模块
	M_PRINT				=0x00000020,		//打印模块
	M_NET_INIT			=0x00000040,		//网络初始化
	M_NET_WORK			=0x00000080,		//网络工作
	M_ALL				=0xFFFFFFFF			//全部功能
};	//V1.2
		
extern int  SDK_Init(int argc, char **argv);					//SDK运行环境初始化
extern void SDK_Exit(void);					//
extern void * GetKey_UI_proc( );

extern int  API_Init(u32 tModule);			//API接口模块初始化 INIT_MODULE
extern int  API_Exit(u32 tModule);			//

//-----------------------------------------------------------------------------------------------------------------------
//◎调试输出
	
enum DBG_TYPE
{
	DBG_NONE			=0,					//无调试输出	
	DBG_CON				=1,					//调试输出到控制台	
	DBG_MEM				=2,					//调试输出到内存	
	DBG_UART_A			=3,					//调试输出到串口A	
	DBG_UART_B			=4,					//调试输出到串口B	
	DBG_USB_CDC			=5,					//调试输出到USB串口	
	DBG_NET				=6,					//调试输出到网络	
	DBG_FILE			=7,					//调试输出到文件	
	DBG_TFLASH			=8,					//调试输出到存储卡	
	DBG_TYPE_MAX
};
enum DBG_LEVEL
{
	DBG_APP_INFO		=0x01,				//普通调试信息		
	DBG_APP_WARMING		=0x02,				//警告调试信息		
	DBG_APP_ERROR		=0x04,				//错误调试信息	
	DBG_APP_SECRECY		=0x08,				//保密调试信息	
	DBG_APP_1			=0x10,				//用户调试信息分组1		如UI部分
	DBG_APP_2			=0x20,				//用户调试信息分组2		如流程码处理
	DBG_APP_3			=0x40,				//用户调试信息分组3		如通信部分处理
	DBG_APP_4			=0x80,				//用户调试信息分组4		如电话功能库
	DBG_APP_MASK		=0xFF				//应用调试信息	
};	//VER:1.1

	//<FUN> 调试输出文本信息,自动换行
	//<INP> tLevel			:   调试信息类型(DBG_LEVEL)
	//<INP> pFmt			:   格式控制串(类似printf)
	//<INP> ...				:   可变参数
extern void API_Trace(   u32 tLevel,char* pFmt,...);	
					
	//<FUN> 调试输出以16进制信息,自动换行
	//<INP> tLevel			:   调试信息类型(DBG_LEVEL)
	//<INP> pMsg			:   提示信息
	//<INP> pBuf			:   调试数据缓冲区
	//<INP> tLen			:   调试数据长度
extern void API_TraceHex(u32 tLevel,char* pMsg,void* pBuf,int tLen);	

	//<FUN> 获取调试类型
	//<RET>  				:   DBG_TYPE
extern int  API_GetDbgType(void);

	//<FUN> 设置调试类型
	//<INP> tType			:   DBG_TYPE
extern int  API_SetDbgType(int tType);

	//<FUN> 获取调试级别(可调试的模块)
	//<RET>  				:   DBG_LEVEL
extern int  API_GetDbgLevel(void);
	//<FUN> 设置调试级别(可调试的模块)
	//<INP> tLevel			:   DBG_LEVEL
extern int  API_SetDbgLevel(int tLevel);

enum ERROR_TYPE
{
    ERROR_INIT_THREAD_CONDITION             = -101,     //初始化线程使用环境
    ERROR_CREATE_THREAD                     = -102     //创建线程
};
	//<FUN> 获取最后一次的错误码
	//<RET> int				:   错误码 errcode.h
extern int  API_GetLastError(void);	

//-----------------------------------------------------------------------------------------------------------------------
//◎系统信息

enum INFO_TYPE		
{
	INFO_DEV_NAME			=0x0101,		//设备名称	   		pVal="KS8210"
	INFO_KERNEL_VER			=0x0102,		//内核软件版本 		pVal="1.0.1"
	INFO_SYS_VER			=0x0103,		//系统软件版本 		pVal="1.0.1"
	INFO_SDK_VER			=0x0104,		//SDK 软件版本 		pVal="1.2.0"
	
	INFO_LCD_TYPE			=0x0201,		//LCD 显示类型 		ret =DISP_TYPE
	
	INFO_ENUM_KEY			=0x0301,		//枚举按键     		ret =按键总数,		pVal=按键          数组
	INFO_ENUM_ICC			=0x0302,		//枚举IC卡读卡器    ret =IC卡总数,		pVal=ICC_INDEX     数组
	INFO_ENUM_MAG			=0x0303,		//枚举磁卡	        ret =磁道总数,
	INFO_ENUM_UART			=0x0304,		//枚举串口     		ret =串口总数,		pVal=UART_INDEX    数组
	INFO_ENUM_NET			=0x0305,		//枚举网络     		ret =网络总数,		pVal=NET_INDEX     数组
	INFO_ENUM_PLAY			=0x0306,		//枚举播放类型    	ret =播放类型总数,	pVal=PLAY_TYPE     数组
	INFO_ENUM_IMAGE			=0x0307,		//枚举图片类型    	ret =图片类型总数,	pVal=IMAGE_TYPE    数组
	INFO_ENUM_LED			=0x0308,		//枚举LED灯    		ret =LED灯总数,		pVal=LED_MASK      数组
	INFO_ENUM_SECMEMORY		=0x0309,		//枚举安全存储器	ret =安全存储器总数,pVal=SECMEMORY_TYPE数组
	INFO_ENUM_PHONE			=0x030A,		//枚举电话模块		ret =电话模块总数,	pVal=PHONE_TYPE    数组	
};	//Ver:2.7

	//<FUN> 获取系统信息
	//<INP> tInfoType		:   系统信息类型(INFO_TYPE)
	//<OUP> pVal			:   系统信息缓冲区
	//<OUP> tValLen			:   系统信息缓冲区长度
	//<RET> int				:   错误码RET_TYPE或INFO_TYPE的值
extern int 	API_GetSysInfo(u32 tInfoType,void* pVal,int tValLen);


enum CTRL_TYPE		
{
	SYS_CTRL_TELS_PWR		=0x0101,	//电话模块电源开关		参数:u8	0/1(高电平)	无此功能	
	SYS_CTRL_TELS_RST		=0x0102,	//电话模块复位开关		参数:u8	0/1(高电平)
	SYS_CTRL_TELS_BOOT		=0x0103,	//电话模块Boot开关		参数:u8	0/1(高电平)				
};	//Ver:1.2

	//<FUN> 系统控制接口，供系统管理维护模块使用
	//<INP> tCtrlType		:   系统信息类型(CTRL_TYPE)
	//<OUP> pVal			:   系统信息缓冲区
	//<OUP> tValLen			:   系统信息缓冲区长度
	//<RET> int				:   错误码RET_TYPE或INFO_TYPE的值
extern int API_Control(u32 tCtrlType,void* pVal,int tValLen);

//-----------------------------------------------------------------------------------------------------------------------
//◎编码转换

	//<FUN> 字符串转换成Unicode2  GB2312 -> UCS2	
extern void API_GbkToUniCode(char *dest,int dest_size, char *src);

	//<FUN> Unicode2转换成字符串  UCS    -> 2GB2312
extern void API_UniCodeToGbk(char *dest,int dest_size, char *src);

extern int  API_UniCodeLen(char* pStr);

//-----------------------------------------------------------------------------------------------------------------------
//◎数据转换	

	//<FUN> Hex数字转成相应字符
	//<FUN> 	0x0-0x9='0'-'9'   0xA-0xF='A'-'F'  其它=' '
extern s8 API_Conv_NumToChar(u8 b);
					
	//<FUN> 字符转成相应Hex数字
	//<FUN> 	'0'-'9'=0x0-0x9  'a'-'f'=0xA-0xF	'A'-'F'=0xA-0xF
extern u8 API_Conv_CharToNum(s8 c);
		
	//<FUN> 字符串转成BCD码，BCD码左对齐
	//<FUN> 	bcd	="\xFF\xFF\xFF\xFF\xFF\xFF\xFF";
	//<FUN> 	API_Conv_StrToBcd("12345",5,bcd);	
	//<FUN> 	bcd	="\x12\x34\x5F\xFF\xFF\xFF\xFF";
extern void API_Conv_StrToBcd_Left(s8* str,int strlen,u8* bcd);

	//<FUN> 字符串转成BCD码，BCD码右对齐
	//<FUN> 	bcd	="\x00\x00\x00\x00\x00\x00\x00";
	//<FUN> 	API_Conv_StrToBcd_Right("12345",5,bcd,7);	
	//<FUN> 	bcd	="\x00\x00\x00\x00\x01\x23\x45F";
extern void API_Conv_StrToBcd_Right(s8* str,int slen,u8 *bcd,int blen);

	//<FUN> BCD码转成字符串
	//<FUN> 	bcd	="\x12\x34\x5F\xFF\xFF\xFF\xFF";
	//<FUN> 	API_Conv_BcdToStr(bcd,4,str);	
	//<FUN> 	str	="12345FFF";
extern void API_Conv_BcdToStr(u8* bcd,int blen,s8* str);

			
	//<FUN> 16进制数字符串转换为数值
	//<FUN> 	szNum="12AB"	szNumLen=4
	//<FUN> 	return 4779
extern u32 	API_Conv_GetHex(u8 *szNum,int szNumLen);


	//<FUN> 10进制数字符串转换为数值
	//<FUN> 	szNum="1234"	szNumLen=4 
	//<FUN> 	return 1234
	//<INP> szNum			:   为10进制数字符串
	//<INP> szNumLen		:   为字符串长度。
	//<RET> u32				:   转换后的数值
extern u32 	API_Conv_GetNum(char* szNum,int szNumLen);


//-----------------------------------------------------------------------------------------------------------------------
//◎加密算法


//-----------------------------------------------------------------------------------------------------------------------
//◎安全管理


//-----------------------------------------------------------------------------------------------------------------------
//◎时间

typedef struct
{
	int	  Year;		// The number of years						range 1900 to xxxx
	int	  Month;	// The number of months, 					range 1 to 12
	int	  Day;		// The day of the month, 					range 1 to 31
	int	  Hour;		// The number of hours past midnight, 		range 0 to 23
	int	  Min;		// The number of minutes after the hour, 	range 0 to 59
	int	  Sec;		// The number of seconds after the minute,  range 0 to 59, (60 to allow for leap seconds)
	int	  MSec;		// The number of MSec after the minute, 	range 
	int	  WeekDay; 	// The number of days since Sunday,    		range 0 to 6
	int	  YearDay; 	// The number of days since January 1, 		range 0 to 365
}DATE_TIME;


	//<FUN> 获取系统时间
	//<OUP> pTime			:   DATE_TIME
extern void API_TimeGet(DATE_TIME* pTime);		

	//<FUN> 设置系统时间
	//<INP> pTime			:   DATE_TIME
extern void API_TimeSet(DATE_TIME* pTime);		


	//<FUN> 获取当前毫秒数
	//<RET> int				:   单位:豪秒
extern int  API_TimeCurrMS(void);				

	//<FUN> 获取当前秒数
	//<RET> int				:   单位:秒
extern int  API_TimeCurrSec(void);				

	//<FUN> 睡眠指定时间
	//<INP> tTime			:   睡眠时间,单位:微秒
extern void API_TimeSleepUS(u32 tTime);			

	//<FUN> 睡眠指定时间
	//<INP> tTime			:   睡眠时间,单位:豪秒
extern void API_TimeSleepMS(u32 tTime);			

	//<FUN> 睡眠指定时间
	//<INP> tTime			:   睡眠时间,单位:秒
extern void API_TimeSleepS(u32 tTime);			

//-----------------------------------------------------------------------------------------------------------------------
//◎文件系统



//-----------------------------------------------------------------------------------------------------------------------
//◎通用定义

enum RET_TYPE
{
	RET_OK			=0x0000,			
	RET_ERR			=0x0001,			
	RET_KNOW		=0xC100,			
	RET_TIMEOUT		=0xC200,
	RET_NOCARD		=0xC300,
	RET_PARERR		=0xC400,
	RET_NOTSUPPORT	=0xC500,
	RET_MASK		=0xFFFF
};
enum ICC_INDEX
{
	ICC_CONTSCT		=0x01,		//接触式IC卡	 contact	
	ICC_NON_CONTSCT	=0x02,		//非接触式IC卡	 non-contact 
	ICC_PSAM1		=0x04,		//PSAM卡1
	ICC_PSAM2		=0x08,		//PSAM卡2
	ICC_MAX			=4
};	
enum UART_INDEX
{
	UART_1			=0x01,		//串口1 控制台,	KN和8112为RJ45,8210为MiniUsb
	UART_2			=0x02,		//串口2 扩展口,	KN和8112为RJ11,8210为扫描头
	UART_3			=0x04,		//串口3 KN为电话模块串口   (仅供系统测试使用)
	UART_4			=0x08,		//串口4 全功能串口Modem	   (仅供系统测试使用)
	UART_MAX		=4
};	
enum NET_INDEX
{
	NET_UNKNOW		=0x00,		//未知
	NET_SYNC_MODEM	=0x01,		//同步Modem
	NET_ASYN_MODEM	=0x02,		//异步Modem
	NET_PLMN_MASTER	=0x04,		//陆上公用移动通信网（Public Land Mobile Network）
	NET_PLMN_SLAVE	=0x08,		//陆上公用移动通信网（Public Land Mobile Network）
	NET_SOCKET		=0x10,		//Socket接口
	NET_FSK			=0x20,		//FSK通信
	NET_MAX			=5
};	

enum PLAY_TYPE
{
	PLAY_BEEP	=0x01,			//Beep
	PLAY_WAVE	=0x02,			//wav语音文件
};

enum IMAGE_TYPE
{
	IMAGE_IMG	=0x01,			//自定义图片文件
	IMAGE_BMP	=0x02,			//
	IMAGE_PNG	=0x04,			//
	IMAGE_GIF	=0x08,			//
};


#define TIME_ONCE		(0)			//马上返回
#define TIME_INFINE		(-1)		//一直等
#define TIME_NOWAIT		(-2)		//不等待


enum EVENT_TYPE
{
	EVENT_NONE		=0x00000000,	//无效事件
	EVENV_ICC_POWERUP_ERR = 0x0000000F, 	//IC卡上电失败
	EVENT_INDEX		=0x000000FF,	//设备索引
	
	EVENT_ICC		=0x00000100,	//接触式IC卡/非接触式IC卡/PSAM卡		
	EVENT_MAG		=0x00000200,	//磁卡刷卡		
	EVENT_NET		=0x00000400,	//网络通信接口			API_NetEvent
	EVENT_USB		=0x00000800,	//USB接口		
					
	EVENT_KEY		=0x00001000,	//按键		
	EVENT_PEN		=0x00002000,	//触摸屏	
	EVENT_UART		=0x00004000,	//UART串口		
	EVENT_AUDIO		=0x00008000,	//音频通信接口	
	
	EVENT_UI		=0x00010000,	//图形用户界面接口	
	EVENT_SYS		=0x00020000,	//系统接口		
	EVENT_MISC		=0x00040000,	//其他杂项接口
	EVENT_PRINT		=0x00080000,	//打印完成

	EVENT_PHONE		=0x00100000,	//电话功能				API_Phone_GetEvent

	EVENT_ERROR		=0x01000000,	//错误	   
	EVENT_TIMEOUT	=0x02000000,	//超时	   
	EVENT_OK  		=0x04000000,	//确认	   确认		确认	是
	EVENT_CANCEL	=0x08000000,	//取消	   返回		退出	否
	EVENT_QUIT		=0x10000000,	//退出
	EVENT_MASK		=0xFFFFFF00	
};	



	//<FUN> 等待相关事件列表触发
	//<FUN> 	任何事件		返回EVENT_ERROR|EVENT_TIMEOUT
	//<FUN> 	EVENT_UI事件	返回EVENT_OK|EVENT_CANCEL|EVENT_QUIT
	//<FUN> 	其它EVENT_TYPE	返回EVENT_TYPE|EVENT_INDEX		
	//<INP> tTimeOutMs		:   等待超时时间，单位:毫秒
	//<INP> ...				:   事件类型(EVENT_TYPE|EVENT_INDEX),如：(EVENT_UART|UART_1)表示串口1
	//<RET> EVENT_TYPE		:   EVENT_ERROR|EVENT_TIMEOUT|EVENT_OK|EVENT_CANCEL|tEventMask
extern u32  API_WaitEvent(int tTimeOutMs,...);
extern u32  API_WaitEventGroup(int tTimeOutMs,int tNum,u32* pEventGroup);
//extern u32  API_WaitEvent_GetCheck(char *buffer,int *retkey,char *disperror,pthread_mutex_t  *w_lock);


	
//-----------------------------------------------------------------------------------------------------------------------
//◎打印机接口


//-----------------------------------------------------------------------------------------------------------------------
//◎卡片操作接口
extern void API_ICC_Reset();

extern int API_ICC_Open(int tCardIndex);

extern int API_ICC_Close(int tCardIndex);

	//<FUN> 卡片上电
	//<INP> tCardIndex		:	卡片索引(ICC_CONTSCT、ICC_NON_CONTSCT、ICC_PSAM1、ICC_PSAM2)
	//<RET> RET_TYPE		:   错误码
extern int  API_ICC_PwrOn( 		int tCardIndex);	

	//<FUN> 返回卡片ATR信息
	//<INP> tCardIndex		:	卡片索引(ICC_CONTSCT、ICC_NON_CONTSCT、ICC_PSAM1、ICC_PSAM2)
	//<OUP> pAtrBuf			:	返回IC卡ATR的数据缓冲区
	//<OUP> pInfoLen		:   ATR的数据缓冲区的最大长度
	//<RET> int				:   返回ATR数据长度
extern int  API_ICC_GetAtr( 	int tCardIndex,u8* pAtrBuf,int nAtrBufMax);	

	
	//<FUN> 卡片下电
	//<INP> tCardIndex		:	卡片索引(ICC_CONTSCT、ICC_NON_CONTSCT、ICC_PSAM1、ICC_PSAM2)
	//<RET> RET_TYPE		:   错误码
extern int  API_ICC_PwrOff(		int tCardIndex);	

	//<FUN> 卡片APDU指令
	//<INP> tCardIndex		:	卡片索引(ICC_CONTSCT、ICC_NON_CONTSCT、ICC_PSAM1、ICC_PSAM2)
	//<INP> pCmdBuf			:   发送的APDU命令数据缓冲区
	//<INP> nCmdLen			:   发送的APDU命令数据长度
	//<OUP> pOutBuf			:   返回数据缓冲区	(应用程序根据卡片结构自己控制缓冲区大小)
	//<OUP> pOutLen			:   返回数据长度
	//<RET> u32				:   返回SW值，如0x9000,0x6A82,0x0000
extern int  API_ICC_Apdu(		int tCardIndex,u8* pCmdBuf,int nCmdLen,u8* pOutBuf,int* pOutLen);

	//<FUN> 设置接触式IC卡事件是否仅检测插入（默认自动上电）。
	//<INP> isOnly			:   为0表示IC卡插入后自动上电，应用WaitEvent等到事件后直接API_ICC_GetAtr
	//<INP> isOnly			:   为1表示仅检测IC卡插入事件，应用WaitEvent等到事件后执行API_ICC_PwrOn+API_ICC_GetAtr
	//<RET> RET_TYPE		:   错误码
extern int  API_ICC_OnlyChkPreSent(int isOnly);
//-----------------------------------------------------------------------------------------------------------------------

#define MAG_DATA_PRESENTS	0x01	// 该磁道有数据
#define MAG_DECODE_SUCCUSS	0x02	// 该磁道数据解码成功

#define	MAG_TRK_LEN			120		// 磁道数据最大长度

typedef struct
{
	u8	Type;						// 输入类型 MAGPAR_TRK or MAGPAR_IC
	u8	Flag[3];					// 磁道标记KS_MAG_TRK_FLAG
	u8	Len[3];						// 磁道数据长度
	u8	Trk[3][MAG_TRK_LEN];		// 磁道数据
}MAGTRK;

extern int  API_SetTrkBuf(MAGTRK* pTrk);

//-----------------------------------------------------------------------------------------------------------------------
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

enum NET_STATUAS
{
	NET_STATUAS_NO_SIM			= 0, //无SIM卡
	NET_STATUAS_SIM_EXIT			= 1, //SIM卡已经插入
	NET_STATUAS_DEACTIVE			= 2, //网络不在线
	NET_STATUAS_ACTIVE				= 3  //网络在线
};
//	V1.5


	//<FUN> 打开通信设备
	//<INP> tCommType		:   通信设备  (NET_SYNC_MODEM、NET_ASYN_MODEM、NET_GPRS_MODEM)
	//<RET> RET_TYPE		:   错误码 
extern int  API_NetOpen(int tCommType);

	//<FUN> 关闭通信设备
	//<RET> RET_TYPE		:   错误码
extern int  API_NetClose(void);

	//<FUN> 设置选项参数
	//<INP> tOption			:   为参数类型(OPT_TYPE)
	//<INP> pVal			:   为参数缓冲区
	//<INP> tValSize		:   为参数缓冲区长度
	//<RET> RET_TYPE		:   错误码
extern int 	API_NetSetOpt(int tOption, void* pVal, int  tValSize);

	//<FUN> 获取选项参数
	//<INP> tOption			:   为参数类型(OPT_TYPE)
	//<INP> pVal			:   为参数缓冲区
	//<INP> tValSize		:   为参数缓冲区长度
	//<RET> RET_TYPE		:   错误码
extern int 	API_NetGetOpt(int tOption, void* pVal, int  tValSize);

extern int 	API_NetActive(int tTimeOutMs);
extern int 	API_NetDeActive(int tTimeOutMs);

	//<FUN> 连接服务
	//<INP> pAddr			:   服务器地址
	//<INP> tPort			:   服务器端口
	//<INP> tTimeOutMs		:	处理超时时间,单位:毫秒
	//<RET> RET_TYPE		:   错误码
extern int 	API_NetConnect(char* pAddr,int tPort,int tTimeOutMs);

	//<FUN> 断开连接
	//<INP> tTimeOutMs		:	处理超时时间,单位:毫秒
	//<RET> RET_TYPE		:   错误码
extern int 	API_NetDisConnect(int tTimeOutMs);

	//<FUN> 发送数据
	//<INP> pSendBuf		:   要发送的数据缓冲区
	//<INP> tSendLen		:   要发送的数据长度
	//<INP> tTimeOutMs		:	处理超时时间,单位:毫秒
	//<RET> RET_TYPE		:   错误码
extern int 	API_NetSend(u8* pSendBuf,int  tSendLen,int tTimeOutMs);

	//<FUN> 接收数据
	//<INP> pRecvBuf		:   接收数据缓冲区
	//<INP> tRecvLen		:   接收数据缓冲区长度
	//<INP> tTimeOutMs		:	处理超时时间,单位:毫秒
	//<RET> RET_TYPE		:   实际收到的数据长度
extern int 	API_NetRecv(u8* pRecvBuf,int tRecvLen,int tTimeOutMs);

extern int  API_NetEvent(int* pRet);

//ZFC, 新增加对网络状态的判断
//<FUN> 判断网络状态
//<RET> RET_TYPE		:   网络的实际状态
extern int  API_NetStatuas(int nType);

//-----------------------------------------------------------------------------------------------------------------------

#define KeyEsc              0x1B
#define KeyEnter            0x0D
#define KeyClear            0x08
#define Key1                0x31
#define Key2                0x32
#define Key3                0x33
#define Key4                0x34
#define Key5                0x35
#define Key6                0x36
#define Key7                0x37
#define Key8                0x38
#define Key9                0x39
#define Key0                0x30
#define KeyF1               0x41
#define KeyF2               0x42
#define KeyF3               0x43
#define KeyF4               0x44
#define KeyStar		    0x2A

// #define MODEL_ZT8225        1

#if MODEL_ZT8225
//ZT8225的输入法切换按键和ZT8210C的切换按键是不同的
	#define KeyDot              0x46
	#define KeyAlpha            0x45
	#define Forword              0x41
	#define Backword           0x42
	#define Pageup	     	    0x43
	#define Pagedown	    0x44
#else
	#define KeyDot              0x45
	#define KeyAlpha            0x46
	#define Forword              0x41
	#define Backword            0x44
	#define Pageup	     	      0x42
	#define Pagedown	      0x43

#endif

extern int   API_GetPen(POINT* pPoint);
extern void  API_GetKey(int* pCode,int* pType);
extern int   API_GetKeyCode(int nTimeMs);
extern int	 API_GetKeyCode_No_Clear(int nTimeMs);
extern void  API_SetKeyDownBeep(int isBeep);
extern int   API_GetKeyDownBeep(void);

extern int   API_KeyEq(int tVal,int tKey);
extern int   API_KeyIsNum(int tVal);

//-----------------------------------------------------------------------------------------------------------------------
typedef struct
{
	u8			bFB;	
	u8			bFD;	
	u8			Bcc;	
	u8			VA;	
	int			Index;	
}UART_RX;				

extern int   API_Uart_Close(int inx);
extern int   API_Uart_Open(int inx);
extern int   API_Uart_SetOptions(int inx,int tBaud,int tDataBit,int tStopBit,int tParity);
extern int   API_Uart_Send(int inx,u8* pSendBuf,int tSendLen);
extern int   API_Uart_Recv(int inx,u8* pRecvBuf,int tRecvLen);

extern int   API_Uart_WaitSendComple(int inx);
extern int   API_Uart_WaitRecv(int inx,u8* pRecvBuf,int tRecvLen,int tTimeOutMS);
extern int   API_Uart_RxClrFlag(UART_RX* pF);
extern int   API_Uart_RxChar(UART_RX* pF,u8 RxCh,u8* pBuf,int tBufLen);
extern int   API_Uart_SendCmd(int inx,u8 *pBuf,int tBuflen);				
extern int   API_Uart_RecvCmd(int inx,UART_RX* pF,u8 *pBuf, int tBufSize,int tTimeOutMs);

//-----------------------------------------------------------------------------------------------------------------------
enum PR_RET
{
	PR_OK				=0,				//正常
	PR_ERR				=1,				//错误
	PR_IS_PRINTING		=2,				//缺纸
	PR_NO_PAPER			=3,				//缺纸
	PR_TEMP_HIGH		=4,				//温度过高
	PR_UNKNOW							//未知
};

extern void  API_PRN_Clear(void);
extern void  API_PRN_GetRect(RECT* pRect);
extern void  API_PRN_SetPos(int x,int y);
extern int   API_PRN_GetPos(int isX);
#define		 API_PRN_GetLine()		API_PRN_GetPos(0)
#define		 API_PRN_SetLine(tLine)	API_PRN_SetPos(0,tLine)

extern void  API_PRN_SetPixel(int x,int y,COLOR color);
extern COLOR API_PRN_GetPixel(int x,int y);
extern void  API_PRN_Line(int x1,int y1,int x2,int y2,COLOR color);
extern void  API_PRN_ShowFill(RECT* pRect,FILL * pFill);
extern void  API_PRN_ShowText(TEXT_TYPE tType,RECT* pRect,char* pText,COLOR tCT,COLOR tCB);
extern void API_PRN_Image(char *pstrImageFile);

extern void  API_PRN_Print( TEXT_TYPE tType,COLOR tCT,COLOR tCB,int tYSpace,char* pText);
extern void  API_PRN_Printf(TEXT_TYPE tType,COLOR tCT,COLOR tCB,int tYSpace,char* pText,...);
extern void  API_PRN_ShowImage(RECT* pRect,IMAGE* pImage);

extern int   API_PRN_Start(int tLine,int tDensity,int tWaitTimeMs);
extern int   API_PRN_Stop(void);
extern int   API_PRN_GetState(void);
extern int   API_PRN_SetSpeedStage(int isFast);

//add by zhzh 
enum PRN_ST
{    
    PRN_ST_OK	 = 0,   //正常
    PRN_ST_OUT	 = 1,	//缺纸
};

enum PRN_ALIGN
{    
    PRN_ALIGN_LEFT	 	= 0,	//靠左
    PRN_ALIGN_RIGHT		= 1,	//靠右
    PRN_ALIGN_CENTER	= 2,	//居中
};

#define TEXT_NOMAL_FONT 0
#define TEXT_SMALL_FONT 1
#define TEXT_BOLD 8
#define TEXT_UNDERLINE 128
#define TEXT_REVERSE 0x200
#define TEXT_ITALIC 64

extern int  API_PRN_InitPrint();
extern void API_PRN_SetText(int pi_iFontSize, int pi_iType, int pi_iAlign, char* pi_caText);
extern void API_PRN_SetPbm(unsigned char * buf, int iln);
extern int API_PRN_StartPrint();
extern int API_PRN_PrnClearStatus();
extern int API_PRN_ContinuePrint();
extern int API_PRN_GetStatus();
extern void API_PRN_StartPrint_Test();
extern void API_PRN_GB_2_UTF(char *pInbuf,int nInlen,char *pOutbuf,int nOutlen);
//-----------------------------------------------------------------------------------------------------------------------
	//<FUN> 设置INI参数（字符串类型）
	//<INP> pFile 		:   int文件路径,API导出时不支持路径.
	//<INP> pSection 		:   int文件段名,[]
	//<INP> pKeyName 		:   int文件关键字名称,标签名称
	//<INP> pStr 			:   标签名称对应的字符串
	//<RET> RET_TYPE 		:   错误码（0成功，非0失败）
extern int   API_Ini_SetStr(char* pFile,char* pSection,char* pKeyName,char* pStr);

	//<FUN> 获取INI参数（字符串类型）
	//<INP> pFile 			:   int文件路径,API导出时不支持路径.
	//<INP> pSection 		:   int文件段名,[]
	//<INP> pKeyName 		:   int文件关键字名称,标签名称
	//<INP> pDefStr 		:   标签名称对应的默认字符串
	//<OUP> pRetStr 		:   返回标签名称对应的字符串的缓冲区，如果失败返回默认字符串pDefStr
	//<INP> nRetSize 		:   返回标签名称对应的字符串的缓冲区大小
	//<RET> RET_TYPE 		:   错误码（0成功，非0失败）
extern int   API_Ini_GetStr(char* pFile,char* pSection,char* pKeyName,char* pDefStr,char* pRetStr,int nRetSize);

	//<FUN> 设置INI参数（整数类型）支持自然整数10进制(123、-1)，无符号16进制数(0xFE)，无符号2进制(0b10011)
	//<INP> pFile 			:   int文件路径,API导出时不支持路径.
	//<INP> pSection 		:   int文件段名,[]
	//<INP> pKeyName 		:   int文件关键字名称,标签名称
	//<INP> nIntVal 		:   标签名称对应的整数数值
	//<RET> RET_TYPE 		:   错误码（0成功，非0失败）
extern int   API_Ini_SetInt(char* pFile,char* pSection,char* pKeyName,int nIntVal);

	//<FUN> 获取INI参数（整数类型）支持自然整数10进制(123、-1)，无符号16进制数(0xFE)，无符号2进制(0b10011)
	//<INP> pFile	 		:   int文件路径,API导出时不支持路径.
	//<INP> pSection 		:   int文件段名,[]
	//<INP> pKeyName 		:   int文件关键字名称,标签名称
	//<INP> nDefVal 		:   标签名称对应的默认整数数值
	//<RET> int 			:   返回标签名称对应的整数数值,如果失败返回默认整数数值nDefVal
extern int   API_Ini_GetInt(char* pFile,char* pSection,char* pKeyName,int nDefVal);
//-----------------------------------------------------------------------------------------------------------------------
enum PHONE_TYPE
{
	PHONE_PSTN				=0x01,		//公用开关电话网络 
};
enum PHONE_CID_TYPE
{
	CID_TYPE_DTMF			=0x01,		//来电类型：DTMF
	CID_TYPE_FSK			=0x06,		//来电类型：FSK
	CID_TYPE_FSK_SDMF		=0x02,		//来电类型：FSK-单数据消息格式  (Single   Data Message Format) 
	CID_TYPE_FSK_MDMF		=0x04,		//来电类型：FSK-复合数据消息格式(Multiple Data Message Format) 
	CID_TYPE_MODEM			=0x80,		//来电类型：由Modem解码
};
enum PAR_ADDR
{
	PAR_DTMF_DURATION_TIME	=1,			//DTMF拨号持续时间,	单位:毫秒,	范围80-160,	默认为120
	PAR_DTMF_INTERVAL_TIME	=2,			//DTMF拨号间隔时间,	单位:毫秒,	范围80-160,	默认为120
	PAR_DTMF_PAUSE_TIME		=3,			//DTMF拨号暂停时间,	单位:10毫秒,范围30-250,	默认为100
	PAR_WAIT_DIALTONE_TIME	=4,			//  等待拨号音时间,	单位:10毫秒,范围30-250	默认为80
	PAR_END
};
enum PHONE_EVENT
{
	PHONE_EVENT_RING			=1,		//振铃事件
	PHONE_EVENT_CID				=2,		//来电事件
	PHONE_EVENT_HOOK_STA		=3		//叉簧状态
};	

	//<FUN> 获取电话事件类型    (当API_WaitEvent返回EVENT_PHONE后使用)
	//<OUP> pRet			:   当RET=PHONE_EVENT_HOOK_STA时,pRet=1为摘机状态,pRet=0为挂机状态
	//<OUP> pRet			:   当RET=PHONE_EVENT_CID     时,pRet=PHONE_CID_TYPE
	//<RET> int				:   为PHONE_EVENT
extern int  API_Phone_GetEvent(int* pRet);

	//<FUN> 获取电话来电信息
	//<OUP> pNumber			:   为来电号码	长度=36字节
	//<OUP> pName			:   为来电姓名	长度=32字节
	//<OUP> pTime			:   为来电时间	长度= 8字节	MMDDHHMM
	//<RET> int				:   错误码
extern int  API_Phone_GetCidInfo(char* pNumber,char* pName,char* pTime);

	//<FUN> 获取电话模块版本
	//<OUP> pMajor			:   为主版本
	//<OUP> pMinor			:   为从版本
	//<RET> int				:   错误码
extern int  API_Phone_Ver(int* pMajor,int* pMinor);

	//<FUN> 电话DTMF拨号	(P/p/,为暂停)
	//<INP> pNumber			:   为电话号码串
	//<RET> int				:   错误码
extern int  API_Phone_Dial(const char* pNumber);

	//<FUN> 摘挂机控制
	//<INP> isOff			:   1为摘机,默认为0 
	//<RET> int				:   错误码
extern int  API_Phone_HookSwitch(u8 isOff);

	//<FUN> 振铃开关控制
	//<INP> isOff			:   1为不振铃,默认为0 
	//<RET> int				:   错误码
extern int  API_Phone_RingSwitch(u8 isOff);

	//<FUN> 麦克开关控制
	//<INP> isOff			:   1为静音,默认为0 
	//<RET> int				:   错误码
extern int  API_Phone_MicSwitch(u8 isOff);

	//<FUN> 分机开关控制
	//<INP> isOff			:   1为断开分机,默认为0 
	//<RET> int				:   错误码
extern int  API_Phone_ExtSwitch(u8 isOff);

	//<FUN> 喇叭开关控制
	//<INP> isMute			:   1为静音,默认为0 
	//<RET> int				:   错误码
extern int  API_Phone_SpkSwitch(u8 isMute);

	//<FUN> 获取机械叉簧状态
	//<OUP> pIsOff			:   1为摘机,默认为0  
	//<RET> int				:   错误码
extern int  API_Phone_GetHookSta(u8* pIsOff);	

	//<FUN> 设置电话模块参数
	//<INP> tAddr			:   参数地址PAR_ADDR
	//<INP> tVal			:   参数数值
	//<RET> int				:   错误码
extern int  API_Phone_SetPar(u8 tAddr,u8  tVal);

	//<FUN> 获取电话模块参数
	//<INP> tAddr			:   参数地址PAR_ADDR
	//<OUP> pVal			:   参数数值
	//<RET> int				:   错误码
extern int  API_Phone_GetPar(u8 tAddr,u8* pVal);
//-----------------------------------------------------------------------------------------------------------------------
	//<FUN> 电池电压校准
	//<INP> v1				:   标准电压1,单位:微伏		6800000		
	//<INP> ad1				:   电压参考值1
	//<INP> v2				:   标准电压2,单位:微伏		8400000		
	//<INP> ad1				:   电压参考值2
	//<RET> int				:   错误码
extern int API_BatCalibration(int v1,int ad1,int v2,int ad2) ;

	//<FUN> 获取电压参考值
	//<RET> int				:   电压参考值
extern int API_GetBatReferVolt(void); 
              
	//<FUN> 获取电池电压
	//<FUN> 				1(volt) 	 = 1000(millivolt)
	//<FUN> 				1(millivolt) = 1000(microvolt) 
	//<OUP> IsAcPwrIn		:   是否插入交流适配器,1表示插入,0表示未插入	
	//<RET> int				:   电池电压,单位:微伏
extern int API_GetBatMicroVolt(int* IsAcPwrIn); 


	//<FUN> 设置显示屏对比度
	//<INP> tRatio			:   显示屏对比度,1-100	
	//<RET> int				:   错误码
extern int API_SetLcdContrast(int tRatio);

	//<FUN> 设置显示屏背光
	//<INP> isOn			:   为1表示开背光,为0表示关背光	
	//<RET> int				:   错误码
extern int API_SetLcdBacklight(int isOn);

enum LED_MASK
{
	LED_BLUE	=0x00000001,			//蓝
	LED_ORANGE	=0x00000002,			//橙
	LED_GREEN	=0x00000004,			//绿		
	LED_RED		=0x00000008,			//红
	LED_ALL		=0xFFFFFFFF,			//
};	
	//<FUN> 设置LED灯开关
	//<INP> tMask			:   为LED_MASK
	//<INP> isOn			:   为1表示开,为0表示关
	//<RET> int				:   错误码
extern int API_SetLedSwitch(u32 tMask,int isOn);


	//<FUN> 设置条码模块开关
	//<INP> isOn			:   为1表示开,为0表示关	
	//<RET> int				:   错误码
extern int API_SetBarCodeBacklight(int isOn);

	//<FUN> 播放wav文件
	//<INP> pWavePath		:   wav文件路径	
	//<RET> int				:   错误码
extern int API_WavePlay(const char* pWaveFile);

	//<FUN> 播放wav文件组
	//<INP> num				:   wav文件总数
	//<INP> pWaveGroupPath	:   wav文件路径数组	
	//<RET> int				:   错误码
extern int API_WavePlayGroup(int num,const char** pWaveGroupPath);

	//<FUN> 停止播放
	//<RET> int				:   错误码
extern int API_WaveStop(void);

	//<FUN> 获取播放进度
	//<RET> int				:   0(播放完成),1-100为播放百分比
extern int API_GetPlayRatio(void);

	//<FUN> 播放Beep
	//<INP> tFreq			:   频率	,单位:赫兹
	//<INP> tTimeMs			:   持续时间,单位:毫秒	
	//<RET> int				:   错误码
extern int API_Beep(u32 tFreq,u32 tTimeMs);

	//<FUN> 获取音量
	//<INP> tFreq			:   频率	,单位:赫兹
	//<INP> tTimeMs			:   持续时间,单位:毫秒	
	//<RET> int				:   0 静音,1-100 音量  
extern int API_GetVolume(void);

	//<FUN> 设置音量
	//<INP> vol				:   0 静音,1-100 音量  
	//<INP> tTimeMs			:   持续时间,单位:毫秒	
	//<RET> int				:   错误码
extern int API_SetVolume(int vol);

//-----------------------------------------------------------------------------------------------------------------------
enum DEFENDER_STA
{
	DEFENDER_NORMAL			=0x0001,			//正常状态
	DEFENDER_DESTROY		=0x0002,			//销毁状态
	DEFENDER_INACTIVE		=0x0004,			//探测功能未激活
};

extern int API_EnableDefender(int isEnable);
extern int API_GetDefenderSta(void);
extern int API_ClrDefenderSta(void);

enum SECMEMORY_TYPE
{
	MEMORY_NVRAM			=0x0001,			//NVRAM  
	MEMORY_FLASH			=0x0002,			//FLASH  
};
extern int API_SecMemorySize( int tType);
extern int API_SecMemoryRead( int tType,int tAddr,void* pBuf,int tLen);
extern int API_SecMemoryWrite(int tType,int tAddr,void* pBuf,int tLen);
	
//-----------------------------------------------------------------------------------------------------------------------

extern void  API_Sdk_Test(void);
	
//-----------------------------------------------------------------------------------------------------------------------

extern void API_SetTraceDest(unsigned char nMode);
//-----------------------------------------------------------------------------------------------------------------------




#endif
