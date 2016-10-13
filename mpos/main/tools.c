
#include <stdio.h>
#include <stdarg.h>
#include "comm.h"
#include "cserial.h"
#include <pthread.h>
#include "T9_define.h"
#include "tool.h"

#define KeyMenu 				0x46  //# �л����뷨
#define Key_Dian 				0x45  //С����
#define Key_Left				   	0x41  //F1
#define Key_Down			        0x43//F3
#define Key_Up				   	0x42//F2
#define Key_Right			    0x44//F4
#define Key_Esc          		0x1B		
#define Key_Enter        		0x0D		
#define Key_Backspace  	    	0x08
#define POSK_INPUT_TIMEOUT       -1001
#define POSK_INPUT_ESC           -1002


static const int LCD_MAX_ROW		= 5;
static const int LCD_PER_ROW		= 1;	//����ʱ��������1��
static int g_lcd_disp_row			= 1;
void Lcd_Clr()
{
	clrscr();
	return;
}

void clrscr()
{
	API_UI_Clear();
	g_lcd_disp_row = 1;
}
u8 getkeycode(int waittime)
{
	int ret = 0;
	if(waittime==0)
	{
		waittime=120;
	}
	ret = API_GetKeyCode(waittime * 1000);
	API_Trace(0, "%s API_GetKeyCode return [%02X]", __FILE__, ret);
	if(-1 == ret) //��ʱ
	{
		return 0;
	}
	else
	{
		return ret;
	}
}


int WrongMsgAndWaitKey( char * pi_msg)
{
	ClrScr("��  ʾ");
	Lcd_printf_center(pi_msg);
	getkeycode(3);	
	return FALSE ;
}

int RightMsgAndWaitKey( char * pi_msg)
{
	ClrScr("��  ʾ");
	Lcd_printf_center(pi_msg);
	getkeycode(3);	
	return TRUE ;
}
int Confirm (int TimeOut)                /* return APP_FAIL|APP_SUCC */
{
	while (TRUE)
	{
		switch (getkeycode(TimeOut))
		{
			case	ESC:	return	APP_FAIL;
			case	ENTER:	return	APP_SUCC;
			case	0:		return  APP_FAIL;
		}

	}
}

int ShowSelectDialog(char *pi_title , char* pi_noticestr , char* pi_okstr , char*pi_conselstr)
{
	if(pi_title != NULL)
		ClrScr(pi_title);
	if(pi_noticestr != NULL)	
			Lcd_printf("%s\n" , pi_noticestr);
	if(pi_okstr != NULL)	
			Lcd_printf("%s\n" ,pi_okstr);
	if(pi_conselstr != NULL)	
			Lcd_printf("%s\n" ,pi_conselstr);
	return TRUE ;
}



void Lcd_printf(const char * format, ...)
{
	char szBuffer[2048] = {0}, szLcdBuffer[2048] = {0};
	char *lpBuffer = NULL, *lpTmp = NULL;
	char szLocator[2] = {'\n', 0x00};

	va_list args;
	va_start(args, format);
	vsprintf(szBuffer, format, args);
	va_end(args);

	lpBuffer = szBuffer;

	while(NULL != (lpTmp = strstr(lpBuffer, szLocator)))
	{
		if(g_lcd_disp_row > LCD_MAX_ROW)	//��������������Զ���գ�������0
		{
            API_Trace(0, "Lcd_printf need to clear");
			Lcd_Clr();
		}
		if(lpTmp != lpBuffer)  // ������з�'\n'֮ǰû��������Ҫ��ʾ��ֱ�ӻ���
		{
			memset(szLcdBuffer, 0x00, sizeof(szLcdBuffer));
			memcpy(szLcdBuffer, lpBuffer, (lpTmp - lpBuffer)/sizeof(char)); // save strings
			API_UI_PrintLine(g_lcd_disp_row, FONT_SIZE_NORMAL, ALIGN_LEFT, szLcdBuffer);
			API_Trace(0, "����ʾ����: line[%d][%s]", g_lcd_disp_row, szLcdBuffer);
		}
		lpBuffer = lpTmp + 1;   //ָ����һ���ַ�
		g_lcd_disp_row += LCD_PER_ROW;
	}
    //ֻ�������ݲŽ�����ʾ����
    if(strlen(lpBuffer) > 0)
    {
	    API_UI_PrintLine(g_lcd_disp_row, FONT_SIZE_NORMAL, ALIGN_LEFT, lpBuffer);
	    API_Trace(0, "����ʾ����: line[%d][%s]", g_lcd_disp_row, lpBuffer);
    }
}

