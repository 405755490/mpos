
#include "client_pos.h"

#ifdef TWOLEVELMPOS
	
int TwoJudgeLeaderOldPwd(char*pi_title )
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
	
	ret = GetStr_limit_titleIME(pi_title,"请输入密码:\n", FONT_SIZE_NORMAL, buf1,0,8,0,1);
	if(ret == APP_FAIL)
		return	 APP_FAIL;
	API_memcpy(pwd_init,"66666666",8);
	if(file_isexist(TWOPARAM)  == 0 ) 
	{
		if((fp = fopen(TWOPARAM,"w+"))==NULL)	 
			return APP_FAIL; 
	}
	if(ret1 == FALSE)
		API_memcpy(pwd_old,pwd_init,8);
	else
		readIniFile(TWOPARAM,"OperPwd",pwd_old,&ret,pwd_init) ;
	if( API_memcmp(buf1  ,pwd_old  , 8 )!= 0 )
		return WrongMsgAndWaitKey("密码输入错误\n");
	else 
		return	APP_SUCC ;
}

int TwoSendKeyToPinPad()
{
	int result = -1 ;
	char tmp[10]={0};
	char title[100]={0};
	char SendStr[300]={0};
	char buf1[300]={0};
	int ret = 0,i=0 ,ioffsize = 0;
	char RecvStr[50]={0};
	CLEAR(title);CLEAR(SendStr);CLEAR(buf1);
	if( TwoJudgeLeaderOldPwd("灌装密钥到密码键盘" )	!= APP_SUCC )
			return APP_FAIL ;
	do
	{
		//读取密钥  判断是否存在
		if(file_isexist(TWOKEYFILE)  == 0 ) 
		{
			WrongMsgAndWaitKey("请先连接母POS下载密钥");
			result = -1 ;break; 
		}
		readIniFile(TWOPARAM, "CompName" ,tmp,&i,"ERR");
		if(memcmp(tmp ,"ERR" ,3 ) == 0 )
		{
			result = -2 ;break; 
		}
		sprintf(title ,"注入%s地区密钥到密码\n键盘!%s" ,tmp ,"输入键盘起始索引:");
		//输入索引号
		ret = GetStr_limit_titleIME("二级密钥POS",title, FONT_SIZE_NORMAL, buf1,2,2,0,1);
		if(ret == APP_FAIL)
		{ 
			result = -3 ; break;
		}
		CLEAR(title);
		sprintf(title ,"注入%s地区密钥到密码\n键盘!起始索引:%s" ,tmp ,buf1);
		ShowSelectDialog("二级密钥POS" , title ,
			"确认键按\"确认\"键," ,"取消键按\"取消\"键");
		if (Confirm(60*3)!=APP_SUCC) 
		{ 
			result = -4 ; break;
		}
		//组密钥数据 
		//len  从索引（含）到0x03（含）的长度
		//发送  0x02 + len(2) + 索引(2) + 明文(160) + 0x03 + lrc(1) 
		//返回  0x02 + len(2) + 结果(2) + 0x03 + lrc(1) 
		memcpy(SendStr , "\x02\x00\xA4" ,3);
		memcpy(SendStr+ 3 ,buf1 , 2);
		CLEAR(buf1);
		ReadDataFromFile(TWOKEYFILE,buf1,16,10,0);
		memcpy(SendStr+5 , buf1 ,160);
		ioffsize = 165 ;
		SendStr[ioffsize] = 0x03 ;
		ioffsize+=1 ;
		SendStr[ioffsize] = _CalcLRC(SendStr+1,ioffsize-1);
		ioffsize+=1 ;
		//连接密码键盘
#ifdef  DEBUG
			posk_pkg_log(1 ,ioffsize,SendStr);
#endif	
			ret = SerialOpen();
			if(ret < 0 )
			{
				return ret ;
			}
			ret =  SerialSendData(SendStr ,167 );
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
				if(memcmp(RecvStr+2 ,"00" ,2) != 0)
				{
					WrongMsgAndWaitKey("下载失败\n");
					return	APP_FAIL;
				}
			}
		RightMsgAndWaitKey("密钥下载成功\n");
		return APP_SUCC ;
	}while(0);
	return result ;
}



