


#ifndef _Tools_HEADFILES_
#define _Tools_HEADFILES_

#define EMV_READ_RF_MASK    (U8)0x80
#define EMV_READ_IC_MASK    (U8)0x40
#define EMV_READ_MC_MASK    (U8)0x20
#define EMV_READ_KB_MASK    (U8)0x10
extern void Disp_Msg(char *message);

extern int StrTrim0(char *dest,char *src,int len,int type);

extern int ERR_MSG(char *str);
extern void APP_SUCC_MSG(char * str);
extern void  MSG(char *str);
extern void DispXY(int x, int y, char *string);

extern void  ClrScr(char *Title);

extern void AsciiToBcd (char *bcd_buf ,const char *ascii_buf ,int conv_len ,char type ) ;

extern void BcdToAscii (char *ascii_buf , char *bcd_buf ,int conv_len ,char type );
extern void Asc_Bcd (char *bcdbuf , char *ascbuf , int asclen) ;
extern int   Confirm (int TimeOut);     
extern void DealPan(char *buffer,int len,char *pan);
extern void addstr(char *buffer,int len,char a);
extern int StrTrim(char *dest,char *src,int len,int type);
extern int PreDial();
extern int Dial(void);
extern int Hangup(void);
extern int Send(char *buf,int buf_len);

int DispInsertICCard(char *pPrompt);
int DispOutICCard(char *pPrompt);
void Blackprintf(int x,int y,char * disp);
int GetDialNo(char * pTelno,int transtype,int dial);
extern void DealAmount2(char *buffer,char *pAmount);
extern void TRACE(char * ptr, unsigned char * buf ,int len);
extern void Lcd_Clr();
void Lcd_printf(const char * format, ...);

void Lcd_printf_Small(int flush_flag,const char * format, ...);

void Lcd_printf_TooSmall(const char * format, ...);
void Lcd_printf_verysmall(const char * format, ...);




extern int ERR_MSG_nohead(char *str);
extern int AddDataToFile(char *filename , char *pi_str ,int pi_len ,int pi_no) ;
extern int ReadDataFromFile(char *filename , char *po_str ,int pi_len ,int pi_NoTotal ,int pi_begin);
extern char _CalcLRC(char *cpBuf, int iLength) ;
extern void  posk_pkg_log(int flag,int pkg_ln,char *pkg) ;
extern int GetUnionKeys( int pi_Only0_9 , char* po_keys) ;
extern int  SerialOpen();

extern int SerialSendData(char *pi_SendData ,int pi_DataLen);

extern int SerialRecvData(char *po_RecvData );

//====================for jxnx=============================================
#endif




































