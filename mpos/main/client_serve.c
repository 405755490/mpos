#include "client_serve.h"

#ifdef  ONELEVELMPOS
static char * disptranshead_buf = NULL;
char*  OneGetAreaCode( char* pi_CodeNo)
{
	int i = 0  ;
	if(pi_CodeNo == NULL)
		return "";
	disptranshead_buf = malloc(20);
	if(disptranshead_buf == NULL)
	{
		return "";
	}
	memset(disptranshead_buf,0,20);
	readIniFile(ONEINITINFOMATION,pi_CodeNo,disptranshead_buf,&i,NULL);
	disptranshead_buf[i] = 0x00 ;
	return disptranshead_buf;	
}

	


int OneOperSet()
{
	int iPage = 1;	 
	do
	{	
		ClrScr("ĸPOS-����Ա����");
		if(1 == iPage%2)
		{
			SetContext(1 , "����Ա����", "",1,0 ,ALIGN_LEFT);
			SetContext(2 , "���ö���������Կ", "",1,0 ,ALIGN_LEFT);
			SetContext(3 , "��ʾR_TEKУ��ֵ", "",1,0 ,ALIGN_LEFT);
			SetContext(4 , "�޸ı���������", "",1,0 ,ALIGN_LEFT);
			SetContext(5 , "���ñ���IP��ַ", "",1,0 ,ALIGN_LEFT);
		}
		else
		{
			SetContext(6 , "���ü��ܻ�IP��ַ�˿�", "",1,0 ,ALIGN_LEFT);
			SetContext(7 , "������ܻ���Կ", "",1,0 ,ALIGN_LEFT);
			SetContext(8 , "���ؼ��ܻ���Կ", "",1,0 ,ALIGN_LEFT);
		}
		API_UI_Flush(NULL);
		switch (getkeycode(60))
		{
			case Key1: OneOperChangePwd();break; 		
			case Key2: OneSetTwoTransferPwd() ; break;
			case Key3: OneShowR_TEKChk();   break;
			case Key4: OneUpdateReserveName();  break;
			case Key5: OneSetLocalIP();  break;
			case Key6: OneSetServerIpAndPort(); break;
			case Key7: OneApplyKeyFromServer(); break;
			case Key8: OneDownKeyFromServer(); break;
			case ENTER:
			case LEFT_PAGE:
			case RIGHT_PAGE:
			case NEXT_PAGE:
			case HEAD_PAGE:
				iPage+=1 ; 
				break;
			case ESC :	
			case 0: 
				return FALSE;
			default : break;
		}
	}while(1);
}

int OneLeaderSet()
{
	int iPage = 1;	 
	do
	{	
		ClrScr("ĸPOS-�쵼����");
		if(1 == iPage%2)
		{
			SetContext(1 , "�쵼1����", "",1,0 ,ALIGN_LEFT);
			SetContext(2 , "�쵼1���ø�����RV1", "",1,0 ,ALIGN_LEFT);
			SetContext(3 , "�쵼2����", "",1,0 ,ALIGN_LEFT);
			SetContext(4 , "�쵼2���ø�����RV1", "",1,0 ,ALIGN_LEFT);
			SetContext(5 , "�쵼3����", "",1,0 ,ALIGN_LEFT);
		}
		else
			SetContext(6 , "�쵼3���ø�����RV1", "",1,0 ,ALIGN_LEFT);
		API_UI_Flush(NULL);
		switch (getkeycode(60))
		{
			case Key1: OneLeaderChangePwd(1);break;			
  			case Key2: OneLeaderSetRootKey(1);break;
			case Key3: OneLeaderChangePwd(2); break;
			case Key4: OneLeaderSetRootKey(2); break;
			case Key5: OneLeaderChangePwd(3);  break;
 			case Key6: OneLeaderSetRootKey(3); break;
			case ENTER:
			case LEFT_PAGE:
			case RIGHT_PAGE:
			case NEXT_PAGE:
			case HEAD_PAGE:
				iPage+=1 ; 
				break;
			case ESC :  
			case 0: 
				return FALSE;
			default : break;
		}
	}while(1);
}

	
int  OnePutKeyToTwoLevelPos()
{	
	int  ret = 0 ;int  ret1 = 0 ;
	int result = 0 ;
	int iPageNum = 1 ;
	char keys[20] = {0};
	char buf1[20] = {0};
	char notice1[50]={0};
	CLEAR(notice1) ;CLEAR(keys) ;
	
	if(file_isexist(ONEINITINFOMATION)	== 0 ) 
		OneInitInfoFlag();

	if( OneJudgeLeaderOldPwd("ĸPOS-����Կ������POS" ,0)	!= APP_SUCC )
		return APP_FAIL ;
	
	do
	{
		OneShowAreaCodeMenu(iPageNum);
		ret = GetUnionKeys( TRUE ,keys) ;
		if(ret < 0 )
		{
			return  ret ;
		}
		else if(ret == 2  ) 
		{
			ret1 = (keys[0]-'0')*10 + (keys[1] -'0');
			if( ret1 >50  || ret1 < 1)
			{
				WrongMsgAndWaitKey("���������Ų��Ϸ�\n����������");
				continue ;
			}
			else
			{
				keys[2] = 0x00 ;
				sprintf(notice1 ,"��������׼����[%s]\n������װ��Կ!" , OneGetAreaCode(keys));
				ShowSelectDialog("ĸPOS-����Կ������POS",notice1,
					"ȷ�ϼ���\"ȷ��\"��," ,"ȡ������\"ȡ��\"��");
				if (Confirm(60*3)!=APP_SUCC) 
						return APP_FAIL ;
				else
				{
					return  OnePutKeyToTwoLevelPosData(keys);
				}
			}
		}
		else if (ret == 1) 
		{
			if((keys[0] == RIGHT_PAGE||keys[0] ==NEXT_PAGE ))
  				{ iPageNum++; continue ;}
			else if(keys[0] == HEAD_PAGE||keys[0] == LEFT_PAGE)
				{ if(iPageNum == 1) iPageNum = 6 ; else  iPageNum--; continue ;}
			else if(keys[0] == ESC) 
				{ return APP_FAIL ;}
			else 
				{iPageNum = 1; WrongMsgAndWaitKey("��������\n����������");continue ;}
		}
		else 
		{
			WrongMsgAndWaitKey("��������\n����������");
			continue ;
		}
	}while(1);
	return  result ;
}

