#ifndef _TOOL_H_
#define _TOOL_H_

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>
#include <termio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <termios.h>
#include <errno.h>
#include <limits.h>
#include <asm/ioctls.h>
#include <sys/time.h>
#include <time.h>
#include <iconv.h>
#include <stdarg.h>
///////////////////////////////////////////////////////////////////////
/*
  ��һ���ֽڵ�8��λ����ʾ��־��¼����
  bit1: ������־, �κ�ʱ����Ҫ��¼
  bit2: ������ʾ��Ϣ
  bit3: �û���������1
  bit4: �û���������2
  bit5: �û���������3
  bit6: �û���������4
  bit7: Ӳ��ָ����Ϣ,һ������²������¼
  bit8: ��־��Ϣ�������׼���,ͬʱ��¼�ļ�
*/
#define LOG_FLAG_ERR             (0x01)         //������־,�κ�ʱ����Ҫ��¼
#define LOG_FLAG_BASE            (0x02)         //������ʾ��Ϣ
#define LOG_FLAG_USER1           (0x04)         //�û���������
#define LOG_FLAG_USER2           (0x08)         //�û���������
#define LOG_FLAG_USER3           (0x10)         //�û���������
#define LOG_FLAG_USER4           (0x20)         //�û���������
#define LOG_FLAG_HDCMD           (0x40)         //Ӳ��ָ����Ϣ,һ������²�Ҫ�����¼
#define LOG_FLAG_STDIO           (0x80)         //��־ͬʱ�������׼���
///////////////////////////////////////////////////////////////////////

#define PUBLIC_SUCCESS           (0)
#define ERR_PUBLIC_BASE          (-10050)
#define ERR_PUBLIC_HEXLN         (ERR_PUBLIC_BASE + (-1))   //�����16�����ַ�������
#define ERR_PUBLIC_HEXCH         (ERR_PUBLIC_BASE + (-2))   //�Ƿ���16�����ַ�
#define ERR_PUBLIC_OPEN_FILE     (ERR_PUBLIC_BASE + (-3))   //���ļ�ʧ��
#define ERR_PUBLIC_FILENULL      (ERR_PUBLIC_BASE + (-4))   //�ļ�ָ��Ϊ��
#define ERR_PUBLIC_SPLIT_NUM     (ERR_PUBLIC_BASE + (-5))   //ָ���ķָ����Ŵ���
#define ERR_PUBLIC_LAST_POS      (ERR_PUBLIC_BASE + (-6))   //û���ҵ���Ľ���λ��
#define ERR_PUBLIC_FILE_CTL      (ERR_PUBLIC_BASE + (-7))   //�ļ�����ʧ��

void FormatStr(char *instr,char *outstr,int len,int filldirection,int fillchar);
void Yuan2Fen(char *instr,int len);
void Fen2Yuan(char *instr);
void loc_trim(const char *instr, char *outstr);
int  readIniFile(char *filename, char *key, char *value, int *len, char *def);
int  writeIniFile(char *filename, char *key, char *value);
int  getNField(char *instr, char *outstr,int n,int divch);
int  Asc2Bcd(unsigned char *in, unsigned char *out, int flag);
void Bcd2Asc(unsigned char *in, unsigned char *out, int ln);
void addEnter(char *src, int ln);
int  is_legal_ip(char *ip);
int  is_legal_ip2(char *ipstr, char ch);
void getDateTime(char *strdate,char *strtime);
unsigned char CRC(unsigned char *buffer, int count);
long  gCalcMac( char *cpVector,char *DataInput,char *key, char *DataOutput,int iDesMode );
int EppcalMac(char * from,char * to,int length,char * IV,char * TriKey);
int   DataXorTwoKey(char *pin1, char *pin2, char *pszRevData,int iMode);

/////////////////////////////////////////////////////////////////////////
int  GetFileLength(char *filename);
void get_preNday(char *buf, int ndays, int format);
int  file_isexist(char *fname);
char *gSplitBcd(char *soustr, short len, char *desstr);
char *gCompressAsc(char *soustr, short len, char *desstr);
void getDateTime2(char *strdate,char *strtime);
void getDateTime3(char *strdate,char *strtime, char *strmsec);
int  get_cur_msec();

int  replaceStr(char* src, char* find_str, char* rep_str, int src_len, int find_len, int rep_len);

FILE *create_log_file(FILE *fp, char *dir, char *pre_name, int log_days);
int  WriteLog2(FILE *fp, char app_log_flag, char cur_log_flag, const char *format, ...);

#endif 

