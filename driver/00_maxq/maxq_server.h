#ifndef __MAXQ_SERVER_H__
#define __MAXQ_SERVER_H__


#define DRIVER_VERSION "maxq32555 V2.10.01"

//#define __DRIVER_FOR_ZT2312E__


#define ZTCARD_USRCARD1    (0x11)      //用户接触卡1
#define ZTCARD_USRCARD2    (0x12)      //用户接触卡2, 606不支持
#define ZTCARD_USRCARD3    (0x13)      //用户接触卡3, 606不支持
#define ZTCARD_RFID1       (0x21)      //用户非接卡1
#define ZTCARD_RFID2       (0x22)      //用户非接卡2, 606不支持
#define ZTCARD_RFID3       (0x23)      //用户非接卡3, 606不支持
#define ZTCARD_PSAM1       (0x31)      //PSAM1
#define ZTCARD_PSAM2       (0x32)      //PSAM2
#define ZTCARD_PSAM3       (0x33)      //PSAM3, 606不支持
#define ZTCARD_PSAM4       (0x34)      //PSAM4, 606不支持

#define ZTCARD_AT_ST       (0x01)      //AT24C01、AT24C02、AT24C04、AT24C08、AT24C16、ST14C02C、ST14C04C、GPM1K、GPM2K、GPM4K
#define ZTCARD_45D041      (0x02)      //45D041
#define ZTCARD_SLE1        (0x03)      //SLE4418、SLE4428
#define ZTCARD_SLE2        (0x04)      //SLE4432、SLE4442
#define ZTCARD_AT2         (0x05)      //AT24C32/64
#define ZTCARD_AT3         (0x06)      //93C46
#define ZTCARD_AT4         (0x07)      //AT153
#define ZTCARD_AT5         (0x08)      //AT102/AT1604
#define ZTCARD_AT6         (0x09)      //AT1608

#define ERR_CARD_SUCCESS 	0x00
#define ERR_CARD_BASE   	(-1000)
#define ERR_CARD_OPEN            (ERR_CARD_BASE + (-1))   //打开串口失败
#define ERR_CARD_SENDCMD_FAIL    (ERR_CARD_BASE + (-2))   //发送失败
#define ERR_CARD_RHEAD           (ERR_CARD_BASE + (-3))   //读开始标志失败
#define ERR_CARD_DATA            (ERR_CARD_BASE + (-4))   //读数据失败
#define ERR_CARD_MAG23           (ERR_CARD_BASE + (-5))   //二三磁道错误
#define ERR_CARD_ICRET           (ERR_CARD_BASE + (-6))   //IC返回错误状态
#define ERR_CARD_UNKNOWN         (ERR_CARD_BASE + (-7))   //未知卡片
#define ERR_CARD_TYPE            (ERR_CARD_BASE + (-8))   //未知卡片
#define ERR_CARD_ACTIVE          (ERR_CARD_BASE + (-9))   //非接触用户卡激活失败
#define ERR_CARD_SLOT            (ERR_CARD_BASE + (-10))  //错误的卡座号
#define ERR_CARD_CMD             (ERR_CARD_BASE + (-11))  //命令执行失败
#define ERR_CARD_SETBPS          (ERR_CARD_BASE + (-12))  //设置波特率失败
#define ERR_CARD_HALT_ITMEOUT    (ERR_CARD_BASE + (-13))  //Halt超时
#define ERR_CARD_END             (ERR_CARD_BASE + (-14))  //未发现结束标记
#define ZTCARD_RFID_HALT         (ERR_CARD_BASE + (-15))  //Halt失败

#define ZTCARD_NOT_SURPORT_CONTACT  (0x1)     //不支持接触式用户卡
#define ZTCARD_NOT_POSITION         (0x2)     //接触式用户卡未插到位
#define ZTCARD_CONTACT_POWERON      (0x3)     //接触式用户卡已上电
#define ZTCARD_CONTACT_POWEROFF     (0x4)     //接触式用户卡未上电
#define ZTCARD_NOT_SURPORT_PSAM     (0x5)     //不支持PSAM卡
#define ZTCARD_PSAM_POWERON         (0x6)     //PSAM卡已上电
#define ZTCARD_PSAM_POWEROFF        (0x7)     //PSAM卡未上电
#define ZTCARD_CONTACT_POWERFAIL    (0x8)     //接触式用户卡上电失败
#define ZTCARD_PSAM_POWERFAIL       (0x9)     //PSAM卡上电失败
#define ZTCARD_NOT_SURPORT_RFID     (0x10)    //不支持非接
#define ZTCARD_RFID_WAIT_TIMEOUT    (0x11)    //等待卡进入感应区超时
#define ZTCARD_RFID_MORE            (0x12)    //有多张卡在感应区
#define ZTCARD_NOT_SURPORT_BPS      (0x13)    //参数不支持(波特率)
#define ZTCARD_NOT_SURPORT_COMM     (0x13)    //命令不支持