int OnePutKeyToTwoLevelPosData( char *pi_AreaCode)
{
	int result  = 0 ;
	int ret = 0  ,i = 0 ,ret1 = 0 ;
	char R_tekStr[50]={0};
	char B_tekStr[50]={0};
	MPOS_ONE_LEVEL_KEY Onelevelkey;
	CLEAR(B_tekStr);
	memset(&Onelevelkey,0,sizeof(MPOS_ONE_LEVEL_KEY));
	do
	{
		ret1 = OneGetR_TEK(R_tekStr);
		if( (ret1 !=APP_SUCC)  )
		{
			WrongMsgAndWaitKey("����ȷ���Ƿ������쵼����");
			result = -1 ;
			break;
		}
		ret = readIniFile(ONEKEYFILE ,"B_TEK" , B_tekStr, &i,"ERR");
	    if((ret != 0)  || memcmp(B_tekStr ,"ERR" , 3 ) == 0 )
		{
			WrongMsgAndWaitKey("��������B_TEK");
			result = -2 ;
			break;
		}
		else
		{	
			memset(Onelevelkey.r_tek , 0 ,sizeof(Onelevelkey.r_tek));
			memcpy(Onelevelkey.r_tek,R_tekStr,16);
			memcpy(Onelevelkey.Areacode, pi_AreaCode ,2);
			memset(Onelevelkey.AreacodeName ,0x20 ,sizeof(Onelevelkey.AreacodeName ));
			memcpy(Onelevelkey.AreacodeName , OneGetAreaCode(pi_AreaCode) ,strlen( OneGetAreaCode(pi_AreaCode)));			
			AsciiToBcd(Onelevelkey.b_tek,B_tekStr,32,0);
			API_TraceHex(1,"B_tekStr0-",Onelevelkey.b_tek,16);
			if ((ret = OneCalcPasskey(&Onelevelkey) )!= 0 )
			{
				result = -3 ;
				break;
			}
			OneSendKeyToTwoLevelPos(&Onelevelkey);
		}
	}while(0);
	return result ;
}

int OneCalcPasskey( MPOS_ONE_LEVEL_KEY *pi_Onelevelkey)
{
	int result = 0, ret = 0 , i = 0 ;
	char Passkey[ENUMPASSKEY_LEN]={0};
	char tmp[16]={0};
	do
	{
		ret = (pi_Onelevelkey->Areacode[0]-'0')*10 + (pi_Onelevelkey->Areacode[1] -'0');
		if( ret >50  || ret < 1)
		{
			WrongMsgAndWaitKey("���������Ų��Ϸ�\n����������");
			result = -1 ;break;
		}
		ret = OneLevelGetKey(Passkey , sizeof(Passkey) , ret-1);
		if(ret != 0 )
		{
			WrongMsgAndWaitKey("�������Ӽ��ܻ�������Կ");
			result = -2 ;break;
		}
		API_TraceHex(1,"��ȡ������������Կ��",Passkey,160);
		API_TraceHex(1,"R_tek===",pi_Onelevelkey->r_tek,16);
		undes(Passkey,pi_Onelevelkey->mingwenkey,pi_Onelevelkey->r_tek,160,16,NULL);
		API_TraceHex(1,"���������������Կ��",pi_Onelevelkey->mingwenkey,160);
		for(i = 0 ;i<10 ;i++ )
		{
			CLEAR(tmp);
			memcpy(tmp ,pi_Onelevelkey->mingwenkey+(i*16) ,16 );
			des(tmp,pi_Onelevelkey->miwenkey[i],pi_Onelevelkey->b_tek,16,16,NULL);
			API_TraceHex(1,"����Կ������",pi_Onelevelkey->miwenkey[i],16);
			des("\x00\x00\x00\x00\x00\x00\x00\x00" , pi_Onelevelkey->mingwenkeyChk[i],(unsigned char *)tmp , 8, 16, NULL);
			API_TraceHex(1,"����ԿУ��ֵ��",pi_Onelevelkey->mingwenkeyChk[i],8);
		}
	}while(0);
	return  result ;
	
	
}

int OneSendKeyToTwoLevelPos(MPOS_ONE_LEVEL_KEY *pi_Onelevelkey)
{
	
	char SendStr[300]={0};
	char RecvStr[10]={0};
	char tmp[50]={0};
	int i = 0 ,ret = 0 ,iOffsize = 0 ;
	AsciiToBcd(tmp,pi_Onelevelkey->Areacode,2,0);
	//ĸ POS���ͣ�  0x02 + LEN + CMD + GID + GNAME + GKEY + 0x03 + LRC 
	memcpy(SendStr , "\x02\x02\x51\x98" ,4);
	SendStr[4]  = tmp[0]  ;
	memcpy(SendStr+5 , pi_Onelevelkey->AreacodeName,8);
	iOffsize += 13;
	for(i= 0 ;i<10 ; i++)
	{
		memcpy(SendStr+iOffsize , pi_Onelevelkey->miwenkey[i],16);
		iOffsize += 16 ; 
		memcpy(SendStr+iOffsize , pi_Onelevelkey->mingwenkeyChk[i],8);
		iOffsize += 8; 
	}
	SendStr[iOffsize] =_CalcLRC(SendStr+1 , iOffsize-1);
	iOffsize +=1 ;
#ifdef  DEBUG
	posk_pkg_log(1 ,iOffsize,SendStr);
#endif	
	ret = SerialOpen();
	if(ret < 0 )
	{
		return ret ;
	}
	ret =  SerialSendData(SendStr ,iOffsize+1 );
	if(ret < 0 )
	{
		return ret ;
	}
	else
	{
		CLEAR(RecvStr);
		ret = SerialRecvData(RecvStr);
#ifdef  DEBUG
		posk_pkg_log(2 , ret,RecvStr);
#endif	
		if(ret < 0 )
		{
			WrongMsgAndWaitKey("���ն���POS����ʧ��\n");
			return ret ;
		}
		API_TraceHex(1,"���ն���POS����������",RecvStr,8);
		if(memcmp(RecvStr+4 ,"00" ,2) != 0)
		{
			WrongMsgAndWaitKey("����ʧ��\n");
			return  APP_FAIL;
		}
	}
	
}

int OneShowWaitDialog()
{
	
    time_t t;
    struct tm * tm;
	char show[50]={0};	
	ClrScr("ĸPOS��Կ����ϵͳ");	
	API_UI_PrintLine(2, FONT_SIZE_VERY_BIG, ALIGN_CENTER, "ͨ��֧��");
	do
	{
		CLEAR(show);
		time(&t);
		tm = localtime(&t);
		sprintf(show , "%04d-%02d-%02d %02d:%02d:%02d" ,tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday,tm->tm_hour,tm->tm_min,tm->tm_sec);
		API_UI_PrintLine(4, FONT_SIZE_NORMAL, ALIGN_CENTER, show );
		if (getkeycode(1)!= 0)
			return  0;
	}
	while(1);	
}

