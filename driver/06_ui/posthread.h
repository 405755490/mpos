#ifndef POSTHREAD_H
#define POSTHREAD_H

#include <QThread>

class PosThread : public QThread
{
    Q_OBJECT

public:
    PosThread();
    ~PosThread();

    void run();
    void SleepTime(int pi_iSec);



};

#endif // POSTHREAD_H
