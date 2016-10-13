//===================================================================
// ��    λ��������֤ͨ���ſƼ����޹�˾
// ��    �ߣ�����
// ��    ����1.0.0	[���汾��.�ΰ汾��.�޶��汾��]
// �������ڣ�2013-6-29 14:33
// �޸����ڣ�2013-6-29 14:33
// ˵    ����include file for standard system include files
// �޸ļ�¼��
//===================================================================


#ifndef _STD_HEAD_H_
#define _STD_HEAD_H_

//===================================================================

#ifdef PC
	typedef char					s8;
	typedef unsigned char   		u8;

	typedef short					s16;
	typedef unsigned short  		u16;
	
	typedef int						s32;
	typedef unsigned int			u32;
#else	
	typedef char					s8;
	typedef unsigned char   		u8;

	typedef short					s16;
	typedef unsigned short  		u16;
	
	typedef long					s32;
	typedef unsigned long			u32;
#endif

	#ifndef NULL
		#define	NULL				(0)
	#endif
	
	#ifndef YES
		#define	YES					(1)
	#endif
	
	#ifndef NO
		#define	NO					(0)
	#endif
	
	#ifndef ON
		#define	ON					(1)
	#endif
	
	#ifndef OFF
		#define	OFF					(0)
	#endif
	
	#ifndef SPK_MUTE
		#define	SPK_MUTE			(1)
	#endif
	#ifndef SPK_VOICE
		#define	SPK_VOICE			(0)
	#endif
	               

	
	#define _MASK(__n,__s)  (((1<<(__s))-1)<<(__n))
	
	#define MIN(a,b) 		(((a) < (b)) ? (a) : (b))
	#define MAX(a,b) 		(((a) > (b)) ? (a) : (b))

	#define	CLEAR(st)		API_memset((void*)&(st),0,sizeof(st));
	#define VALRESET(v)		if(v){(v)=0;}else{(v)=1;}

//===================================================================
	
	#include "ks_stdlib.h"
	#include "ks_gui.h"
	#include "ks_sdk.h"
	#include "ks_sysunit.h"

	#include "app_sdk.h"
//===================================================================
	
#endif