int TwoChangePwd()
{
	int  ret = 0 ;int  ret1 = 0 ;
	char buf1[20] = {0};
	char pwd[20] = {0};
	if( TwoJudgeLeaderOldPwd("二级密钥POS操作员改密" )	!= APP_SUCC )
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
			ret = writeIniFile(TWOPARAM ,"OperPwd" , pwd );
			if(ret == 0 )
				return	RightMsgAndWaitKey("修改成功\n");
			else
				return WrongMsgAndWaitKey("保存操作员密码失败\n");
		}
		else
			return	WrongMsgAndWaitKey("两次密码输入不一致\n");
	}	
}


int TwoLevelPosShowWaitDialog()
{
	char tmp[10]={0};char show[100]={0};
	int i = 1 ;
    time_t t;
    struct tm * tm;
	CLEAR(tmp);		
	readIniFile(TWOPARAM,"CompName",tmp,&i,"未知");
	ClrScr("二级密钥POS管理系统");
	Lcd_printf_center("\n%s\n" , "通联支付");
	Lcd_printf_center("%s\n" , tmp);
	do 
	{
		CLEAR(show);
		time(&t);
		tm = localtime(&t);
		sprintf(show , "%04d-%02d-%02d %02d:%02d:%02d" ,tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday,tm->tm_hour,tm->tm_min,tm->tm_sec);
		API_UI_PrintLine(4, FONT_SIZE_NORMAL, ALIGN_CENTER, show );
		if( getkeycode(1)!= 0  )
			return APP_SUCC;
	}while(1);
	return APP_SUCC;
}
int TwoLevelPosJudgeHaveB_TEK()
{
	char tmp[50]={0};
	int i = 0 ;
	CLEAR(tmp);
	if(file_isexist(TWOPARAM)  == 0 ) 
		return -1; 
	readIniFile(TWOPARAM,"B_TEK",tmp,&i,"ERR");
	API_TraceHex(1,"B_TEK=====",tmp,32);
	if( i < 32 )
		return -2 ;
	return APP_SUCC ;
}
int  TwoLevelPosGetKey( MPOS_TWO_LEVEL_KEY  *pi_key)
{
	FILE *fp;
	int result  = 0  , i = 0;
	char tmp[50]={0};
	char key[200]={0};
	CLEAR(tmp);CLEAR(key);
	do
	{
		if(file_isexist(TWOKEYFILE)  == 0 ) 
		{
			if((fp = fopen(TWOKEYFILE,"w+"))==NULL)	 
			{	result = -1 ;break; }
		}
		readIniFile(TWOPARAM,"B_TEK",tmp,&i,"ERR");
		if( i < 32 )
		{
			result = -1 ;break;
		}
		memset(pi_key->b_tek , 0 ,sizeof(pi_key->b_tek));		
		AsciiToBcd(pi_key->b_tek,tmp,32,0);
		API_TraceHex(1,"B_TEK是",pi_key->b_tek,16);
		for(i= 0 ;i<10 ;i++)
		{
			undes(pi_key->miwenkey[i] ,pi_key->mingwenkey,pi_key->b_tek  , 16,16,NULL);
			API_TraceHex(1,"明文密钥是",pi_key->mingwenkey,16);
			CLEAR(tmp);
			des("\x00\x00\x00\x00\x00\x00\x00\x00" ,(unsigned char *)tmp, pi_key->mingwenkey , 8, 16, NULL);
			API_TraceHex(1,"主密钥校验值是",tmp,8);
			if(memcmp(tmp  , pi_key->mingwenkeyChk[i]  , 8) != 0 )
			{
				API_TraceHex(1,"报文传递主密钥校验值是",pi_key->mingwenkeyChk[i],8);
				WrongMsgAndWaitKey("密钥校验失败");
				result = -2 ;break;
			}
			AddDataToFile(TWOKEYFILE,pi_key->mingwenkey,16,i);
		}
		RightMsgAndWaitKey("\n密钥导入成功\n");
	}while(0);
	return result ;
}
int TwoLevelPosSaveKeyFromMpos(char *pi_keyData , int pi_keyLen)
{
	MPOS_TWO_LEVEL_KEY twolevelkey ;
	int result = 0 ;
	int i = 0  ,ioffsize = 0 ;
	memset(&twolevelkey,0,sizeof(MPOS_TWO_LEVEL_KEY));
	do 
	{
		if(pi_keyData ==NULL)
		{
			result = -1 ;break;
		}
		memcpy(twolevelkey.AreacodeName ,pi_keyData+4 , 8);
		for(i = 0 ;i<8 ;i++)
		{
			if(twolevelkey.AreacodeName[i] == 0x20) 
			{
				twolevelkey.AreacodeName[i] = 0x00;
				break;
			}
		}
		printf("地区码是【%s】\n" , twolevelkey.AreacodeName);
		writeIniFile(TWOPARAM,"CompName",twolevelkey.AreacodeName);
		if(pi_keyLen  < 250 )
		{
			WrongMsgAndWaitKey("母POS下发参数有误");
			result = -2 ;break;
		}
		ioffsize = 12 ; //2+1+1+8 
		for(i= 0 ;i<10 ;i++)
		{
			memcpy(twolevelkey.miwenkey[i] , pi_keyData+ioffsize, 16 );
			ioffsize += 16 ;
			API_TraceHex(1,"密文密钥是",twolevelkey.miwenkey[i],16);
			memcpy(twolevelkey.mingwenkeyChk[i] , pi_keyData+ioffsize, 8 );
			ioffsize += 8 ;
			API_TraceHex(1,"主密钥校验值是",twolevelkey.mingwenkeyChk[i],8);
		}
		if ((result = TwoLevelPosGetKey(&twolevelkey))!= 0 )
		{
			WrongMsgAndWaitKey("密钥导入出错");
			API_Trace(1,"密钥导入result====%d",result);
			result = -3 ;break;
		}
		else
		{
			result = 0 ;break;
		}
	}while(1);
	return result ;
}


