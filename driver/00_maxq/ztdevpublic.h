/******************************************************************************
  文 件 名:  ztdevpublic.c
  当前版本:  V1.00.00  2012/08/24    
  功能描述:  linux设备驱动公用函数头文件，函数声明，宏定义等。
  修改记录:  
  					 V1.00.00  Billy  2012/09/18  第一次编写		
  Copyright (C), 2008-2018, Shenzhen Zhengtong Electronics Co.LTD
******************************************************************************/
#ifndef __ZTLOGDEV_H__
#define __ZTLOGDEV_H__

#define ZTLOG_OUTDEV_NONE			(0x00)
#define ZTLOG_OUTDEV_FILE			(0x01)
#define ZTLOG_OUTDEV_STDIO		(0x02)
#define ZTLOG_OUTDEV_BOTH			(0x03)

#define ZTLOG_CRIS					(0x00)				 //关键信息
#define ZTLOG_EROR          (0x01)         //错误信息
#define ZTLOG_WARN       		(0x02)         //警告信息
#define ZTLOG_FUNC          (0x03)         //提示信息
#define ZTLOG_INFO          (0x04)         //函数名称
#define ZTLOG_RECV          (0x05)         //通信数据
#define ZTLOG_SEND          (0x06)         //通信数据
#define ZTLOG_RESV          (0x07)         //保留

typedef struct 
{
	int outdev;					//输出设备
	int debuglevel;			//调试等级
	int logmaxlen;			//最大日志长度，以M为单位1-8M,最大为8M
	char path[32];			//日志存放路径
	char devname[32];		//日志设备名称
}ZTDEVLOG;

/* openini使用inifile构造段表和项表，并将INI置为可用
 * 返回值:
 *	 0: 成功
 *	-1: INI文件格式错
 *	-2: 打开文件错 
*/
extern int ztini_open(const char *inifile);
/* 析构段表和项表，释放所用的内存，并将INI置为不可用 */
extern void ztini_close(void);
/* 在链表中查找seg段的item项，出错返回NULL，否则返回指向项值的指针
 * 返回的指针已分配内存，由调用者释放 
 */
extern int  ztini_get_item(char *seg, char *item, char *value);
/* 按整数返回项值，出错返回-1 */
extern int  ztini_get_item_int(char *seg, char *item);

extern void ztlog_enable(ZTDEVLOG ztlog);
extern int ztlog_printf(int loglevel,char * format,...);
extern int ztlog_tofile(char * filename,char * format,...);
#endif  //__ZTLOGDEV__
