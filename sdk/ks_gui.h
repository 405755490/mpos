
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



#define ColorWhite			RGB(0xFF,0xFF,0xFF)	//白色

#define ColorBlack			RGB(0x00,0x00,0x00)	//黑色

#define ColorRed			RGB(0xFF,0x00,0x00)	//紅色

#define ColorGreen			RGB(0x00,0xFF,0x00)	//綠色

#define ColorBlue			RGB(0x00,0x00,0xFF)	//薘色

#define ColorYellow			RGB(0xFF,0xFF,0x00)	//黃色

#define ColorCyan			RGB(0x00,0xFF,0xFF)	//淺薘色

#define ColorMagenta		RGB(0xFF,0x00,0xFF)	//桃紅色



#define ColorOrange			RGB(0xFF,0x7F,0x00)	//橙色

#define ColorViolet			RGB(0x4F,0x2F,0x4F)	//紫色

#define ColorBrown			RGB(0xA5,0x2A,0x2A)	//棕色

#define ColorGrey			RGB(0xC0,0xC0,0xC0)	//灰色



#define ColorGold			RGB(0xCD,0x7F,0x32)	//金色

#define ColorSilver			RGB(0xE6,0xE8,0xFA)	//銀色

#define ColorScarlet		RGB(0x8C,0x17,0x17)	//鮮紅色

#define ColorAzure			RGB(0xF0,0xFF,0xFF)	//天薘色

#define ColorBlueviolet		RGB(0x8A,0x2B,0xE2)	//青紫色



#define ColorCrimson		RGB(0xDC,0x14,0x3C)	//鮮紅色

#define ColorDarkblue		RGB(0x00,0x00,0x8B)	//深薘色

#define ColorDarkgray		RGB(0xA9,0xA9,0xA9)	//深灰色	


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

	DISP_DEPTH_1		=0x00000001,	//颜色深度     单色

	DISP_DEPTH_8		=0x00000008,	//颜色深度  8位颜色

	DISP_DEPTH_16		=0x00000010,	//颜色深度 16位颜色

	DISP_DEPTH_24		=0x00000018,	//颜色深度 24位颜色

	DISP_DEPTH_32		=0x00000020,	//颜色深度 32位颜色

	DISP_DEPTH			=0x000000FF,	//颜色深度 掩码

	

	DISP_MONOC			=0x00010000,	//单色

	DISP_RGB565			=0x00020000,	//RGB565格式

	DISP_RGB888			=0x00040000,	//RGB888格式

	DISP_RGB32			=0x00080000,	//RGB888格式

	DISP_TRANSPARENT	=0x00100000		//支持通透颜色，供图片使用

};

	

typedef struct

{

	u8					mask;			//0x1B

	u8					type;			//0xF1

	u8					ver;			//0x01

	u8					offset;			//数据开始的数据偏移地址(speed开始的数据)

										//前面为数据文件专用头定义

	u32					disp_type;		//

    COLOR 				trans_color;	//RGB(r,g,b,a):rgb为彩色图片使用

	int					w;				//宽

	int					h;				//高

	int					num;			//帧数

	u8*					speed;			//长度为:num,每帧停留时间,单位100MS

	u8*					idata;			//单色图片长度为:num * ((w+8-1)/8) * h	

										//彩色图片长度为:num * w * h * (DISP_DEPTH/8)

}IMAGE;									//图片文件数据定义，文件使用mmap后和结构体一致







enum FILL_TYPE

{

	FILL_NONE				=0x00000000,	//彩屏不填充,单色屏使用白色填充

				

	FILL_BORDER_UP			=0x10000000,	//绘制上边框,单色屏使用border_color的r填充

	FILL_BORDER_DOWN		=0x20000000,	//绘制下边框,单色屏使用border_color的g填充

	FILL_BORDER_LEFT		=0x40000000,	//绘制左边框,单色屏使用border_color的b填充

	FILL_BORDER_RIGHT		=0x80000000,	//绘制右边框,单色屏使用border_color的a填充

	FILL_BORDER				=0xF0000000,	//绘制边框,  单色屏使用border_color的r,g,b,a分别填充up、down、left、right

	

	FILL_BORDER_3D			=0x01000000,	//当FILL_BORDER存在时,绘制边框时使用三维效果

	FILL_BORDER_SHADOW		=0x02000000,	//当FILL_BORDER存在时,绘制边框时使用阴影效果

	FILL_BORDER_DOUBLE		=0x04000000,	//当FILL_BORDER存在时,绘制边框时使用双线条 		

	FILL_BORDER_ROUNDED		=0x08000000,	//当FILL_BORDER存在时,绘制边框时使用圆角		

	

	FILL_SOLID				=0x00100000,	//实心填充,  		

	FILL_CROSS				=0x00200000,	//交叉填充,仅单色屏使用solid_color.r,g交替按行填充



	FILL_IMG_DATA			=0x00400000,	//显示图像数据	pimg