#define ZTRET_MAXQ_SUCCESS			0	//操作成功
#define ZTRET_MAXQ_ERROR				-100
#define ZTRET_MAXQ_TIMEOUT			-101

#define ZTRET_ICC_PARAM_UNSUPPORT
#define ZTRET_ICC_NOCARD
#define ZTRET_ICC_POWER_UP
#define ZTRET_ICC_POWER_FAILD
#define ZTRET_ICC_TIMEOUT
#define ZTRET_ICC_DATA_ERROR

#define ZTRET_PSAM_PARAM_UNSUPPORT
#define ZTRET_PSAM_NOCARD
#define ZTRET_PSAM_POWER_UP
#define ZTRET_PSAM_POWER_FAILD
#define ZTRET_PSAM_TIMEOUT
#define ZTRET_PSAM_DATA_ERROR

#ifndef __DRIVER_FOR_ZT2312E__
#define ZT566_SUCCESS           0                       //成功
#define ERR_566_BASE          (-1100)                 	//错误基数
#define ERR_566_NOT_INIT      (ERR_566_BASE + (-1))   	//未初始化
#define ERR_566_INIT          (ERR_566_BASE + (-2))   	//初始化错误
#define ERR_566_WRITE         (ERR_566_BASE + (-3))   	//发送命令失败
#define ERR_566_START         (ERR_566_BASE + (-4))   	//读开始标志超时
#define ERR_566_READLN        (ERR_566_BASE + (-5))   	//读长度超时
#define ERR_566_READDATA      (ERR_566_BASE + (-6))   	//读数据超时
#define ERR_566_RSP_ERR       (ERR_566_BASE + (-7))   	//命令返回错误状态
#define ERR_566_P_PARAM       (ERR_566_BASE + (-8))   	//P参数范围错误
#define ERR_566_F_PARAM1      (ERR_566_BASE + (-9))   	//F参数错误1
#define ERR_566_F_PARAM2      (ERR_566_BASE + (-10))  	//F参数错误2
#define ERR_566_F_PARAM3      (ERR_566_BASE + (-11))  	//F参数错误3
#define ERR_566_F_PARAM4      (ERR_566_BASE + (-12))  	//F参数错误4
#define ERR_566_F_PARAM5      (ERR_566_BASE + (-13))  	//F参数错误5
#define ERR_566_F_PARAM6      (ERR_566_BASE + (-14))  	//F参数错误6
#define ERR_566_F_PARAM7      (ERR_566_BASE + (-15))  	//F参数错误7
#define ERR_566_F_PARAM8      (ERR_566_BASE + (-16))  	//F参数错误8
#define ERR_566_CONFIG        (ERR_566_BASE + (-17))  	//键盘配置文件错误
#define ERR_566_HEXLN		  (ERR_566_BASE + (-18))	//16进制长度出错
#define ERR_566_CRC           (ERR_566_BASE + (-19))    //crc校验失败
#endif 

#define MAX32555_SUCCESS           0                       //成功
#define ERR_32555_BASE          (-1200)                 	//错误基数
#define ERR_32555_NOTOPEN          (ERR_32555_BASE + (-1))    //32555未打开
#define ERR_32555_OPEN_ALREADY	   (ERR_32555_BASE + (-2))

int  ztcard_open(char *port_str);
int ztcard_close();
int ztcard_reset();

int ztcard_ic_sts(int card_no);

int ztcard_contact_setbps(int card_no, int bps);
int ztcard_contact_poweron(int card_no, int delay_ms, char *ATR);
int ztcard_contact_poweroff(int card_no);
int ztcard_contact_set_cardtype(int card_no, int card_type);
int ztcard_contact_get_cardtype(int card_no);
int ztcard_contact_sts(int card_no);
int ztcard_contact_apdu(int card_no, char *inapdu, int inapdu_ln, char *outapdu, int *outapdu_ln);

int ztcard_psam_sts(int card_no);   //获取PSAM卡状态
int ztcard_psam_setbps(int card_no, int bps);
int ztcard_psam_poweron(int card_no, int delay_ms, char *ATR);
int ztcard_psam_poweroff(int card_no);
int ztcard_psam_set_cardtype(int card_no, int card_type);
int ztcard_psam_get_cardtype(int card_no);
int ztcard_psam_apdu(int card_no, char *inapdu, int inapdu_ln, char *outapdu, int *outapdu_ln);

