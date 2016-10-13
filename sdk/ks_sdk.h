
#ifndef _KS_SDK_H_
#define _KS_SDK_H_

//#include "stdafx.h"
#include "ks_gui.h"
//-----------------------------------------------------------------------------------------------------------------------

enum TRACE_MODE
{    
    TRACE_TO_NULL =         0x00,   //�����������Ϣ
    TRACE_TO_CONSOLE =		0x01,	//������Ϣ������ն���ʾ��
    TRACE_TO_FILE =			0x02	//������Ϣ������ļ���
};
//-----------------------------------------------------------------------------------------------------------------------
enum INIT_MODULE
{
	M_SYS				=0x00000001,		//ϵͳ
	M_DISPLAY			=0x00000002,		//�����ʾ
	M_INPUT				=0x00000004,		//����ϵͳ
	M_UI_CFG			=0x00000008,		//����UI����
	
	M_CARD				=0x00000010,		//��Ƭģ��
	M_PRINT				=0x00000020,		//��ӡģ��
	M_NET_INIT			=0x00000040,		//�����ʼ��
	M_NET_WORK			=0x00000080,		//���繤��
	M_ALL				=0xFFFFFFFF			//ȫ������
};	//V1.2
		
extern int  SDK_Init(int argc, char **argv);					//SDK���л�����ʼ��
extern void SDK_Exit(void);					//
extern void * GetKey_UI_proc( );

extern int  API_Init(u32 tModule);			//API�ӿ�ģ���ʼ�� INIT_MODULE
extern int  API_Exit(u32 tModule);			//

//-----------------------------------------------------------------------------------------------------------------------
//��������
	
enum DBG_TYPE
{
	DBG_NONE			=0,					//�޵������	
	DBG_CON				=1,					//�������������̨	
	DBG_MEM				=2,					//����������ڴ�	
	DBG_UART_A			=3,					//�������������A	
	DBG_UART_B			=4,					//�������������B	
	DBG_USB_CDC			=5,					//���������USB����	
	DBG_NET				=6,					//�������������	
	DBG_FILE			=7,					//����������ļ�	
	DBG_TFLASH			=8,					//����������洢��	
	DBG_TYPE_MAX
};
enum DBG_LEVEL
{
	DBG_APP_INFO		=0x01,				//��ͨ������Ϣ		
	DBG_APP_WARMING		=0x02,				//���������Ϣ		
	DBG_APP_ERROR		=0x04,				//���������Ϣ	
	DBG_APP_SECRECY		=0x08,				//���ܵ�����Ϣ	
	DBG_APP_1			=0x10,				//�û�������Ϣ����1		��UI����
	DBG_APP_2			=0x20,				//�û�������Ϣ����2		�������봦��
	DBG_APP_3			=0x40,				//�û�������Ϣ����3		��ͨ�Ų��ִ���
	DBG_APP_4			=0x80,				//�û�������Ϣ����4		��绰���ܿ�
	DBG_APP_MASK		=0xFF				//Ӧ�õ�����Ϣ	
};	//VER:1.1

	//<FUN> ��������ı���Ϣ,�Զ�����
	//<INP> tLevel			:   ������Ϣ����(DBG_LEVEL)
	//<INP> pFmt			:   ��ʽ���ƴ�(����printf)
	//<INP> ...				:   �ɱ����
extern void API_Trace(   u32 tLevel,char* pFmt,...);	
					
	//<FUN> ���������16������Ϣ,�Զ�����
	//<INP> tLevel			:   ������Ϣ����(DBG_LEVEL)
	//<INP> pMsg			:   ��ʾ��Ϣ
	//<INP> pBuf			:   �������ݻ�����
	//<INP> tLen			:   �������ݳ���
extern void API_TraceHex(u32 tLevel,char* pMsg,void* pBuf,int tLen);	

	//<FUN> ��ȡ��������
	//<RET>  				:   DBG_TYPE
extern int  API_GetDbgType(void);

	//<FUN> ���õ�������
	//<INP> tType			:   DBG_TYPE
extern int  API_SetDbgType(int tType);

	//<FUN> ��ȡ���Լ���(�ɵ��Ե�ģ��)
	//<RET>  				:   DBG_LEVEL
extern int  API_GetDbgLevel(void);
	//<FUN> ���õ��Լ���(�ɵ��Ե�ģ��)
	//<INP> tLevel			:   DBG_LEVEL
extern int  API_SetDbgLevel(int tLevel);

enum ERROR_TYPE
{
    ERROR_INIT_THREAD_CONDITION             = -101,     //��ʼ���߳�ʹ�û���
    ERROR_CREATE_THREAD                     = -102     //�����߳�
};
	//<FUN> ��ȡ���һ�εĴ�����
	//<RET> int				:   ������ errcode.h
extern int  API_GetLastError(void);	