	FILL_IMG_FILE			=0x00800000,	//显示图像文件	pimg

	

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

	TEXT_SIZE_TOOSMALL		=-2,			//特小字体

	TEXT_SIZE_SMALL			=-1,			//小字体

	TEXT_SIZE_NORMAL		= 0,			//正常字体

	TEXT_SIZE_BIG			= 1,			//大字体

	TEXT_SIZE_TOOBIG		= 2,			//特大字体

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

	TEXT_NORMAL			=0x00000000,	//普通

	TEXT_SHADOW			=0x00000100,	//阴影字(彩色有效)

	TEXT_BORDER			=0x00000200,	//空心字

	TEXT_BOLD			=0x00000400,	//加粗

	TEXT_BACK			=0x00000800,	//带背景色

	

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

	IME_NUM			=0x00000001,		//数字

	IME_abc			=0x00000002,		//小写字母

	IME_ABC			=0x00000004,		//大小字母

	IME_Abc			=0x00000008,		//大小写混合字母

	IME_SYM			=0x00000010,		//符号

	IME_SUM			=0x00000020,		//金额

	IME_PY			=0x00000040,		//拼音 支持GB2312编码

	IME_PYGBK		=0x00000080,		//全拼 支持GBK编码

	IME_FMT			=0x00000100,		//格式化模式数字输入，如IP,账号等.

	IME_MASK		=0x000001FF,		//掩码

	IME_PIN_MODE	=0x10000000,		//密码模式	

	IME_ENG			=IME_ABC|IME_abc|IME_Abc,		

	IME_END	

}IME_TYPE;			//V1.2		
	


typedef enum

{

	MENU_ICON_NUM		=0x0001,		//图标为序号,	与MENU_LIST组合使用

	MENU_ICOM_IMG		=0x0002,		//图标为图像,	与MENU_LIST组合使用

	MENU_LIST			=0x0100,		//列表菜单

	MENU_RADIO			=0x0200,		//单项选择菜单

	MENU_CHECK			=0x0400,		//多项选择菜单

	MENU_MUILT_LINE		=0x1000,		//多行文本,		与其它类型组合使用

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

			

	K_UP			=0x01,		//上方向键

	K_DOWN			=0x02,		//下方向键

	K_LEFT			=0x03,		//左方向键

	K_RIGHT			=0x04,		//右方向键

								

	K_MENU			=0x05,		//菜单	

	K_IME			=0x06,		//输入法	

	K_SYM			=0x07,		//符号	

	K_BACK			=0x08,		//返回	

	

	K_LSK			=0x0A,		//左软键		

	K_RSK			=0x0B,		//左软键

	

	K_CANCEL		=0x0C,		//取消

	K_OK			=0x0D,		//确认

	K_DEL			=0x0E,		//删除

	K_QUIT			=0x0F,		//退出

	

	K_FUNC			=0x10,		//功能

	K_F1			=0x11,		//功能1

	K_F2			=0x12,		//功能2

	K_F3			=0x13,		//功能3

	K_F4			=0x14,		//功能4



	K_CALL_LOG		=0x1A,		//通话记录

	K_CALL_BACK		=0x1B,		//回拨

	K_PRE_DIAL		=0x1C,		//预拨号

	K_IP_DIAL		=0x1D,		//IP拨号

	K_RE_DIAL		=0x1E,		//重拨

	K_FLASH			=0x1F,		//闪断



	K_INVALID		=0x00

}KEY_VAL;						//V3按键定义



typedef enum 

{

	KEY_EVENT_UP	=0,		//弹起  0

	KEY_EVENT_DOWN	=1,		//按下  1

	KEY_REPEAT      =2,		//重复  2

	KEY_LONG_PRESS  =999,	//长按  3

	KEY_TYPE_END			//

}KEY_TYPE;					//按键类型



typedef enum

{															

    PEN_UP       	=0,		//弹起	0			            

    PEN_DOWN     	=1,		//按下  1                        

    PEN_REPEAT	 	=999,	//重复  2                        

    PEN_LONG_TAP 	=999,	//长按  3                        

    PEN_MOVE		=4	,	//移动  4     触摸笔或手指按在屏上移动，鼠标按住左键在屏上移动                   

    PEN_FLOAT		=5	,	//浮动  5     触摸笔悬浮在屏上移动，	鼠标没有按键在屏上移动                      

    PEN_ABORT	 	=999,   //终止  6                              

    PEN_TYPE_END            //                    

}PEN_TYPE;					//触摸类型 float

//------------------------------------------------------------------------------------------------------------------------------
//上面全部删掉
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
    LINE_PROMPT             = 1,        //提示信息的显示行数
    LINE_PROMPT_NEXT        = 2,        //提示信息第二行
    LINE_EDIT               = 3,        //编辑框的显示行数  
    LINE_LAST_PROMPT        = 4,        //后续提示信息的显示行数
    LINE_IME                = 5         //输入法显示的行数
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
