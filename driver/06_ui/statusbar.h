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
    QTimer *c_tmrTime; //时间显示定时器

    QLabel   *c_labTime;         //时间显示文字
    QLabel   *c_battery;         //电池图标
    QLabel   *c_adapter;         //适配器图标
    QLabel   *c_signal;          //信号量图标
    QLabel   *c_data;            //数据信号图标
};
#endif // STATUSBAR_H