//-----------------------------------------------------------------------------------------------------------------------
//��ϵͳ��Ϣ

enum INFO_TYPE		
{
	INFO_DEV_NAME			=0x0101,		//�豸����	   		pVal="KS8210"
	INFO_KERNEL_VER			=0x0102,		//�ں�����汾 		pVal="1.0.1"
	INFO_SYS_VER			=0x0103,		//ϵͳ����汾 		pVal="1.0.1"
	INFO_SDK_VER			=0x0104,		//SDK ����汾 		pVal="1.2.0"
	
	INFO_LCD_TYPE			=0x0201,		//LCD ��ʾ���� 		ret =DISP_TYPE
	
	INFO_ENUM_KEY			=0x0301,		//ö�ٰ���     		ret =��������,		pVal=����          ����
	INFO_ENUM_ICC			=0x0302,		//ö��IC��������    ret =IC������,		pVal=ICC_INDEX     ����
	INFO_ENUM_MAG			=0x0303,		//ö�ٴſ�	        ret =�ŵ�����,
	INFO_ENUM_UART			=0x0304,		//ö�ٴ���     		ret =��������,		pVal=UART_INDEX    ����
	INFO_ENUM_NET			=0x0305,		//ö������     		ret =��������,		pVal=NET_INDEX     ����
	INFO_ENUM_PLAY			=0x0306,		//ö�ٲ�������    	ret =������������,	pVal=PLAY_TYPE     ����
	INFO_ENUM_IMAGE			=0x0307,		//ö��ͼƬ����    	ret =ͼƬ��������,	pVal=IMAGE_TYPE    ����
	INFO_ENUM_LED			=0x0308,		//ö��LED��    		ret =LED������,		pVal=LED_MASK      ����
	INFO_ENUM_SECMEMORY		=0x0309,		//ö�ٰ�ȫ�洢��	ret =��ȫ�洢������,pVal=SECMEMORY_TYPE����
	INFO_ENUM_PHONE			=0x030A,		//ö�ٵ绰ģ��		ret =�绰ģ������,	pVal=PHONE_TYPE    ����	
};	//Ver:2.7

	//<FUN> ��ȡϵͳ��Ϣ
	//<INP> tInfoType		:   ϵͳ��Ϣ����(INFO_TYPE)
	//<OUP> pVal			:   ϵͳ��Ϣ������
	//<OUP> tValLen			:   ϵͳ��Ϣ����������
	//<RET> int				:   ������RET_TYPE��INFO_TYPE��ֵ
extern int 	API_GetSysInfo(u32 tInfoType,void* pVal,int tValLen);


enum CTRL_TYPE		
{
	SYS_CTRL_TELS_PWR		=0x0101,	//�绰ģ���Դ����		����:u8	0/1(�ߵ�ƽ)	�޴˹���	
	SYS_CTRL_TELS_RST		=0x0102,	//�绰ģ�鸴λ����		����:u8	0/1(�ߵ�ƽ)
	SYS_CTRL_TELS_BOOT		=0x0103,	//�绰ģ��Boot����		����:u8	0/1(�ߵ�ƽ)				
};	//Ver:1.2

	//<FUN> ϵͳ���ƽӿڣ���ϵͳ����ά��ģ��ʹ��
	//<INP> tCtrlType		:   ϵͳ��Ϣ����(CTRL_TYPE)
	//<OUP> pVal			:   ϵͳ��Ϣ������
	//<OUP> tValLen			:   ϵͳ��Ϣ����������
	//<RET> int				:   ������RET_TYPE��INFO_TYPE��ֵ
extern int API_Control(u32 tCtrlType,void* pVal,int tValLen);

//-----------------------------------------------------------------------------------------------------------------------
//�����ת��

	//<FUN> �ַ���ת����Unicode2  GB2312 -> UCS2	
extern void API_GbkToUniCode(char *dest,int dest_size, char *src);

	//<FUN> Unicode2ת�����ַ���  UCS    -> 2GB2312
extern void API_UniCodeToGbk(char *dest,int dest_size, char *src);

extern int  API_UniCodeLen(char* pStr);

//-----------------------------------------------------------------------------------------------------------------------
//������ת��	

	//<FUN> Hex����ת����Ӧ�ַ�
	//<FUN> 	0x0-0x9='0'-'9'   0xA-0xF='A'-'F'  ����=' '
extern s8 API_Conv_NumToChar(u8 b);
					
	//<FUN> �ַ�ת����ӦHex����
	//<FUN> 	'0'-'9'=0x0-0x9  'a'-'f'=0xA-0xF	'A'-'F'=0xA-0xF
extern u8 API_Conv_CharToNum(s8 c);
		
	//<FUN> �ַ���ת��BCD�룬BCD�������
	//<FUN> 	bcd	="\xFF\xFF\xFF\xFF\xFF\xFF\xFF";
	//<FUN> 	API_Conv_StrToBcd("12345",5,bcd);	
	//<FUN> 	bcd	="\x12\x34\x5F\xFF\xFF\xFF\xFF";
