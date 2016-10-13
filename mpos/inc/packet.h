#ifndef PACKET_H
#define PACKET_H

/*****************************************************************
trans_bitmap    结构定义每种交易的信息类型、位图
transtype      POS内交易类型码
msg_id          信息类型码（串）
processcode     处理代码
BIPMAP[8]
*****************************************************************/
typedef struct
{
    unsigned char   transtype;			//*== 交易类型码==*/
    char    msg_id[3];			//*== 信息类型码==*/
    char    proccode[4];		//*== 处理码    ==*
    char    bitmap[17];			//*== 交易位图  ==*/
} TBitmap;

TBitmap gBitmap[]=															
{
/*签到*/{LOGON,		"\x08\x00" ,"\x00\x00\x00" ,"\x00\x38\x00\x00\x00\xC1\x00\x10"},
/*改密*/{CHANGEPWD,"\x07\x00" ,"\x00\x00\x00" ,"\x00\x38\x00\x00\x00\xC1\x00\x01"},
/*下载密钥*/{DOWNMAINKEY,"\x02\x00" ,"\x00\x00\x00" ,"\x30\x38\x04\x80\x00\xC0\x80\x01"},


}

#endif
