#ifndef __CSOCKET_H__
#define __CSOCKET_H__

#include <time.h>
#include <sys/time.h>

class CSocket
{
private:
	int    c_iSckfd;                       //�ļ�������
	bool   c_connected;                    //�Ƿ����ӳɹ�
	struct timeval send_time_val;

public:
	CSocket();
	virtual ~CSocket();

    bool  connected();
	bool  connect_srv(char *p_caHost, char *p_caPort);
	void  disconnect_srv();
	int   read(char *p_caOutstr, int p_iReadln, int p_iTimeout);
	int   write(char *p_caInstr, int p_iWriteln);
};

#endif  //__CSOCKET_H__
