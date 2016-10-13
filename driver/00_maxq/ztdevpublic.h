/******************************************************************************
  �� �� ��:  ztdevpublic.c
  ��ǰ�汾:  V1.00.00  2012/08/24    
  ��������:  linux�豸�������ú���ͷ�ļ��������������궨��ȡ�
  �޸ļ�¼:  
  					 V1.00.00  Billy  2012/09/18  ��һ�α�д		
  Copyright (C), 2008-2018, Shenzhen Zhengtong Electronics Co.LTD
******************************************************************************/
#ifndef __ZTLOGDEV_H__
#define __ZTLOGDEV_H__

#define ZTLOG_OUTDEV_NONE			(0x00)
#define ZTLOG_OUTDEV_FILE			(0x01)
#define ZTLOG_OUTDEV_STDIO		(0x02)
#define ZTLOG_OUTDEV_BOTH			(0x03)

#define ZTLOG_CRIS					(0x00)				 //�ؼ���Ϣ
#define ZTLOG_EROR          (0x01)         //������Ϣ
#define ZTLOG_WARN       		(0x02)         //������Ϣ
#define ZTLOG_FUNC          (0x03)         //��ʾ��Ϣ
#define ZTLOG_INFO          (0x04)         //��������
#define ZTLOG_RECV          (0x05)         //ͨ������
#define ZTLOG_SEND          (0x06)         //ͨ������
#define ZTLOG_RESV          (0x07)         //����

typedef struct 
{
	int outdev;					//����豸
	int debuglevel;			//���Եȼ�
	int logmaxlen;			//�����־���ȣ���MΪ��λ1-8M,���Ϊ8M
	char path[32];			//��־���·��
	char devname[32];		//��־�豸����
}ZTDEVLOG;

/* openiniʹ��inifile����α���������INI��Ϊ����
 * ����ֵ:
 *	 0: �ɹ�
 *	-1: INI�ļ���ʽ��
 *	-2: ���ļ��� 
*/
extern int ztini_open(const char *inifile);
/* �����α������ͷ����õ��ڴ棬����INI��Ϊ������ */
extern void ztini_close(void);
/* �������в���seg�ε�item�������NULL�����򷵻�ָ����ֵ��ָ��
 * ���ص�ָ���ѷ����ڴ棬�ɵ������ͷ� 
 */
extern int  ztini_get_item(char *seg, char *item, char *value);
/* ������������ֵ��������-1 */
extern int  ztini_get_item_int(char *seg, char *item);

extern void ztlog_enable(ZTDEVLOG ztlog);
extern int ztlog_printf(int loglevel,char * format,...);
extern int ztlog_tofile(char * filename,char * format,...);
#endif  //__ZTLOGDEV__