void Lcd_printf_center(const char * format, ...)
{
	char szBuffer[2048] = {0}, szLcdBuffer[2048] = {0};
	char *lpBuffer = NULL, *lpTmp = NULL;
	char szLocator[2] = {'\n', 0x00};

	va_list args;
	va_start(args, format);
	vsprintf(szBuffer, format, args);
	va_end(args);

	lpBuffer = szBuffer;

	while(NULL != (lpTmp = strstr(lpBuffer, szLocator)))
	{
		if(g_lcd_disp_row > LCD_MAX_ROW)	//��������������Զ���գ�������0
		{
			Lcd_Clr();
		}
		if(lpTmp != lpBuffer)  // ������з�'\n'֮ǰû��������Ҫ��ʾ��ֱ�ӻ���
		{
			memset(szLcdBuffer, 0x00, sizeof(szLcdBuffer));
			memcpy(szLcdBuffer, lpBuffer, (lpTmp - lpBuffer)/sizeof(char)); // save strings
			API_UI_PrintLine(g_lcd_disp_row, FONT_SIZE_NORMAL, ALIGN_CENTER, szLcdBuffer);
			API_Trace(0, "Lcd_printf_center 1: line[%d][%s]", g_lcd_disp_row, szLcdBuffer);
		}
		lpBuffer = lpTmp + 1;   //ָ����һ���ַ�
		g_lcd_disp_row += LCD_PER_ROW;
	}
    //ֻ�������ݲŽ�����ʾ����
    if(strlen(lpBuffer) > 0)
    {
	    API_UI_PrintLine(g_lcd_disp_row, FONT_SIZE_NORMAL, ALIGN_CENTER, lpBuffer);
	    API_Trace(0, "Lcd_printf_center 2: line[%d][%s]", g_lcd_disp_row, lpBuffer);
    }
}

void  ClrScr(char *Title)
{
	int i,length;
	char buffer[20];
	clrscr();
	API_Trace(0, "[%s]", Title);
	API_UI_SetTitle(FONT_SIZE_BIG, Title, TEXT_REVERSE_NO);
	return;
}



int emv_bcd_2_asc(uchar * bcd, int asclen, uchar * asc, int align) 
{
	int cnt;
	uchar *pbcd = bcd;
	uchar * pasc = asc;

	if ((asclen & 0x01) && align) {  /*�б��Ƿ�Ϊ�����Լ����Ǳ߶��� */
		cnt = 1;
		asclen ++;
	} else {
		cnt = 0;
	}
	for (; cnt < asclen; cnt++, pasc++) {
		*pasc = ((cnt & 0x01) ? (*pbcd ++ & 0x0f) : (*pbcd >> 4));
		*pasc += ((*pasc > 9) ? ('A' - 10) : '0');
	}
	*pasc = 0;
	return 0;
}
void APP_ShowSta(char* pTitle,char* pMsg)
{
    clrscr();
    API_GUI_Confirm(pTitle, pMsg, NULL, NULL);
}

char * DispTransHead(int dispflag)
{
	return (char *)("�й�����");
}






