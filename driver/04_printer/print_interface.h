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
    void InitDll(int argc, char **argv);				//��ʼ����̬���ӿ� ,���ô����� ��Qt ������ʹ��
    				                  
    int  OpenPrinter();						//���豸
    void ClosePrinter();
    int  PrintStr(char *textBuf);               //�ú���ֻ���Դ�ӡӢ����ĸ������
    void PrintGraph(const char* imageFileName); //��ӡͼƬ
    void SetLeftMargin(int leftMargin);                //������߾� ��λ����
    
    void SetFont(char *p_caType);                      //������Ҫ��ӡ������     ����Ĭ�� �� 0
                                                   //                       ΢���ź�  "msyh"   
    void SetTextType(int i_type);                      //   i_type   �������ֵ���д���� 
                                                   //   1 ����������д  0 ����������д 
               
    void SetAlign(int iAlign);                         //   iAlign  0 �����  
                                                   //           1 �Ҷ���
                                                   //           2 �м����                                                    
    void FillData(int i_font_type ,char *p_caInfo,int font_size);  // FONT_TYPE     ��������
    int  PrintData();     /*ret:  0 �ɹ�
                            -2 ��ӡ�����ر�
                            -1 ��ӡ���쳣
                            1 ��ӡ��æ
                            2 ��ӡ��ȱֽ
                            3 ��ӡ��æ +  ��ӡ��ȱֽ
                            4 ��ӡ������
                            5 ��ӡ��æ + ����
                            6 ��ӡ��ȱֽ + ����
                            7 ��ӡ��æ +  ��ӡ��ȱֽ + ����
                            8 ��ʱ
                            ����  δ֪����  
                            */
    int  PrnContinuePrint();   //������ӡȱֽʱ��ͣ��ӡ������
    int  PrnClearStatus();     // ��� ��ӡȱֽʱ����ͣ��ӡ״̬

    int  PrnSetPrintSpeed(int speed); //���ô�ӡ�ٶ� 1 ���� 2���� 3����
    int  PrnSetSpaceLine(int  mode ,int line);   //���ô�ӡǰ����ֽ�Ŀ�������
                                                 // mode 0 ǰ��ֽ������
                                                 //      1 ����ֽ������
                                                 // line  0~65535
    int  PrnGetStatus();       /*ret:  -1  �����쳣
                                       -2  ��ӡ���ѹر�
                                        0 ��ӡ������
                                        1 ��ӡ��æ
                                        2 ��ӡ��ȱֽ
                                        3 ��ӡ��æ +  ��ӡ��ȱֽ
                                        4 ��ӡ������
                                        5 ��ӡ��æ + ����
                                        6 ��ӡ��ȱֽ + ����
                                        7 ��ӡ��æ +  ��ӡ��ȱֽ + ����
                                       ����  δ֪����*/
                                       
    void  PrnPrintBmpData(char *Data,int len);
    void  GetVersion(char *p_caVersion); //��ȡ�����İ汾��
                                        

#ifdef __cplusplus
}
#endif

#endif

