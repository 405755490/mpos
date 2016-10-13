//===================================================================
// 单    位：深圳市证通金信科技有限公司
// 作    者：付庆
// 版    本：0.00.01	[主版本号.次版本号.修订版本号]
// 创建日期：2008-5-30 12:59
// 修改日期：2008-5-30 12:59
// 说    明：用户界面封装
// 修改记录：
//===================================================================

#ifndef _APP_SDK_H_
#define _APP_SDK_H_


#include "std_head.h"
//=======================================================================================================================
	extern const char* TXT_OK;
	extern const char* TXT_CANCEL;
	extern const char* TXT_BACK;

	#define TOK				((char*)TXT_OK)		
	#define TCANCEL			((char*)TXT_CANCEL)		
	#define TBACK			((char*)TXT_BACK)		
	
//=======================================================================================================================

	#define _LANG_ID_		(1)											//0为英文	1为中文
	#define DS(en,ch)		((_LANG_ID_==0)?(en):(ch))					//多语言定义
//=======================================================================================================================
	
	#define	RET_EVENT(e)		if(e==EVENT_QUIT){return 1;}else{return 0;} 

//=======================================================================================================================
	extern int  APP_WaitUiOp(int tTimeOutMs);										

				//返回0确认，返回1取消				
	extern int  APP_Affirm(char* pTitle,char* pMsg,char* pLeft,char* pRight,int tAffirmKey,int tTimeOutMs);
	
				//返回0密码正确，返回1密码错误，返回-1取消输入
	extern int  APP_CheckPin(char* pTitle,char* pMsg,char* pPinStr,int tTimeOutMs);
	
				//返回0成功获取字符串且不为空,返回非0失败
	extern int  APP_GetCfgStr(const char* pMoudle,const char* pKeyName,char* pStr,int tStrSize);
	

//=======================================================================================================================
	extern int  APP_DisConnect(char* pTitle,int tTimeOutMs);	
	extern int  APP_Connect(char* pTitle,char* pAddr,int tPort,int tTimeOutMs);	
	extern int  APP_Send(char* pTitle,u8* pBuf,int tLen,int tTimeOutMs);	
	extern int  APP_Recv(char* pTitle,u8* pBuf,int tLen,int tTimeOutMs);
//=======================================================================================================================
	extern void APP_PlayWave(const char* pWavPath);
//=======================================================================================================================

#endif