/****************************************************************/
/*������: API_GUI_Edit_GetInputIME                              */
/*����:   ��ʾ�༭��,�����ܴ���ͨ������������(����,����,��Ļ,����)*/
/*����:   pstrPrompt, ��ʾ��Ϣ      					        */
/*        nFontSize, pstrPrompt����ʾ����                       */
/*        pstrLastPrompt, �༭������ʾ��Ϣ                    */
/*        nLastFontSize, pstrLastPrompt����ʾ����               */
/*        pstrText, ���������       					        */
/*        nMaxLen, ��󳤶ȣ�������󳤶Ⱥ��Զ�����             */
/*        nTimeLimit, �ȴ�ʱ��, ��λΪ����, 0��ʾû�г�ʱʱ��   */
/*����ֵ: >0, ���볤��,��ʾ�ɹ�                                 */
/*        -1, ȡ������(����CANCEL)                              */
/*        -2, ��ʱ 			                                    */
/****************************************************************/
int GUI_Edit_GetInputIME(char* pstrPrompt, int nFontSize, char * pstrLastPrompt, int nLastFontSize, char* out, int max_ln, int min_ln ,u32 nTimeLimit,int pi_speca_zifu)
{
    char szLocator[2] = {'\n', 0x00}, szPrompt[128] = {0};
    char *lpTmp = NULL;
    char szTmp[12] = {0};
	int iRet = 0, iLen = 0, iTotalLen = 0, need_flush = 1;
	T9RESULT res;
	char data[100]={0};
    unsigned long long begin = API_TimeCurrMS();
	memset(data, 0, sizeof(data));
	char ch= 0x00 ;
	char tmp = 0x00 ;
	char number_key[12][30]={
		{0,'0'},
		{1,'0'},
		{2,'A','B','C','a','b','c','0'},
		{3,'D','E','F','d','e','f','0'},
		{4,'G','H','I','g','h','i','0'},
		{5,'J','K','L','j','k','l','0'},
		{6,'M','N','O','m','n','o','0'},
		{7,'P','Q','R','S','p','q','r','s','0'},
		{8,'T','U','V','t','u','v','0'},
		{9,'W','X','Y','Z','w','x','y','z','0'},
		{10,'.','>','/',',','?','-','=','+','|','*','%','!','@','[',']','{','}','(',')','&','0'}, //�����ַ�
		};
	int flag_change = 0 ; //�л����뷨�Ƿ���Ч
	int flag_change_times = 0 ;//�������л����뷨�Ĵ���
    if(NULL != pstrPrompt)
    {        
        //ֻ����������ʾ
        lpTmp = strstr(pstrPrompt, szLocator);
        if((NULL != lpTmp) && (*(lpTmp+1) != 0x00))
        {
            //�����һ��
            memcpy(szPrompt, pstrPrompt, (lpTmp - pstrPrompt)/sizeof(char));  
            SetContent(LINE_PROMPT, szPrompt, nFontSize, ALIGN_LEFT);  
            SetContent(LINE_PROMPT_NEXT, lpTmp+1, nFontSize, ALIGN_LEFT);  
        }
        else
        {
            SetContent(LINE_PROMPT, pstrPrompt, nFontSize, ALIGN_LEFT);  
        }              
    }
    if(NULL != pstrLastPrompt)
    {
        SetContent(LINE_LAST_PROMPT, pstrLastPrompt, nLastFontSize, ALIGN_CENTER);        
    }
	 SetEdit(LINE_EDIT, data, 0, FONT_SIZE_VERY_SMALL, ALIGN_CENTER);
	while(1)
	{
		if((nTimeLimit>0) && (API_TimeCurrMS()- begin > nTimeLimit))
	   {   
		   return -2;
	   }
		res = T9_getch(&ch);
		if( ch!=KeyMenu )  
		{
			flag_change_times = 0 ;//ֻҪ�����л����뷨��������0		
			tmp = 0x00;
		}
		 if( res == T9_TIMEOUT )
		{
			return POSK_INPUT_TIMEOUT;
			break;
		}
		else if( (res == T9_SUCC)&&(ch == Key_Backspace) && strlen(data)>0 )
		{
			data[strlen(data)-1] = 0;
		}
		else if( (res == T9_SUCC)&& ( ch == Key_Enter))
		{
			if(min_ln != 0 && (int)strlen(data)<min_ln)
			{
				continue;
			}
			strcpy(out,data);
			return strlen(data);
		}
		else if((res == T9_SUCC)&& ( ch == Key_Esc))
		{
			return POSK_INPUT_ESC;
		}
		//������ 
		else if((res == T9_SUCC)&&  (ch == Key_Dian) && (pi_speca_zifu == 1) )
		{
			data[strlen(data)] =  ':' ; //Ĭ����ʾ  ' : '  ð��-48 �պ���10
		}
		//������
		else if((res == T9_SUCC)&&  (ch<= Key9)  && (ch >= Key0) )
		{
			data[strlen(data)] = ch  ;
		}
		else if( (res == T9_SUCC)&&  ( ch == KeyMenu ) && (strlen(data) >0 ) )
		{	
			//���µ�һ�ν������ĸ����֣����ж��ö�ά������ĸ�����
			if( (flag_change_times == 0) && (tmp == 0x00 ) )   tmp = data[strlen(data)-1];
			if(  (tmp <=Key9 )&& ( tmp >=Key2 ) || tmp == ':') //2��9��������ĸ
			{	
				flag_change_times++;
				if(number_key[tmp-'0'][flag_change_times] == '0') //�ж��Ƿ������һ�����ǵĻ���Ҫ��Ϊ��һ��
				{	
					flag_change_times = 0 ;
					data[strlen(data)-1] = number_key[tmp-'0'][flag_change_times] + '0';
				}
				else
				data[strlen(data)-1] = number_key[tmp-'0'][flag_change_times];
			}			
		}
		if(max_ln != 0 && (int)strlen(data)>max_ln)
		{
			data[strlen(data)-1] = 0;
		}
		
		SetEdit(LINE_EDIT, data, 0, FONT_SIZE_VERY_SMALL, ALIGN_CENTER);
    }
	return strlen(data);
}


