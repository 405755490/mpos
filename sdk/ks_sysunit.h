
#ifndef _KS_SYSUNIT_H_
#define _KS_SYSUNIT_H_


//=======================================================================================================================
//=======================================================================================================================
//=======================================================================================================================
	enum KSP_TYPE
	{
		KSP_START			=0,			
		KSP_FILE			=1,					//普通文件		
		KSP_DRIVER			=2,					//驱动	
		KSP_SDK				=3,					//SDK	
		KSP_SYS_APP			=4,					//系统应用	
		KSP_USR_APP			=5,					//用户应用		
		KSP_END
	};	

	typedef struct
	{
        char 			tag[15+1];				// 应用标识
        char 			name_en[30+2];			// 应用名称(英文)
        char 			name_cn[30+2];			// 应用名称(中文)
        char			sup_dev[15+1];			// 应用支持的设备   (暂时不使用)
        char			sdk_ver[7+1];			// 支持的SDK版本  	[123.567]
        char			app_ver[11+1];			// 应用软件版本	  	[123.567.901]
        char			app_time[16+4];			// 应用软件日期时间	[2013-10-08 13:42]
		u8				VA[64];					// 扩展
	}APP_FIX_INFO;              				// V1.2 

	typedef struct
	{
		char			Tag[16];				// 软件标识(目录名称) 
		u8				Seq;					// 应用序号(暂时不使用)
		u8				Disable;				// 是否禁用
		u8				VA[64-2];				// 扩展
		u8				UserData[64];			// 用户数据,SU模块不使用
	}APP_VAR_INFO;								// V1.3 

	#define	KSP_NEED_REBOOT	0x01			    // 安装完成后需要重新启动
	
