/******************************************************************************
  文 件 名:  ztmisc_interface.h
  当前版本:  V1.06  2014/08/26    
  功能描述:  ZT8225产品检测控制类设备驱动头文件，包括函数声明，错误
             返回值的宏定义，数据结构定义等内容。
  修改记录:  
  					 V1.00.01  	Billy  2013/04/07  第一次编写		
  					 V1.01.00	Billy  2013/07/23  增加键盘声音控制接口。
  					 V1.02.00	Hzy	   2014/04/25  增加GPRS驱动接口		
  					 V1.03.00  	Billy  2014/06/05  增加背光调节接口。
  					 V1.04.00  	Billy  2014/07/01  增加系统关机接口。
  					 V1.05.00  	Billy  2014/07/02  增加蜂鸣器驱动接口。
  					 V1.05.01  	Hzy	   2014/08/18  修改GPRS驱动接口
  					 V1.05.02  	Hzy	   2014/08/22  完善查询GPRS模块网络是否在线接口
  					 V1.06.00	Hzy	   2014/08/26  增加读取系统版本号接口
  					 V1.06.01	Hzy	   2014/09/29  根据最新的文件系统，完善驱动并测试
  					 V1.06.02	Hzy	   2015/01/28  ppp拨号时如果判断正在或已经拨号，不再重拨
  					 V1.06.03	lyc	   2015/02/10  优化电池电量突变问题
  					 V1.07.01	lyc	   2015/03/31  添加gprs接口，获取临小区信息
  					 V1.08.01	lyc	   2015/03/31  添加gprs接口，获取运营商信息
  					 V1.09.00	lyc	   2015/05/13  添加gprs接口，添加钟工需求的基站信息接口ZTMISC_GPRS_BASE_STATION，添加姚涛需求的基站信息接口ZTMISC_GPRS_BASE_STATION_TIME
  					 V1.09.01	lyc	   2015/05/13  添加获取一个lac接口，姚涛需求
  					 V1.09.02	lyc	   2015/06/06  条码扫描接口打开
  					 V1.09.03	lyc	   2015/06/09  修改电源管理打开及关闭接口
  					 V1.09.04	lyc	   2015/06/12  修改gprs_get ATTACH接口 判断获得ip才是网络连接成功
  					 V1.09.05	lyc	   2015/06/19  修改版本获取接口 处理uboot kernel 版本读取不到的问题
  Copyright (C), 2001-2008, Shenzhen Zhengtong Electronics Co.LTD
******************************************************************************/
#ifndef __ZTMISC_INTERFACE_H__
#define __ZTMISC_INTERFACE_H__

#define ZTMISC_VERSION "ZTMISC_V1.09.05"

#define ZTRET_MISC_SUCCESS           0
#define ZTRET_MISC_ERROR             -3000
#define ZTRET_MISC_FUNC_UNSUPPORT    ZTRET_MISC_ERROR-1
#define ZTRET_MISC_OPENDEV_ERROR	 ZTRET_MISC_ERROR-2
#define ZTRET_MISC_PARA_ERROR	     ZTRET_MISC_ERROR-3
#define ZTRET_MISC_TIMEOUT		     ZTRET_MISC_ERROR-4
#define ZTRET_MISC_READ_ERROR		 ZTRET_MISC_ERROR-5
#define ZTRET_MISC_READ_TIMEOUT		 ZTRET_MISC_ERROR-6
#define ZTRET_MISC_WRITE_ERROR		 ZTRET_MISC_ERROR-7
#define ZTRET_MISC_GET_BASE_ERROR		 ZTRET_MISC_ERROR-8

//设备LED灯控制
#define ZTMISC_ENABLE_LED_RED					0x01		//使能LED灯为红色
#define ZTMISC_ENABLE_LED_GREEN					0x02		//使能LED灯为绿色
#define ZTMISC_ENABLE_LED_BLUE					0x03		//使能LED灯为蓝色
#define ZTMISC_ENABLE_LED_YELLOW				0x04		//使能LED灯为黄色

//获取终端参数ID号
#define ZTMISC_SYS_MODLE_ID						0x01		//
#define ZTMISC_SYS_SERIAL_NO					0x02		//
#define ZTMISC_SYS_HWPCB_VERSION				0x03		//
#define ZTMISC_SYS_BOOT_VERSION					0x04		//
#define ZTMISC_SYS_KERNEL_VERSION				0x05		//
#define ZTMISC_SYS_ROOTFS_VERSION				0x06		//
#define ZTMISC_SYS_MAC							0x07		//

#define ZTMISC_SYS_CLIENT_ID0					0x40		//
#define ZTMISC_SYS_CLIENT_ID1					0x41		//
#define ZTMISC_SYS_CLIENT_ID2					0x42		//
#define ZTMISC_SYS_CLIENT_ID3					0x43		//
#define ZTMISC_SYS_CLIENT_ID4					0x44		//
#define ZTMISC_SYS_CLIENT_ID5					0x45		//
#define ZTMISC_SYS_CLIENT_ID6					0x46		//
#define ZTMISC_SYS_CLIENT_ID7					0x47		//
#define ZTMISC_SYS_CLIENT_ID8					0x48		//
#define ZTMISC_SYS_CLIENT_ID9					0x49		//
#define ZTMISC_SYS_CLIENT_ID10					0x4A		//
#define ZTMISC_SYS_CLIENT_ID11					0x4B		//
#define ZTMISC_SYS_CLIENT_ID12					0x4C		//
#define ZTMISC_SYS_CLIENT_ID13					0x4D		//
#define ZTMISC_SYS_CLIENT_ID14					0x4E		//
#define ZTMISC_SYS_CLIENT_ID15					0x4F		//