int GetStr_limit_titleIME(char * title,char *prompt, int nFontSize, char *buffer,int minlen,int len,int type ,int pi_speca_zifu)
{  

	char tmp[100]={0};
	int ret;
	const int waittime = 300 * 1000;
	memset(buffer,'\0',len);
	memset(tmp,0,sizeof(tmp));

	while(1)
	{
		ClrScr(title);
		ret = GUI_Edit_GetInputIME(prompt, FONT_SIZE_NORMAL, "��ȷ��������", FONT_SIZE_NORMAL, tmp, len,0, waittime,pi_speca_zifu);				 
		if (ret < 1)
		{
			return APP_FAIL;
		}
		if (ret<minlen &&minlen > 0 )
		{
			RightMsgAndWaitKey("λ�����㣬������");
			continue;
		}
		break;
	}

	memcpy(buffer,tmp,ret);
	memset(buffer+ret,0,len-ret);//��������
	return APP_SUCC;
}

/*******************************************************************************
*	�������ƣ�AsciiToBcd
*	��������: ��Դ�������ڵ�ASCII��ת��Ϊѹ��BCD�룬�洢��Ŀ�Ļ�������
*	��������: ASCII��ֵ��Сд�����У���Χ(0~9��a~f��A~F)
*	�޸�����: 2011-04-01	
*	���������
char	*bcd_buf:		Ŀ�Ļ�����
char	*ascii_buf:		Դ������
int		conv_len:		Ҫת����ASCII������
char	type:			0-����룬1-�Ҷ���
*	�����������
*	����ֵ  ����
*******************************************************************************/
void AsciiToBcd (char *bcd_buf ,const char *ascii_buf ,int conv_len ,char type )  
{
	int      cnt;  
	char     ch,ch1;    
	if ( conv_len & 0x01 && type )/*�б��Ƿ�Ϊ�����Լ����Ǳ߶���*/
		ch1 = 0 ;
	else
		ch1 = 0x55 ;

	for ( cnt = 0 ; cnt < conv_len ; ascii_buf ++ , cnt ++ ) 
	{
		if ( *ascii_buf >= 'a' )
			ch = *ascii_buf - 'a' + 10 ;
		else if ( *ascii_buf >= 'A' )
			ch = *ascii_buf- 'A' + 10 ;
		else if ( *ascii_buf >= '0' )
			ch = *ascii_buf-'0' ;
		else
		{

			ch = (*ascii_buf);
			ch &= 0x0f;//��������λ
		}
		if ( ch1 == 0x55 )
			ch1 = ch ;
		else 
		{
			*bcd_buf ++ = ch1 << 4 | ch ;
			ch1 = 0x55 ;
		}
	}//for
	if ( ch1 != 0x55 )
		*bcd_buf = ch1 << 4 ;

	return ;
}



/*******************************************************************************
*	�������ƣ�BcdToAscii
*	��������: ��Դ�������ڵ�ѹ��BCD��ת��ΪASCII�룬�洢��Ŀ�Ļ�������
*	��������: 
*	�޸�����: 2011-04-01	
*	���������
char	*ascii_buf:		Ŀ��Դ������
char	*bcd_buf:		Դ������
int		conv_len:		Ҫת����BCD������
char	type:			0-����룬1-�Ҷ���
*	�����������
*	����ֵ  ����
*******************************************************************************/
void BcdToAscii (char *ascii_buf , char *bcd_buf ,int conv_len ,char type )
{

	int  cnt ;
	unsigned char *pBcdBuf;

	pBcdBuf = (unsigned char *)bcd_buf;

	if ( (conv_len & 0x01) && type ) /*�б��Ƿ�Ϊ�����Լ����Ǳ߶���*/
	{                           /*0��1��*/
		cnt = 1 ;
		conv_len ++ ;
	}
	else
		cnt = 0 ;
	for ( ; cnt < conv_len ; cnt ++ , ascii_buf ++ ) 
	{
		*ascii_buf = ( ( cnt & 0x01 ) ? ( *pBcdBuf ++ & 0x0f ) : ( *pBcdBuf >> 4 ) ) ;
		*ascii_buf += ( ( *ascii_buf > 9 ) ? ( 'A' - 10 ) : '0' ) ;
	}
	*ascii_buf=0;
	return ;
}