int OneLeaderChangePwd( int pi_iLeaderNo)
{
	int  ret = 0 ;int  ret1 = 0 ;
	char pwd[20] = {0};
	char buf1[20] = {0};
	char notice[50]={0};
	char notice1[50]={0};
	CLEAR(notice) ;
	CLEAR(notice1) ;
	sprintf(notice , "ĸPOS-�쵼%d����" , pi_iLeaderNo);
	sprintf(notice1 , "LeaderPwd%d" ,pi_iLeaderNo );
	if( OneJudgeLeaderOldPwd( notice ,pi_iLeaderNo)	!= APP_SUCC )
		return APP_FAIL ;
	else
	{
		CLEAR(buf1);CLEAR(pwd);
		ret = GetStr_limit_titleIME(notice,"������������:\n", FONT_SIZE_NORMAL, buf1,8,8,0,1);
		if(ret == APP_FAIL)
			return	 APP_FAIL;
		ret1 = GetStr_limit_titleIME(notice,"������һ��������:\n", FONT_SIZE_NORMAL, pwd,8,8,0,1);
		if(ret1 == APP_FAIL)
			return	 APP_FAIL;
		if( (ret == ret1) && (API_memcmp(buf1  ,pwd  , 8 ) == 0) )
		{
			ret = writeIniFile(ONEPARAM ,notice1 , pwd );
			if(ret == 0 )
				return	RightMsgAndWaitKey("�޸ĳɹ�\n");
			else
				return WrongMsgAndWaitKey("�����쵼����ʧ��\n");
		}
		else
			return	WrongMsgAndWaitKey("�����������벻һ��\n");
	}	
}


int OneSetServerIpAndPort()
{
	FILE *fp;
	int  i = 0 ;
	char key[100]={0};char buf1[50]={0};char buf2[50]={0};
	char buf11[50]={0};char buf22[50]={0};
	CLEAR(key) ;CLEAR(buf1) ;CLEAR(buf2) ;CLEAR(buf11) ;CLEAR(buf22) ;
	int ret = 0 ;
	if(file_isexist(ONEPARAM)  == 0 ) 
	{
		if((fp = fopen(ONEPARAM,"w+"))==NULL)    
			return APP_FAIL; 
	}
	if( OneJudgeLeaderOldPwd("ĸPOS-���ܻ�����" ,0) != APP_SUCC )
		return APP_FAIL ;		
	readIniFile(ONEPARAM,"ServerIP" ,buf1,&i,"1.1.1.1(Ĭ��)");
	readIniFile(ONEPARAM,"ServerPort" ,buf2,&i,"80(Ĭ��)");
	sprintf(buf11 ,"IP: %s" ,buf1);	
	sprintf(buf22 ,"�˿�: %s" ,buf2);
	do
	{
		ClrScr("ĸPOS-���ܻ�����");
		SetContext(1 , buf11, "",1,0 ,ALIGN_LEFT);
		SetContext(2 , buf22, "",1,0 ,ALIGN_LEFT);
		switch (getkeycode(60))
		{
			case Key1: OneSetServerIP();break; 		
			case Key2: OneSetServerPort() ; break;
			default: 
				break;
		}
		
	}while(0);	
	return APP_SUCC ;
}

int OneSetServerIP()
{
	return OneSetIP("ĸPOS-���ܻ�����" , "ServerIP" ,0 );
}

int OneSetLocalIP()
{
	return OneSetIP("ĸPOS-����IP����" , "LocalIP" ,1 );
}


int OneSetIP( char *pi_title , char *pi_NeedSaveFlagName ,int pi_NeedJudgePwd)
{
	FILE *fp;
	int  i = 0 ;
	int result = 0 ;
	char key[100]={0};char buf1[50]={0};
	CLEAR(key) ;CLEAR(buf1) ;
	int ret = 0 ;
	if(file_isexist(ONEPARAM)  == 0 ) 
	{
		if((fp = fopen(ONEPARAM,"w+"))==NULL)    
			return APP_FAIL; 
	}
	if( (pi_NeedJudgePwd == 1) && OneJudgeLeaderOldPwd(pi_title ,0) != APP_SUCC )
		return APP_FAIL ;
	do
	{
		ClrScr(pi_title);
		ret = API_GUI_Edit_GetInputIp("������IP:", FONT_SIZE_NORMAL, "��ȷ��������", FONT_SIZE_NORMAL, buf1, 15,  300*1000);
		if(ret  <1)
		{ 
			result = -1 ; break;
		}
		if( OneJudgeLegalIp(buf1 ,ret ) != APP_SUCC)
		{
			WrongMsgAndWaitKey("IP���벻�Ϸ�");
			result = -2 ; break;
		}
		else
		{
			writeIniFile(ONEPARAM,pi_NeedSaveFlagName,buf1);
			RightMsgAndWaitKey("IP���óɹ�");
			result = 0 ; break;
		}
	}while(0);
	return result ;	
}


int  OneSetServerPort()
{
	
	FILE *fp;
	int  i = 0 ;
	int result = 0 ;
	char key[100]={0};char buf1[50]={0};
	CLEAR(key) ;CLEAR(buf1) ;
	int ret = 0 ;
	if(file_isexist(ONEPARAM)  == 0 ) 
	{
		if((fp = fopen(ONEPARAM,"w+"))==NULL)    
			return APP_FAIL; 
	}
	do
	{
		ClrScr("ĸPOS-���ܻ�����");
		ret = API_GUI_Edit_GetInputIp("������˿�:", FONT_SIZE_NORMAL, "��ȷ��������", FONT_SIZE_NORMAL, buf1, 5,  300*1000);
		if(ret  <1)
		{ 
			result = -1 ; break;
		}
		else
		{
			writeIniFile(ONEPARAM,"ServerPort",buf1);
			RightMsgAndWaitKey("�˿����óɹ�");
			result = 0 ; break;
		}
	}while(0);
	return result ;	
}

int OneJudgeLegalIp( char *pi_IP  , int pi_len)
{
	
	char buf[17] ={0};
	int  k,i,j,flag=0;	
	if (pi_len < 0)
	{
		return APP_FAIL;
	}
	if ((pi_len<7)||(pi_len>15))
	{
		return APP_FAIL;
	}
	pi_IP[pi_len]=0;
	for(k=0,i=0;i<pi_len;i++)
	{
		if (pi_IP[i]=='.') k++;
	}
	if (k!=3) 
	{
		return APP_FAIL;
	}
	for(k=0,i=j=0;i<pi_len;i++)
	{
		if (pi_IP[i]=='.')
		{
			if (((i-j)<1)||((i-j)>3))
			{
				return APP_FAIL;
				break;
			}
			memset(buf,0,sizeof(buf));
			memcpy(buf,pi_IP+j,i-j);
			if ((atoi(buf)<0)||(atoi(buf)>255))
			{
				return APP_FAIL;
				break;
			}
			j=i+1;
			k++;
		}
	}//for
	if (k==3)
	{
		if (((pi_len-j)<1)||((pi_len-j)>3))
		{
			return APP_FAIL;
		}
		memset(buf,0,sizeof(buf));
		memcpy(buf,pi_IP+j,pi_len-j);
		if ((atoi(buf)<0)||(atoi(buf)>255))
		{
			return APP_FAIL;
		}
		flag=1;
	}
	return APP_SUCC ;
	
}

