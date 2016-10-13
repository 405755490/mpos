#ifndef StatusThread_H
#define StatusThread_H

#include <QThread>

class StatusThread : public QThread
{
    Q_OBJECT

public:
    StatusThread();
    ~StatusThread();

    int  c_SimInsert; //simø®≤Â»Î±Í÷æ

    void run();
    void SleepTime(int pi_iSec);
    void statusGPRS();
    void statusPower();

signals:
    void timetick();
    void batterytick(int level);
    void adaptertick(int flag);
    void gprstick(int level);
    void downdatatick(int flag);
};

#endif // StatusThread_H
