
#ifndef _KS_SYSUNIT_H_
#define _KS_SYSUNIT_H_


//=======================================================================================================================
//=======================================================================================================================
//=======================================================================================================================
	enum KSP_TYPE
	{
		KSP_START			=0,			
		KSP_FILE			=1,					//��ͨ�ļ�		
		KSP_DRIVER			=2,					//����	
		KSP_SDK				=3,					//SDK	
		KSP_SYS_APP			=4,					//ϵͳӦ��	
		KSP_USR_APP			=5,					//�û�Ӧ��		
		KSP_END
	};	

	typedef struct
	{
        char 			tag[15+1];				// Ӧ�ñ�ʶ
        char 			name_en[30+2];			// Ӧ������(Ӣ��)
        char 			name_cn[30+2];			// Ӧ������(����)
        char			sup_dev[15+1];			// Ӧ��֧�ֵ��豸   (��ʱ��ʹ��)
        char			sdk_ver[7+1];			// ֧�ֵ�SDK�汾  	[123.567]
        char			app_ver[11+1];			// Ӧ������汾	  	[123.567.901]
        char			app_time[16+4];			// Ӧ���������ʱ��	[2013-10-08 13:42]
		u8				VA[64];					// ��չ
	}APP_FIX_INFO;              				// V1.2 

	typedef struct
	{
		char			Tag[16];				// �����ʶ(Ŀ¼����) 
		u8				Seq;					// Ӧ�����(��ʱ��ʹ��)
		u8				Disable;				// �Ƿ����
		u8				VA[64-2];				// ��չ
		u8				UserData[64];			// �û�����,SUģ�鲻ʹ��
	}APP_VAR_INFO;								// V1.3 

	#define	KSP_NEED_REBOOT	0x01			    // ��װ��ɺ���Ҫ��������
	
