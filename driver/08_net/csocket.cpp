#include "csocket.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

/*[method***********************************************************************
 *def:  public ivoid CSocket::CSocket()
 *func: ������������๹�캯��.
*****************************************************************************]*/
CSocket::CSocket()
{
	c_iSckfd = 0;
    c_connected = false;

	//��ʱ����
	send_time_val.tv_sec  = 10;  //���������ӵĳ�ʱʱ��,��Ϊ�̶���10��,���ý��ճ�ʱ,���ղ��÷�������ʽ
	send_time_val.tv_usec = 0;
}

/*[method***********************************************************************
 *def:  public ivoid CSocket::~CSocket()
 *func: ����������������.
*****************************************************************************]*/
CSocket::~CSocket()
{
	disconnect_srv();
}

/*[method***********************************************************************
 *def:  public bool CSocket::connect_srv(char *p_caHost, char *p_caPort)
 *func: ���ӷ�����
*****************************************************************************]*/
bool CSocket::connect_srv(char *p_caHost, char *p_caPort)
{
	char caTmpIp[32]={0};
	memcpy(caTmpIp, p_caHost, strlen(p_caHost));
	struct sockaddr_in servaddr;

	c_iSckfd = socket(PF_INET, SOCK_STREAM, 0);			//��ʽsocket��TCP
	setsockopt(c_iSckfd, SOL_SOCKET, SO_SNDTIMEO, &send_time_val, sizeof(struct timeval));

	bzero(&servaddr, sizeof(struct sockaddr_in));     //��ʼ��servaddr
	servaddr.sin_family = PF_INET;
	servaddr.sin_port = htons(atoi(p_caPort));
	printf("caTmpIp[%s]\n", caTmpIp);
	if((servaddr.sin_addr.s_addr = inet_addr(caTmpIp)) == INADDR_NONE)
	{
		printf("The connect is not correct  111!\n");
		close(c_iSckfd);
		c_iSckfd = 0;
		return false;	//The IP is not correct!
	}

    c_connected = false;
	if(connect( c_iSckfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr))==0)	//��������
	{
		/* ���� socket ����Ϊ��������ʽ */
		if(fcntl( c_iSckfd, F_SETFL, O_NONBLOCK) == -1) return false;
		c_connected = true;
		return true;   //�������ӳɹ�
	}
	else
	{
		printf("The connect is not correct  222!\n");
		close(c_iSckfd);
		c_iSckfd = 0;
		return false;
	}
	printf("The connect is not correct!  333\n");
	return false;
}

/*[method***********************************************************************
 *def:  public void CSocket::disconnect_srv()
 *func: �Ͽ�����
*****************************************************************************]*/
void  CSocket::disconnect_srv()
{
	if(c_iSckfd == 0 ) return;
	if(c_connected==true) close(c_iSckfd);
	c_iSckfd = 0;
	c_connected = false;
}

/*[method***********************************************************************
 *def:  public int CSocket::read(char *p_caOutstr, int p_iReadln, int p_iTimeout)
 *func: ��ָ��ʱ���ڶ�ָ���������ݡ�
 *args: #p_caOutstr      ����������
        #p_iReadln       ��Ҫ��ȡ�����ݳ���
        #p_iTimeout      ��ʱʱ��
 *ret:  ret=0      �ɹ���������
        ret<0      ������ʧ��
*****************************************************************************]*/
int CSocket::read(char *p_caOutstr, int p_iReadln, int p_iTimeout)
{
	int ready_recv_ln, cur_recv_ln;
    time_t begin;

    if( c_iSckfd == 0) 
    {
    	printf("CSocket::read c_iSckfd == 0  return -1!\n");
    	return -1;     //��ʼ��ʧ��.ָ��������������
    }
    	
    begin = time(NULL);
	ready_recv_ln = 0;
	cur_recv_ln = 0;
	while( 1==1 )
	{
    	cur_recv_ln = recv(c_iSckfd, p_caOutstr+ready_recv_ln, p_iReadln - ready_recv_ln, 0);
		if( 0 <= cur_recv_ln )
		{
			//printf("read data len is��%d��\n" ,cur_recv_ln);
			return cur_recv_ln;
		}			
		/*
		ready_recv_ln = ready_recv_ln + cur_recv_ln;
		if( p_iReadln <= ready_recv_ln) 
		{
			printf("CSocket::read p_iReadln <= ready_recv_ln  return ready_recv_ln[%d]!\n", ready_recv_ln);
			return ready_recv_ln;
		}
		
			
		if( cur_recv_ln > 0 ) 
			continue;
		*/	    		
    	usleep(1000);

		if( (time(NULL)-begin) >= p_iTimeout ) 
		{
			printf("CSocket::read Timeout  return -2!\n");
			return -2;
		}
			
    }
	printf("CSocket::read  return -3!\n");
    return -3;
}

/*[method***********************************************************************
 *def:  public int CSocket::write(char *p_caInstr, int p_iWriteln)
 *func: ��������
 *args: #p_caInstr    ��Ҫ���͵�����
        #p_iWriteln   ��Ҫ���͵����ݳ���
*****************************************************************************]*/
int CSocket::write(char *p_caInstr, int p_iWriteln)
{
	int result=0;

	if( c_iSckfd == 0)	return -1;  //ָ����������������

	result = send( c_iSckfd, p_caInstr, p_iWriteln, 0);    //����ɹ������ط����ֽ���

	if(result < 0) return -2;    //�������ݴ���
	if(result != p_iWriteln)   return -3;      //�������ݳ��ȴ���

	return 0;
}

bool CSocket::connected()
{
    return c_connected;
}
