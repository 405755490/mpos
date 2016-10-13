
#ifndef _KS_GUI_H_
#define _KS_GUI_H_

typedef u32	COLOR;	

#define 	RGB_NULL		(0)

#define 	CNUL			(0)

#define 	RGB(r,g,b)		(((r)<<24)|((g)<<16)|((b)<<8))

#define 	RGB_M(r,g,b,a)	(((r)<<24)|((g)<<16)|((b)<<8)|(a))

#define 	CR(c)			(((c)>>24)&0xFF)

#define 	CG(c)			(((c)>>16)&0xFF)

#define 	CB(c)			(((c)>>8)&0xFF)

#define 	CA(c)			((c)&0xFF)



#define ColorWhite			RGB(0xFF,0xFF,0xFF)	//��ɫ

#define ColorBlack			RGB(0x00,0x00,0x00)	//��ɫ

#define ColorRed			RGB(0xFF,0x00,0x00)	//�tɫ

#define ColorGreen			RGB(0x00,0xFF,0x00)	//�Gɫ

#define ColorBlue			RGB(0x00,0x00,0xFF)	//�Rɫ

#define ColorYellow			RGB(0xFF,0xFF,0x00)	//�Sɫ

#define ColorCyan			RGB(0x00,0xFF,0xFF)	//�\�Rɫ

#define ColorMagenta		RGB(0xFF,0x00,0xFF)	//�Ҽtɫ



#define ColorOrange			RGB(0xFF,0x7F,0x00)	//��ɫ

#define ColorViolet			RGB(0x4F,0x2F,0x4F)	//��ɫ

#define ColorBrown			RGB(0xA5,0x2A,0x2A)	//��ɫ

#define ColorGrey			RGB(0xC0,0xC0,0xC0)	//��ɫ



#define ColorGold			RGB(0xCD,0x7F,0x32)	//��ɫ

#define ColorSilver			RGB(0xE6,0xE8,0xFA)	//�yɫ

#define ColorScarlet		RGB(0x8C,0x17,0x17)	//�r�tɫ

#define ColorAzure			RGB(0xF0,0xFF,0xFF)	//���Rɫ

#define ColorBlueviolet		RGB(0x8A,0x2B,0xE2)	//����ɫ



#define ColorCrimson		RGB(0xDC,0x14,0x3C)	//�r�tɫ

#define ColorDarkblue		RGB(0x00,0x00,0x8B)	//���Rɫ

#define ColorDarkgray		RGB(0xA9,0xA9,0xA9)	//���ɫ	


typedef struct

{

    int 				x;

    int					y;

}POINT;



typedef struct

{

    int 				x;

    int					y;

    int 				w;

    int 				h;

    int 				x2;

    int					y2;

}RECT;



#define RECT2(r)		(r)->x2=(r)->x+(r)->w-1;(r)->y2=(r)->y+(r)->h-1;



enum DISP_TYPE

{

	DISP_DEPTH_1		=0x00000001,	//��ɫ���     ��ɫ

	DISP_DEPTH_8		=0x00000008,	//��ɫ���  8λ��ɫ

	DISP_DEPTH_16		=0x00000010,	//��ɫ��� 16λ��ɫ

	DISP_DEPTH_24		=0x00000018,	//��ɫ��� 24λ��ɫ

	DISP_DEPTH_32		=0x00000020,	//��ɫ��� 32λ��ɫ

	DISP_DEPTH			=0x000000FF,	//��ɫ��� ����

	

	DISP_MONOC			=0x00010000,	//��ɫ

	DISP_RGB565			=0x00020000,	//RGB565��ʽ

	DISP_RGB888			=0x00040000,	//RGB888��ʽ

	DISP_RGB32			=0x00080000,	//RGB888��ʽ

	DISP_TRANSPARENT	=0x00100000		//֧��ͨ͸��ɫ����ͼƬʹ��

};

	

typedef struct

