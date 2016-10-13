#ifndef __PRINT_INTERFACE_H__
#define __PRINT_INTERFACE_H__


#define TEXT_NOMAL_FONT 0
#define TEXT_SMALL_FONT 1
#define TEXT_BOLD 8
#define TEXT_UNDERLINE 128
#define TEXT_REVERSE 0x200
#define TEXT_ITALIC 64

#define FONT 22



#ifdef __cplusplus 
extern "C"
{ 
#endif
    void InitDll(int argc, char **argv);				//初始化动态链接库 ,调用代码是 非Qt 程序者使用
    				                  
    int  OpenPrinter();						//打开设备
    void ClosePrinter();
    int  PrintStr(char *textBuf);               //该函数只可以打印英文字母和数字
    void PrintGraph(const char* imageFileName); //打印图片
    void SetLeftMargin(int leftMargin);                //设置左边距 单位像素
    
    void SetFont(char *p_caType);                      //设置需要打印的字体     楷体默认 传 0
                                                   //                       微软雅黑  "msyh"   
    void SetTextType(int i_type);                      //   i_type   设置文字的书写方向 
                                                   //   1 从右往左书写  0 从左向右书写 
               
    void SetAlign(int iAlign);                         //   iAlign  0 左对齐  
                                                   //           1 右对齐
                                                   //           2 中间对齐                                                    
    void FillData(int i_font_type ,char *p_caInfo,int font_size);  // FONT_TYPE     字体类型
    int  PrintData();     /*ret:  0 成功
                            -2 打印机被关闭
                            -1 打印机异常
                            1 打印机忙
                            2 打印机缺纸
                            3 打印机忙 +  打印机缺纸
                            4 打印机过热
                            5 打印机忙 + 过热
                            6 打印机缺纸 + 过热
                            7 打印机忙 +  打印机缺纸 + 过热
                            8 超时
                            其它  未知错误  
                            */
    int  PrnContinuePrint();   //继续打印缺纸时暂停打印的数据
    int  PrnClearStatus();     // 清除 打印缺纸时额暂停打印状态

    int  PrnSetPrintSpeed(int speed); //设置打印速度 1 低速 2正常 3高速
    int  PrnSetSpaceLine(int  mode ,int line);   //设置打印前后走纸的空像素行
                                                 // mode 0 前走纸像素行
                                                 //      1 后走纸像素行
                                                 // line  0~65535
    int  PrnGetStatus();       /*ret:  -1  其它异常
                                       -2  打印机已关闭
                                        0 打印机正常
                                        1 打印机忙
                                        2 打印机缺纸
                                        3 打印机忙 +  打印机缺纸
                                        4 打印机过热
                                        5 打印机忙 + 过热
                                        6 打印机缺纸 + 过热
                                        7 打印机忙 +  打印机缺纸 + 过热
                                       其它  未知错误*/
                                       
    void  PrnPrintBmpData(char *Data,int len);
    void  GetVersion(char *p_caVersion); //获取驱动的版本号
                                        

#ifdef __cplusplus
}
#endif

#endif

