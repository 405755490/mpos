
#ifndef __QT_UI_INCLUDED_H__
#define __QT_UI_INCLUDED_H__

#include "stdafx.h"

typedef struct
{
	pthread_cond_t *cont_query_qt;
	pthread_mutex_t *lock_cont_qt;
	int  nResult;		//UI�¼�: ȷ��-0x01��ȡ��-0x02, ��ʱ-0x03
}QT_CONDITION;


//��������QT�����SDK��ͬ������
void qt_set_condition(QT_CONDITION * pqc);
//֪ͨQT��UI�����˳�
//void qt_ui_quit();
#endif

