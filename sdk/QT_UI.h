
#ifndef __QT_UI_INCLUDED_H__
#define __QT_UI_INCLUDED_H__

#include "stdafx.h"

typedef struct
{
	pthread_cond_t *cont_query_qt;
	pthread_mutex_t *lock_cont_qt;
	int  nResult;		//UI事件: 确定-0x01，取消-0x02, 超时-0x03
}QT_CONDITION;


//设置用于QT界面和SDK的同步变量
void qt_set_condition(QT_CONDITION * pqc);
//通知QT的UI界面退出
//void qt_ui_quit();
#endif

