
#ifndef __STDAFX_H_INCLUDED__
#define __STDAFX_H_INCLUDED__


#ifndef __OS_LINUX__
#define __OS_LINUX__
#endif

#ifdef __OS_LINUX__
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <linux/ioctl.h>
#include <sys/ioctl.h>
#else

#endif

#ifndef __TYPE_U8__
#define __TYPE_U8__
typedef unsigned char u8;
#endif

#ifndef __TYPE_U32__
#define __TYPE_U32__
typedef unsigned int  u32;
#endif

#ifndef __TYPE_S8__
#define __TYPE_S8__
typedef char          s8;
#endif

#ifndef __TYPE_U64__
#define __TYPE_U64__
typedef unsigned long long u64;
#endif

#endif