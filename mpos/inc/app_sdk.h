//===================================================================
// ��    λ��������֤ͨ���ſƼ����޹�˾
// ��    �ߣ�����
// ��    ����0.00.01	[���汾��.�ΰ汾��.�޶��汾��]
// �������ڣ�2008-5-30 12:59
// �޸����ڣ�2008-5-30 12:59
// ˵    �����û������װ
// �޸ļ�¼��
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

	#define _LANG_ID_		(1)											//0ΪӢ��	1Ϊ����
	#define DS(en,ch)		((_LANG_ID_==0)?(en):(ch))					//�����Զ���
//=======================================================================================================================
	
	#define	RET_EVENT(e)		if(e==EVENT_QUIT){return 1;}else{return 0;} 

//=======================================================================================================================
	extern int  APP_WaitUiOp(int tTimeOutMs);										

				//����0ȷ�ϣ�����1ȡ��				
	extern int  APP_Affirm(char* pTitle,char* pMsg,char* pLeft,char* pRight,int tAffirmKey,int tTimeOutMs);
	
				//����0������ȷ������1������󣬷���-1ȡ������
	extern int  APP_CheckPin(char* pTitle,char* pMsg,char* pPinStr,int tTimeOutMs);
	
				//����0�ɹ���ȡ�ַ����Ҳ�Ϊ��,���ط�0ʧ��
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
