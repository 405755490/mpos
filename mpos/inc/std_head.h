//===================================================================
// 单    位：深圳市证通金信科技有限公司
// 作    者：付庆
// 版    本：1.0.0	[主版本号.次版本号.修订版本号]
// 创建日期：2013-6-29 14:33
// 修改日期：2013-6-29 14:33
// 说    明：include file for standard system include files
// 修改记录：
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