//=======================================================================================================================

		//<FUN> ��ȡӦ����������ǩ�б�
		//<OUP> pTagGroup		:   ��ǩ�б�	(���Զ�����,��ΪNULL)
		//<INP> tGroutSize		:   Ӧ�������
		//<INP> tTagSize		:   ��ǩ��󳤶�
		//<RET> 				:   KSP_USR_APP������,ʧ�ܷ���-1
		//<REM>					:	char tAllTag[10][16];
		//<REM>					:	int tNum=SU_GetAppNum(tAllTag,10,16);
	extern int SU_GetAppNum(char* pTagGroup,int tGroutSize,int tTagSize);

		//<FUN> ��ѯ�����Ƿ��Զ�����Ӧ��
		//<INP> pTag			:   ��ǩ(��ʹ��)
		//<RET> 				:   ����0��ʾ���Զ�����,����1��ʾ�Զ�����,����-1��ʾ����
	extern int SU_GetIsAutoRun(const char* pTag);

		//<FUN> ���ÿ����Ƿ��Զ�����Ӧ��
		//<INP> pTag			:   ��ǩ(��ʹ��)
		//<INP> tIsAutoRun		:   0��ʾ���Զ�����,1��ʾ�Զ�����
		//<RET> 				:   ����0��ʾ�ɹ�,����-1��ʾ����
	extern int SU_SetIsAutoRun(const char* pTag,int tIsAutoRun);

		//<FUN> ��ѯȱʡӦ��
		//<OUP> pTag			:   ����ȱʡӦ�õı�ǩ���һ�����õ�Ӧ�ñ�ǩ
		//<RET> 				:   ����1��ʾ���õ�ȱʡ��ǩ������0��ʾ��һ�����õ�Ӧ�ñ�ǩ,����-1��ʾ����
	extern int SU_GetDefApp(char* pTag);

		//<FUN> ����ȱʡӦ��
		//<INP> pTag			:   ��ǩ
		//<RET> 				:   ����0��ʾ�ɹ�,����-1��ʾ����
	extern int SU_SetDefApp(const char* pTag);

		//<FUN> ����Ӧ�ÿɱ����
		//<INP> pTag			:   ��ǩ
		//<INP> pInfo			:   �ɱ����
		//<RET> 				:   ����0��ʾ�ɹ�,����-1��ʾ����
	extern int SU_SetAppVarInfo(const char* pTag,const APP_VAR_INFO* pInfo);

		//<FUN> ��ѯӦ�ÿɱ����
		//<INP> pTag			:   ��ǩ
		//<OUP> pInfo			:   �ɱ����
		//<RET> 				:   ����0��ʾ�ɹ�,����-1��ʾ����
	extern int SU_GetAppVarInfo(const char* pTag,      APP_VAR_INFO* pInfo);

		//<FUN> ��ѯӦ�ù̶�����
		//<INP> pTag			:   ��ǩ(֧���û�Ӧ�ú�ϵͳӦ��,ΪNULL��ѯ�Լ��Ĺ̶�����)
		//<OUP> pInfo			:   �̶�����
		//<RET> 				:   ����0��ʾ�ɹ�,����-1��ʾ����
	extern int SU_GetAppFixInfo(const char* pTag,      APP_FIX_INFO* pInfo);
	
		//<FUN> ɾ������Ӧ��
		//<RET> 				:   ����0��ʾ�ɹ�,����-1��ʾ����
	extern int SU_DelAllApp(void);
	
		//<FUN> ɾ��Ӧ��
		//<INP> pTag			:   ��ǩ
		//<RET> 				:   ����0��ʾ�ɹ�,����-1��ʾ����
	extern int SU_DelApp(const char* pTag);

		//<FUN> �ƶ�Ӧ��
		//<INP> pTag			:   ��ǩ(֧���û�Ӧ��,ΪNULLʧ��)
		//<INP> tDir			:   <0���ƣ�tDir>0����
		//<RET> 				:   ����0��ʾ�ɹ�,����1��ʾ�ѵ��߽粻���ƶ�,����<0��ʾ����
	extern int SU_MoveApp(const char* pTag,int tDir);
	
		//<FUN> ��װӦ��
		//<INP> pKspPath		:   KSP�ļ�ȫ·��
		//<RET> 				:   ����>=0��ʾ�ɹ�,����-1��ʾ����
		//<RET> 				:   ����KSP_NEED_REBOOT��ʾ��Ҫ����
	extern int SU_SetupApp(const char* pKspPath);

		//<FUN> ����Ӧ���Ƿ����
		//<INP> pTag			:   ��ǩ(֧���û�Ӧ�ú�ϵͳӦ��,ΪNULLʧ��)
		//<RET> 				:   ����KSP_USR_APP��ʾ���û�Ӧ��,����KSP_SYS_APP��ʾ��ϵͳӦ��,����-1��ʾ����
	extern int SU_FindApp(const char* pTag);

		//<FUN> �˳�
		//<INP> pArgStr			:   ���в���(��ΪNULL)
		//<RET> 				:   ����0��ʾ�ɹ�,����-1��ʾ����
	extern int SU_Exit(const char* pArgStr);

		//<FUN> ����Ӧ��
		//<INP> pTag			:   ��ǩ
		//<INP> pArgStr			:   ���в���(��ΪNULL)
		//<RET> 				:   ����0��ʾ�ɹ�,����-1��ʾ����
	extern int SU_GotoApp(const char* pTag,const char* pArgStr);

		//<FUN> ��ѯ����Ӧ��Ŀ¼
		//<INP> pTag			:   ��ǩ(֧���û�Ӧ�ú�ϵͳӦ��,ΪNULLʧ��)
		//<INP> pAppDir			:   Ŀ¼������(��'/'��β)
		//<INP> tAppDirSize		:   Ŀ¼��������С	
		//<RET> 				:   ����KSP_USR_APP��ʾ���û�Ӧ��,����KSP_SYS_APP��ʾ��ϵͳӦ��,����-1��ʾ����
	extern int SU_GetAppPath(const char* pTag,char* pAppDir,int tAppDirSize);
	
		//<FUN> ��ѯ�ն����к�
		//<OUP> pSnBuf			:   ���кŻ�����
		//<INP> tSnSize			:   ���кŻ���������С
		//<RET> 				:   ����0��ʾ�ɹ�,����-1��ʾ����
	extern int SU_GetTermSN(char* pSnBuf,int tSnSize);
	
		//<FUN> �����ն����к�
		//<INP> pSnBuf			:   ���кŻ�����
		//<INP> tSnSize			:   ���кų���
		//<RET> 				:   ����0��ʾ�ɹ�,����-1��ʾ����
	extern int SU_SetTermSN(char* pSnBuf,int tSnSize);

		//<FUN> ��������ģʽ
		//<INP> pTitle			:   �������,ΪNULLʹ��ϵͳĬ��ֵ
		//<INP> pMsg			:   �������,ΪNULLʹ��ϵͳĬ��ֵ
		//<INP> tUartInx		:   ��PCTͨ��ʹ�õĴ���
		//<RET> 				:   ����0��ʾ����,����1��ʾ�˳�
	extern int SU_RunCmdMode(char* pTitle,char* pMsg,int tUartInx);
	
		//<FUN> ϵͳ����
		//<INP> pTitle			:   �������,ΪNULLʹ��ϵͳĬ��ֵ
		//<INP> pMsg			:   �������,ΪNULLʹ��ϵͳĬ��ֵ
	extern void SU_ReBoot(const char* pTitle,const char* pMsg);
	
		//<FUN> ϵͳ�ػ�
		//<INP> pTitle			:   �������,ΪNULLʹ��ϵͳĬ��ֵ
		//<INP> pMsg			:   �������,ΪNULLʹ��ϵͳĬ��ֵ
	extern void SU_PwrOff(const char* pTitle,const char* pMsg);
	