{

	u8					mask;			//0x1B

	u8					type;			//0xF1

	u8					ver;			//0x01

	u8					offset;			//���ݿ�ʼ������ƫ�Ƶ�ַ(speed��ʼ������)

										//ǰ��Ϊ�����ļ�ר��ͷ����

	u32					disp_type;		//

    COLOR 				trans_color;	//RGB(r,g,b,a):rgbΪ��ɫͼƬʹ��

	int					w;				//��

	int					h;				//��

	int					num;			//֡��

	u8*					speed;			//����Ϊ:num,ÿ֡ͣ��ʱ��,��λ100MS

	u8*					idata;			//��ɫͼƬ����Ϊ:num * ((w+8-1)/8) * h	

										//��ɫͼƬ����Ϊ:num * w * h * (DISP_DEPTH/8)

}IMAGE;									//ͼƬ�ļ����ݶ��壬�ļ�ʹ��mmap��ͽṹ��һ��







enum FILL_TYPE

{

	FILL_NONE				=0x00000000,	//���������,��ɫ��ʹ�ð�ɫ���

				

	FILL_BORDER_UP			=0x10000000,	//�����ϱ߿�,��ɫ��ʹ��border_color��r���

	FILL_BORDER_DOWN		=0x20000000,	//�����±߿�,��ɫ��ʹ��border_color��g���

	FILL_BORDER_LEFT		=0x40000000,	//������߿�,��ɫ��ʹ��border_color��b���

	FILL_BORDER_RIGHT		=0x80000000,	//�����ұ߿�,��ɫ��ʹ��border_color��a���

	FILL_BORDER				=0xF0000000,	//���Ʊ߿�,  ��ɫ��ʹ��border_color��r,g,b,a�ֱ����up��down��left��right

	

	FILL_BORDER_3D			=0x01000000,	//��FILL_BORDER����ʱ,���Ʊ߿�ʱʹ����άЧ��

	FILL_BORDER_SHADOW		=0x02000000,	//��FILL_BORDER����ʱ,���Ʊ߿�ʱʹ����ӰЧ��

	FILL_BORDER_DOUBLE		=0x04000000,	//��FILL_BORDER����ʱ,���Ʊ߿�ʱʹ��˫���� 		

	FILL_BORDER_ROUNDED		=0x08000000,	//��FILL_BORDER����ʱ,���Ʊ߿�ʱʹ��Բ��		

	

	FILL_SOLID				=0x00100000,	//ʵ�����,  		

	FILL_CROSS				=0x00200000,	//�������,����ɫ��ʹ��solid_color.r,g���水�����



	FILL_IMG_DATA			=0x00400000,	//��ʾͼ������	pimg

	FILL_IMG_FILE			=0x00800000,	//��ʾͼ���ļ�	pimg

	

	FILL_MASK				=0xFFF00000

};



typedef struct

{

    u32 						type;						//

    COLOR 						solid_color;				//

    COLOR 						border_color;				//

    void*						pimg;						//

}FILL;



//==============================================================================================================================

//==============================================================================================================================



typedef enum

{

	TEXT_SIZE_TOOSMALL		=-2,			//��С����

	TEXT_SIZE_SMALL			=-1,			//С����

	TEXT_SIZE_NORMAL		= 0,			//��������

	TEXT_SIZE_BIG			= 1,			//������

	TEXT_SIZE_TOOBIG		= 2,			//�ش�����

}TEXT_SIZE_TYPE;



typedef enum

{

	TEXT_3X5			=4,

	TEXT_6X8			=6,

	TEXT_12				=12,

	TEXT_16				=16,

	TEXT_24				=24,

	TEXT_32				=32,		

	TEXT_SIZE			=0x000000FF,

	

	TEXT_NONE			=0x00000000,

	TEXT_NORMAL			=0x00000000,	//��ͨ

	TEXT_SHADOW			=0x00000100,	//��Ӱ��(��ɫ��Ч)

	TEXT_BORDER			=0x00000200,	//������

	TEXT_BOLD			=0x00000400,	//�Ӵ�

	TEXT_BACK			=0x00000800,	//������ɫ

	

	TEXT_ALIGN_LEFT		=0x10000000,	//def

	TEXT_ALIGN_CENTER	=0x20000000,

	TEXT_ALIGN_RIGHT	=0x40000000,

	TEXT_ALIGN_MASK		=0x70000000,

	

	TEXT_VALIGN_TOP		=0x01000000,

	TEXT_VALIGN_CENTER	=0x02000000,	//def

	TEXT_VALIGN_BOTTOM	=0x04000000,

	TEXT_VALIGN_MASK	=0x07000000



}TEXT_TYPE;	//V1.1



