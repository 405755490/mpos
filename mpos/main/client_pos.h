#ifndef CLIENT_POS_H
#define CLIENT_POS_H
#include "comm.h"

#ifdef  TWOLEVELMPOS

#define ENUMPASSKEY_LEN1 200
typedef struct
{
	char Areacode[2] ;
	char AreacodeName[10];
	char b_tek[17];
	char r_tek[17];
	char mingwenkey[ENUMPASSKEY_LEN1];
	char miwenkey[10][16];
	char mingwenkeyChk[10][8] ;
}MPOS_TWO_LEVEL_KEY;

extern int TwoLevelPos() ;
extern int TwoLevelPosGetB_TEK();
extern int TwoLevelPosJudgeHaveKEY();
extern int TwoLevelPosGetKeyFromMpos();
extern int TwoLevelPosSaveKeyFromMpos(char *pi_keyData , int pi_keyLen);
extern int TwoLevelPosCheckKey(char *pi_CliperKey , char*pi_PlainKeyChk , char *po_PlainKey);
extern int TwoLevelPosJudgeHaveB_TEK();

extern int TwoLevelPosShowWaitDialog();
extern int TwoChangePwd();
extern int TwoPutKeyToPinPad();
extern int TwoSendKeyToPinPad();
extern int  TwoLevelPosGetKey( MPOS_TWO_LEVEL_KEY  *pi_key) ;
#endif
#endif