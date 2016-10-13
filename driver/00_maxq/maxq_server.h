#ifndef __MAXQ_SERVER_H__
#define __MAXQ_SERVER_H__


#define DRIVER_VERSION "maxq32555 V2.10.01"

//#define __DRIVER_FOR_ZT2312E__


#define ZTCARD_USRCARD1    (0x11)      //�û��Ӵ���1
#define ZTCARD_USRCARD2    (0x12)      //�û��Ӵ���2, 606��֧��
#define ZTCARD_USRCARD3    (0x13)      //�û��Ӵ���3, 606��֧��
#define ZTCARD_RFID1       (0x21)      //�û��ǽӿ�1
#define ZTCARD_RFID2       (0x22)      //�û��ǽӿ�2, 606��֧��
#define ZTCARD_RFID3       (0x23)      //�û��ǽӿ�3, 606��֧��
#define ZTCARD_PSAM1       (0x31)      //PSAM1
#define ZTCARD_PSAM2       (0x32)      //PSAM2
#define ZTCARD_PSAM3       (0x33)      //PSAM3, 606��֧��
#define ZTCARD_PSAM4       (0x34)      //PSAM4, 606��֧��

#define ZTCARD_AT_ST       (0x01)      //AT24C01��AT24C02��AT24C04��AT24C08��AT24C16��ST14C02C��ST14C04C��GPM1K��GPM2K��GPM4K
#define ZTCARD_45D041      (0x02)      //45D041
#define ZTCARD_SLE1        (0x03)      //SLE4418��SLE4428
#define ZTCARD_SLE2        (0x04)      //SLE4432��SLE4442
#define ZTCARD_AT2         (0x05)      //AT24C32/64
#define ZTCARD_AT3         (0x06)      //93C46
#define ZTCARD_AT4         (0x07)      //AT153
#define ZTCARD_AT5         (0x08)      //AT102/AT1604
#define ZTCARD_AT6         (0x09)      //AT1608

#define ERR_CARD_SUCCESS 	0x00
#define ERR_CARD_BASE   	(-1000)
#define ERR_CARD_OPEN            (ERR_CARD_BASE + (-1))   //�򿪴���ʧ��
#define ERR_CARD_SENDCMD_FAIL    (ERR_CARD_BASE + (-2))   //����ʧ��
#define ERR_CARD_RHEAD           (ERR_CARD_BASE + (-3))   //����ʼ��־ʧ��
#define ERR_CARD_DATA            (ERR_CARD_BASE + (-4))   //������ʧ��
#define ERR_CARD_MAG23           (ERR_CARD_BASE + (-5))   //�����ŵ�����
#define ERR_CARD_ICRET           (ERR_CARD_BASE + (-6))   //IC���ش���״̬
#define ERR_CARD_UNKNOWN         (ERR_CARD_BASE + (-7))   //δ֪��Ƭ
#define ERR_CARD_TYPE            (ERR_CARD_BASE + (-8))   //δ֪��Ƭ
#define ERR_CARD_ACTIVE          (ERR_CARD_BASE + (-9))   //�ǽӴ��û�������ʧ��
#define ERR_CARD_SLOT            (ERR_CARD_BASE + (-10))  //����Ŀ�����
#define ERR_CARD_CMD             (ERR_CARD_BASE + (-11))  //����ִ��ʧ��
#define ERR_CARD_SETBPS          (ERR_CARD_BASE + (-12))  //���ò�����ʧ��
#define ERR_CARD_HALT_ITMEOUT    (ERR_CARD_BASE + (-13))  //Halt��ʱ
#define ERR_CARD_END             (ERR_CARD_BASE + (-14))  //δ���ֽ������
#define ZTCARD_RFID_HALT         (ERR_CARD_BASE + (-15))  //Haltʧ��

