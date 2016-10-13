#ifndef __CHARSETCONVER_H__
#define __CHARSETCONVER_H__
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



//#define UINT8 unsigned char 
//#define UINT16 unsigned short 
//#define TRUE 1
//#define FALSE 0
//#define OUTLEN 1024 

extern int code_convert(char *from_charset, char *to_charset, char *inbuf,int inlen,char *outbuf,int outlen);


#endif