//=======================================================================================================================

		//<FUN> 获取应用总数及标签列表
		//<OUP> pTagGroup		:   标签列表	(会自动清零,可为NULL)
		//<INP> tGroutSize		:   应用最大数
		//<INP> tTagSize		:   标签最大长度
		//<RET> 				:   KSP_USR_APP的总数,失败返回-1
		//<REM>					:	char tAllTag[10][16];
		//<REM>					:	int tNum=SU_GetAppNum(tAllTag,10,16);
	extern int SU_GetAppNum(char* pTagGroup,int tGroutSize,int tTagSize);

		//<FUN> 查询开机是否自动运行应用
		//<INP> pTag			:   标签(不使用)
		//<RET> 				:   返回0表示不自动运行,返回1表示自动运行,返回-1表示错误
	extern int SU_GetIsAutoRun(const char* pTag);

		//<FUN> 设置开机是否自动运行应用
		//<INP> pTag			:   标签(不使用)
		//<INP> tIsAutoRun		:   0表示不自动运行,1表示自动运行
		//<RET> 				:   返回0表示成功,返回-1表示错误
	extern int SU_SetIsAutoRun(const char* pTag,int tIsAutoRun);

		//<FUN> 查询缺省应用
		//<OUP> pTag			:   返回缺省应用的标签或第一个可用的应用标签
		//<RET> 				:   返回1表示设置的缺省标签，返回0表示第一个可用的应用标签,返回-1表示错误
	extern int SU_GetDefApp(char* pTag);

		//<FUN> 设置缺省应用
		//<INP> pTag			:   标签
		//<RET> 				:   返回0表示成功,返回-1表示错误
	extern int SU_SetDefApp(const char* pTag);

		//<FUN> 设置应用可变参数
		//<INP> pTag			:   标签
		//<INP> pInfo			:   可变参数
		//<RET> 				:   返回0表示成功,返回-1表示错误
	extern int SU_SetAppVarInfo(const char* pTag,const APP_VAR_INFO* pInfo);

		//<FUN> 查询应用可变参数
		//<INP> pTag			:   标签
		//<OUP> pInfo			:   可变参数
		//<RET> 				:   返回0表示成功,返回-1表示错误
	extern int SU_GetAppVarInfo(const char* pTag,      APP_VAR_INFO* pInfo);

		//<FUN> 查询应用固定参数
		//<INP> pTag			:   标签(支持用户应用和系统应用,为NULL查询自己的固定参数)
		//<OUP> pInfo			:   固定参数
		//<RET> 				:   返回0表示成功,返回-1表示错误
	extern int SU_GetAppFixInfo(const char* pTag,      APP_FIX_INFO* pInfo);
	
		//<FUN> 删除所有应用
		//<RET> 				:   返回0表示成功,返回-1表示错误
	extern int SU_DelAllApp(void);
	
		//<FUN> 删除应用
		//<INP> pTag			:   标签
		//<RET> 				:   返回0表示成功,返回-1表示错误
	extern int SU_DelApp(const char* pTag);

		//<FUN> 移动应用
		//<INP> pTag			:   标签(支持用户应用,为NULL失败)
		//<INP> tDir			:   <0上移，tDir>0下移
		//<RET> 				:   返回0表示成功,返回1表示已到边界不能移动,返回<0表示错误
	extern int SU_MoveApp(const char* pTag,int tDir);
	
		//<FUN> 安装应用
		//<INP> pKspPath		:   KSP文件全路径
		//<RET> 				:   返回>=0表示成功,返回-1表示错误
		//<RET> 				:   返回KSP_NEED_REBOOT表示需要重启
	extern int SU_SetupApp(const char* pKspPath);

		//<FUN> 查找应用是否存在
		//<INP> pTag			:   标签(支持用户应用和系统应用,为NULL失败)
		//<RET> 				:   返回KSP_USR_APP表示是用户应用,返回KSP_SYS_APP表示是系统应用,返回-1表示错误
	extern int SU_FindApp(const char* pTag);

		//<FUN> 退出
		//<INP> pArgStr			:   运行参数(可为NULL)
		//<RET> 				:   返回0表示成功,返回-1表示错误
	extern int SU_Exit(const char* pArgStr);

		//<FUN> 运行应用
		//<INP> pTag			:   标签
		//<INP> pArgStr			:   运行参数(可为NULL)
		//<RET> 				:   返回0表示成功,返回-1表示错误
	extern int SU_GotoApp(const char* pTag,const char* pArgStr);

		//<FUN> 查询所在应用目录
		//<INP> pTag			:   标签(支持用户应用和系统应用,为NULL失败)
		//<INP> pAppDir			:   目录缓冲区(以'/'结尾)
		//<INP> tAppDirSize		:   目录缓冲区大小	
		//<RET> 				:   返回KSP_USR_APP表示是用户应用,返回KSP_SYS_APP表示是系统应用,返回-1表示错误
	extern int SU_GetAppPath(const char* pTag,char* pAppDir,int tAppDirSize);
	
		//<FUN> 查询终端序列号
		//<OUP> pSnBuf			:   序列号缓冲区
		//<INP> tSnSize			:   序列号缓冲区区大小
		//<RET> 				:   返回0表示成功,返回-1表示错误
	extern int SU_GetTermSN(char* pSnBuf,int tSnSize);
	
		//<FUN> 设置终端序列号
		//<INP> pSnBuf			:   序列号缓冲区
		//<INP> tSnSize			:   序列号长度
		//<RET> 				:   返回0表示成功,返回-1表示错误
	extern int SU_SetTermSN(char* pSnBuf,int tSnSize);

		//<FUN> 进入命令模式
		//<INP> pTitle			:   界面标题,为NULL使用系统默认值
		//<INP> pMsg			:   界面标题,为NULL使用系统默认值
		//<INP> tUartInx		:   与PCT通信使用的串口
		//<RET> 				:   返回0表示返回,返回1表示退出
	extern int SU_RunCmdMode(char* pTitle,char* pMsg,int tUartInx);
	
		//<FUN> 系统重启
		//<INP> pTitle			:   界面标题,为NULL使用系统默认值
		//<INP> pMsg			:   界面标题,为NULL使用系统默认值
	extern void SU_ReBoot(const char* pTitle,const char* pMsg);
	
		//<FUN> 系统关机
		//<INP> pTitle			:   界面标题,为NULL使用系统默认值
		//<INP> pMsg			:   界面标题,为NULL使用系统默认值
	extern void SU_PwrOff(const char* pTitle,const char* pMsg);
	