#define ZTCARD_NOT_SURPORT_CONTACT  (0x1)     //��֧�ֽӴ�ʽ�û���
#define ZTCARD_NOT_POSITION         (0x2)     //�Ӵ�ʽ�û���δ�嵽λ
#define ZTCARD_CONTACT_POWERON      (0x3)     //�Ӵ�ʽ�û������ϵ�
#define ZTCARD_CONTACT_POWEROFF     (0x4)     //�Ӵ�ʽ�û���δ�ϵ�
#define ZTCARD_NOT_SURPORT_PSAM     (0x5)     //��֧��PSAM��
#define ZTCARD_PSAM_POWERON         (0x6)     //PSAM�����ϵ�
#define ZTCARD_PSAM_POWEROFF        (0x7)     //PSAM��δ�ϵ�
#define ZTCARD_CONTACT_POWERFAIL    (0x8)     //�Ӵ�ʽ�û����ϵ�ʧ��
#define ZTCARD_PSAM_POWERFAIL       (0x9)     //PSAM���ϵ�ʧ��
#define ZTCARD_NOT_SURPORT_RFID     (0x10)    //��֧�ַǽ�
#define ZTCARD_RFID_WAIT_TIMEOUT    (0x11)    //�ȴ��������Ӧ����ʱ
#define ZTCARD_RFID_MORE            (0x12)    //�ж��ſ��ڸ�Ӧ��
#define ZTCARD_NOT_SURPORT_BPS      (0x13)    //������֧��(������)
#define ZTCARD_NOT_SURPORT_COMM     (0x13)    //���֧��

#define ZTRET_MAXQ_SUCCESS			0	//�����ɹ�
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
#define ZT566_SUCCESS           0                       //�ɹ�
#define ERR_566_BASE          (-1100)                 	//�������
#define ERR_566_NOT_INIT      (ERR_566_BASE + (-1))   	//δ��ʼ��
#define ERR_566_INIT          (ERR_566_BASE + (-2))   	//��ʼ������
#define ERR_566_WRITE         (ERR_566_BASE + (-3))   	//��������ʧ��
#define ERR_566_START         (ERR_566_BASE + (-4))   	//����ʼ��־��ʱ
#define ERR_566_READLN        (ERR_566_BASE + (-5))   	//�����ȳ�ʱ
#define ERR_566_READDATA      (ERR_566_BASE + (-6))   	//�����ݳ�ʱ
#define ERR_566_RSP_ERR       (ERR_566_BASE + (-7))   	//����ش���״̬
#define ERR_566_P_PARAM       (ERR_566_BASE + (-8))   	//P������Χ����
#define ERR_566_F_PARAM1      (ERR_566_BASE + (-9))   	//F��������1
#define ERR_566_F_PARAM2      (ERR_566_BASE + (-10))  	//F��������2
#define ERR_566_F_PARAM3      (ERR_566_BASE + (-11))  	//F��������3
#define ERR_566_F_PARAM4      (ERR_566_BASE + (-12))  	//F��������4
#define ERR_566_F_PARAM5      (ERR_566_BASE + (-13))  	//F��������5
#define ERR_566_F_PARAM6      (ERR_566_BASE + (-14))  	//F��������6
#define ERR_566_F_PARAM7      (ERR_566_BASE + (-15))  	//F��������7
#define ERR_566_F_PARAM8      (ERR_566_BASE + (-16))  	//F��������8
#define ERR_566_CONFIG        (ERR_566_BASE + (-17))  	//���������ļ�����
#define ERR_566_HEXLN		  (ERR_566_BASE + (-18))	//16���Ƴ��ȳ���
#define ERR_566_CRC           (ERR_566_BASE + (-19))    //crcУ��ʧ��
#endif 

#define MAX32555_SUCCESS           0                       //�ɹ�
#define ERR_32555_BASE          (-1200)                 	//�������
#define ERR_32555_NOTOPEN          (ERR_32555_BASE + (-1))    //32555δ��
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

int ztcard_psam_sts(int card_no);   //��ȡPSAM��״̬
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
 * parameter: byte -- input, 4: ������ĸ��ֽڣ� 8:�����8���ֽ� (���ֽ��ڸߵ�ַ�����ֽ��ڵ׵�ַ)
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
maxq_led:8210E led�ƿ��ƽӿ�
num_led:�ƺ�    1:��һ���ƣ������ң�
		2:�ڶ�����
		3:��������
		4:������ͬλ�õ�(λ��������������)
		5:ȫ��
mode:����ģʽ   0:���
		1:����
		2:���ƺ��ӳ���ƣ��ӳ�ʱ��ȡ����delaytime_on������
		3:����(����ʱ��ȡ����delaytime_on delaytime_off)
delaytime_on    ��������ʱ��
delaytime_of    �������ʱ��
*/
int maxq_led(int num_led,int mode,int delaytime_on,int delaytime_off);
#endif 



#endif