int OneInitInfoFlag()
{
	FILE *fp;
	int i = 0 ;
	char title[51][20]={ 
		"����" ,"�Ϻ�" ,"���" ,"����" ,"���" ,"����" ,"̨��" ,"�ӱ�" ,"ɽ��" ,"���ɹ�" ,
		"����" ,"����" ,"������" ,"����" ,"�㽭" ,"����" ,"����" ,"����" ,"ɽ��" ,"����" ,
		"����" ,"����" ,"�㶫" ,"����" ,"����" ,"�Ĵ�" ,"����" ,"����" ,"����" ,"����" ,
		"����" ,"����" ,"�ຣ" ,"�½�" ,"��������1" ,"��������2" ,"��������3" ,"��������4" ,"��������5" ,"��������6" ,
		"��������7" ,"��������8" ,"��������9" ,"��������10" ,"��������11" ,"��������12" ,"��������13" ,"��������14" ,"��������15" ,"��������16" ,
		};
	char value[5]={0};
	if((fp = fopen(ONEINITINFOMATION,"w+"))==NULL)    
			return APP_FAIL; 
	for( i =1 ;i<51 ; i++)
	{
		CLEAR(value) ;
		sprintf(value ,"%02d" ,i);
		writeIniFile(ONEINITINFOMATION,value,title[i-1]);
	}
	return APP_SUCC ;
}

int OneLeaderSetRootKey(int pi_iLeaderNo)
{	
	FILE *fp;
	int ret = 0 ;
	char key[50]={0};
	char buf1[50]={0};
	char notice[50]={0};
	char notice1[50]={0};
	char notice2[50]={0};
	CLEAR(notice2) ;
	CLEAR(notice) ;
	CLEAR(notice1) ;
	sprintf(notice , "ĸPOS-���ø�����RV%d" , pi_iLeaderNo);
	sprintf(notice1 , "RV%d" ,pi_iLeaderNo );
	sprintf(notice2 , "�����������RV%d,32�ַ�" , pi_iLeaderNo);	
	if(file_isexist(ONEKEYFILE)  == 0 ) 
	{
		if((fp = fopen(ONEKEYFILE,"w+"))==NULL)    
			return APP_FAIL; 
	}
	if( OneJudgeLeaderOldPwd(notice ,pi_iLeaderNo) != APP_SUCC )
		return APP_FAIL ;
	else
	{
		CLEAR(buf1) ;
		ret = GetStr_limit_titleIME(notice,notice2, FONT_SIZE_NORMAL, buf1,32,32,0,1);
		if(ret == APP_FAIL )
			return	APP_FAIL;
		else
		{
			CLEAR(key) ;CLEAR(key) ;
			AsciiToBcd(key,buf1,32,0);
			API_TraceHex(1,"����ķ�����",key,16);			
			des("\x00\x00\x00\x00\x00\x00\x00\x00" , (unsigned char *)notice2,(unsigned char *)key , 8, 16, NULL);
			API_TraceHex(1,"����ķ�����У��ֵ��",notice2,8);
			CLEAR(key) ;
			BcdToAscii(key ,notice2 ,8 , 0);
			CLEAR(notice2) ;
			sprintf(notice2 , "CheckValue��%s" , key);
			CLEAR(key) ;
			sprintf(key , "������RV%d���óɹ�" , pi_iLeaderNo);
			ret = writeIniFile(ONEKEYFILE ,notice1 , buf1 );
			if(ret != 0 ) 
				return WrongMsgAndWaitKey("���������ʧ��\n");
			ShowSelectDialog(notice,key,notice2,NULL);
			getkeycode(10);
			return APP_SUCC ;
		}		
	}
}


int OneJudgeLeaderOldPwd(char*pi_title , int pi_iLeaderNo)
{

#ifdef  DEBUG
	return APP_SUCC;
#endif	
	FILE *fp;
	int  ret = 0 ;int  ret1 = 0 ;
	char buf1[20] = {0};
	char pwd_old[20] = {0};
	char pwd_init[20] = {0};
	char notice1[50]={0};
	CLEAR(pwd_old) ;
	CLEAR(notice1) ;
	CLEAR(pwd_init) ;
	if(pi_iLeaderNo  == 0)
		sprintf(notice1 , "OperPwd%d" ,pi_iLeaderNo );	
	else
		sprintf(notice1 , "LeaderPwd%d" ,pi_iLeaderNo );	
	ret = GetStr_limit_titleIME(pi_title,"����������:\n", FONT_SIZE_NORMAL, buf1,0,8,0,1);
	if(ret == APP_FAIL)
		return	 APP_FAIL;
    if( pi_iLeaderNo  == 0)        API_memcpy(pwd_init,"66666666",8);
	else if( pi_iLeaderNo  == 1)   API_memcpy(pwd_init,"11111111",8);
	else if( pi_iLeaderNo  == 2)   API_memcpy(pwd_init,"22222222",8);
	else if( pi_iLeaderNo  == 3)   API_memcpy(pwd_init,"33333333",8);
	else return  APP_FAIL;	
	if(file_isexist(ONEPARAM)  == 0 ) 
	{
		if((fp = fopen(ONEPARAM,"w+"))==NULL)    
			return APP_FAIL; 
	}
	if(ret1 == FALSE)
		API_memcpy(pwd_old,pwd_init,8);
	else
		readIniFile(ONEPARAM,notice1,pwd_old,&ret,pwd_init) ;
	if( API_memcmp(buf1  ,pwd_old  , 8 )!= 0 )
		return WrongMsgAndWaitKey("�����������\n");
	else 
		return  APP_SUCC ;
}


int OneOperChangePwd()
{
	int  ret = 0 ;int  ret1 = 0 ;
	char pwd[20] = {0};
	char buf1[20] = {0};
	char notice1[50]={0};
	CLEAR(notice1) ;
	sprintf(notice1 , "OperPwd%d" ,0 );
	if( OneJudgeLeaderOldPwd("����Ա����" ,0)	!= APP_SUCC )
		return APP_FAIL ;
	else
	{
		CLEAR(buf1);CLEAR(pwd);
		ret = GetStr_limit_titleIME("����Ա����","������������:\n", FONT_SIZE_NORMAL, buf1,8,8,0,1);
		if(ret == APP_FAIL)
			return	 APP_FAIL;
		ret1 = GetStr_limit_titleIME("����Ա����","������һ��������:\n", FONT_SIZE_NORMAL, pwd,8,8,0,1);
		if(ret1 == APP_FAIL)
			return	 APP_FAIL;
		if( (ret == ret1) && (API_memcmp(buf1  ,pwd  , 8 ) == 0) )
		{
			ret = writeIniFile(ONEPARAM ,notice1 , pwd );
			if(ret == 0 )
				return	RightMsgAndWaitKey("�޸ĳɹ�\n");
			else
				return WrongMsgAndWaitKey("�������Ա����ʧ��\n");
		}
		else
			return	WrongMsgAndWaitKey("�����������벻һ��\n");
	}	
}