extern void API_Conv_StrToBcd_Left(s8* str,int strlen,u8* bcd);

	//<FUN> �ַ���ת��BCD�룬BCD���Ҷ���
	//<FUN> 	bcd	="\x00\x00\x00\x00\x00\x00\x00";
	//<FUN> 	API_Conv_StrToBcd_Right("12345",5,bcd,7);	
	//<FUN> 	bcd	="\x00\x00\x00\x00\x01\x23\x45F";
extern void API_Conv_StrToBcd_Right(s8* str,int slen,u8 *bcd,int blen);

	//<FUN> BCD��ת���ַ���
	//<FUN> 	bcd	="\x12\x34\x5F\xFF\xFF\xFF\xFF";
	//<FUN> 	API_Conv_BcdToStr(bcd,4,str);	
	//<FUN> 	str	="12345FFF";
extern void API_Conv_BcdToStr(u8* bcd,int blen,s8* str);

			
	//<FUN> 16�������ַ���ת��Ϊ��ֵ
	//<FUN> 	szNum="12AB"	szNumLen=4
	//<FUN> 	return 4779
extern u32 	API_Conv_GetHex(u8 *szNum,int szNumLen);


	//<FUN> 10�������ַ���ת��Ϊ��ֵ
	//<FUN> 	szNum="1234"	szNumLen=4 
	//<FUN> 	return 1234
	//<INP> szNum			:   Ϊ10�������ַ���
	//<INP> szNumLen		:   Ϊ�ַ������ȡ�
	//<RET> u32				:   ת�������ֵ
extern u32 	API_Conv_GetNum(char* szNum,int szNumLen);


//-----------------------------------------------------------------------------------------------------------------------
//������㷨


//-----------------------------------------------------------------------------------------------------------------------
//��ȫ����


//-----------------------------------------------------------------------------------------------------------------------
//��ʱ��

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


	//<FUN> ��ȡϵͳʱ��
	//<OUP> pTime			:   DATE_TIME
extern void API_TimeGet(DATE_TIME* pTime);		

	//<FUN> ����ϵͳʱ��
	//<INP> pTime			:   DATE_TIME
extern void API_TimeSet(DATE_TIME* pTime);		


	//<FUN> ��ȡ��ǰ������
	//<RET> int				:   ��λ:����
extern int  API_TimeCurrMS(void);				

	//<FUN> ��ȡ��ǰ����
	//<RET> int				:   ��λ:��
extern int  API_TimeCurrSec(void);				

	//<FUN> ˯��ָ��ʱ��
	//<INP> tTime			:   ˯��ʱ��,��λ:΢��
extern void API_TimeSleepUS(u32 tTime);			

	//<FUN> ˯��ָ��ʱ��
	//<INP> tTime			:   ˯��ʱ��,��λ:����
extern void API_TimeSleepMS(u32 tTime);			

	//<FUN> ˯��ָ��ʱ��
	//<INP> tTime			:   ˯��ʱ��,��λ:��
extern void API_TimeSleepS(u32 tTime);			

//-----------------------------------------------------------------------------------------------------------------------
//���ļ�ϵͳ



//-----------------------------------------------------------------------------------------------------------------------
//��ͨ�ö���

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
	ICC_CONTSCT		=0x01,		//�Ӵ�ʽIC��	 contact	
	ICC_NON_CONTSCT	=0x02,		//�ǽӴ�ʽIC��	 non-contact 
	ICC_PSAM1		=0x04,		//PSAM��1
	ICC_PSAM2		=0x08,		//PSAM��2
	ICC_MAX			=4
};	
enum UART_INDEX
{
	UART_1			=0x01,		//����1 ����̨,	KN��8112ΪRJ45,8210ΪMiniUsb
	UART_2			=0x02,		//����2 ��չ��,	KN��8112ΪRJ11,8210Ϊɨ��ͷ
	UART_3			=0x04,		//����3 KNΪ�绰ģ�鴮��   (����ϵͳ����ʹ��)
	UART_4			=0x08,		//����4 ȫ���ܴ���Modem	   (����ϵͳ����ʹ��)
	UART_MAX		=4
};	
enum NET_INDEX
{
	NET_UNKNOW		=0x00,		//δ֪
	NET_SYNC_MODEM	=0x01,		//ͬ��Modem
	NET_ASYN_MODEM	=0x02,		//�첽Modem
	NET_PLMN_MASTER	=0x04,		//½�Ϲ����ƶ�ͨ������Public Land Mobile Network��
	NET_PLMN_SLAVE	=0x08,		//½�Ϲ����ƶ�ͨ������Public Land Mobile Network��
	NET_SOCKET		=0x10,		//Socket�ӿ�
	NET_FSK			=0x20,		//FSKͨ��
	NET_MAX			=5
};	

