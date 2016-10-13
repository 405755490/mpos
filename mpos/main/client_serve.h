
#ifndef CLIENT_SERVER_H
#define CLIENT_SERVER_H
#include "comm.h"

#ifdef  ONELEVELMPOS

extern void  OneShowAreaCodeMenu( int pi_iPageNum) ;
extern int OneLevelPos() ;
extern int OneLeaderSet() ;
extern int OneOperSet() ;
extern char* OneGetAreaCode( char* pi_CodeNo) ;
extern int OneApplyKeyFromServer() ;
extern int OneLevelGetKey(char *po_CiphertextKey , int pi_CiphertextKey_len ,int pi_BeginNum );
extern int OneLevelSaveKey(char *pi_CiphertextKey ,int pi_KeyNum);
extern int OneDownKeyFromServer();
extern int OneUpdateReserveName();
extern int OneGetR_TEK( char *po_R_tekStr);
extern int OneShowR_TEKChk();
extern int OneSetTwoTransferPwd();
extern int OneOperChangePwd();
extern int OneJudgeLeaderOldPwd(char*pi_title , int pi_iLeaderNo);
extern int OneLeaderSetRootKey(int pi_iLeaderNo);
extern int OneInitInfoFlag();
extern int OneJudgeLegalIp( char *pi_IP  , int pi_len);
extern int  OneSetServerPort() ;
extern int OneSetIP( char *pi_title , char *pi_NeedSaveFlagName ,int pi_NeedJudgePwd);

extern int OneSetServerIP();
extern int OneSetLocalIP();
extern int OneSetServerIpAndPort();
extern int OneLeaderChangePwd( int pi_iLeaderNo);
extern int OneShowWaitDialog();
extern int OneSendKeyToTwoLevelPos(MPOS_ONE_LEVEL_KEY *pi_Onelevelkey);
extern int OneCalcPasskey( MPOS_ONE_LEVEL_KEY *pi_Onelevelkey);
extern int OnePutKeyToTwoLevelPosData( char *pi_AreaCode);
extern int  OnePutKeyToTwoLevelPos() ;






#endif
#endif