int Hangup(void)
{  
	int ret = 0 ;
	if(gConnected == CONNECT)
	{
		APP_DisConnect("",30*1000);
		gConnected = DISCONNECT;
	}
	return APP_SUCC;
}
int APP_DisConnect(char* pTitle,int tTimeOutMs)	
{
	//add by zhzh
	API_UI_ClearAll();
	API_UI_SetTitle(FONT_SIZE_BIG, pTitle, TEXT_REVERSE_NO);	
	API_UI_PrintLine(2, FONT_SIZE_NORMAL, ALIGN_CENTER, "���ڶϿ�����...");
	return API_NetDisConnect(tTimeOutMs);
}
int APP_Connect(char* pTitle,char* pAddr,int tPort,int tTimeOutMs)	
{
	//add by zhzh
	//������ʾ+socket����
	int iRet=0;
	API_UI_Clear();
	API_UI_SetTitle(FONT_SIZE_BIG, pTitle, TEXT_REVERSE_NO);	
	API_UI_PrintLine(2, FONT_SIZE_NORMAL, ALIGN_CENTER, "�������Ӻ�̨");
	API_UI_PrintLine(3, FONT_SIZE_NORMAL, ALIGN_CENTER, "���Ժ�...");
	iRet = API_NetConnect(pAddr,tPort,tTimeOutMs);
	if(0 == iRet)
	{
		return  APP_SUCC;
	}
	else
	{
		return -1;	
	}
}

int APP_Send(char* pTitle,u8* pBuf,int tLen,int tTimeOutMs)	
{
	int iRet=0;
	API_UI_ClearAll();
	API_UI_SetTitle(FONT_SIZE_BIG, pTitle, TEXT_REVERSE_NO);	
	API_UI_PrintLine(2, FONT_SIZE_NORMAL, ALIGN_CENTER, "�����Ӻ�̨");
	API_UI_PrintLine(3, FONT_SIZE_NORMAL, ALIGN_CENTER, "�������ݰ�...");
	iRet = API_NetSend(pBuf,tLen,tTimeOutMs);
	if(0 == iRet)
		return 0;
	else
		return -1;
}
int APP_Recv(char* pTitle,u8* pBuf,int tLen,int tTimeOutMs)	
{

	int iRet=0;
	API_UI_ClearAll();
	API_UI_SetTitle(FONT_SIZE_BIG, pTitle, TEXT_REVERSE_NO);
	API_UI_PrintLine(2, FONT_SIZE_NORMAL, ALIGN_CENTER, "�����Ӻ�̨");
	API_UI_PrintLine(3, FONT_SIZE_NORMAL, ALIGN_CENTER, "���շ���...");
	iRet = API_NetRecv(pBuf,tLen,tTimeOutMs);
	API_Trace(0, "\n     API_NetRecv return [%d]          \n", iRet);
	if(-2 == iRet)
	{
		ztmisc_gprs_disconnect();
		return TRANSTIMEOUT;
	}
	else if((-1 == iRet) || (-3 == iRet))   //-1��ʾ����������
	{
		
		ztmisc_gprs_disconnect();
		return QUIT;
	}
	else
	{
		API_TraceHex(DBG_APP_INFO,"�����յ������ݡ�APP_Recv:",pBuf,iRet);	
		return iRet;
	}
}



int Receive(char *buf)  
{
	int len_1 = 0 ,len=0,port,timewait,ret,i , ipast = 0 ;
	unsigned char  buffer[500];
	int iRecLen;
	int itime = 0 ;
	char ctime[10]={0};
	int recv_len2;
	char title[30];
	memset(buffer,0,sizeof(buffer));

	//һ�ν�����
	iRecLen=APP_Recv(title, buffer, 500, 60);
	if(iRecLen<= 0)//���յ�����Ĭ��������256���ֽ�
	{
		Hangup();
		WrongMsgAndWaitKey("\n���׳�ʱ\n�����½���");
		return TRANSTIMEOUT;
	}
	if(buffer[0] == 'E')
	{
		if( buffer[1] = 0x01)
			WrongMsgAndWaitKey("����������Կ\n");
		else if(buffer[1] = 0x0C)
			WrongMsgAndWaitKey("�Ƿ�����������Կ������\n");
		else
			WrongMsgAndWaitKey("δ֪������\n");
		return  APP_FAIL ;
	}
	else if(buffer[0] == 'A')
	{
		memcpy(buf,buffer+1,iRecLen -1);
		return  iRecLen -1;
	}
	else 
	{
		WrongMsgAndWaitKey("�������ݽ�������\n");
		return  APP_FAIL ;
	}





	/*
	iRecLen=APP_Recv(title, buffer, 1, timewait);
	if(iRecLen==QUIT)
		return QUIT;
	if(iRecLen<= 0)//���յ�����Ĭ��������256���ֽ�
	{
		Hangup();
		ERR_MSG("\n���׳�ʱ\n�����½���");
		return TRANSTIMEOUT;
	}
	if(buffer[0] == 'E')
	{
		if((recv_len2=APP_Recv(title, buffer+iRecLen, 1, timewait)) <= 0)
		{
			Hangup();
			ERR_MSG("\n���׳�ʱ\n�����½���");
			return TRANSTIMEOUT;
		}
		if( buffer[1] = 0x01)
			WrongMsgAndWaitKey("����������Կ\n");
		else if(buffer[1] = 0x0C)
			WrongMsgAndWaitKey("�Ƿ�����������Կ������\n");
		else
			WrongMsgAndWaitKey("λ�ô�����\n");
		return  APP_FAIL ;
	}
	else  if(buffer[0] == 'A')
	{
		if((recv_len2=APP_Recv(title, buffer+iRecLen, 16, timewait)) <= 0)
		{
			Hangup();
			ERR_MSG("\n���׳�ʱ\n�����½���");
			return TRANSTIMEOUT;
		}
	}
	return len;

	*/
}



