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
		ClrScr("母POS-操作员设置");
		if(1 == iPage%2)
		{
			SetContext(1 , "操作员改密", "",1,0 ,ALIGN_LEFT);
			SetContext(2 , "设置二级传输密钥", "",1,0 ,ALIGN_LEFT);
			SetContext(3 , "显示R_TEK校验值", "",1,0 ,ALIGN_LEFT);
			SetContext(4 , "修改保留区名字", "",1,0 ,ALIGN_LEFT);
			SetContext(5 , "设置本机IP地址", "",1,0 ,ALIGN_LEFT);
		}
		else
		{
			SetContext(6 , "设置加密机IP地址端口", "",1,0 ,ALIGN_LEFT);
			SetContext(7 , "申请加密机密钥", "",1,0 ,ALIGN_LEFT);
			SetContext(8 , "下载加密机密钥", "",1,0 ,ALIGN_LEFT);
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
		ClrScr("母POS-领导设置");
		if(1 == iPage%2)
		{
			SetContext(1 , "领导1改密", "",1,0 ,ALIGN_LEFT);
			SetContext(2 , "领导1设置根分量RV1", "",1,0 ,ALIGN_LEFT);
			SetContext(3 , "领导2改密", "",1,0 ,ALIGN_LEFT);
			SetContext(4 , "领导2设置根分量RV1", "",1,0 ,ALIGN_LEFT);
			SetContext(5 , "领导3改密", "",1,0 ,ALIGN_LEFT);
		}
		else
			SetContext(6 , "领导3设置根分量RV1", "",1,0 ,ALIGN_LEFT);
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

	if( OneJudgeLeaderOldPwd("母POS-灌密钥到二级POS" ,0)	!= APP_SUCC )
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
				WrongMsgAndWaitKey("您输入的序号不合法\n请重新输入");
				continue ;
			}
			else
			{
				keys[2] = 0x00 ;
				sprintf(notice1 ,"您现在正准备给[%s]\n地区灌装密钥!" , OneGetAreaCode(keys));
				ShowSelectDialog("母POS-灌密钥到二级POS",notice1,
					"确认键按\"确认\"键," ,"取消键按\"取消\"键");
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
				{iPageNum = 1; WrongMsgAndWaitKey("输入有误\n请重新输入");continue ;}
		}
		else 
		{
			WrongMsgAndWaitKey("输入有误\n请重新输入");
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
			WrongMsgAndWaitKey("请先确认是否设置领导分量");
			result = -1 ;
			break;
		}
		ret = readIniFile(ONEKEYFILE ,"B_TEK" , B_tekStr, &i,"ERR");
	    if((ret != 0)  || memcmp(B_tekStr ,"ERR" , 3 ) == 0 )
		{
			WrongMsgAndWaitKey("请先设置B_TEK");
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
			WrongMsgAndWaitKey("您输入的序号不合法\n请重新输入");
			result = -1 ;break;
		}
		ret = OneLevelGetKey(Passkey , sizeof(Passkey) , ret-1);
		if(ret != 0 )
		{
			WrongMsgAndWaitKey("请先连接加密机下载密钥");
			result = -2 ;break;
		}
		API_TraceHex(1,"读取出来的密文密钥是",Passkey,160);
		API_TraceHex(1,"R_tek===",pi_Onelevelkey->r_tek,16);
		undes(Passkey,pi_Onelevelkey->mingwenkey,pi_Onelevelkey->r_tek,160,16,NULL);
		API_TraceHex(1,"计算出来的明文密钥是",pi_Onelevelkey->mingwenkey,160);
		for(i = 0 ;i<10 ;i++ )
		{
			CLEAR(tmp);
			memcpy(tmp ,pi_Onelevelkey->mingwenkey+(i*16) ,16 );
			des(tmp,pi_Onelevelkey->miwenkey[i],pi_Onelevelkey->b_tek,16,16,NULL);
			API_TraceHex(1,"主密钥密文是",pi_Onelevelkey->miwenkey[i],16);
			des("\x00\x00\x00\x00\x00\x00\x00\x00" , pi_Onelevelkey->mingwenkeyChk[i],(unsigned char *)tmp , 8, 16, NULL);
			API_TraceHex(1,"主密钥校验值是",pi_Onelevelkey->mingwenkeyChk[i],8);
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
	//母 POS发送：  0x02 + LEN + CMD + GID + GNAME + GKEY + 0x03 + LRC 
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
			WrongMsgAndWaitKey("接收二级POS数据失败\n");
			return ret ;
		}
		API_TraceHex(1,"接收二级POS返回数据是",RecvStr,8);
		if(memcmp(RecvStr+4 ,"00" ,2) != 0)
		{
			WrongMsgAndWaitKey("下载失败\n");
			return  APP_FAIL;
		}
	}
	
}

