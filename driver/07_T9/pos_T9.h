
#ifndef __POS_T9_H_INCLUDED__
#define __POS_T9_H_INCLUDED__

T9RESULT T9_getch(unsigned char *ch);
void T9_lcd_cls();
void T9_lcd_image(int col, int width, int height, char *img, int show_flag, int file_flag);
void T9_lcd_show(int col, int reserv, char *s1, int ln, int show_flag, int un_position, int un_len);
#endif