int  Dial( char *pi_ServerIp,  int pi_ServerPort)
{
	int iRet = 0;int iPPP  = 1 ;
	int itimes = 0;
	int iCount = 0, ppp_chong =0;
	int iTimeOut =	60 ,iMax = 3;
	time_t begin;
	begin = time(NULL);

	if(pi_ServerPort < 0 || pi_ServerPort >65535)
		return APP_FAIL ;
	if(NET_STATUAS_NO_SIM == API_NetStatuas(0x01))
	{
		ClrScr("��ʾ");
		Lcd_printf_center("\n���Ȳ���SIM��\n�����������");	
		getkeycode(30);
		return APP_FAIL;
	}
	
Lab_APN:

    iCount = 0;
	ppp_chong = 0;
	while(1)
	{
		iRet = API_GetKeyCode(100);
		if((iRet == KeyEsc))
		{
			gConnected=DISCONNECT;
			return APP_FAIL;
		}
		if(time(NULL)-begin > iTimeOut)
		{
			gConnected=DISCONNECT;
			API_Trace(0, "Dial ���ų�ʱ!");
			return APP_FAIL;
		}	
	//��ѯ�����Ƿ�����
			if(NET_STATUAS_ACTIVE != API_NetStatuas(0x02))
			{
			//�ȹҶ��ٲ���
				iRet = ztmisc_gprs_disconnect();//�Ҷϲ��ţ��´��ٲ���
				ztmisc_gprs_connect();//������������
				ClrScr("��ʾ");
				Lcd_printf_center("\n GPRS������ ...\n");	
				for(itimes = 0 ;itimes < 10;itimes++)
				{
					API_TimeSleepS(2);
					if(NET_STATUAS_ACTIVE == API_NetStatuas(0x02))
					{
						break ;
					}
					else  //�ȴ�  2* 9 = 18��
					{
						if(itimes == 9)
						{	
						  itimes = 0;
						  if(iPPP -- <1)
						  { 
								ClrScr("��ʾ");
								Lcd_printf_center("\n GPRS����ʧ�� ...\n");							
								ztmisc_gprs_disconnect();//�Ҷϲ��ţ��´��ٲ���
								getkeycode(5);
								return APP_FAIL ;
							}
						}
					}
				}
			}
			if(iCount >= iMax)
			{
				API_NetStatuas(0x02);
				API_Trace(0, "���Ӵ�������[%d]", iMax);
				ClrScr("��ʾ");
				Lcd_printf_center("\n���Ӵ�������");
			    ztmisc_gprs_disconnect();//�Ҷϲ��ţ��´��ٲ���
				getkeycode(5);
				gConnected=DISCONNECT;
				Hangup();	
				return APP_FAIL;
			}

		API_TimeSleepS(1);
		iRet = APP_Connect("��ʾ",pi_ServerIp,pi_ServerPort,10*1000);
		if (iRet != APP_SUCC)
		{
			gConnected=DISCONNECT;
			iCount += 1;
			clrscr();
			Lcd_printf_center("\n��[%d]����ʧ��",iCount); 			
			getkeycode(1);
			continue;
		}
		clrscr();
		gConnected=CONNECT;//���ӳɹ�		
		return APP_SUCC;
	}
	return APP_SUCC;
}