int OneSetTwoTransferPwd()
{
	FILE *fp;
	char key[50]={0};
	char buf1[50]={0};
	char notice2[50]={0};
	CLEAR(notice2) ;
	int ret = 0 ;
	if(file_isexist(ONEKEYFILE)  == 0 ) 
	{
		if((fp = fopen(ONEKEYFILE,"w+"))==NULL)    
			return APP_FAIL; 
	}
	if( OneJudgeLeaderOldPwd("ĸPOS-���ô�����Կ" ,0) != APP_SUCC )
		return APP_FAIL ;
	else
	{
		
		CLEAR(buf1) ;
		ret = GetStr_limit_titleIME("ĸPOS-���ô�����Կ",
			"���������������ԿB_TEK,\n32�ַ�", FONT_SIZE_NORMAL, buf1,32,32,0,1);
		if(ret == APP_FAIL )
			return	APP_FAIL;
		else
		{
			CLEAR(key) ;
			AsciiToBcd(key,buf1,32,0);
			API_TraceHex(1,"����ķ�����",key,16);			
			des("\x00\x00\x00\x00\x00\x00\x00\x00" , (unsigned char *)notice2,(unsigned char *)key , 8, 16, NULL);
			API_TraceHex(1,"����ķ�����У��ֵ��",notice2,8);
			CLEAR(key);
			BcdToAscii(key ,notice2 ,8 , 0);
			CLEAR(notice2) ;
			sprintf(notice2 , "CheckValue��%s" , key);
			if(file_isexist(ONEKEYFILE)  == 0 ) 
			{
				if((fp = fopen(ONEKEYFILE,"w+"))==NULL)
				{
					WrongMsgAndWaitKey("���ļ�ʧ��");
					return	APP_FAIL;
				}
			}
			ShowSelectDialog("ĸPOS-���ô�����Կ","������ԿB_TEK",notice2,NULL);
			if(Confirm(60*5)==APP_SUCC)
			{
				ret = writeIniFile(ONEKEYFILE ,"B_TEK" , buf1 );
				if(ret != 0 ) 
				{
					WrongMsgAndWaitKey("����B_TEKʧ��\n");
					return	APP_FAIL;
				}
				else
					return APP_SUCC;
			}
			return APP_FAIL ;
		}
	}
}


int OneShowR_TEKChk()
{	
	int result = 0 ;
	char notice2[50]={0};char key[50]={0};
	char buf1[50]={0};
	CLEAR(key) ;
	CLEAR(buf1) ;CLEAR(notice2) ;
	if( OneJudgeLeaderOldPwd("ĸPOS-R_TEKУ��ֵ" ,0) != APP_SUCC )
		return APP_FAIL ;
	do
	{
		if ((result =OneGetR_TEK(key)) != APP_SUCC )
		{
			WrongMsgAndWaitKey("��鿴�Ƿ������쵼����");
			API_Trace(1,"OneGetR_TEK==result==[%d]",result);
			return result;
		}
		API_TraceHex(1,"R_TEK�������ķ�����",key,16);	
		des("\x00\x00\x00\x00\x00\x00\x00\x00" , (unsigned char *)notice2,(unsigned char *)key , 8, 16, NULL);
		API_TraceHex(1,"����ķ�����У��ֵ��",notice2,8);
		CLEAR(buf1) ;
		BcdToAscii(buf1 ,notice2 ,8 , 0);
		CLEAR(notice2) ;
		sprintf(notice2 , "%s" , buf1);	
		ShowSelectDialog("ĸPOS-R_TEKУ��ֵ","R_TEK��У��ֵ��",notice2,NULL);
		getkeycode(10);
		return APP_SUCC ;
		
	}while(0);
	return APP_SUCC ;
}

int OneGetR_TEK( char *po_R_tekStr)
{
	FILE *fp;
	int  i = 0 ;
	int result = 0 ;char key[50]={0};
	char buf1[50]={0};char buf2[50]={0};char buf3[50]={0};
	CLEAR(buf1) ;CLEAR(buf2) ;CLEAR(buf3) ;
	CLEAR(key) ;
	do
	{
		if(po_R_tekStr == NULL)
		{
			result = -5 ; break;
		}
		if(file_isexist(ONEKEYFILE)  == 0 ) 
		{
			result = -1 ; break;
		}	
		if( readIniFile(ONEKEYFILE,"RV1",buf1,&i,"ERR") != 0  || i < 5)
		{
			result = -2 ; break;
		}
		AsciiToBcd(key,buf1,32,0);CLEAR(buf1) ;
		if( readIniFile(ONEKEYFILE,"RV2",buf1,&i,"ERR") != 0 || i < 5 )
		{
			result = -3 ; break;
		}
		AsciiToBcd(buf2,buf1,32,0);CLEAR(buf1) ;
		if( readIniFile(ONEKEYFILE,"RV3",buf1,&i,"ERR") != 0  || i < 5)
		{
			result = -4 ; break;
		}
		AsciiToBcd(buf3,buf1,32,0);
		for(i=0 ;i<16 ;i++ )
		{
			key[i] = key[i] ^buf2[i]^buf3[i] ;
		}
		API_TraceHex(1,"R_TEK�������ķ�����",key,16);	
		memcpy(po_R_tekStr ,key ,16 );
		return APP_SUCC ;		
	}while(0);
	return  result ;	
}


