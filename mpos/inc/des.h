#ifndef __DES_H__
#define __DES_H__

/*[title
    标准DES/3DES加密
]*/

/*[note
	DES算法分为ECB、CBC两种模式, 在使用时如果vec传入0则表示ECB算法,否则其中为初始向量
]*/

/*[fields
]*/

/*[errcodes */
#define ERR_DES_BASE     (-10200)       //DES/TDES基准错误码
#define SUCC               0
#define ERR_DES_NOT_8MUL            (ERR_DES_BASE+(-1))      //数据长度不是8的倍数
#define ERR_DES_FAIL                (ERR_DES_BASE+(-2))      //des加密或解密失败
#define ERR_DES_TDES_FAIL           (ERR_DES_BASE+(-3))      //3des加密或解密失败

/*]*/

/*[public */
int des(unsigned char *src, unsigned char *dst, unsigned char *key, int src_len, int key_len, unsigned char *vec);
int undes(unsigned char *src, unsigned char *dst, unsigned char *key, int src_len, int key_len, unsigned char *vec);
/*]*/

#endif //__DES_H__