//=======================================================================================================================
//=======================================================================================================================
//=======================================================================================================================

	#define SIZE_TOOSMALL		API_GUI_TextSize(TEXT_SIZE_TOOSMALL)		//��С�ֺ�		
	#define SIZE_SMALL			API_GUI_TextSize(TEXT_SIZE_SMALL)			//С�ֺ�
	#define SIZE_NORMAL			API_GUI_TextSize(TEXT_SIZE_NORMAL)			//�����ֺ�
	#define SIZE_BIG			API_GUI_TextSize(TEXT_SIZE_BIG)				//���ֺ�
	#define SIZE_TOOBIG			API_GUI_TextSize(TEXT_SIZE_TOOBIG)			//�ش��ֺ�
	#define SIZE_GBK			TEXT_24										//֧��GBK������ֺ�
	
	#define	KEQ(k,v)			(API_KeyEq((k),(v)))								//�жϰ����Ƿ�ָ������
	#define	KNUM(v)				(API_KeyIsNum((v)))									//�жϰ����Ƿ����ּ�
	#define	IS_MONOC			(API_GetSysInfo(INFO_LCD_TYPE,NULL,0)&DISP_MONOC)	//�ж��Ƿ�Ϊ�ڰ���
	
	#define HIT_MSG_TIME		300
	#define HIT_INFO_TIME		3000
	
		//<RET> 				:   ����0��ʾ����,����1��ʾ�˳�
    typedef int (*APP_HANDLE)(char* title); 

	extern int  SU_SetHasTitle(int isHas);
	extern int  SU_SetDefWinType(u32 tWinType);	

		//<FUN> ��������
	extern int  SU_GUI_Win(char* pTitle,char* pOk,char* pCancel);					

		//<FUN> �ȴ�UI�¼�
	extern u32  SU_WaitUiEvent(int tTimeOutMs);										

		//<FUN> �ȴ�������
	extern int  SU_WaitKeyDown(int tTimeOutMs);										


		//<FUN> ��Ļ������ʾ״̬��Ϣ������ʾ
	extern void SU_ShowSta(	char* pTitle,char* pMsg);

		//<FUN> ��Ļ������ʾ��ʾ��Ϣ���ȴ�UI����
	extern int  SU_ShowMsg(	char* pTitle,char* pMsg,int tTimeOutMs);				

		//<FUN> ��Ļ���Ͽ�ʼ��ʾ��Ϣ���ȴ�UI����
	extern int  SU_ShowInfo(char* pTitle,char* pMsg,int tTimeOutMs);				
	
		//<FUN> ������ʾ
	extern void SU_HitPopMsg(char* pTitle,char* pMsg,IMAGE* pImg,int tTimeOutMs);	
	
		//<FUN> �˵�����
		//<RET> 				:   ����0��ʾ����,����1��ʾ�˳�
	extern int  SU_ProMenu(char* pTitle,int tNum,const char** pMenuText,const APP_HANDLE* pMenuFunc);
	
		//<FUN> ����ѡ��˵�
		//<RET> 				:   �ɹ�ѡ�񷵻�0-N,���˳�����-1,�����ػ�ʱ����-2
	extern int  SU_RdoMenu(char* pTitle,char* pMsg,int tNum,int tDef,const char** pMenuText);
		
		//<FUN> �����
		//<RET> 				:   �ɹ����뷵�س���0-N,���˳�����-1,�����ػ�ʱ����-2
	extern int  SU_Input(char* pTitle,char* pHitMsg,char* pEditBuf,int tMax,u32 tImeMode,u32 tImeLimit,int tTimeOutMs);

		//<FUN> д�ļ�
	extern int  SU_WriteFile(const char* pPath,void* pBuf,int tLen);
	
		//<FUN> ���ļ�
	extern int  SU_ReadFile(const char* pPath,void* pBuf,int tLen);	

//=======================================================================================================================
//=======================================================================================================================
//=======================================================================================================================


#endif