typedef enum 

{

	IME_NONE		=0x00000000,		//  

	IME_NUM			=0x00000001,		//����

	IME_abc			=0x00000002,		//Сд��ĸ

	IME_ABC			=0x00000004,		//��С��ĸ

	IME_Abc			=0x00000008,		//��Сд�����ĸ

	IME_SYM			=0x00000010,		//����

	IME_SUM			=0x00000020,		//���

	IME_PY			=0x00000040,		//ƴ�� ֧��GB2312����

	IME_PYGBK		=0x00000080,		//ȫƴ ֧��GBK����

	IME_FMT			=0x00000100,		//��ʽ��ģʽ�������룬��IP,�˺ŵ�.

	IME_MASK		=0x000001FF,		//����

	IME_PIN_MODE	=0x10000000,		//����ģʽ	

	IME_ENG			=IME_ABC|IME_abc|IME_Abc,		

	IME_END	

}IME_TYPE;			//V1.2		
	


typedef enum

{

	MENU_ICON_NUM		=0x0001,		//ͼ��Ϊ���,	��MENU_LIST���ʹ��

	MENU_ICOM_IMG		=0x0002,		//ͼ��Ϊͼ��,	��MENU_LIST���ʹ��

	MENU_LIST			=0x0100,		//�б�˵�

	MENU_RADIO			=0x0200,		//����ѡ��˵�

	MENU_CHECK			=0x0400,		//����ѡ��˵�

	MENU_MUILT_LINE		=0x1000,		//�����ı�,		�������������ʹ��

	MENU_MAX			=0xFFFF

}UI_MENU_TYPE;



typedef enum 

{

	K_0				='0',

	K_1				='1',				

	K_2				='2',				

	K_3				='3',				

	K_4				='4',				

	K_5				='5',				

	K_6				='6',				

	K_7				='7',				

	K_8				='8',				

	K_9				='9',			

	K_STAR			='*',			

	K_POUND			='#',			

			

	K_UP			=0x01,		//�Ϸ����

	K_DOWN			=0x02,		//�·����

	K_LEFT			=0x03,		//�����

	K_RIGHT			=0x04,		//�ҷ����

								

	K_MENU			=0x05,		//�˵�	

	K_IME			=0x06,		//���뷨	

	K_SYM			=0x07,		//����	

	K_BACK			=0x08,		//����	

	

	K_LSK			=0x0A,		//�����		

	K_RSK			=0x0B,		//�����

	

	K_CANCEL		=0x0C,		//ȡ��

	K_OK			=0x0D,		//ȷ��

	K_DEL			=0x0E,		//ɾ��

	K_QUIT			=0x0F,		//�˳�

	

	K_FUNC			=0x10,		//����

	K_F1			=0x11,		//����1

	K_F2			=0x12,		//����2

	K_F3			=0x13,		//����3

	K_F4			=0x14,		//����4



	K_CALL_LOG		=0x1A,		//ͨ����¼

	K_CALL_BACK		=0x1B,		//�ز�

	K_PRE_DIAL		=0x1C,		//Ԥ����

	K_IP_DIAL		=0x1D,		//IP����

	K_RE_DIAL		=0x1E,		//�ز�

	K_FLASH			=0x1F,		//����



	K_INVALID		=0x00

}KEY_VAL;						//V3��������



typedef enum 

{

	KEY_EVENT_UP	=0,		//����  0

	KEY_EVENT_DOWN	=1,		//����  1

	KEY_REPEAT      =2,		//�ظ�  2

	KEY_LONG_PRESS  =999,	//����  3

	KEY_TYPE_END			//

}KEY_TYPE;					//��������



typedef enum

