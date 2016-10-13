#ifndef __DES_H__
#define __DES_H__

/*[title
    ��׼DES/3DES����
]*/

/*[note
	DES�㷨��ΪECB��CBC����ģʽ, ��ʹ��ʱ���vec����0���ʾECB�㷨,��������Ϊ��ʼ����
]*/

/*[fields
]*/

/*[errcodes */
#define ERR_DES_BASE     (-10200)       //DES/TDES��׼������
#define SUCC               0
#define ERR_DES_NOT_8MUL            (ERR_DES_BASE+(-1))      //���ݳ��Ȳ���8�ı���
#define ERR_DES_FAIL                (ERR_DES_BASE+(-2))      //des���ܻ����ʧ��
#define ERR_DES_TDES_FAIL           (ERR_DES_BASE+(-3))      //3des���ܻ����ʧ��

/*]*/

/*[public */
int des(unsigned char *src, unsigned char *dst, unsigned char *key, int src_len, int key_len, unsigned char *vec);
int undes(unsigned char *src, unsigned char *dst, unsigned char *key, int src_len, int key_len, unsigned char *vec);
/*]*/

#endif //__DES_H__
