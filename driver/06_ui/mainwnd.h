#ifndef MAINWND_H
#define MAINWND_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include "statusbar.h"
#include <QSignalMapper>
#include <QtGui/QPushButton>

//================================= *********���ܿ��� Begin**************=================================

//������ʾ������ͼƬ�����滻
//ʾ��
//API_UI_ShowImg("/yaffs/pos/yilianlogo.png", 50, 60, 240, 120); //��������ͼƬ


//�����Ƿ���8210�豸��1Ϊ�ǣ�0Ϊ��
#define   ZT8210_GUI         1  

//�����Ƿ�򿪵��Կ���
#define   GUI_DEBUG          0 

//����֧�ֵ�����  //msyh֧��GBK//������֧��GBK
//8210CϵͳĬ�ϲ���msyh�ֿ�

//#ifndef LAN_MSYH //΢���ź�
//#define LAN_MSYH          
//#endif

#ifndef LAN_HEI //����
#define LAN_HEI         
#endif

//#ifndef LAN_KAI //����
//#define LAN_KAI         
//#endif


//�����Ƿ��Ǵ����Ļ���  
#ifndef GUI_HAND          
#define GUI_HAND
#endif

//================================= *********���ܿ��� End**************=================================
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

#define BACKGROUND_IMG  "./images/bg.png"  //����ͼƬ
#define WAIT_IMG  		"./images/wait.png"  //����ͼƬ
//*********************��ʾ������궨��***************************************
#define TOTAL_WIDE                 240 //8225�豸�Ŀ��
#define TOTAL_HEIGHT               320 //8225�豸�ĸ߶�
#define STATUS_HEIGHT              20  //״̬���ĸ߶�


//X���� ����
#define LEFT_OF_LITTLE_BUTTON_X    5 //���Сbutton��X����
#define LEFT_OF_LARGE_BUTTON_X     5 //��button��X����
#define RIGHT_OF_LITTLE_BUTTON_X   (TOTAL_WIDE -(LEFT_OF_LITTLE_BUTTON_X)-WIDE_OF_LITTLE_BUTTON) //�ұ�Сbutton��X����

//Y���궨��
#define  HEIGHE_FIRST_BUTTON        35 //��һ��button�Ķ��߾�
#define  INTERVAL_BUTTON            15 //��ť֮��ļ�϶
#define  NEXT_POSITION_BUTTON     (HIGHT_OF_LITTLE_BUTTON+INTERVAL_BUTTON)//Сbutton�ĸ߶ȼ��� ��ť֮��ļ�϶
#define  NEXT_POSITION_BUTTON_L     (HIGHT_OF_LARGE_BUTTON+INTERVAL_BUTTON)//��button�ĸ߶ȼ��� ��ť֮��ļ�϶


#define WIDE_OF_LITTLE_BUTTON      105 //Сbutton�Ŀ��
#define HIGHT_OF_LITTLE_BUTTON     30 //Сbutton�ĸ߶�
#define WIDE_OF_LARGE_BUTTON       210 //��button�Ŀ��
#define HIGHT_OF_LARGE_BUTTON      33 //��button�ĸ߶�
//*********************��ʾ������궨��*******����********************************
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
	int GetKey( char *po_cKey); //��ȡ��ֵ
    void SaveLog(char *msg);
    char caTmp[128];
	char caKey[10];  //��ż�ֵ
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
    QLabel *c_labTitle1;     //��������
    QLabel *c_labTitle2;     //��������
    QLabel *c_labBt;        //��ť����
    QLabel *c_lab1;         //��������1
    QLabel *c_lab2;         //��������2
    QLabel *c_lab3;         //��������3
    QLabel *c_lab4;         //��������4
    QLabel *c_lab5;         //��������5
    QLabel *c_lab6;         //ʱ������
    QLabel *c_lab7;         //��ʾ��Ϣ
    QLabel *c_lab8;         //����ʱ
//************��Ϊbutton******************************************
    QPushButton *c_btn[5][3];  //��������


//***************************************************
    QLabel *c_labImage;     //ͼƬ
    QLabel *c_labImage2;    //ͼƬ
    QLabel *c_labImage3;    //ͼƬlogo
    QLineEdit *c_edit;      //�����
	StatusBar  *c_statusbar;  //״̬��
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
