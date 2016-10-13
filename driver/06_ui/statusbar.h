#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QtGui>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>
#include "statusthread.h"

class QWidget;

class StatusBar : public QWidget
{
    Q_OBJECT
public:
    StatusBar(QWidget *parent = 0);
    ~StatusBar(void);

    int  get_cur_msec();
    void getDateTime(char *p_strdate,char *p_strtime, char *p_strmsec, int *p_iweek);

protected:

private slots:
    void onTimeShow();
    void updateBattery(int level);
    void updateAdapter(int flag);
    void updateData(int flag);
    void updateGPRS(int level);

private:
    StatusThread * c_timeThread;
    StatusThread * c_statusThread;
    QTimer *c_tmrTime; //ʱ����ʾ��ʱ��

    QLabel   *c_labTime;         //ʱ����ʾ����
    QLabel   *c_battery;         //���ͼ��
    QLabel   *c_adapter;         //������ͼ��
    QLabel   *c_signal;          //�ź���ͼ��
    QLabel   *c_data;            //�����ź�ͼ��
};
#endif // STATUSBAR_H