int OneUpdateReserveName()
{
	FILE *fp;
	int  i = 0 ;
	int result = 0 ;
	char key[50]={0};char notice2[50]={0};
	char buf1[50]={0};char buf2[50]={0};char buf3[50]={0};
	CLEAR(key) ;CLEAR(buf1) ;CLEAR(buf2) ;CLEAR(buf3) ;CLEAR(notice2) ;
	int ret = 0 ;
	if( OneJudgeLeaderOldPwd("ĸPOS-�޸ı���������" ,0) != APP_SUCC )
		return APP_FAIL ;
	do
	{
		if(file_isexist(ONEINITINFOMATION)  == 0 ) 
			OneInitInfoFlag();
		
		ret = GetStr_limit_titleIME("ĸPOS-�޸ı���������","�����뱣�������:\n", FONT_SIZE_NORMAL, buf1,2,2,0,1);
		if(ret == APP_FAIL)
		{ 
				result = -1 ; break;
		}
		readIniFile(ONEINITINFOMATION,buf1 ,key,&i,NULL);
		if(API_memcmp(key,"����",4) !=0)
		{
			ShowSelectDialog("ĸPOS-�޸ı���������",NULL,"����ı�Ų��Ǳ�����,\n�������޸�!",NULL);
			getkeycode(60);result = -2 ; break;
		}
		else
		{
			sprintf(buf2 , "Ϊ%s���������µĺ�������,\nֻ���޸�1��!" , buf1);
			ClrScr("ĸPOS-�޸ı���������");
			ret = API_GUI_Edit_GetInputIME(buf2, FONT_SIZE_VERY_VERY_SMALL, "��ȷ��������", FONT_SIZE_NORMAL, buf3, 30, 300 * 1000 );
			if (ret < 1 ) 
			{ 
					result = -3 ; break;
			}
			else
			{	
				CLEAR(buf2) ;
				sprintf(buf2 , "Ϊ%s�������Ƹ�Ϊ%s,\nֻ���޸�1��,������!" , buf1 ,buf3);
				ShowSelectDialog("ĸPOS-�޸ı���������",NULL,buf2,"\nȷ��/ȡ��");
				if (Confirm(60*3)!=APP_SUCC) 
				{ 
						result = -4 ; break;
				}
				else
				{
					writeIniFile(ONEINITINFOMATION,buf1,buf3);
					CLEAR(buf2) ;
					sprintf(buf2 , "��%s�������Ƹ�Ϊ%s�ɹ�!" , buf1 ,buf3);
					ShowSelectDialog("ĸPOS-�޸ı���������",NULL,buf2,NULL);
					getkeycode(10);
					result = 0 ; break;
				}
			}
				
		}
	}while(0) ;
	return result ;
}

int OneDownKeyFromServer()
{
	
	int i = 0 ,ret = 0,result = 0 ;
	int BeginIndex =0  , EndIndex = 0 ;
	char ciphertextkey[20]={0};
	char plaintextkey[20]={0};
	char chk[10]={0};
	char chk1[50]={0};
	char sendstr[100]={0};
	char recvstr[100]={0};
	char Serverip[20] = {0};
	char Serverport[10] = {0};
	char key[50]={0};
	char tmp[100]={0};
	do
	{
		if ((ret =OneGetR_TEK(key)) != APP_SUCC )
		{
			API_Trace(1,"OneGetR_TEK==result==[%d]",ret);
			WrongMsgAndWaitKey("��鿴�Ƿ������쵼����");
			return ret;
		}
		if(file_isexist(ONEPARAM)  == 0 ) 
		{
			result = -1 ;break;
		}
		readIniFile(ONEPARAM,"ServerIP",Serverip,&i,"ERR");
		if((i==3)&&(memcmp(Serverip ,"ERR" ,3) == 0))
		{
			WrongMsgAndWaitKey("�������ü��ܻ�IP");
			result = -4 ;break;
		}
		readIniFile(ONEPARAM,"ServerPort",Serverport,&i,"ERR");
		if((i==3)&&(memcmp(Serverport ,"ERR" ,3) == 0))
		{
			WrongMsgAndWaitKey("�������ü��ܻ��˿�");
			result = -4 ;break;
		}
		
		if(Dial( Serverip , atoi(Serverport)) != APP_SUCC)
		{         
			result = -2 ;break;	
		}
		if(OneShowKeyNoSelect("ĸPOS-���ؼ��ܻ���Կ" , &BeginIndex, &EndIndex)!= APP_SUCC)
		{
			result = -7 ;break; 
		}
		for(i =BeginIndex  ;i <EndIndex+1 ; i++)
		{
			//   1���ؼ��ܻ���Կ
			CLEAR(tmp);
			sprintf(tmp, "���ڴӼ��ܻ����ص�[%d]��\n��Կ,���Ժ�....." , i);
			ShowSelectDialog("ĸPOS-���ؼ��ܻ���Կ",NULL,tmp,NULL);
			result = 0 ;
			CLEAR(sendstr);
			sendstr[0] = 0x31 ;
			sendstr[1] = (i>>8)&0xff; ;
			sendstr[2] = i%256;
			ret=APP_Send("���ؼ��ܻ���Կ",(u8*)sendstr,3,60);
			API_Trace(0, "�������ݰ����ret = [%d]", ret);
			if( Receive(recvstr) < 1 )
			{
				result = -3 ;break;	
			}
			else
			{				
				CLEAR(chk);//����8���ֽڵ�У��ֵ
				CLEAR(ciphertextkey);
				memcpy(ciphertextkey, recvstr  , 16);
				API_TraceHex(1,"����Կ������",ciphertextkey,16);
				memcpy(chk, recvstr + 16 , 8);
				API_TraceHex(1,"����ԿУ��ֵ��",chk,8);
			}
			//  2 ������ܻ�ת����
			CLEAR(sendstr);
			memcpy(sendstr , "\x05\x52\x10\x00\x00" ,5);
			memcpy(sendstr+5 , ciphertextkey ,16);
			ret=APP_Send("���ؼ��ܻ���Կ",(u8*)sendstr,21,60);
			API_Trace(0, "�������ݰ����ret = [%d]", ret);
			if( Receive(recvstr) < 1 )
			{
				result = -4 ;break;	
			}
			else
			{				
				CLEAR(ciphertextkey);
				CLEAR(plaintextkey);CLEAR(chk1);
				memcpy(ciphertextkey, recvstr  , 16);
				API_TraceHex(1,"��ת���ܡ�����Կ������",ciphertextkey,16);
				des(ciphertextkey,plaintextkey, key,16,16,NULL);
				API_TraceHex(1,"����Կ������",plaintextkey,16);
				des("\x00\x00\x00\x00\x00\x00\x00\x00" , (unsigned char *)chk1,(unsigned char *)plaintextkey , 8, 16, NULL);
				API_TraceHex(1,"��������Կ��У��ֵ��",chk1,8);
				if( API_memcmp(chk1,chk,8)  != 0 )
				{
					WrongMsgAndWaitKey("����ԿУ��ֵ��ƥ��\n");
					result = -5 ;break;	
				}
				else
				{
					if(OneLevelSaveKey(ciphertextkey , i-1 ) != APP_SUCC )
					result = -6 ;break;	
				}
			}
		}
		if(result == 0)
		{
			ShowSelectDialog("ĸPOS-���ؼ��ܻ���Կ","����ȫ���ն�����Կ�ɹ�",NULL,NULL);
			getkeycode(10);
		}
	}while(0);
	return  result ;
}