int  TwoLevelPosGetKeyFromMpos()
{
	
	char SendStr[30]={0};
	char RecvStr[300]={0};
	char tmp[50]={0};
	int i = 0 ,ret = 0 ;
	int result = APP_SUCC;
	do
	{
		ret = SerialOpen();
		if(ret < 0 )
		{
			if(Confirm(60*3) ==APP_SUCC)
			{
				ClrScr("二级密钥POS管理系统");
				Lcd_printf_center("\n%s\n" , "请先打开串口");
			}
			result = -2 ;break;
		}
		CLEAR(RecvStr);
		ClrScr("二级密钥POS管理系统");
		Lcd_printf_center("\n%s\n" , "从母POS下载密钥...");
		ret = SerialRecvData(RecvStr);
#ifdef  DEBUG
		posk_pkg_log(2 , ret,RecvStr);
#endif	
		if(ret < 0 )
		{
			result = -3 ;break;
		}
		API_TraceHex(1,"接收母POS返回数据是",RecvStr,ret);
		ret = TwoLevelPosSaveKeyFromMpos(RecvStr ,ret);
		API_Trace(1,"保存母pos密钥ret====%d",ret);
		if(ret < 0 )
		{
			WrongMsgAndWaitKey("密钥数据保存失败\n");
			result = -4 ;break;
		}
		CLEAR(SendStr);
		memcpy(SendStr ,"\x02\x00\x05\x98\x01\x30\x30\x03\x9D" , 9);
		ret =  SerialSendData(SendStr ,9 );
		if(ret < 0 )
		{
			result = -5 ;break;
		}
	}while(0);
	return result ;
}
int TwoLevelPosJudgeHaveKEY()
{
	char tmp[300]={0};
	int i = 0 ;
	CLEAR(tmp);
	if(file_isexist(TWOKEYFILE)  == 0 ) 
		return -1; 
	if((i = ReadDataFromFile(TWOKEYFILE,tmp,(16/*+8 check value not save now*/),10,0))!= 0)
	{
		WrongMsgAndWaitKey("密钥文件读取失败\n需要重新下载");
		API_fremove(TWOKEYFILE);
		return -2 ;
	}
#ifdef DEBUG
	API_TraceHex(1,"10组密文密钥是",tmp,160);
#endif
	return APP_SUCC ;

}