enum PLAY_TYPE
{
	PLAY_BEEP	=0x01,			//Beep
	PLAY_WAVE	=0x02,			//wav�����ļ�
};

enum IMAGE_TYPE
{
	IMAGE_IMG	=0x01,			//�Զ���ͼƬ�ļ�
	IMAGE_BMP	=0x02,			//
	IMAGE_PNG	=0x04,			//
	IMAGE_GIF	=0x08,			//
};


#define TIME_ONCE		(0)			//���Ϸ���
#define TIME_INFINE		(-1)		//һֱ��
#define TIME_NOWAIT		(-2)		//���ȴ�


enum EVENT_TYPE
{
	EVENT_NONE		=0x00000000,	//��Ч�¼�
	EVENV_ICC_POWERUP_ERR = 0x0000000F, 	//IC���ϵ�ʧ��
	EVENT_INDEX		=0x000000FF,	//�豸����
	
	EVENT_ICC		=0x00000100,	//�Ӵ�ʽIC��/�ǽӴ�ʽIC��/PSAM��		
	EVENT_MAG		=0x00000200,	//�ſ�ˢ��		
	EVENT_NET		=0x00000400,	//����ͨ�Žӿ�			API_NetEvent
	EVENT_USB		=0x00000800,	//USB�ӿ�		
					
	EVENT_KEY		=0x00001000,	//����		
	EVENT_PEN		=0x00002000,	//������	
	EVENT_UART		=0x00004000,	//UART����		
	EVENT_AUDIO		=0x00008000,	//��Ƶͨ�Žӿ�	
	
	EVENT_UI		=0x00010000,	//ͼ���û�����ӿ�	
	EVENT_SYS		=0x00020000,	//ϵͳ�ӿ�		
	EVENT_MISC		=0x00040000,	//��������ӿ�
	EVENT_PRINT		=0x00080000,	//��ӡ���

	EVENT_PHONE		=0x00100000,	//�绰����				API_Phone_GetEvent

	EVENT_ERROR		=0x01000000,	//����	   
	EVENT_TIMEOUT	=0x02000000,	//��ʱ	   
	EVENT_OK  		=0x04000000,	//ȷ��	   ȷ��		ȷ��	��
	EVENT_CANCEL	=0x08000000,	//ȡ��	   ����		�˳�	��
	EVENT_QUIT		=0x10000000,	//�˳�
	EVENT_MASK		=0xFFFFFF00	
};	



	//<FUN> �ȴ�����¼��б���
	//<FUN> 	�κ��¼�		����EVENT_ERROR|EVENT_TIMEOUT
	//<FUN> 	EVENT_UI�¼�	����EVENT_OK|EVENT_CANCEL|EVENT_QUIT
	//<FUN> 	����EVENT_TYPE	����EVENT_TYPE|EVENT_INDEX		
	//<INP> tTimeOutMs		:   �ȴ���ʱʱ�䣬��λ:����
	//<INP> ...				:   �¼�����(EVENT_TYPE|EVENT_INDEX),�磺(EVENT_UART|UART_1)��ʾ����1
	//<RET> EVENT_TYPE		:   EVENT_ERROR|EVENT_TIMEOUT|EVENT_OK|EVENT_CANCEL|tEventMask
extern u32  API_WaitEvent(int tTimeOutMs,...);
extern u32  API_WaitEventGroup(int tTimeOutMs,int tNum,u32* pEventGroup);
//extern u32  API_WaitEvent_GetCheck(char *buffer,int *retkey,char *disperror,pthread_mutex_t  *w_lock);


	
//-----------------------------------------------------------------------------------------------------------------------
//���ӡ���ӿ�


//-----------------------------------------------------------------------------------------------------------------------
//��Ƭ�����ӿ�
extern void API_ICC_Reset();

extern int API_ICC_Open(int tCardIndex);

extern int API_ICC_Close(int tCardIndex);

	//<FUN> ��Ƭ�ϵ�
	//<INP> tCardIndex		:	��Ƭ����(ICC_CONTSCT��ICC_NON_CONTSCT��ICC_PSAM1��ICC_PSAM2)
	//<RET> RET_TYPE		:   ������
extern int  API_ICC_PwrOn( 		int tCardIndex);	

	//<FUN> ���ؿ�ƬATR��Ϣ
	//<INP> tCardIndex		:	��Ƭ����(ICC_CONTSCT��ICC_NON_CONTSCT��ICC_PSAM1��ICC_PSAM2)
	//<OUP> pAtrBuf			:	����IC��ATR�����ݻ�����
	//<OUP> pInfoLen		:   ATR�����ݻ���������󳤶�
	//<RET> int				:   ����ATR���ݳ���
