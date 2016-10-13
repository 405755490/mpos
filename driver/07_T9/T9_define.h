#ifndef __T9_DEFINE_H__
#define __T9_DEFINE_H__

typedef enum
{
	T9_KEY_1 = 0x31,
	T9_KEY_2 = 0x32,
	T9_KEY_3 = 0x33,
	T9_KEY_4 = 0x34,
	T9_KEY_5 = 0x35,
	T9_KEY_6 = 0x36,
	T9_KEY_7 = 0x37,
	T9_KEY_8 = 0x38,
	T9_KEY_9 = 0x39,
	T9_KEY_0 = 0x30,
	T9_KEY_F1 = 0x41,
	T9_KEY_F2 = 0x42,
	T9_KEY_F3 = 0x43,
	T9_KEY_F4 = 0x44,
	T9_KEY_A  = 0x45,			//*
	T9_KEY_B  = 0x46,			//#
	T9_KEY_LS = 0x47,			//左选择
	T9_KEY_MU = 0x48,			//菜单
	T9_KEY_RS = 0x49,			//右选择
	T9_KEY_CANCEL = 0x1B,		//取消
	T9_KEY_CLAER = 0x08,		//清除
	T9_KEY_ENTER = 0x0D,		//确认
	
}KEY_T9_VALUE;


//输入模式
typedef enum
{
	T9_DEF=0,    //设置默认模式
	T9_NUM=1,    //数字输入
	T9_CHS=2,    //汉字输入
	T9_CAP=3,    //大写输入
	T9_LOW=4,    //小写输入
	T9_SPI=5     //特殊符号
}T9MODE;
//输入结果
typedef enum
{
	T9_CONTINUE=0,   //继续输入
	T9_SUCC=1,      //输入成功
	T9_ESC=2,       //返回一个取消按键,供调用者使用
	T9_DEL=3,       //返回一个删除状态,供调用者使用
	T9_ENTER=4,     //返回一个确定按键,供调用者使用
	T9_TIMEOUT=5    //返回超时,供调用者使用
}T9RESULT;

typedef T9RESULT  (*T9GETKEY)(unsigned char *ch);  //键盘输入函数,获取一个输入字符
typedef void (*T9LCDCLS)(int flag);  //清除显示区域函数
typedef void (*T9LCDSHOW)(int col, int reserv, char *s1, int ln, int show_flag, int un_position, int un_len);    //输入显示函数,显示区域需要2行
typedef void (*T9LCDIMAGE)(int col, int width, int height, char *img, int show_flag, int file_flag);   //显示图形

extern unsigned char *T9_version();
extern void setT9ControlKey(int width, unsigned char convert_key, unsigned char esc_key, unsigned char ok_key, unsigned char up_key,  unsigned char dn_key,  unsigned char page_up_key, unsigned char page_down_key , unsigned char del_key);
extern void setT9ControlFunc(T9GETKEY func1, T9LCDCLS func2, T9LCDSHOW func3, T9LCDIMAGE func4);
extern void T9_set_mode(T9MODE cur_mode);
extern T9RESULT T9Run(unsigned char *input);
extern void T9_set_mode(T9MODE cur_mode);

#endif  //__T9_DEFINE_H__