/********************************************************************************
*	�������ƣ�                                                                   
*	��������:                                                                    
*	�޸�����:    2016/10/10--11:44:45                                       
*	���������                                                                   
*	���������                                                                   
*	����ֵ��                                                                     
*	���ߣ�       Undefined                                                       
*******************************************************************************/
int OneLevelPos()
{	
	char Key=0;
	while(1)
	{
		OneShowWaitDialog();
		do
		{	
			ClrScr("ĸPOS��Կ����ϵͳ");
			SetContext(1 , "�쵼����", "",1,0 ,ALIGN_LEFT);
			SetContext(2 , "����Ա����", "",1,0 ,ALIGN_LEFT);
			SetContext(3 , "��װ������Կ����ԿPOS", "",1,0 ,ALIGN_LEFT);
#ifdef DEBUG
			SetContext(4 , "���Թ���", "",1,0 ,ALIGN_LEFT);
#endif
			API_UI_Flush(NULL);
			Key=getkeycode(60*30);
			switch (Key)
			{
				case Key1: 
					OneLeaderSet();
					break;			
				case Key2: 
					OneOperSet();
					break;
				case Key3: 
				    OnePutKeyToTwoLevelPos();
					break;	
#ifdef DEBUG
				case Key4:
					test();
					break;
#endif
				default : break;
			}
		}while(0);
	}
}

int OneLevelSaveKey(char *pi_CiphertextKey ,int pi_KeyNum)
{
	FILE *fp;
	int result = 0 ;
	int Filesize = 0 ;
	do
	{
		if(file_isexist(ONELEVELKEY)  == 0 ) 
		{
			if((fp = fopen(ONELEVELKEY,"w+"))==NULL)	 
			{	result = -1 ;break; }
		}
		if( AddDataToFile(ONELEVELKEY ,pi_CiphertextKey , 16 ,pi_KeyNum )!= 0 )
		{   result = -3 ;break; };
	}while(0);
	return result ;
}

int OneLevelGetKey(char *po_CiphertextKey , int pi_CiphertextKey_len ,int pi_BeginNum )
{
	FILE *fp;
	int result = 0 ;
	int Filesize = 0 ;
	do
	{
		if(po_CiphertextKey ==NULL  )
		{
			result = -5 ;break;
		}
		else if(pi_BeginNum < 0 || pi_BeginNum > 50)
		{
			result = -6 ;break;
		}
		else if( pi_CiphertextKey_len < (16*10))
		{
			result = -7 ;break;
		}
		if(file_isexist(ONELEVELKEY)  == 0 ) 
		{
			if((fp = fopen(ONELEVELKEY,"w+"))==NULL)	 
			{	result = -1 ;break; }
		}
		if( ReadDataFromFile(ONELEVELKEY ,po_CiphertextKey , 16 ,10 , pi_BeginNum)!= 0 )
		{	result = -3 ;break; };
	}while(0);
	return result ;
}

int OneShowKeyNoSelect(char*pi_tile,  int *po_BeginIndex, int *po_EndIndex)
{
	int result = APP_SUCC,ret = 0  ;
	char buf[10]={0};
	char beginindex[100]={0};
	char endindex[100]={0};
	*po_BeginIndex = 1 ;
	*po_EndIndex = 500 ;
	do
	{
		sprintf(beginindex , "���ܻ���Կ��ʼ����%03d" ,*po_BeginIndex  );
		sprintf(endindex , "���ܻ���Կ��������%03d" ,*po_EndIndex  );
		ShowSelectDialog(pi_tile,beginindex,endindex,"��ȷ�ϼ�����...");
		switch(getkeycode(60*30))
		{
			case Key1: 
			{
				while(1)
				{
					ClrScr(pi_tile);
					ret = API_GUI_Edit_GetInputNum("������Կ��ʼ����", FONT_SIZE_NORMAL, "����밴�����", FONT_SIZE_NORMAL, buf, 3, 60* 1000);
					if ((ret<0))
					{
						break;
					}
					else
					{
						*po_BeginIndex = atoi(buf);
						break;
					}
				}
				
			}
			continue;
			case Key2: 
			{
				while(1)
				{
					ClrScr(pi_tile);
					ret = API_GUI_Edit_GetInputNum("������Կ��������", FONT_SIZE_NORMAL, "����밴�����", FONT_SIZE_NORMAL, buf, 3, 60* 1000);
					if ((ret<0))
					{
						break;
					}
					else
					{
						*po_EndIndex = atoi(buf);
						break;
					}
				}
				
			}
			continue;
			case ENTER: 
				{ 	
					if(*po_BeginIndex  >  *po_EndIndex)
					{
						WrongMsgAndWaitKey("��ʼ��������С�ڽ�������");
						continue;
					}
					result = APP_SUCC;
					return result ;
				}
		    case ESC: 
				{ result = -2 ;return result ;}
			default : continue;
			
		}
	}while(1);
	return result ;
}

