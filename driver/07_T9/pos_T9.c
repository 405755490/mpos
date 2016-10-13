
#include "T9_define.h"
#include "maxq_server.h"
#include "gui_interface.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

typedef enum
{
    ALIGN_LEFT      = 0x00,
    ALIGN_CENTER    = 0x01,
    ALIGN_RIGHT     = 0x02
}TEXT_ALIGN_FORMAT;


typedef enum
{
    FONT_SIZE_VERY_SMALL    = 16,
    FONT_SIZE_SMALL         = 18,
    FONT_SIZE_NORMAL        = 20,
    FONT_SIZE_BIG           = 22,
    FONT_SIZE_VERY_BIG      = 24
}TEXT_FONT_SIZE;


typedef enum
{    
    LINE_PROMPT             = 2,        //提示信息的显示行数   
    LINE_EDIT               = 3,        //编辑框的显示行数  
    LINE_LAST_PROMPT        = 4,        //后续提示信息的显示行数
    LINE_IME                = 5         //输入法显示的行数
}SHOW_LINE;



//键盘输入回调函数
int t9_getch_timeout=60;
T9RESULT T9_getch(unsigned char *ch)
{
	time_t begin;
	
	//printf("T9_getch\n");
	begin = time(NULL);
	kbd_566_enable(0x03);
	while(1==1)
	{
		//超时控制,自己实现
		//超时 return T9_TIMEOUT;
		if( (time(NULL) - begin) > t9_getch_timeout ) 
		{
				kbd_566_enable(0x00);
				return T9_TIMEOUT;
		}
		ch[0] = kbd_566_getkey();
		
		if( ch[0] != 0x00 )
		{
				//printf("kbd_566_getkey return [%02X]\n", ch[0]);
				kbd_566_enable(0x00);
				return T9_SUCC;
		} 

		
	}
	kbd_566_enable(0x00);
	return T9_SUCC;
}

//显示器输入法区域清除回调函数
void T9_lcd_cls()
{
	//printf("T9_lcd_cls\n");

	//ClearWnd();
	//DevShowImage(1, 53, 13, 19, NULL, 0, 12);
	//DevShowImage(1, 53, 13, 19, NULL, 0, 13);
}

//显示器输入法区域字符显示回调函数
void T9_lcd_show(int col, int reserv, char *s1, int ln, int show_flag, int un_position, int un_len)
{
	int position;
	char show_buf[32]={0};
	position = un_position - 1;
	//printf("T9_lcd_show\n");
	//printf("s1 = [%s], un_position = [%d]\n", s1, un_position);
	if( ln == -1 )
	{
		ln = strlen(s1);
	}
  
	if(position < 0)
	{
		//DevShowStr(9, col+1, 0, reserv, s1, SHOW_TEXT, "", "", show_flag);
		SetContent(LINE_IME, s1, FONT_SIZE_SMALL, ALIGN_LEFT);
		//SetSelect(s1, 0, 1);
	}
	else
	{	
		memcpy(show_buf, s1, position);
        //printf("show_buf = [%s]\n", show_buf);
		strcat(show_buf, "[");
        //printf("un_len = [%d]\n", un_len);
	    memcpy(show_buf+strlen(show_buf), s1+position, un_len);
        //printf("s1+position = [%s]\n", s1+position);
        //printf("show_buf = [%s]\n", show_buf);
		strcat(show_buf, "]");
        //printf("show_buf = [%s]\n", show_buf);
		memcpy(show_buf+strlen(show_buf), s1+position+un_len, strlen(s1)-(position+un_len));
        //printf("s1+position+un_len = [%s]\n", s1+position+un_len);
		//DevShowStr(9, col+1, 0, reserv, show_buf, SHOW_TEXT, "", "", show_flag);
		//printf("In T9_lcd_show, show_buf=[%s]\n", show_buf);
		SetContent(LINE_IME, show_buf, FONT_SIZE_NORMAL, ALIGN_LEFT);
	}
}

//显示器输入法区域图形显示回调函数
void T9_lcd_image(int col, int width, int height, char *img, int show_flag, int file_flag)
{
	//printf("T9_lcd_image\n");
	//DevShowImage(col, 53, width, height, img, show_flag, file_flag);
	SetContent(LINE_IME, img, FONT_SIZE_NORMAL,ALIGN_RIGHT);
}
/*
int T9_demo()
{
	char s[128];
	T9RESULT res;

	ztlcd_init();
	ztkbd_open();

	ztlcd_cls(1, 10, ZTLCD_FONT_12X12, 1);

	setT9ControlKey(21, POSK_KEY_SET, POSK_KEY_CANCEL, POSK_KEY_ENTER, POSK_KEY_PGUP, POSK_KEY_PGDN, POSK_KEY_CLEAR);

	setT9ControlFunc(T9_getch, T9_lcd_cls, T9_lcd_show, T9_lcd_image);

	T9_set_mode(T9_NUM);

	memset(s, 0, sizeof(s));
	while(1==1)
	{
		res = T9Run((unsigned char*)(s+strlen(s)));
		if( res == T9_TIMEOUT )
		{
			printf("timeout\n");
			break;
		}
		if( res == T9_DEL && strlen(s)>0 )
			s[strlen(s)-1] = 0;

		ztlcd_cls(3, 6, 0);
		ztlcd_str(3, 1, 1);
    }

	ztkbd_close();
	ztlcd_free();

	return 0;
}*/