int TwoLevelPosGetB_TEK()
{
	FILE * fp ;
	int result = 0 ;
	int ret = -1 ;
	char notice2[50]={0};char key[50]={0};
	char buf1[50]={0};
	CLEAR(key) ;
	CLEAR(buf1) ;CLEAR(notice2) ;
	do 
	{
		if((ret =TwoLevelPosJudgeHaveB_TEK()) !=APP_SUCC)  
		{
			printf("ret========%d\n" ,ret);
			ret = GetStr_limit_titleIME("二级密钥POS管理系统",
				"请设置传输密钥B_TEK,\n32个16进制字符", FONT_SIZE_NORMAL, buf1,32,32,0,1);
			if((ret ==APP_SUCC))
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
				ShowSelectDialog("二级密钥POS管理系统","传输密钥B_TEK",notice2,NULL);
				if(file_isexist(TWOPARAM)  == 0 ) 
				{
					if((fp = fopen(TWOPARAM,"w+"))==NULL)
					{
						WrongMsgAndWaitKey("打开文件失败");
						continue;
					}
				}
				if(Confirm(60*5)==APP_SUCC)
				{
					ret = writeIniFile(TWOPARAM ,"B_TEK" , buf1 );
					if(ret != 0 ) 
						 WrongMsgAndWaitKey("保存B_TEK失败\n");
				}
			}
			continue;
		}
		if(TwoLevelPosJudgeHaveKEY() !=APP_SUCC)  
		{
			ShowSelectDialog("二级密钥POS管理系统"," ","从母POS下载密钥",NULL);
			if( TwoLevelPosGetKeyFromMpos() != APP_SUCC)
				continue;
		}

		TwoLevelPosShowWaitDialog();
		return APP_SUCC ;
	}while(1);
	return result ;
}

#define TEST_KEY "02519801B1B1BEA920202020F40379AB9E0EC533F40379AB9E0EC53382E13665B4624DF5950973182317F80B950973182317F80B00962B60AA556E65F40379AB9E0EC533F40379AB9E0EC53382E13665B4624DF5950973182317F80B950973182317F80B00962B60AA556E65F40379AB9E0EC533F40379AB9E0EC53382E13665B4624DF5950973182317F80B950973182317F80B00962B60AA556E65F40379AB9E0EC533F40379AB9E0EC53382E13665B4624DF5950973182317F80B950973182317F80B00962B60AA556E65F40379AB9E0EC533F40379AB9E0EC53382E13665B4624DF5950973182317F80B950973182317F80B00962B60AA556E65AA"
int Test()
{
	char tmp[500]={0};
	CLEAR(tmp);
    API_Trace(1, "%s - %d【%d】", __FILE__, __LINE__,strlen(TEST_KEY));
	AsciiToBcd(tmp,TEST_KEY,strlen(TEST_KEY),0);
	TwoLevelPosSaveKeyFromMpos(tmp , (strlen(TEST_KEY)+1)/2);
	return 0 ;
}

int TwoLevelPosLock()
{
	do
	{
		if(TwoJudgeLeaderOldPwd("终端已锁定")== APP_SUCC )
			return APP_SUCC ;
		
	}while(1) ;
}
int TwoLevelPos()
{	
#ifdef DEBUG
	Test();
#endif
	//接收母POS操作员输入的传输密钥
	TwoLevelPosGetB_TEK();	
	do
	{	
		ClrScr("二级密钥POS管理系统");
		SetContext(1 , "操作员改密", "",1,0 ,ALIGN_LEFT);
		SetContext(2 , "注入密钥到密码键盘", "",1,0 ,ALIGN_LEFT);
#ifdef DEBUG
		SetContext(3 , "测试功能", "",1,0 ,ALIGN_LEFT);
#endif
		API_UI_Flush(NULL);
		switch (getkeycode(30))
		{
			case Key1: 
				TwoChangePwd();
				break;			
			case Key2: 
				TwoSendKeyToPinPad();
				break;
#ifdef DEBUG
			case Key3:
				Test();
				break;				
#endif
			case ESC:
				TwoLevelPosShowWaitDialog();
				break;
			case 0:
				TwoLevelPosLock();
				break;
			default : break;
		}
	}while(1);
}
#endif