#define  SEND_TEST "003C600003000060310001100108000020000000C00012000003313030303031363138383032313030313032313031363200110000000100300003303120"
int OneApplyKeyFromServer()
{
	int i = 0 ,ret = 0,result = 0 ;
	int BeginIndex,  EndIndex=0 ;
	char sendstr[200]={0};
	char recvstr[500]={0};
	char Serverip[20] = {0};
	char Serverport[10] = {0 };
	do
	{
		if(file_isexist(ONEPARAM)  == 0 ) 
		{
			WrongMsgAndWaitKey("ȱ�ٱ������IP���˿�\n");
			result = -1 ;break;
		}
		readIniFile(ONEPARAM,"ServerIP",Serverip,&i,"ERR");
		if((i==3)&&(memcmp(Serverip ,"ERR" ,3) == 0))
		{
			WrongMsgAndWaitKey("�������ü��ܻ�IP");
			result = -4 ;break;
		}
		readIniFile(ONEPARAM,"ServerPort",Serverport,&i,"ERR");
		if((i==3)&&(memcmp(Serverport ,"ERR" ,3) == 0))
		{
			WrongMsgAndWaitKey("�������ü��ܻ��˿�");
			result = -4 ;break;
		}
#ifdef DEBUG
		if(Dial( "58.246.226.173" , 40004) != APP_SUCC)
		{         
			result = -2 ;break;	
		}
		if(OneShowKeyNoSelect("ĸPOS-������ܻ���Կ" , &BeginIndex, &EndIndex)!= APP_SUCC)
		{
			result = -7 ;break;	
		}
		CLEAR(sendstr);
		AsciiToBcd(sendstr,SEND_TEST,strlen(SEND_TEST),0);
		API_Trace(1, "%s - %d��%d����%d����%d��", __FILE__, __LINE__,strlen(SEND_TEST),BeginIndex, EndIndex);
		ret=APP_Send("������ܻ�������Կ",(u8*)sendstr,(strlen(SEND_TEST)+1)/2,60);
		API_Trace(0, "�������ݰ����ret = [%d]", ret);
		if(  i= Receive(recvstr) < 0 )
		{
			result = -3 ;break; 
		}
		API_TraceHex(1,"��������",recvstr,i);
		ShowSelectDialog("ĸPOS-������ܻ���Կ",NULL,"����500���ն�����Կ�ɹ�",NULL);
		getkeycode(10);
#else 
		if(Dial( Serverip , atoi(Serverport)) != APP_SUCC)
		{         
			result = -2 ;break;	
		}
		if(OneShowKeyNoSelect("ĸPOS-������ܻ���Կ" , &BeginIndex, &EndIndex)!= APP_SUCC)
		{
			result = -7 ;break;	
		}
		for(i =BeginIndex  ;i <EndIndex+1 ; i++)
		{
			CLEAR(sendstr);
			sendstr[0] = 0x11 ;
			sendstr[1] = (i>>8)&0xff; ;
			sendstr[2] = i%256;
			ret=APP_Send("������ܻ�������Կ",(u8*)sendstr,3,60);
			API_Trace(0, "�������ݰ����ret = [%d]", ret);
			if( Receive(recvstr) < 0 )
			{
				result = -3 ;break;	
			}
			//���뱣������
		}
		if(result == 0)
		{
			ShowSelectDialog("ĸPOS-������ܻ���Կ",NULL,"����ȫ���ն�����Կ�ɹ�",NULL);
			getkeycode(10);
		}
#endif
	}while(0);
	return  result ;
}
void  OneShowAreaCodeMenu( int pi_iPageNum)
{
	
	ClrScr("ĸPOS-����Կ������POS");
	char tmp1[100]={0};
	char tmp2[100]={0};
	char tmp3[100]={0};
	CLEAR(tmp1);CLEAR(tmp2);CLEAR(tmp3);
	Lcd_printf("%s\n", "������λ��ź�ȷ��ѡ��:");
	if(pi_iPageNum % 6 == 1)
	{
		Lcd_printf("%s\n", "  01���� 02�Ϻ� 03���");
		Lcd_printf("%s\n", "  04���� 05��� 06����");
		Lcd_printf("%s\n", "  07̨�� 08�ӱ� 09ɽ��");
		Lcd_printf("%s\n", "  10���ɹ� 11���� 12����");
	}
	else if(pi_iPageNum % 6 == 2)
	{		
		Lcd_printf("%s\n", "  13������ 14���� 15�㽭");
		Lcd_printf("%s\n", "  16���� 17���� 18����");
		Lcd_printf("%s\n", "  19ɽ�� 20���� 21����");
		Lcd_printf("%s\n", "  22���� 23�㶫 24����");
	}
	else if(pi_iPageNum % 6 == 3)
	{		
		Lcd_printf("%s\n", "  25���� 26�Ĵ� 27����");
		Lcd_printf("%s\n", "  28���� 29���� 30����");
		Lcd_printf("%s\n", "  31���� 32���� 33�ຣ");
		Lcd_printf("%s\n", "  34�½� ");
	}
	else if(pi_iPageNum % 6 == 4)
	{		
		sprintf(tmp1,"  35%s  36%s" ,OneGetAreaCode("35") , OneGetAreaCode("36"));
		sprintf(tmp2,"  37%s  38%s" ,OneGetAreaCode("37") , OneGetAreaCode("38"));
		sprintf(tmp3,"  39%s  40%s" ,OneGetAreaCode("39") , OneGetAreaCode("40"));
		Lcd_printf("%s\n", tmp1);
		Lcd_printf("%s\n", tmp2);
		Lcd_printf("%s\n", tmp3);
	}
	else if(pi_iPageNum % 6 == 5)
	{		
		sprintf(tmp1,"  41%s  42%s" ,OneGetAreaCode("41") , OneGetAreaCode("42"));
		sprintf(tmp2,"  43%s 44%s" ,OneGetAreaCode("43") , OneGetAreaCode("44"));
		sprintf(tmp3,"  45%s 46%s" ,OneGetAreaCode("45") , OneGetAreaCode("46"));
		Lcd_printf("%s\n", tmp1);
		Lcd_printf("%s\n", tmp2);
		Lcd_printf("%s\n", tmp3);
	}
	else if(pi_iPageNum % 6 == 0)
	{		
		sprintf(tmp1," 47%s 48%s" ,OneGetAreaCode("47") , OneGetAreaCode("48"));
		sprintf(tmp2," 49%s 50%s" ,OneGetAreaCode("49") , OneGetAreaCode("50"));
		Lcd_printf("\n%s\n", tmp1);
		Lcd_printf("%s\n", tmp2);
	}
}
#ifdef DEBUG
int test()
{
	int result ;
	char tmp[200]={0};
	result =OneLevelSaveKey("\x08\x02\x4F\xCF\x81\x1D\xA6\x72\x08\x02\x4F\xCF\x81\x1D\xA6\x72" ,0);
	result =OneLevelSaveKey("\x0F\x8A\xDF\xFB\x11\xDC\x27\x84\x0F\x8A\xDF\xFB\x11\xDC\x27\x84" ,1);
	result =OneLevelSaveKey("\x08\x02\x4F\xCF\x81\x1D\xA6\x72\x08\x02\x4F\xCF\x81\x1D\xA6\x72" ,2);
	result =OneLevelSaveKey("\x0F\x8A\xDF\xFB\x11\xDC\x27\x84\x0F\x8A\xDF\xFB\x11\xDC\x27\x84" ,3);
	result =OneLevelSaveKey("\x08\x02\x4F\xCF\x81\x1D\xA6\x72\x08\x02\x4F\xCF\x81\x1D\xA6\x72" ,4);
	result =OneLevelSaveKey("\x0F\x8A\xDF\xFB\x11\xDC\x27\x84\x0F\x8A\xDF\xFB\x11\xDC\x27\x84" ,5);
	result =OneLevelSaveKey("\x08\x02\x4F\xCF\x81\x1D\xA6\x72\x08\x02\x4F\xCF\x81\x1D\xA6\x72" ,6);
	result =OneLevelSaveKey("\x0F\x8A\xDF\xFB\x11\xDC\x27\x84\x0F\x8A\xDF\xFB\x11\xDC\x27\x84" ,7);
	result =OneLevelSaveKey("\x08\x02\x4F\xCF\x81\x1D\xA6\x72\x08\x02\x4F\xCF\x81\x1D\xA6\x72" ,8);
	result =OneLevelSaveKey("\x0F\x8A\xDF\xFB\x11\xDC\x27\x84\x0F\x8A\xDF\xFB\x11\xDC\x27\x84" ,9);
	result =OneLevelSaveKey("\x08\x02\x4F\xCF\x81\x1D\xA6\x72\x08\x02\x4F\xCF\x81\x1D\xA6\x72" ,10);
	OneLevelGetKey(tmp , sizeof(tmp) , 0);
	API_TraceHex(1,"��ȡ��������Կ��",tmp,160);
	return 0 ;
}
#endif


#endif
