#ifndef PACKET_H
#define PACKET_H

/*****************************************************************
trans_bitmap    �ṹ����ÿ�ֽ��׵���Ϣ���͡�λͼ
transtype      POS�ڽ���������
msg_id          ��Ϣ�����루����
processcode     �������
BIPMAP[8]
*****************************************************************/
typedef struct
{
    unsigned char   transtype;			//*== ����������==*/
    char    msg_id[3];			//*== ��Ϣ������==*/
    char    proccode[4];		//*== ������    ==*
    char    bitmap[17];			//*== ����λͼ  ==*/
} TBitmap;

TBitmap gBitmap[]=															
{
/*ǩ��*/{LOGON,		"\x08\x00" ,"\x00\x00\x00" ,"\x00\x38\x00\x00\x00\xC1\x00\x10"},
/*����*/{CHANGEPWD,"\x07\x00" ,"\x00\x00\x00" ,"\x00\x38\x00\x00\x00\xC1\x00\x01"},
/*������Կ*/{DOWNMAINKEY,"\x02\x00" ,"\x00\x00\x00" ,"\x30\x38\x04\x80\x00\xC0\x80\x01"},


}

#endif
