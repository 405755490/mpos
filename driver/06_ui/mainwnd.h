#ifndef MAINWND_H
#define MAINWND_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include "statusbar.h"
#include <QSignalMapper>
#include <QtGui/QPushButton>

//================================= *********功能开关 Begin**************=================================

//待机显示的银联图片可以替换
//示例
//API_UI_ShowImg("/yaffs/pos/yilianlogo.png", 50, 60, 240, 120); //易联背景图片


//定义是否是8210设备，1为是，0为后
#define   ZT8210_GUI         1  

//定义是否打开调试开关
#define   GUI_DEBUG          0 

//定义支持的语言  //msyh支持GBK//其他不支持GBK
//8210C系统默认不带msyh字库

//#ifndef LAN_MSYH //微软雅黑
//#define LAN_MSYH          
//#endif

#ifndef LAN_HEI //黑体
#define LAN_HEI         
#endif

//#ifndef LAN_KAI //楷体
//#define LAN_KAI         
//#endif


//定义是否是触屏的机器  
#ifndef GUI_HAND          
#define GUI_HAND
#endif

//================================= *********功能开关 End**************=================================
#define PAGE_X          0
#define PAGE_Y          0
#define PAGE_H          320
#define PAGE_W          240
#define TITLE_H         48
#define TITLE_W         240
#define LABEL_H         45
#define LABEL_W         240
#define BUTTON_H        47
#define BUTTON_W        240

#define BACKGROUND_IMG  "./images/bg.png"  //背景图片
#define WAIT_IMG  		"./images/wait.png"  //背景图片
//*********************显示面板坐标定义***************************************
#define TOTAL_WIDE                 240 //8225设备的宽度
#define TOTAL_HEIGHT               320 //8225设备的高度
#define STATUS_HEIGHT              20  //状态栏的高度


//X坐标 定义
#define LEFT_OF_LITTLE_BUTTON_X    5 //左边小button的X坐标
#define LEFT_OF_LARGE_BUTTON_X     5 //大button的X坐标
#define RIGHT_OF_LITTLE_BUTTON_X   (TOTAL_WIDE -(LEFT_OF_LITTLE_BUTTON_X)-WIDE_OF_LITTLE_BUTTON) //右边小button的X坐标

//Y坐标定义
#define  HEIGHE_FIRST_BUTTON        35 //第一个button的顶边距
#define  INTERVAL_BUTTON            15 //按钮之间的间隙
#define  NEXT_POSITION_BUTTON     (HIGHT_OF_LITTLE_BUTTON+INTERVAL_BUTTON)//小button的高度加上 按钮之间的间隙
#define  NEXT_POSITION_BUTTON_L     (HIGHT_OF_LARGE_BUTTON+INTERVAL_BUTTON)//大button的高度加上 按钮之间的间隙


#define WIDE_OF_LITTLE_BUTTON      105 //小button的宽度
#define HIGHT_OF_LITTLE_BUTTON     30 //小button的高度
#define WIDE_OF_LARGE_BUTTON       210 //大button的宽度
#define HIGHT_OF_LARGE_BUTTON      33 //大button的高度
//*********************显示面板坐标定义*******结束********************************
class MainWnd : public QWidget
{
    Q_OBJECT

public:
    explicit MainWnd(QWidget *parent = 0);
    ~MainWnd();

    void ClearWnd(int pi_iMode);
    void SetImage1(char *pi_caPath,char *p,int len_X,int len_Y);
    void Set_EndTime(int time);
    void ShowTime1();
    void SetTitle(char *pi_caBuff, int pi_flag, int pi_iFontSize);
    void SetContent(int pi_iLineNo, char *pi_caBuff, int pi_iFontSize, int pi_iAlign);
    void SetButton(char *pi_caBuff);
    void SetEdit(int pi_iLine, char *pi_caBuff, int pi_iFlag, int pi_iFontSize, int pi_iAlign);
	void setWait();
    void SetSelect(char *pi_caBuff, int pi_iPos, int pi_iLen);
    void SetImage(char *pi_caPath, int pi_iX, int pi_iY, int pi_iW, int pi_iH);
    void SetContext(int pi_iLine , char *pi_caBuffLeft,char *pi_caBuffRight,int pi_iModeLeft,int pi_iModeRight,int pi_iAlign_mode );
    void setBackground(QString p_caSrc);
	int GetKey( char *po_cKey); //获取键值
    void SaveLog(char *msg);
    char caTmp[128];
	char caKey[10];  //存放键值
    char caTitle[128];
    char caContent1[128];
    char caContent2[128];
    char caContent3[128];
    char caContent4[128];
    char caContent5[128];
    char caContent7[128];