int OneShowWaitDialog()
{
	
    time_t t;
    struct tm * tm;
	char show[50]={0};	
	ClrScr("母POS密钥管理系统");	
	API_UI_PrintLine(2, FONT_SIZE_VERY_BIG, ALIGN_CENTER, "通联支付");
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
	sprintf(notice , "母POS-领导%d改密" , pi_iLeaderNo);
	sprintf(notice1 , "LeaderPwd%d" ,pi_iLeaderNo );
	if( OneJudgeLeaderOldPwd( notice ,pi_iLeaderNo)	!= APP_SUCC )
		return APP_FAIL ;
	else
	{
		CLEAR(buf1);CLEAR(pwd);
		ret = GetStr_limit_titleIME(notice,"请输入新密码:\n", FONT_SIZE_NORMAL, buf1,8,8,0,1);
		if(ret == APP_FAIL)
			return	 APP_FAIL;
		ret1 = GetStr_limit_titleIME(notice,"再输入一次新密码:\n", FONT_SIZE_NORMAL, pwd,8,8,0,1);
		if(ret1 == APP_FAIL)
			return	 APP_FAIL;
		if( (ret == ret1) && (API_memcmp(buf1  ,pwd  , 8 ) == 0) )
		{
			ret = writeIniFile(ONEPARAM ,notice1 , pwd );
			if(ret == 0 )
				return	RightMsgAndWaitKey("修改成功\n");
			else
				return WrongMsgAndWaitKey("保存领导密码失败\n");
		}
		else
			return	WrongMsgAndWaitKey("两次密码输入不一致\n");
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
	if( OneJudgeLeaderOldPwd("母POS-加密机设置" ,0) != APP_SUCC )
		return APP_FAIL ;		
	readIniFile(ONEPARAM,"ServerIP" ,buf1,&i,"1.1.1.1(默认)");
	readIniFile(ONEPARAM,"ServerPort" ,buf2,&i,"80(默认)");
	sprintf(buf11 ,"IP: %s" ,buf1);	
	sprintf(buf22 ,"端口: %s" ,buf2);
	do
	{
		ClrScr("母POS-加密机设置");
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
	return OneSetIP("母POS-加密机设置" , "ServerIP" ,0 );
}

int OneSetLocalIP()
{
	return OneSetIP("母POS-本机IP设置" , "LocalIP" ,1 );
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
		ret = API_GUI_Edit_GetInputIp("请输入IP:", FONT_SIZE_NORMAL, "按确定键跳过", FONT_SIZE_NORMAL, buf1, 15,  300*1000);
		if(ret  <1)
		{ 
			result = -1 ; break;
		}
		if( OneJudgeLegalIp(buf1 ,ret ) != APP_SUCC)
		{
			WrongMsgAndWaitKey("IP输入不合法");
			result = -2 ; break;
		}
		else
		{
			writeIniFile(ONEPARAM,pi_NeedSaveFlagName,buf1);
			RightMsgAndWaitKey("IP设置成功");
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
		ClrScr("母POS-加密机设置");
		ret = API_GUI_Edit_GetInputIp("请输入端口:", FONT_SIZE_NORMAL, "按确定键跳过", FONT_SIZE_NORMAL, buf1, 5,  300*1000);
		if(ret  <1)
		{ 
			result = -1 ; break;
		}
		else
		{
			writeIniFile(ONEPARAM,"ServerPort",buf1);
			RightMsgAndWaitKey("端口设置成功");
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
		"北京" ,"上海" ,"天津" ,"重庆" ,"香港" ,"澳门" ,"台湾" ,"河北" ,"山西" ,"内蒙古" ,
		"辽宁" ,"吉林" ,"黑龙江" ,"江苏" ,"浙江" ,"安徽" ,"福建" ,"江西" ,"山东" ,"河南" ,
		"湖北" ,"湖南" ,"广东" ,"广西" ,"海南" ,"四川" ,"贵州" ,"云南" ,"西藏" ,"陕西" ,
		"甘肃" ,"宁夏" ,"青海" ,"新疆" ,"保留地区1" ,"保留地区2" ,"保留地区3" ,"保留地区4" ,"保留地区5" ,"保留地区6" ,
		"保留地区7" ,"保留地区8" ,"保留地区9" ,"保留地区10" ,"保留地区11" ,"保留地区12" ,"保留地区13" ,"保留地区14" ,"保留地区15" ,"保留地区16" ,
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
	sprintf(notice , "母POS-设置根分量RV%d" , pi_iLeaderNo);
	sprintf(notice1 , "RV%d" ,pi_iLeaderNo );
	sprintf(notice2 , "请输入根分量RV%d,32字符" , pi_iLeaderNo);	
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
			API_TraceHex(1,"输入的分量是",key,16);			
			des("\x00\x00\x00\x00\x00\x00\x00\x00" , (unsigned char *)notice2,(unsigned char *)key , 8, 16, NULL);
			API_TraceHex(1,"输入的分量的校验值是",notice2,8);
			CLEAR(key) ;
			BcdToAscii(key ,notice2 ,8 , 0);
			CLEAR(notice2) ;
			sprintf(notice2 , "CheckValue是%s" , key);
			CLEAR(key) ;
			sprintf(key , "根分量RV%d设置成功" , pi_iLeaderNo);
			ret = writeIniFile(ONEKEYFILE ,notice1 , buf1 );
			if(ret != 0 ) 
				return WrongMsgAndWaitKey("保存根分量失败\n");
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
	ret = GetStr_limit_titleIME(pi_title,"请输入密码:\n", FONT_SIZE_NORMAL, buf1,0,8,0,1);
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
		return WrongMsgAndWaitKey("密码输入错误\n");
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
	if( OneJudgeLeaderOldPwd("操作员改密" ,0)	!= APP_SUCC )
		return APP_FAIL ;
	else
	{
		CLEAR(buf1);CLEAR(pwd);
		ret = GetStr_limit_titleIME("操作员改密","请输入新密码:\n", FONT_SIZE_NORMAL, buf1,8,8,0,1);
		if(ret == APP_FAIL)
			return	 APP_FAIL;
		ret1 = GetStr_limit_titleIME("操作员改密","再输入一次新密码:\n", FONT_SIZE_NORMAL, pwd,8,8,0,1);
		if(ret1 == APP_FAIL)
			return	 APP_FAIL;
		if( (ret == ret1) && (API_memcmp(buf1  ,pwd  , 8 ) == 0) )
		{
			ret = writeIniFile(ONEPARAM ,notice1 , pwd );
			if(ret == 0 )
				return	RightMsgAndWaitKey("修改成功\n");
			else
				return WrongMsgAndWaitKey("保存操作员密码失败\n");
		}
		else
			return	WrongMsgAndWaitKey("两次密码输入不一致\n");
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
	if( OneJudgeLeaderOldPwd("母POS-设置传输密钥" ,0) != APP_SUCC )
		return APP_FAIL ;
	else
	{
		
		CLEAR(buf1) ;
		ret = GetStr_limit_titleIME("母POS-设置传输密钥",
			"请输入二级传输密钥B_TEK,\n32字符", FONT_SIZE_NORMAL, buf1,32,32,0,1);
		if(ret == APP_FAIL )
			return	APP_FAIL;
		else
		{
			CLEAR(key) ;
			AsciiToBcd(key,buf1,32,0);
			API_TraceHex(1,"输入的分量是",key,16);			
			des("\x00\x00\x00\x00\x00\x00\x00\x00" , (unsigned char *)notice2,(unsigned char *)key , 8, 16, NULL);
			API_TraceHex(1,"输入的分量的校验值是",notice2,8);
			CLEAR(key);
			BcdToAscii(key ,notice2 ,8 , 0);
			CLEAR(notice2) ;
			sprintf(notice2 , "CheckValue是%s" , key);
			if(file_isexist(ONEKEYFILE)  == 0 ) 
			{
				if((fp = fopen(ONEKEYFILE,"w+"))==NULL)
				{
					WrongMsgAndWaitKey("打开文件失败");
					return	APP_FAIL;
				}
			}
			ShowSelectDialog("母POS-设置传输密钥","传输密钥B_TEK",notice2,NULL);
			if(Confirm(60*5)==APP_SUCC)
			{
				ret = writeIniFile(ONEKEYFILE ,"B_TEK" , buf1 );
				if(ret != 0 ) 
				{
					WrongMsgAndWaitKey("保存B_TEK失败\n");
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
	if( OneJudgeLeaderOldPwd("母POS-R_TEK校验值" ,0) != APP_SUCC )
		return APP_FAIL ;
	do
	{
		if ((result =OneGetR_TEK(key)) != APP_SUCC )
		{
			WrongMsgAndWaitKey("请查看是否设置领导分量");
			API_Trace(1,"OneGetR_TEK==result==[%d]",result);
			return result;
		}
		API_TraceHex(1,"R_TEK异或出来的分量是",key,16);	
		des("\x00\x00\x00\x00\x00\x00\x00\x00" , (unsigned char *)notice2,(unsigned char *)key , 8, 16, NULL);
		API_TraceHex(1,"输入的分量的校验值是",notice2,8);
		CLEAR(buf1) ;
		BcdToAscii(buf1 ,notice2 ,8 , 0);
		CLEAR(notice2) ;
		sprintf(notice2 , "%s" , buf1);	
		ShowSelectDialog("母POS-R_TEK校验值","R_TEK的校验值是",notice2,NULL);
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
		API_TraceHex(1,"R_TEK异或出来的分量是",key,16);	
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
	if( OneJudgeLeaderOldPwd("母POS-修改保留区名字" ,0) != APP_SUCC )
		return APP_FAIL ;
	do
	{
		if(file_isexist(ONEINITINFOMATION)  == 0 ) 
			OneInitInfoFlag();
		
		ret = GetStr_limit_titleIME("母POS-修改保留区名字","请输入保留区编号:\n", FONT_SIZE_NORMAL, buf1,2,2,0,1);
		if(ret == APP_FAIL)
		{ 
				result = -1 ; break;
		}
		readIniFile(ONEINITINFOMATION,buf1 ,key,&i,NULL);
		if(API_memcmp(key,"保留",4) !=0)
		{
			ShowSelectDialog("母POS-修改保留区名字",NULL,"输入的编号不是保留区,\n不允许修改!",NULL);
			getkeycode(60);result = -2 ; break;
		}
		else
		{
			sprintf(buf2 , "为%s分组输入新的汉字名称,\n只能修改1次!" , buf1);
			ClrScr("母POS-修改保留区名字");
			ret = API_GUI_Edit_GetInputIME(buf2, FONT_SIZE_VERY_VERY_SMALL, "按确定键跳过", FONT_SIZE_NORMAL, buf3, 30, 300 * 1000 );
			if (ret < 1 ) 
			{ 
					result = -3 ; break;
			}
			else
			{	
				CLEAR(buf2) ;
				sprintf(buf2 , "为%s分组名称改为%s,\n只能修改1次,请慎重!" , buf1 ,buf3);
				ShowSelectDialog("母POS-修改保留区名字",NULL,buf2,"\n确认/取消");
				if (Confirm(60*3)!=APP_SUCC) 
				{ 
						result = -4 ; break;
				}
				else
				{
					writeIniFile(ONEINITINFOMATION,buf1,buf3);
					CLEAR(buf2) ;
					sprintf(buf2 , "将%s分组名称改为%s成功!" , buf1 ,buf3);
					ShowSelectDialog("母POS-修改保留区名字",NULL,buf2,NULL);
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
			WrongMsgAndWaitKey("请查看是否设置领导分量");
			return ret;
		}
		if(file_isexist(ONEPARAM)  == 0 ) 
		{
			result = -1 ;break;
		}
		readIniFile(ONEPARAM,"ServerIP",Serverip,&i,"ERR");
		if((i==3)&&(memcmp(Serverip ,"ERR" ,3) == 0))
		{
			WrongMsgAndWaitKey("请先设置加密机IP");
			result = -4 ;break;
		}
		readIniFile(ONEPARAM,"ServerPort",Serverport,&i,"ERR");
		if((i==3)&&(memcmp(Serverport ,"ERR" ,3) == 0))
		{
			WrongMsgAndWaitKey("请先设置加密机端口");
			result = -4 ;break;
		}
		
		if(Dial( Serverip , atoi(Serverport)) != APP_SUCC)
		{         
			result = -2 ;break;	
		}
		if(OneShowKeyNoSelect("母POS-下载加密机密钥" , &BeginIndex, &EndIndex)!= APP_SUCC)
		{
			result = -7 ;break; 
		}
		for(i =BeginIndex  ;i <EndIndex+1 ; i++)
		{
			//   1下载加密机密钥
			CLEAR(tmp);
			sprintf(tmp, "正在从加密机下载第[%d]个\n密钥,请稍候....." , i);
			ShowSelectDialog("母POS-下载加密机密钥",NULL,tmp,NULL);
			result = 0 ;
			CLEAR(sendstr);
			sendstr[0] = 0x31 ;
			sendstr[1] = (i>>8)&0xff; ;
			sendstr[2] = i%256;
			ret=APP_Send("下载加密机密钥",(u8*)sendstr,3,60);
			API_Trace(0, "发送数据包结果ret = [%d]", ret);
			if( Receive(recvstr) < 1 )
			{
				result = -3 ;break;	
			}
			else
			{				
				CLEAR(chk);//保存8个字节的校验值
				CLEAR(ciphertextkey);
				memcpy(ciphertextkey, recvstr  , 16);
				API_TraceHex(1,"主密钥密文是",ciphertextkey,16);
				memcpy(chk, recvstr + 16 , 8);
				API_TraceHex(1,"主密钥校验值是",chk,8);
			}
			//  2 申请加密机转加密
			CLEAR(sendstr);
			memcpy(sendstr , "\x05\x52\x10\x00\x00" ,5);
			memcpy(sendstr+5 , ciphertextkey ,16);
			ret=APP_Send("下载加密机密钥",(u8*)sendstr,21,60);
			API_Trace(0, "发送数据包结果ret = [%d]", ret);
			if( Receive(recvstr) < 1 )
			{
				result = -4 ;break;	
			}
			else
			{				
				CLEAR(ciphertextkey);
				CLEAR(plaintextkey);CLEAR(chk1);
				memcpy(ciphertextkey, recvstr  , 16);
				API_TraceHex(1,"【转加密】主密钥密文是",ciphertextkey,16);
				des(ciphertextkey,plaintextkey, key,16,16,NULL);
				API_TraceHex(1,"主密钥明文是",plaintextkey,16);
				des("\x00\x00\x00\x00\x00\x00\x00\x00" , (unsigned char *)chk1,(unsigned char *)plaintextkey , 8, 16, NULL);
				API_TraceHex(1,"明文主密钥的校验值是",chk1,8);
				if( API_memcmp(chk1,chk,8)  != 0 )
				{
					WrongMsgAndWaitKey("主密钥校验值不匹配\n");
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
			ShowSelectDialog("母POS-下载加密机密钥","生成全部终端主密钥成功",NULL,NULL);
			getkeycode(10);
		}
	}while(0);
	return  result ;
}



/********************************************************************************
*	函数名称：                                                                   
*	函数介绍:                                                                    
*	修改日期:    2016/10/10--11:44:45                                       
*	输入参数：                                                                   
*	输出参数：                                                                   
*	返回值：                                                                     
*	作者：       Undefined                                                       
*******************************************************************************/
int OneLevelPos()
{	
	char Key=0;
	while(1)
	{
		OneShowWaitDialog();
		do
		{	
			ClrScr("母POS密钥管理系统");
			SetContext(1 , "领导设置", "",1,0 ,ALIGN_LEFT);
			SetContext(2 , "操作员设置", "",1,0 ,ALIGN_LEFT);
			SetContext(3 , "灌装分组密钥到密钥POS", "",1,0 ,ALIGN_LEFT);
#ifdef DEBUG
			SetContext(4 , "测试功能", "",1,0 ,ALIGN_LEFT);
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
		sprintf(beginindex , "加密机密钥开始索引%03d" ,*po_BeginIndex  );
		sprintf(endindex , "加密机密钥结束索引%03d" ,*po_EndIndex  );
		ShowSelectDialog(pi_tile,beginindex,endindex,"按确认键继续...");
		switch(getkeycode(60*30))
		{
			case Key1: 
			{
				while(1)
				{
					ClrScr(pi_tile);
					ret = API_GUI_Edit_GetInputNum("输入密钥开始索引", FONT_SIZE_NORMAL, "输错请按清除键", FONT_SIZE_NORMAL, buf, 3, 60* 1000);
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
					ret = API_GUI_Edit_GetInputNum("输入密钥结束索引", FONT_SIZE_NORMAL, "输错请按清除键", FONT_SIZE_NORMAL, buf, 3, 60* 1000);
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
						WrongMsgAndWaitKey("起始索引必须小于结束索引");
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
			WrongMsgAndWaitKey("缺少必须参数IP及端口\n");
			result = -1 ;break;
		}
		readIniFile(ONEPARAM,"ServerIP",Serverip,&i,"ERR");
		if((i==3)&&(memcmp(Serverip ,"ERR" ,3) == 0))
		{
			WrongMsgAndWaitKey("请先设置加密机IP");
			result = -4 ;break;
		}
		readIniFile(ONEPARAM,"ServerPort",Serverport,&i,"ERR");
		if((i==3)&&(memcmp(Serverport ,"ERR" ,3) == 0))
		{
			WrongMsgAndWaitKey("请先设置加密机端口");
			result = -4 ;break;
		}
#ifdef DEBUG
		if(Dial( "58.246.226.173" , 40004) != APP_SUCC)
		{         
			result = -2 ;break;	
		}
		if(OneShowKeyNoSelect("母POS-申请加密机密钥" , &BeginIndex, &EndIndex)!= APP_SUCC)
		{
			result = -7 ;break;	
		}
		CLEAR(sendstr);
		AsciiToBcd(sendstr,SEND_TEST,strlen(SEND_TEST),0);
		API_Trace(1, "%s - %d【%d】【%d】【%d】", __FILE__, __LINE__,strlen(SEND_TEST),BeginIndex, EndIndex);
		ret=APP_Send("请求加密机产生密钥",(u8*)sendstr,(strlen(SEND_TEST)+1)/2,60);
		API_Trace(0, "发送数据包结果ret = [%d]", ret);
		if(  i= Receive(recvstr) < 0 )
		{
			result = -3 ;break; 
		}
		API_TraceHex(1,"返回数据",recvstr,i);
		ShowSelectDialog("母POS-申请加密机密钥",NULL,"生成500个终端主密钥成功",NULL);
		getkeycode(10);
#else 
		if(Dial( Serverip , atoi(Serverport)) != APP_SUCC)
		{         
			result = -2 ;break;	
		}
		if(OneShowKeyNoSelect("母POS-申请加密机密钥" , &BeginIndex, &EndIndex)!= APP_SUCC)
		{
			result = -7 ;break;	
		}
		for(i =BeginIndex  ;i <EndIndex+1 ; i++)
		{
			CLEAR(sendstr);
			sendstr[0] = 0x11 ;
			sendstr[1] = (i>>8)&0xff; ;
			sendstr[2] = i%256;
			ret=APP_Send("请求加密机产生密钥",(u8*)sendstr,3,60);
			API_Trace(0, "发送数据包结果ret = [%d]", ret);
			if( Receive(recvstr) < 0 )
			{
				result = -3 ;break;	
			}
			//无须保存数据
		}
		if(result == 0)
		{
			ShowSelectDialog("母POS-申请加密机密钥",NULL,"生成全部终端主密钥成功",NULL);
			getkeycode(10);
		}
#endif
	}while(0);
	return  result ;
}
void  OneShowAreaCodeMenu( int pi_iPageNum)
{
	
	ClrScr("母POS-灌密钥到二级POS");
	char tmp1[100]={0};
	char tmp2[100]={0};
	char tmp3[100]={0};
	CLEAR(tmp1);CLEAR(tmp2);CLEAR(tmp3);
	Lcd_printf("%s\n", "输入两位序号后确认选择:");
	if(pi_iPageNum % 6 == 1)
	{
		Lcd_printf("%s\n", "  01北京 02上海 03天津");
		Lcd_printf("%s\n", "  04重庆 05香港 06澳门");
		Lcd_printf("%s\n", "  07台湾 08河北 09山西");
		Lcd_printf("%s\n", "  10内蒙古 11辽宁 12吉林");
	}
	else if(pi_iPageNum % 6 == 2)
	{		
		Lcd_printf("%s\n", "  13黑龙江 14江苏 15浙江");
		Lcd_printf("%s\n", "  16安徽 17福建 18江西");
		Lcd_printf("%s\n", "  19山东 20河南 21湖北");
		Lcd_printf("%s\n", "  22湖南 23广东 24广西");
	}
	else if(pi_iPageNum % 6 == 3)
	{		
		Lcd_printf("%s\n", "  25海南 26四川 27贵州");
		Lcd_printf("%s\n", "  28云南 29西藏 30陕西");
		Lcd_printf("%s\n", "  31甘肃 32宁夏 33青海");
		Lcd_printf("%s\n", "  34新疆 ");
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
	API_TraceHex(1,"读取出来的密钥是",tmp,160);
	return 0 ;
}
#endif


#endif