//**:***************************************************************************
//**:���ܣ�д���ݵ��ļ���
//**:**************************************************************************/
int AddDataToFile(char *filename , char *pi_str ,int pi_len ,int pi_no)
{
	long len=0;
	int ret;
	FILE *fp;
	fp = fopen(filename, "r+");
	if(fp == NULL)  return ERR_PUBLIC_OPEN_FILE;
	ret = fseek(fp, pi_no *pi_len , 0);
	if(ret<0) 
	{
		fclose(fp);
		return ERR_PUBLIC_FILE_CTL;
	}
	len = ftell(fp);
    fwrite(pi_str , 1 , pi_len ,fp );
	fclose(fp);
	return 0;
}
/********************************************************************************
*	�������ƣ�                                                                   
*	��������:                                                                    
*	�޸�����:    2016/10/11--16:9:45                                       
*	���������      
	pi_len : ��Ҫ��ȡһ����¼�ĳ���
   pi_NoTotal  :��Ҫ��ȡ��������¼
   pi_begin : �ӵڼ�����¼��ʼ
*	���������                                                                   
*	����ֵ��                                                                     
*	���ߣ�       Undefined                                                       
*******************************************************************************/
int ReadDataFromFile(char *filename , char *po_str ,int pi_len ,int pi_NoTotal ,int pi_begin)
{
	long len=0 ,len1=0;
	int ret;
	FILE *fp;
	fp = fopen(filename, "r+");
	len = pi_begin *pi_len*pi_NoTotal ;
	if(fp == NULL)  return ERR_PUBLIC_OPEN_FILE;
	ret = fseek(fp, 0 , SEEK_END);
	len1 = ftell(fp);
	if(len1 < (len+(pi_len*pi_NoTotal) )) 
	{
		fclose(fp);
		return ERR_PUBLIC_LAST_POS ;
	}
	ret = fseek(fp, len , 0);
	if(ret<0)
	{
		fclose(fp);
		return ERR_PUBLIC_FILE_CTL;
	}
	fread(po_str , 1,pi_len*pi_NoTotal ,fp );
	fclose(fp);
	return 0;
}
char _CalcLRC(char *cpBuf, int iLength)
{
	int     i;
	char   ch;
	ch = '\x00';
	for(i=0; i<iLength; i++)        ch ^= cpBuf[i];
	return(ch);
}

void API_getDateTime(char *strdate,char *strtime, char *strmsec)
{
    time_t t;
    struct tm * tm;

    //ȡ������ʱ��
    time(&t);
    tm = localtime(&t);

	//������ʱ���ʽ��
    if(strdate != NULL) sprintf(strdate, "%04d-%02d-%02d",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday);
    if(strtime != NULL) sprintf(strtime, "%02d:%02d:%02d",tm->tm_hour,tm->tm_min,tm->tm_sec);

	if(strmsec != NULL) sprintf(strmsec, "%03d", get_cur_msec() % 1000);
}


void Dec2Hex(unsigned char *in, unsigned char *out, int ln)
{
	int i;
	char *tmp_out;

	tmp_out = (char*)malloc((ln+1)*2);

	memset(tmp_out, 0, (ln+1)*2);
	for(i=0; i<ln; i++)
		sprintf(tmp_out+(i*2), "%02X", in[i] & 0xFF);

	memset(out, 0, ln*2+1);
	memcpy(out, tmp_out, ln*2);
	free(tmp_out);
}
int  WriteAppLog(char *filename, int flag, const char *format, ...)
{
    int  n;
    char dt[32]={0};				//, tmp[12];     //�������ʱ��
	va_list arg_ptr;              //�����������
    FILE *fp;
    fp = fopen(filename, "a+w");  //��׷�ӷ�ʽ�򿪻򴴽�һ���ļ�,ȡ���ļ����
	//��־�ļ�����,�򷵻�
	if(fp == NULL) return -1;
	//ȡ�ñ������,��ʼ�����������
    va_start(arg_ptr, format);
	//�������׼���
	if( flag==1 || flag==3) vprintf(format, arg_ptr);        //������printf**
	//ȡ������ʱ��
	API_getDateTime(dt, (char*)(dt+11), (char*)(dt+20));
    dt[10] = 32;   dt[19] = 32;   dt[23] = 32;

	//д����ʱ��
    fwrite(dt, 1, strlen(dt), fp);

    //����־����д����־�ļ�
    if( flag==2 || flag==3 )
        n = vfprintf(fp, format, arg_ptr);  //����ֵΪд����ֽ���

	//���������������
    va_end(arg_ptr);

	//ˢ���ļ�
    fflush(fp);
    fclose(fp);

    return 0;
}