//GPRS模块使用的宏定义
#define ZTMISC_GPRS_IMEI						0x01		//查询GPRS模块产品序列号IMEI(国际移动设备身份码的缩写)
#define ZTMISC_GPRS_IMSI						0x02		//查询GPRS模块IMSI(国际移动用户识别码的缩写)
#define ZTMISC_GPRS_CCID						0x03		//查询GPRS模块CCID(SIM卡的识别标识)
#define ZTMISC_GPRS_CCID_EX						0x52		//查询GPRS模块CCID(供状态栏使用)
#define ZTMISC_GPRS_SIGNAL						0x04		//查询GPRS模块信号强度
#define ZTMISC_GPRS_REGIST						0x05		//查询GPRS模块网络是否注册
#define ZTMISC_GPRS_ATTACH						0x06		//查询GPRS模块网络是否在线
#define ZTMISC_GPRS_FMR							0x09		//查询GPRS模块版本号
#define ZTMISC_GPRS_SIGNAL_EX					0x0A		//查询GPRS模块信号强度,专给主控程序调用
#define ZTMISC_GPRS_ATTACH_EX					0x0B		//查询GPRS模块网络是否在线,专给主控程序调用
#define ZTMISC_GPRS_STATUS			   			0x0C		//查询GPRS模块通讯是否正常

#define ZTMISC_GPRS_LAC							0x07		//查询GPRS模块无限基站号
#define ZTMISC_GPRS_CID							0x08		//查询GPRS模块无线小区号
//add LYC 
#define ZTMISC_GPRS_MCC							0x0d		
#define ZTMISC_GPRS_MNC							0x0e		
#define ZTMISC_GPRS_RXLEV						0x0f		
#define ZTMISC_GPRS_RSSI							0x29

#define ZTMISC_GPRS_BASE_STATION_TIME           0x23
#define ZTMISC_GPRS_GET_ONE_LAC           0x24


#define ZTMISC_GPRS_OPERATOR							0x22//获取运营商信息
#define ZTMISC_GPRS_BASE_STATION							0x50//获取基站信息 按钟工需求排序操作
#define ZTMISC_GPRS_BASE_STATION_UNDISPOSED							0x51//获取基站信息 at+mcell=0,21原始数据


#define ZTPMGR_MODE_NORMAL						0x0
#define ZTPMGR_MODE_IDLE						0x1
#define ZTPMGR_MODE_SUSPEND						0x2

#define	ZTPMGR_LOCK								0x30
#define	ZTPMGR_UNLOCK							0x31
#define	ZTPMGR_SET_IDLE_TIME					0x32
#define	ZTPMGR_SET_SUSPEND_TIME					0x33
#define	ZTPMGR_SET_IDLE_WP_SOURCE				0x34
#define	ZTPMGR_SET_SUSPEND_WP_SOURCE			0x35
#define	ZTPMGR_SET_IDLE_DEV_STATUS				0x36
#define	ZTPMGR_SET_SUSPEND_DEV_STATUS			0x37
#define	ZTPMGR_SET_IDLE_BL_STATUS				0x38
#define	ZTPMGR_SET_SUSPEND_BL_STATUS  			0x39

extern char * ztmisc_version(void);
extern int ztmisc_zt606_reset(void);
extern int ztmisc_zt566_reset(void);
extern int ztmisc_zt566_download_into(void);
extern int ztmisc_zt566_download_exit(void);
extern int ztmisc_set_rtc(char *bcdTime);
extern int ztmisc_get_rtc(char *bcdTime);
extern int ztmisc_poweroff(void);
extern int ztmisc_barcode_scan(unsigned char * barcode,int to_s);
//extern int ztmisc_audio_enable(char *path, int to_s);
extern int ztmisc_led_enable(int type, bool enable, long on_ms, long off_ms);
extern int ztmisc_backlight_enable(bool enable); 
extern int ztmisc_sys_getinfo(int cmd, char *param);
extern int ztmisc_sys_setparam(int cmd, char *param);
extern int ztmisc_gprs_connect(void);
extern int ztmisc_gprs_disconnect(void);
extern int ztmisc_gprs_reset(void);
extern int ztmisc_gprs_SetConnectNet(char *connectname);
extern int ztmisc_gprs_get_APNLine(char *gprs_apn);
extern int ztmisc_gprs_APN(char *gprs_apn);
extern int ztmisc_gprs_UsrPasswd(char *usr, char *passwd);
extern int ztmisc_gprs_get(int mode, char *outstr);
extern int ztmisc_brightness_adjust(int persent);
extern int ztmisc_buzzer_control(unsigned int to_ms);
extern int ztmisc_pmgr_enable(int mode);
extern int ztmisc_pmgr_disable(int mode);
extern int ztmisc_pmgr_setparam(int cmd,int arg);
extern int ztmisc_system_suspend(void);
extern int ztmisc_adapter_status(void);
extern int ztmisc_printer_status(void);
extern int ztmisc_battery_status(void);
extern int ztmisc_USB_status(void);
extern int ztmisc_TF_status(void);

//下面接口函数是最初开发的，测试程序可能还有用到，新开发的应用不建议使用下面的接口。上面的函数中已实现下面的接口函数功能
extern int ztmisc_gprs_siglevel(void);
extern int ztmisc_gprs_link(void);
extern int ztmisc_gprs_status(void);
extern int ztmisc_sys_ver(char *pbt, char *pos , char *pfs);
extern int ztmisc_dbgport_control(unsigned int mode);	//
extern int ztmisc_audio_enable(unsigned char enable);   //0x0=audio disable 0x1=enable telephone audio 0x2=enable soundcard audio 


#endif  //_ZTLCD_INTERFACE_H__
