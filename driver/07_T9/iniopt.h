#ifndef ___INIOPT__H__20151120__fq___
#define ___INIOPT__H__20151120__fq___

#define CONFIG_FILE			"PADMODE.ini"
#define INI_KEY_PADMODE		"KS8210_PADMODE"

#define DEVCONFG				"/ztparam/device.ini"
#define INI_KEY_DEVICEID		"ID"

#define T9BACKUP				"/yaffs/padcfg/libT9.so"
#define T9BACPPATH				"/yaffs/padcfg/"
#define STARTPATH				"/yaffs/etc/app_start.sh"

#define SHCOPYT9				"cp /yaffs/padcfg/libT9.so /yaffs/pos/lib/libT9.so"
#define TOBACKUP				"cp /yaffs/pos/lib/libT9.so /yaffs/padcfg/libT9.so"
#define SHFALG					"/yaffs/szzt_init &"
#define CHMODSTART				"chmod 777 /yaffs/etc/app_start.sh"

//KS8210EB0100B0100153100027
/*
KS8210E-B11-B11�ֳֽ���POS�ն� 
KS8210E-B12-B12�ֳֽ���POS�ն� 
KS8210E-B18-B18�ֳֽ���POS�ն�  
KS8210E-B19-B19�ֳֽ���POS�ն� 
KS8210E-B20-B20�ֳֽ���POS�ն� 
KS8210E-B21-B21�ֳֽ���POS�ն� 
KS8210E-B24-B24�ֳֽ���POS�ն� 
KS8210E-B27-B27�ֳֽ���POS�ն� 
KS8210E-B28-B28�ֳֽ���POS�ն� 
*/

#define BADSN_CNT    9
static const char badSN[BADSN_CNT][32] = {
	"KS8210EB1100B1100",
	"KS8210EB1200B1200",
	"KS8210EB1800B1800",
	"KS8210EB1900B1900",
	"KS8210EB2000B2000",
	"KS8210EB2100B2100",
	"KS8210EB2400B2400",
	"KS8210EB2700B2700",
	"KS8210EB2800B2800"
	};


typedef enum
{
	T9_PAD_DEF = 0,    		//��׼T9����ģʽ
	T9_PAD_1 = 1		//������֤����ģʽ
}PADMODE;

typedef enum
{
	DEV_OK = 0,		//�Ǵ������
	DEV_BAD	= 1,	//�������
}DEVFLAG;

PADMODE read_padmode();
int write_padmode(PADMODE tmode);
DEVFLAG isBadSerial();
int hasT9bakExt();
void T9backup();
void changStartsh();


#endif