void  posk_pkg_log(int flag,int pkg_ln,char *pkg)
{
	char pkg_tmp[3000]={0};
	memset(pkg_tmp,0,sizeof(pkg_tmp));
	Dec2Hex(pkg,pkg_tmp,pkg_ln);
	//BcdToAscii(pkg_tmp,pkg,pkg_ln,0);
	if(flag == 1)
	{
		WriteAppLog(SERIALTOTWOLEVELPOS, 2, "���͵�����[%s]\n",  pkg_tmp);
	}
	else
	{
		WriteAppLog(SERIALTOTWOLEVELPOS, 2, "���մӴ���[%s]\n", pkg_tmp);
	}
}



int GetUnionKeys( int pi_Only0_9 , char* po_keys)
{ 	
	u32 uret,transRet;
	int tCode,tType;
	u32 uaEvent[5];
	int uNum = 0 ,keyNum=0;;
	int result = 0 ;
	int	type;
	char sKeybuff[11];
	CLEAR(sKeybuff) ;

#if  1  //	���ڷ�װ���ã�һ��Ҫ��ʼ����
	MAGTRK 	tTrk;
	memset(tTrk.Flag,0,sizeof(tTrk.Flag));
	memset(tTrk.Len,0,sizeof(tTrk.Len));
	memset(tTrk.Trk,0,sizeof(tTrk.Trk));
	tTrk.Type = 0;//��ʼ��״̬
	API_SetTrkBuf(&tTrk);
#endif
		
	do
	{
		if(po_keys == NULL)
		{
			return -1 ; 
		}
		uret = API_WaitEvent(60*1000,EVENT_KEY, EVENT_NONE);
	    if(uret == EVENT_KEY)
		{
			API_GetKey(&tCode,&type);
			//printf("keyNum==[%d] type =[%x]   tCode==[%x]  \n" ,keyNum,type,tCode);
			if(type == KEY_EVENT_DOWN)
			{
			    if(tCode == K_OK )
				{
					if(keyNum < 1 ) 
					{
						return 0 ;
					}
					memcpy(po_keys , sKeybuff , keyNum);
					return keyNum; 
				}
				else if(pi_Only0_9 == TRUE)
				{
					if((tCode>=K_0 && tCode<=K_9 && (keyNum<10) ))
						sKeybuff[keyNum++]=tCode&0xff;
					else if((keyNum == 0 )&&(
						tCode ==RIGHT_PAGE ||tCode ==LEFT_PAGE||tCode == HEAD_PAGE
						||tCode ==NEXT_PAGE||tCode ==ESC)) //��Ӧȡ������ҳ��
					{
						po_keys[0] = tCode&0xff  ;return 1 ;
					}
				}
				else
				{
					if((tCode>=K_0&&tCode<=K_9)&& (keyNum<10)||tCode==K_STAR||tCode==K_POUND)
						sKeybuff[keyNum++]=tCode&0xff;
					else if((keyNum == 0 )&&(
						tCode ==RIGHT_PAGE ||tCode ==LEFT_PAGE||tCode == HEAD_PAGE
						||tCode ==NEXT_PAGE||tCode ==ESC)) //��Ӧȡ������ҳ��
					{
						po_keys[0] = tCode&0xff  ;return 1 ;
					}
				}
				continue ;
			}
			else
			{
				return -4 ; 
			}
		}
		else
		{
			return  -3 ; 
		}
	}while(1);
	return  result ;
}
int  SerialOpen()
{
	int result = 0;
	do
	{
		if(API_Serial_Open("/dev/ttySAC0" ,9600 ) != APP_SUCC)
		{
			WrongMsgAndWaitKey("���ڴ�ʧ��\n");
			result = -1 ;break;
		}		
	}while(0);
	return result ;
}
int SerialSendData(char *pi_SendData ,int pi_DataLen)
{
	int result = 0;
	do
	{
		if (API_Serial_Send(pi_SendData ,pi_DataLen ,60) != 0 )
		{
			WrongMsgAndWaitKey("��������ʧ��\n");
			result = -2 ;break;
		}
		
	}while(0);
	return result ;
}
int SerialRecvData(char *po_RecvData )
{
	int result = 0;
	do
	{
		if ((result = API_Serial_Receive(po_RecvData  ,60) ) < 0 )
		{
			WrongMsgAndWaitKey("��������ʧ��\n");
			result = -1 ;break;
		}
	}while(0);
	return result ;
}


