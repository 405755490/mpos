
/********************************************************************************
*	�������ƣ�                                                                   
*	��������:                                                                    
*	�޸�����:                                                                    
*	���������                                                                   
*	���������                                                                   
*	����ֵ��                                                                     
*	���ߣ�       Undefined                                                       
*******************************************************************************/
#include <sys/time.h>
#include "gui_interface.h"
#include "comm.h"
#include "client_pos.h"
#include "client_serve.h"

void * CtlTask(void *);

void * CtlTask(void * pBuf)
{
	do
	{
#ifdef ONELEVELMPOS
		OneLevelPos();
#endif
#ifdef TWOLEVELMPOS
		TwoLevelPos();
#endif		
	}while(1);
}






