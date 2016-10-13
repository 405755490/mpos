#ifndef __PRINT_API__
#define __PRINT_API__

#include <QObject>
#include "ztloger.h"

#define TEXT_NOMAL_FONT 0
#define TEXT_SMALL_FONT 1
#define TEXT_BOLD 8
#define TEXT_UNDERLINE 128
#define TEXT_REVERSE 0x200
#define TEXT_ITALIC 64

#define IOC_PRINTER_MAGIC  'B'
#define LP_GET_STATUS       				_IO(IOC_PRINTER_MAGIC, 11)
#define LP_SET_GOPAPER  						_IO(IOC_PRINTER_MAGIC, 12)
#define LP_SET_TIMEOUT  						_IO(IOC_PRINTER_MAGIC, 13)
#define LP_SET_SPEED  							_IO(IOC_PRINTER_MAGIC, 14)
#define LP_SET_GRAY  								_IO(IOC_PRINTER_MAGIC, 15)
#define LP_SET_HEATTYPE							_IO(IOC_PRINTER_MAGIC, 16)
#define LP_SET_START_STEP						_IO(IOC_PRINTER_MAGIC, 17)
#define LP_SET_STOP_STEP						_IO(IOC_PRINTER_MAGIC, 18)
#define LP_SET_CONTINUE							_IO(IOC_PRINTER_MAGIC, 19)
#define LP_RESET_PRINTER								_IO(IOC_PRINTER_MAGIC, 20)

#define LP_BUFFER_SIZE PAGE_SIZE*25  //PAGE_SIZE = 4096 total=102400 byte
#define PRINTER_PROC_IDLE 					0x0
#define PRINTER_PROC_MOTOSTART			0x1
#define PRINTER_PROC_SENDDATA				0x2
#define PRINTER_PROC_HEAT						0x3
#define PRINTER_PROC_MOTOSTEP 			0x4
#define PRINTER_PROC_MOTOSTOP				0x5

//#define TIMER_TRIG_100US 275
#define TIMER_TRIG_100US 8

#define LP_STATUS_BUSY 	(0x1<<0)
#define LP_STATUS_PHE 	(0x1<<1)
#define LP_STATUS_TH	 	(0x1<<2)
#define LP_STATUS_TIMEOUT	 	(0x1<<3)

#define LP_SPEED_LOW			0x0
#define LP_SPEED_MIDDLE		0x1
#define LP_SPEED_HIGH			0x2

#define LP_GRAY_LOW				0x0
#define LP_GRAY_MIDDLE		0x1
#define LP_GRAY_HIGH			0x2



typedef struct PrnData
{ 
    int font_type;
    int font_size;  
    QString s_data;
}PrnData;


void getDateTime(char *strdate,char *strtime,char *);

class PrintApi : public QObject
{
    Q_OBJECT
    
public:
    explicit PrintApi(QObject *parent = 0);
    ~PrintApi();
public:
    int  PrnOpen();
    void PrnClose();
    int  PrnPrintStr(char *textBuf);
    void PrnPrintGraph(const char* imageFileName); //打印图片
    void PrnSetLeftMargin(int leftMargin);
     
    void PrnSetFont(char *p_caType); //设置需要打印的字体     楷体默认 传 0
                                     //                       微软雅黑  "msyh"   
    void PrnSetTextType(int i_type); //   i_type   设置文字的书写方向 
                                     //   1 从右往左书写  0 从左向右书写 
    void PrnSetAlign(int iAlign);    //   iAlign  0 左对齐  
                                     //           1 右对齐
                                     //           2 中间对齐                                                    
    void PrnFillData(int i_font_type ,char *p_caInfo,int font_size=0); // FONT_TYPE     字体类型
    int  PrnPrintData(); // 
    int  ContinuePrint();
    int  ClearPrintStatus();
    int  SetPrintSpeed(int speed);
    int  SetPrintSpaceLine(int mode ,int line);                                                                 
    int  GetPrintStatus();
    void  PrnBmpData(char *data,int len);
                                     


private:
    void PrnCreatBmp(int height,QString qstr);
    unsigned long text_flag;
    int rightmargin;
    int _linewidth;
    int _fontsize;
    int _texttype;   //字体模式
    char caType[32]; //字体种别
    char caDataBuff[5000000]; //打印缓冲区
    int  _iDatalen;  //打印数据长度
    int  _iAlign;    //文字对齐方式 0 左对齐 1 右对齐 2 中间对齐
    int  _fd;        //打印机设备句柄
    int  _start;     //
    int  _end;
    ZTLoger *c_loger;
};
#endif