extern int  API_ICC_GetAtr( 	int tCardIndex,u8* pAtrBuf,int nAtrBufMax);	

	
	//<FUN> ��Ƭ�µ�
	//<INP> tCardIndex		:	��Ƭ����(ICC_CONTSCT��ICC_NON_CONTSCT��ICC_PSAM1��ICC_PSAM2)
	//<RET> RET_TYPE		:   ������
extern int  API_ICC_PwrOff(		int tCardIndex);	

	//<FUN> ��ƬAPDUָ��
	//<INP> tCardIndex		:	��Ƭ����(ICC_CONTSCT��ICC_NON_CONTSCT��ICC_PSAM1��ICC_PSAM2)
	//<INP> pCmdBuf			:   ���͵�APDU�������ݻ�����
	//<INP> nCmdLen			:   ���͵�APDU�������ݳ���
	//<OUP> pOutBuf			:   �������ݻ�����	(Ӧ�ó�����ݿ�Ƭ�ṹ�Լ����ƻ�������С)
	//<OUP> pOutLen			:   �������ݳ���
	//<RET> u32				:   ����SWֵ����0x9000,0x6A82,0x0000
extern int  API_ICC_Apdu(		int tCardIndex,u8* pCmdBuf,int nCmdLen,u8* pOutBuf,int* pOutLen);

	//<FUN> ���ýӴ�ʽIC���¼��Ƿ�������루Ĭ���Զ��ϵ磩��
	//<INP> isOnly			:   Ϊ0��ʾIC��������Զ��ϵ磬Ӧ��WaitEvent�ȵ��¼���ֱ��API_ICC_GetAtr
	//<INP> isOnly			:   Ϊ1��ʾ�����IC�������¼���Ӧ��WaitEvent�ȵ��¼���ִ��API_ICC_PwrOn+API_ICC_GetAtr
	//<RET> RET_TYPE		:   ������
extern int  API_ICC_OnlyChkPreSent(int isOnly);
//-----------------------------------------------------------------------------------------------------------------------

#define MAG_DATA_PRESENTS	0x01	// �ôŵ�������
#define MAG_DECODE_SUCCUSS	0x02	// �ôŵ����ݽ���ɹ�

#define	MAG_TRK_LEN			120		// �ŵ�������󳤶�

typedef struct
{
	u8	Type;						// �������� MAGPAR_TRK or MAGPAR_IC
	u8	Flag[3];					// �ŵ����KS_MAG_TRK_FLAG
	u8	Len[3];						// �ŵ����ݳ���
	u8	Trk[3][MAG_TRK_LEN];		// �ŵ�����
}MAGTRK;

extern int  API_SetTrkBuf(MAGTRK* pTrk);

//-----------------------------------------------------------------------------------------------------------------------
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

enum NET_STATUAS
{
	NET_STATUAS_NO_SIM			= 0, //��SIM��
	NET_STATUAS_SIM_EXIT			= 1, //SIM���Ѿ�����
	NET_STATUAS_DEACTIVE			= 2, //���粻����
	NET_STATUAS_ACTIVE				= 3  //��������
};
//	V1.5


	//<FUN> ��ͨ���豸
	//<INP> tCommType		:   ͨ���豸  (NET_SYNC_MODEM��NET_ASYN_MODEM��NET_GPRS_MODEM)
	//<RET> RET_TYPE		:   ������ 
extern int  API_NetOpen(int tCommType);

	//<FUN> �ر�ͨ���豸
	//<RET> RET_TYPE		:   ������
extern int  API_NetClose(void);

	//<FUN> ����ѡ�����
	//<INP> tOption			:   Ϊ��������(OPT_TYPE)
	//<INP> pVal			:   Ϊ����������
	//<INP> tValSize		:   Ϊ��������������
	//<RET> RET_TYPE		:   ������
extern int 	API_NetSetOpt(int tOption, void* pVal, int  tValSize);

	//<FUN> ��ȡѡ�����
	//<INP> tOption			:   Ϊ��������(OPT_TYPE)
	//<INP> pVal			:   Ϊ����������
	//<INP> tValSize		:   Ϊ��������������
	//<RET> RET_TYPE		:   ������
extern int 	API_NetGetOpt(int tOption, void* pVal, int  tValSize);

extern int 	API_NetActive(int tTimeOutMs);
extern int 	API_NetDeActive(int tTimeOutMs);

	//<FUN> ���ӷ���
	//<INP> pAddr			:   ��������ַ
	//<INP> tPort			:   �������˿�
	//<INP> tTimeOutMs		:	����ʱʱ��,��λ:����
	//<RET> RET_TYPE		:   ������
extern int 	API_NetConnect(char* pAddr,int tPort,int tTimeOutMs);

	//<FUN> �Ͽ�����
	//<INP> tTimeOutMs		:	����ʱʱ��,��λ:����
	//<RET> RET_TYPE		:   ������
extern int 	API_NetDisConnect(int tTimeOutMs);

	//<FUN> ��������
	//<INP> pSendBuf		:   Ҫ���͵����ݻ�����
	//<INP> tSendLen		:   Ҫ���͵����ݳ���
	//<INP> tTimeOutMs		:	����ʱʱ��,��λ:����
	//<RET> RET_TYPE		:   ������
extern int 	API_NetSend(u8* pSendBuf,int  tSendLen,int tTimeOutMs);

	//<FUN> ��������
	//<INP> pRecvBuf		:   �������ݻ�����
	//<INP> tRecvLen		:   �������ݻ���������
	//<INP> tTimeOutMs		:	����ʱʱ��,��λ:����
	//<RET> RET_TYPE		:   ʵ���յ������ݳ���
extern int 	API_NetRecv(u8* pRecvBuf,int tRecvLen,int tTimeOutMs);

extern int  API_NetEvent(int* pRet);

//ZFC, �����Ӷ�����״̬���ж�
//<FUN> �ж�����״̬
//<RET> RET_TYPE		:   �����ʵ��״̬
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
//ZT8225�����뷨�л�������ZT8210C���л������ǲ�ͬ��
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
	PR_OK				=0,				//����
	PR_ERR				=1,				//����
	PR_IS_PRINTING		=2,				//ȱֽ
	PR_NO_PAPER			=3,				//ȱֽ
	PR_TEMP_HIGH		=4,				//�¶ȹ���
	PR_UNKNOW							//δ֪
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
    PRN_ST_OK	 = 0,   //����
    PRN_ST_OUT	 = 1,	//ȱֽ
};

enum PRN_ALIGN
{    
    PRN_ALIGN_LEFT	 	= 0,	//����
    PRN_ALIGN_RIGHT		= 1,	//����
    PRN_ALIGN_CENTER	= 2,	//����
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
	//<FUN> ����INI�������ַ������ͣ�
	//<INP> pFile 		:   int�ļ�·��,API����ʱ��֧��·��.
	//<INP> pSection 		:   int�ļ�����,[]
	//<INP> pKeyName 		:   int�ļ��ؼ�������,��ǩ����
	//<INP> pStr 			:   ��ǩ���ƶ�Ӧ���ַ���
	//<RET> RET_TYPE 		:   �����루0�ɹ�����0ʧ�ܣ�
extern int   API_Ini_SetStr(char* pFile,char* pSection,char* pKeyName,char* pStr);

	//<FUN> ��ȡINI�������ַ������ͣ�
	//<INP> pFile 			:   int�ļ�·��,API����ʱ��֧��·��.
	//<INP> pSection 		:   int�ļ�����,[]
	//<INP> pKeyName 		:   int�ļ��ؼ�������,��ǩ����
	//<INP> pDefStr 		:   ��ǩ���ƶ�Ӧ��Ĭ���ַ���
	//<OUP> pRetStr 		:   ���ر�ǩ���ƶ�Ӧ���ַ����Ļ����������ʧ�ܷ���Ĭ���ַ���pDefStr
	//<INP> nRetSize 		:   ���ر�ǩ���ƶ�Ӧ���ַ����Ļ�������С
	//<RET> RET_TYPE 		:   �����루0�ɹ�����0ʧ�ܣ�
extern int   API_Ini_GetStr(char* pFile,char* pSection,char* pKeyName,char* pDefStr,char* pRetStr,int nRetSize);

	//<FUN> ����INI�������������ͣ�֧����Ȼ����10����(123��-1)���޷���16������(0xFE)���޷���2����(0b10011)
	//<INP> pFile 			:   int�ļ�·��,API����ʱ��֧��·��.
	//<INP> pSection 		:   int�ļ�����,[]
	//<INP> pKeyName 		:   int�ļ��ؼ�������,��ǩ����
	//<INP> nIntVal 		:   ��ǩ���ƶ�Ӧ��������ֵ
	//<RET> RET_TYPE 		:   �����루0�ɹ�����0ʧ�ܣ�
extern int   API_Ini_SetInt(char* pFile,char* pSection,char* pKeyName,int nIntVal);