    char caContext1_left[128];
    char caContext2_left[128];
    char caContext3_left[128];
    char caContext4_left[128];
    char caContext5_left[128];
	char caContext6_left[128];
    char caContext7_left[128];
    char caContext8_left[128];
    char caContext9_left[128];
    char caContext0_left[128];
	
    char caContext1_right[128];
    char caContext2_right[128];
    char caContext3_right[128];
    char caContext4_right[128];
    char caContext5_right[128];
	char caContext6_right[128];
    char caContext7_right[128];
    char caContext8_right[128];
    char caContext9_right[128];
    char caContext0_right[128];

    char caButton[128];
    char caEdit[128];
    char caSelect[128];
    char caPath[128];
	
private:
    unsigned char timenum;
    QLabel *c_labTitle1;     //标题区域
    QLabel *c_labTitle2;     //标题区域
    QLabel *c_labBt;        //按钮区域
    QLabel *c_lab1;         //内容区域1
    QLabel *c_lab2;         //内容区域2
    QLabel *c_lab3;         //内容区域3
    QLabel *c_lab4;         //内容区域4
    QLabel *c_lab5;         //内容区域5
    QLabel *c_lab6;         //时间区域
    QLabel *c_lab7;         //提示信息
    QLabel *c_lab8;         //倒计时
//************改为button******************************************
    QPushButton *c_btn[5][3];  //内容区域


//***************************************************
    QLabel *c_labImage;     //图片
    QLabel *c_labImage2;    //图片
    QLabel *c_labImage3;    //图片logo
    QLineEdit *c_edit;      //输入框
	StatusBar  *c_statusbar;  //状态栏
    QTimer *time;
private slots:
    void Time();
    void ShowTime();
    void Set_time(int time);
    void ClearWnd2(int pi_iMode);
    void SetTitle2(char *pi_caBuff, int pi_flag, int pi_iFontSize);
    void SetContent2(int pi_iLineNo, char *pi_caBuff, int pi_iFontSize, int pi_iAlign);
    void SetButton2(char *pi_caBuff);
    void SetEdit2(int pi_iLine, char *pi_caBuff, int pi_iFlag, int pi_iFontSize, int pi_iAlign);
    void SetSelect2(char *pi_caBuff, int pi_iPos, int pi_iLen);
    void SetImage2(char *pi_caPath, int pi_iX, int pi_iY, int pi_iW, int pi_iH);
    void SetContext2(int pi_iLine , char *pi_caBuffLeft,char *pi_caBuffRight,int pi_iModeLeft,int pi_iModeRight ,int pi_iAlign_mode);

	void setWait2();	
	void c_btn_key(QString s);




signals:
	void c_sigshowtime();
    void c_sigsetendtime(int time);
    void c_sigsetWait();
    void c_sigClearWnd(int pi_iMode);
    void c_sigSetTitle(char *pi_caBuff, int pi_flag, int pi_iFontSize);
    void c_sigSetContent(int pi_iLineNo, char *pi_caBuff, int pi_iFontSize, int pi_iAlign);
    void c_sigSetButton(char *pi_caBuff);
    void c_sigSetEdit(int pi_iLine, char *pi_caBuff, int pi_iFlag, int pi_iFontSize, int pi_iAlign);
    void c_sigSetSelect(char *pi_caBuff, int pi_iPos, int pi_iLen);
    void c_sigSetImage(char *pi_caPath, int pi_iX, int pi_iY, int pi_iW, int pi_iH);
    void c_sigSetContext2(int pi_iLine, char *pi_caBuffLeft, char *pi_caBuffRight, int pi_iModeLeft, int pi_iModeRight,int pi_iAlign_mode);
};

#endif // MAINWND_H
