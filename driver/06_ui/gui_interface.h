#ifndef GUI_INTERFACE_H
#define GUI_INTERFACE_H


#ifdef __cplusplus
extern "C"
  {
#endif
    
    int InitGui(int argc, char **argv);
    int ExecGui();
    void ReleaseGui();
    char * Get_UI_Version(char *version);
    void ClearWnd(int pi_iMode);
    void SetTitle(char *pi_caBuff, int pi_flag, int pi_iFontSize);
    //增加第6行,行号99
    void SetContent(int pi_iLineNo, char *pi_caBuff, int pi_iFontSize, int pi_iAlign);
    void SetButton(char *pi_caBuff);
    void SetEdit(int pi_iLine, char *pi_caBuff, int pi_iFlag, int pi_iFontSize, int pi_iAlign);

    void SetSelect(char *pi_caBuff, int pi_iPos, int pi_iLen);
    //显示图片
    //pi_ix的值为 -1:居中显示 -2:图片居中,暂不显示与99配合使用 99:显示小图片，与-2配合使用 其它:显示客户logo
    void SetImage(char *pi_caPath, int pi_iX, int pi_iY, int pi_iW, int pi_iH);
    void SetContext(int pi_iLine , char *pi_caBuffLeft,char *pi_caBuffRight,int pi_iModeLeft,int pi_iModeRight ,int Align_mode);
	int  GetKey_UI(char *pio_cKey);
	void SetWait();
    //动态显示时间,第五行的位置
    void show_Time();
    //修改图片大小
    void UI_Set_Image(char * pi_caPath, char * p, int len_X, int len_Y);
    void Set_endTime(int time);
#ifdef __cplusplus
}
#endif

#endif // GUI_INTERFACE_H