	//<FUN> ��ȡINI�������������ͣ�֧����Ȼ����10����(123��-1)���޷���16������(0xFE)���޷���2����(0b10011)
	//<INP> pFile	 		:   int�ļ�·��,API����ʱ��֧��·��.
	//<INP> pSection 		:   int�ļ�����,[]
	//<INP> pKeyName 		:   int�ļ��ؼ�������,��ǩ����
	//<INP> nDefVal 		:   ��ǩ���ƶ�Ӧ��Ĭ��������ֵ
	//<RET> int 			:   ���ر�ǩ���ƶ�Ӧ��������ֵ,���ʧ�ܷ���Ĭ��������ֵnDefVal
extern int   API_Ini_GetInt(char* pFile,char* pSection,char* pKeyName,int nDefVal);
//-----------------------------------------------------------------------------------------------------------------------
enum PHONE_TYPE
{
	PHONE_PSTN				=0x01,		//���ÿ��ص绰���� 
};
enum PHONE_CID_TYPE
{
	CID_TYPE_DTMF			=0x01,		//�������ͣ�DTMF
	CID_TYPE_FSK			=0x06,		//�������ͣ�FSK
	CID_TYPE_FSK_SDMF		=0x02,		//�������ͣ�FSK-��������Ϣ��ʽ  (Single   Data Message Format) 
	CID_TYPE_FSK_MDMF		=0x04,		//�������ͣ�FSK-����������Ϣ��ʽ(Multiple Data Message Format) 
	CID_TYPE_MODEM			=0x80,		//�������ͣ���Modem����
};
enum PAR_ADDR
{
	PAR_DTMF_DURATION_TIME	=1,			//DTMF���ų���ʱ��,	��λ:����,	��Χ80-160,	Ĭ��Ϊ120
	PAR_DTMF_INTERVAL_TIME	=2,			//DTMF���ż��ʱ��,	��λ:����,	��Χ80-160,	Ĭ��Ϊ120
	PAR_DTMF_PAUSE_TIME		=3,			//DTMF������ͣʱ��,	��λ:10����,��Χ30-250,	Ĭ��Ϊ100
	PAR_WAIT_DIALTONE_TIME	=4,			//  �ȴ�������ʱ��,	��λ:10����,��Χ30-250	Ĭ��Ϊ80
	PAR_END
};
enum PHONE_EVENT
{
	PHONE_EVENT_RING			=1,		//�����¼�
	PHONE_EVENT_CID				=2,		//�����¼�
	PHONE_EVENT_HOOK_STA		=3		//���״̬
};	

	//<FUN> ��ȡ�绰�¼�����    (��API_WaitEvent����EVENT_PHONE��ʹ��)
	//<OUP> pRet			:   ��RET=PHONE_EVENT_HOOK_STAʱ,pRet=1Ϊժ��״̬,pRet=0Ϊ�һ�״̬
	//<OUP> pRet			:   ��RET=PHONE_EVENT_CID     ʱ,pRet=PHONE_CID_TYPE
	//<RET> int				:   ΪPHONE_EVENT
extern int  API_Phone_GetEvent(int* pRet);

	//<FUN> ��ȡ�绰������Ϣ
	//<OUP> pNumber			:   Ϊ�������	����=36�ֽ�
	//<OUP> pName			:   Ϊ��������	����=32�ֽ�
	//<OUP> pTime			:   Ϊ����ʱ��	����= 8�ֽ�	MMDDHHMM
	//<RET> int				:   ������
extern int  API_Phone_GetCidInfo(char* pNumber,char* pName,char* pTime);

	//<FUN> ��ȡ�绰ģ��汾
	//<OUP> pMajor			:   Ϊ���汾
	//<OUP> pMinor			:   Ϊ�Ӱ汾
	//<RET> int				:   ������
extern int  API_Phone_Ver(int* pMajor,int* pMinor);

	//<FUN> �绰DTMF����	(P/p/,Ϊ��ͣ)
	//<INP> pNumber			:   Ϊ�绰���봮
	//<RET> int				:   ������
extern int  API_Phone_Dial(const char* pNumber);

	//<FUN> ժ�һ�����
	//<INP> isOff			:   1Ϊժ��,Ĭ��Ϊ0 
	//<RET> int				:   ������
extern int  API_Phone_HookSwitch(u8 isOff);

	//<FUN> ���忪�ؿ���
	//<INP> isOff			:   1Ϊ������,Ĭ��Ϊ0 
	//<RET> int				:   ������
extern int  API_Phone_RingSwitch(u8 isOff);

	//<FUN> ��˿��ؿ���
	//<INP> isOff			:   1Ϊ����,Ĭ��Ϊ0 
	//<RET> int				:   ������
extern int  API_Phone_MicSwitch(u8 isOff);

	//<FUN> �ֻ����ؿ���
	//<INP> isOff			:   1Ϊ�Ͽ��ֻ�,Ĭ��Ϊ0 
	//<RET> int				:   ������
extern int  API_Phone_ExtSwitch(u8 isOff);

	//<FUN> ���ȿ��ؿ���
	//<INP> isMute			:   1Ϊ����,Ĭ��Ϊ0 
	//<RET> int				:   ������
extern int  API_Phone_SpkSwitch(u8 isMute);

	//<FUN> ��ȡ��е���״̬
	//<OUP> pIsOff			:   1Ϊժ��,Ĭ��Ϊ0  
	//<RET> int				:   ������
extern int  API_Phone_GetHookSta(u8* pIsOff);	