int ztcard_rfid_active(int delay_ms, char *card_type, char *uid, char *ATR);
int ztcard_rfid_halt(int delay_ms);
int ztcard_rfid_apdu(int card_no, char *inapdu, int inapdu_ln, char *outapdu, int *outapdu_ln);


int ztcard_ic_poweron(int card_no, int delay_ms, char *ATR);
int ztcard_ic_poweroff(int card_no);
int ztcard_ic_read(int card_no, unsigned short addr, unsigned short len, unsigned char * data);
int ztcard_ic_pinauth(int card_no, unsigned char pinlen, unsigned char *pindata);
int ztcard_ic_pininit(int card_no, unsigned char pinlen, unsigned char *pindata);
int ztcard_ic_write(int card_no, unsigned short addr, unsigned short len, unsigned char * data);

int ztcard_rfmem_active(int delay_ms, char *card_type, char *uid, char *ATR);
int ztcard_rfmem_halt(int delay_ms);
int ztcard_rfmem_pinauth( unsigned char sector,unsigned char pintype, unsigned char *pindata);
int ztcard_rfmem_read_block(unsigned char block,unsigned char * data);
int ztcard_rfmem_write_block(unsigned char block,unsigned char * data);

int maxq_get_chipid(char * sn);
int maxq_beep(char delaytime_on,char delaytime_off,char times);


int ztmag_read2(char *mag2, char *mag3);
int ztmag_read3(char *mag1,char *mag2, char *mag3);

int ztcard_mag_read(char * track1,char * track2,char * track3,int delay_ms);
int ztcard_firmware_version(char *cup_ver, char *bank_ver, char *fact_ver);

int ztcard_set_polling_start(int param);
int ztcard_set_polling_end();
int ztcard_get_polling_status();
int ztcard_get_mag_data(char * track1,char * track2,char * track3);

/*
 * parameter: byte -- input, 4: 随机数四个字节， 8:随机数8个字节 (高字节在高地址，底字节在底地址)
 *
 */
int maxq_get_random_data(unsigned short byte, char *random);


#ifndef __DRIVER_FOR_ZT2312E__
int kbd_566_getVersion(char *version);    //get firmware version
int kbd_566_open(int bps, char *port_str);
int kbd_566_close();

int kbd_566_enable(int param);
char kbd_566_getkey();
void kbd_566_clear();
int kbd_566_reset(int param);

int kbd_566_load_MK_mingwen(int mk_idx, char *mk, int mk_ln, char *chk_str);
int kbd_566_load_MK_miwen(int rk_idx, int mk_idx, char *mk, int mk_ln, int rk_ln,char *chk_str);

int kbd_566_loadRKey(int mk_idx, char *mk, int mk_ln, char *chk_str);
int kbd_566_loadMK_plain(int mk_idx, char *mk, int mk_ln, int chk_flag, int old_mk_ln, char *chk_str);
int kbd_566_loadMK_cipher(int rk_idx, int mk_idx, char *mk, int mk_ln, int chk_flag, int rk_ln, char *chk_str);
int kbd_566_loadWK(int mk_idx, int wk_idx, char *wsWK, int mk_ln, int wk_ln, char *chk_str);

int kbd_566_get_chk(int index, char *chk_str);

int kbd_566_setWkKey(int mk_idx,int wk_idx);
int kbd_566_enable(int param);
int kbd_566_startPwdInput(int pwd_ln, int en_mode, int timeout);
int kbd_566_getPassword(int mk_idx, int wk_idx, char *pwd, char *card_no);

int kbd_566_dataMac(char *indata, int inlen, char *outData,int mk_idx, int wk_idx, int mk_or_wk, int mac_type, int key_ln, int split_len);
int kbd_566_dataEncrypt(int en_or_de, char *instr, int inlen, char *outstr, int mk_idx, int wk_idx, int ecb_or_cbc,int mk_or_wk, int key_ln); 
int kbd_566_getStatus(); 
int kbd_566_selfdestruct_enable();
int kbd_566_selfdestruct_isenable();
int kbd_566_selfdestruct_status(void);

/*
maxq_led:8210E led灯控制接口
num_led:灯号    1:第一个灯（从左到右）
		2:第二个灯
		3:第三个灯
		4:第三个同位置灯(位置三上有两个灯)
		5:全灯
mode:亮灯模式   0:灭灯
		1:亮灯
		2:亮灯后延迟灭灯（延迟时间取决于delaytime_on参数）
		3:灯闪(亮灭时间取决于delaytime_on delaytime_off)
delaytime_on    灯亮持续时间
delaytime_of    灯灭持续时间
*/
int maxq_led(int num_led,int mode,int delaytime_on,int delaytime_off);
#endif 



#endif