{															

    PEN_UP       	=0,		//����	0			            

    PEN_DOWN     	=1,		//����  1                        

    PEN_REPEAT	 	=999,	//�ظ�  2                        

    PEN_LONG_TAP 	=999,	//����  3                        

    PEN_MOVE		=4	,	//�ƶ�  4     �����ʻ���ָ���������ƶ�����갴ס����������ƶ�                   

    PEN_FLOAT		=5	,	//����  5     �����������������ƶ���	���û�а����������ƶ�                      

    PEN_ABORT	 	=999,   //��ֹ  6                              

    PEN_TYPE_END            //                    

}PEN_TYPE;					//�������� float

//------------------------------------------------------------------------------------------------------------------------------
//����ȫ��ɾ��
typedef enum
{
    ALIGN_LEFT      = 0x00,
    ALIGN_CENTER    = 0x01,
    ALIGN_RIGHT     = 0x02
}TEXT_ALIGN_FORMAT;

typedef enum
{
    TEXT_REVERSE_NO         = 0x01,
    TEXT_REVERSE_YES        = 0x00
}TEXT_REVERSE;


typedef enum
{
    FONT_SIZE_VERY_VERY_SMALL = 15,
    FONT_SIZE_VERY_SMALL    = 16,
    FONT_SIZE_SMALL         = 17,
    FONT_SIZE_NORMAL        = 20,
    FONT_SIZE_BIG           = 22,
    FONT_SIZE_VERY_BIG      = 24
}TEXT_FONT_SIZE;


typedef enum
{    
    LINE_PROMPT             = 1,        //��ʾ��Ϣ����ʾ����
    LINE_PROMPT_NEXT        = 2,        //��ʾ��Ϣ�ڶ���
    LINE_EDIT               = 3,        //�༭�����ʾ����  
    LINE_LAST_PROMPT        = 4,        //������ʾ��Ϣ����ʾ����
    LINE_IME                = 5         //���뷨��ʾ������
}SHOW_LINE;

extern void  API_UI_Flush(RECT* pRect);
extern void  API_UI_ShowImg(char * pstrImgFile, int nPosX, int nPosY, int nImgWidth, int nImgHeight);
extern void  API_UI_Clear();
extern void  API_UI_ClearAll();
extern void  API_UI_SetTitle(int nFontSize, char * pstrTitle, int nFlag);
extern void  API_UI_PrintLine(int nLine, int nFontSize, int nAlign, char* pText);
extern int   API_GUI_Edit_GetAmount(char* pstrPrompt, int nFontSize, char * pstrLastPrompt, int nLastFontSize, char * pstrAmount,u32 nTimeLimit);
extern int   API_GUI_Edit_GetInputNum(char* pstrPrompt, int nFontSize, char * pstrLastPrompt, int nLastFontSize, char* pstrNUm, int nMaxLen, u32 nTimeLimit);
extern int   API_GUI_Edit_GetInputIp(char* pstrPrompt, int nFontSize, char * pstrLastPrompt, int nLastFontSize, char* pstrNUm, int nMaxLen, u32 nTimeLimit);
extern int   API_GUI_Edit_GetInputPwd(char* pstrPrompt, int nFontSize, char * pstrLastPrompt, int nLastFontSize, char* pstrPwd, int nMaxLen, u32 nTimeLimit);
extern int   API_GUI_Edit_GetPassWord(char* pstrPrompt, char * pstrLastPrompt, char* pstrPwd, int nMaxLen, u32 nTimeLimit, int mk_idx, int wk_idx, char *card_no, int en_mode);
extern int   API_GUI_Edit_GetInputIME(char* pstrPrompt, int nFontSize, char * pstrLastPrompt, int nLastFontSize, char* pstrText, int nMaxLen, u32 nTimeLimit);
extern int   API_GUI_Confirm(char* pTitle, char * pStr, char* pOk,char* pCancel);
extern void  API_GUI_Edit_Prompt(char* pFrontTextBuf, char* pAfterTextBuf, int nMaxLen);
extern int   API_GUI_Edit_GetText(char* pAscText,int tMaxLen);

#endif