	//<FUN> ���õ绰ģ�����
	//<INP> tAddr			:   ������ַPAR_ADDR
	//<INP> tVal			:   ������ֵ
	//<RET> int				:   ������
extern int  API_Phone_SetPar(u8 tAddr,u8  tVal);

	//<FUN> ��ȡ�绰ģ�����
	//<INP> tAddr			:   ������ַPAR_ADDR
	//<OUP> pVal			:   ������ֵ
	//<RET> int				:   ������
extern int  API_Phone_GetPar(u8 tAddr,u8* pVal);
//-----------------------------------------------------------------------------------------------------------------------
	//<FUN> ��ص�ѹУ׼
	//<INP> v1				:   ��׼��ѹ1,��λ:΢��		6800000		
	//<INP> ad1				:   ��ѹ�ο�ֵ1
	//<INP> v2				:   ��׼��ѹ2,��λ:΢��		8400000		
	//<INP> ad1				:   ��ѹ�ο�ֵ2
	//<RET> int				:   ������
extern int API_BatCalibration(int v1,int ad1,int v2,int ad2) ;

	//<FUN> ��ȡ��ѹ�ο�ֵ
	//<RET> int				:   ��ѹ�ο�ֵ
extern int API_GetBatReferVolt(void); 
              
	//<FUN> ��ȡ��ص�ѹ
	//<FUN> 				1(volt) 	 = 1000(millivolt)
	//<FUN> 				1(millivolt) = 1000(microvolt) 
	//<OUP> IsAcPwrIn		:   �Ƿ���뽻��������,1��ʾ����,0��ʾδ����	
	//<RET> int				:   ��ص�ѹ,��λ:΢��
extern int API_GetBatMicroVolt(int* IsAcPwrIn); 


	//<FUN> ������ʾ���Աȶ�
	//<INP> tRatio			:   ��ʾ���Աȶ�,1-100	
	//<RET> int				:   ������
extern int API_SetLcdContrast(int tRatio);

	//<FUN> ������ʾ������
	//<INP> isOn			:   Ϊ1��ʾ������,Ϊ0��ʾ�ر���	
	//<RET> int				:   ������
extern int API_SetLcdBacklight(int isOn);

enum LED_MASK
{
	LED_BLUE	=0x00000001,			//��
	LED_ORANGE	=0x00000002,			//��
	LED_GREEN	=0x00000004,			//��		
	LED_RED		=0x00000008,			//��
	LED_ALL		=0xFFFFFFFF,			//
};	
	//<FUN> ����LED�ƿ���
	//<INP> tMask			:   ΪLED_MASK
	//<INP> isOn			:   Ϊ1��ʾ��,Ϊ0��ʾ��
	//<RET> int				:   ������
extern int API_SetLedSwitch(u32 tMask,int isOn);


	//<FUN> ��������ģ�鿪��
	//<INP> isOn			:   Ϊ1��ʾ��,Ϊ0��ʾ��	
	//<RET> int				:   ������
extern int API_SetBarCodeBacklight(int isOn);

	//<FUN> ����wav�ļ�
	//<INP> pWavePath		:   wav�ļ�·��	
	//<RET> int				:   ������
extern int API_WavePlay(const char* pWaveFile);

	//<FUN> ����wav�ļ���
	//<INP> num				:   wav�ļ�����
	//<INP> pWaveGroupPath	:   wav�ļ�·������	
	//<RET> int				:   ������
extern int API_WavePlayGroup(int num,const char** pWaveGroupPath);

	//<FUN> ֹͣ����
	//<RET> int				:   ������
extern int API_WaveStop(void);

	//<FUN> ��ȡ���Ž���
	//<RET> int				:   0(�������),1-100Ϊ���Űٷֱ�
extern int API_GetPlayRatio(void);

	//<FUN> ����Beep
	//<INP> tFreq			:   Ƶ��	,��λ:����
	//<INP> tTimeMs			:   ����ʱ��,��λ:����	
	//<RET> int				:   ������
extern int API_Beep(u32 tFreq,u32 tTimeMs);

	//<FUN> ��ȡ����
	//<INP> tFreq			:   Ƶ��	,��λ:����
	//<INP> tTimeMs			:   ����ʱ��,��λ:����	
	//<RET> int				:   0 ����,1-100 ����  
extern int API_GetVolume(void);

	//<FUN> ��������
	//<INP> vol				:   0 ����,1-100 ����  
	//<INP> tTimeMs			:   ����ʱ��,��λ:����	
	//<RET> int				:   ������
extern int API_SetVolume(int vol);

//-----------------------------------------------------------------------------------------------------------------------
enum DEFENDER_STA
{
	DEFENDER_NORMAL			=0x0001,			//����״̬
	DEFENDER_DESTROY		=0x0002,			//����״̬
	DEFENDER_INACTIVE		=0x0004,			//̽�⹦��δ����
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