//=======================================================================================================================
//=======================================================================================================================
//=======================================================================================================================

	#define SIZE_TOOSMALL		API_GUI_TextSize(TEXT_SIZE_TOOSMALL)		//特小字号		
	#define SIZE_SMALL			API_GUI_TextSize(TEXT_SIZE_SMALL)			//小字号
	#define SIZE_NORMAL			API_GUI_TextSize(TEXT_SIZE_NORMAL)			//正常字号
	#define SIZE_BIG			API_GUI_TextSize(TEXT_SIZE_BIG)				//大字号
	#define SIZE_TOOBIG			API_GUI_TextSize(TEXT_SIZE_TOOBIG)			//特大字号
	#define SIZE_GBK			TEXT_24										//支持GBK编码的字号
	
	#define	KEQ(k,v)			(API_KeyEq((k),(v)))								//判断按键是否指定按键
	#define	KNUM(v)				(API_KeyIsNum((v)))									//判断按键是否数字键
	#define	IS_MONOC			(API_GetSysInfo(INFO_LCD_TYPE,NULL,0)&DISP_MONOC)	//判断是否为黑白屏
	
	#define HIT_MSG_TIME		300
	#define HIT_INFO_TIME		3000
	
		//<RET> 				:   返回0表示返回,返回1表示退出
    typedef int (*APP_HANDLE)(char* title); 

	extern int  SU_SetHasTitle(int isHas);
	extern int  SU_SetDefWinType(u32 tWinType);	

		//<FUN> 创建窗口
	extern int  SU_GUI_Win(char* pTitle,char* pOk,char* pCancel);					

		//<FUN> 等待UI事件
	extern u32  SU_WaitUiEvent(int tTimeOutMs);										

		//<FUN> 等待键按下
	extern int  SU_WaitKeyDown(int tTimeOutMs);										


		//<FUN> 屏幕居中显示状态信息，仅显示
	extern void SU_ShowSta(	char* pTitle,char* pMsg);

		//<FUN> 屏幕居中显示提示信息，等待UI操作
	extern int  SU_ShowMsg(	char* pTitle,char* pMsg,int tTimeOutMs);				

		//<FUN> 屏幕左上开始显示信息，等待UI操作
	extern int  SU_ShowInfo(char* pTitle,char* pMsg,int tTimeOutMs);				
	
		//<FUN> 弹出提示
	extern void SU_HitPopMsg(char* pTitle,char* pMsg,IMAGE* pImg,int tTimeOutMs);	
	
		//<FUN> 菜单处理
		//<RET> 				:   返回0表示返回,返回1表示退出
	extern int  SU_ProMenu(char* pTitle,int tNum,const char** pMenuText,const APP_HANDLE* pMenuFunc);
	
		//<FUN> 单项选择菜单
		//<RET> 				:   成功选择返回0-N,按退出返回-1,按返回或超时返回-2
	extern int  SU_RdoMenu(char* pTitle,char* pMsg,int tNum,int tDef,const char** pMenuText);
		
		//<FUN> 输入框
		//<RET> 				:   成功输入返回长度0-N,按退出返回-1,按返回或超时返回-2
	extern int  SU_Input(char* pTitle,char* pHitMsg,char* pEditBuf,int tMax,u32 tImeMode,u32 tImeLimit,int tTimeOutMs);

		//<FUN> 写文件
	extern int  SU_WriteFile(const char* pPath,void* pBuf,int tLen);
	
		//<FUN> 读文件
	extern int  SU_ReadFile(const char* pPath,void* pBuf,int tLen);	

//=======================================================================================================================
//=======================================================================================================================
//=======================================================================================================================


#endif
