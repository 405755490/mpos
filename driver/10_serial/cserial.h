#ifndef __CSERIAL_H__
#define __CSERIAL_H__

/* C接口的串口通用控制方法
   作者：coon 2011-10-28
*/

#define ZT_SUCCESS     		0                       //成功
#define ERR_BASE			(-1100)					//错误基数
#define ERR_NOT_INIT		(ERR_BASE + (-1))   	//未初始化
#define ERR_TIMEOUT			(ERR_BASE + (-2))		//超时
#define ERR_WRITE			(ERR_BASE + (-3))		//发送错误
#define ERR_INIT				(ERR_BASE + (-4))   	//初始化出错





#define  CS_SUCCESS              (0)                   //成功
#define  ERR_CS_BASE             (-10150)              //错误号码基数
#define  ERR_CS_OPEN_COM         (ERR_CS_BASE + (-1))  //打开串口失败
#define  ERR_CS_NOT_OPEN         (ERR_CS_BASE + (-2))  //串口未打开
#define  ERR_CS_READLN           (ERR_CS_BASE + (-3))  //读长度指定错误
#define  ERR_CS_READ             (ERR_CS_BASE + (-4))  //读动作错误
#define  ERR_CS_WRITELN          (ERR_CS_BASE + (-5))  //写长度指定错误
#define  ERR_CS_WRITE            (ERR_CS_BASE + (-6))  //写动作错误
#define  ERR_CS_BPS              (ERR_CS_BASE + (-7))  //波特率指定错误
#define  ERR_CS_SETATTR          (ERR_CS_BASE + (-8))  //设置属性失败
#define  ERR_CS_DEVLEN           (ERR_CS_BASE + (-9))  //设备名超长

typedef struct
{
    int  com_fd;         //文件描述符,-1表示没有关联设备
    int  com_bps;        //串口波特率
    int  com_parity;     //串口奇偶校验
    int  com_databit;    //数据位
    int  com_stopbit;    //停止位
    char com_port[64];   //串口设备文件
}CSerial;

int  cserial_init(CSerial *cs, char *dev, int bps);      //初始化控制信息
int  cserial_open(CSerial *cs);                          //打开指定串口
void cserial_close(CSerial *cs);                         //关闭指定串口
void cserial_clear(CSerial *cs);                         //清除串口
int  cserial_readData(CSerial *cs, char *s, int ln);     //读串口数据
int  cserial_writeData(CSerial *cs, char *s, int ln);    //发送串口数据

//add by zhzh
int API_Serial_Open(char *pi_caPort_str, int pi_ibps);
int API_Serial_Close();
int API_Serial_Send(char *pi_caBuff, int pi_iLen, int pi_iTimeout);
int API_Serial_Receive(char *po_caBuff, int pi_iTimeout);

#endif //__CSERIAL_H__
