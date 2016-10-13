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
    //���ӵ�6��,�к�99
    void SetContent(int pi_iLineNo, char *pi_caBuff, int pi_iFontSize, int pi_iAlign);
    void SetButton(char *pi_caBuff);
    void SetEdit(int pi_iLine, char *pi_caBuff, int pi_iFlag, int pi_iFontSize, int pi_iAlign);

    void SetSelect(char *pi_caBuff, int pi_iPos, int pi_iLen);
    //��ʾͼƬ
    //pi_ix��ֵΪ -1:������ʾ -2:ͼƬ����,�ݲ���ʾ��99���ʹ�� 99:��ʾСͼƬ����-2���ʹ�� ����:��ʾ�ͻ�logo
    void SetImage(char *pi_caPath, int pi_iX, int pi_iY, int pi_iW, int pi_iH);
    void SetContext(int pi_iLine , char *pi_caBuffLeft,char *pi_caBuffRight,int pi_iModeLeft,int pi_iModeRight ,int Align_mode);
	int  GetKey_UI(char *pio_cKey);
	void SetWait();
    //��̬��ʾʱ��,�����е�λ��
    void show_Time();
    //�޸�ͼƬ��С
    void UI_Set_Image(char * pi_caPath, char * p, int len_X, int len_Y);
    void Set_endTime(int time);
#ifdef __cplusplus
}
#endif

#endif // GUI_INTERFACE_H
