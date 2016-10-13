
#ifndef _KS_STDLIB_H_
#define _KS_STDLIB_H_


//���׼�ⶨ��
//-----------------------------------------------------------------------------------------------------------------------

	extern double	API_atof(const char* s);
	extern int	    API_atoi(const char* s);
	extern long    	API_atol(const char* s);

	extern int		API_rand (void);
	extern void		API_srand(unsigned int n);

	extern int		API_abs	(int  n);
	extern long   	API_labs(long n);

	extern double 	API_sin  (double f);
	extern double 	API_cos  (double f);
	extern double 	API_tan  (double f);
	extern double 	API_sinh (double f);
	extern double 	API_cosh (double f);
	extern double 	API_tanh (double f);
	extern double 	API_asin (double f);
	extern double 	API_acos (double f);
	extern double 	API_atan (double f);
	extern double 	API_atan2(double f1, double f2);
	extern double 	API_exp  (double f);
	extern double 	API_log  (double f);
	extern double 	API_log10(double f);
	extern double 	API_pow  (double f1, double f2);
	extern double 	API_sqrt (double f);
	extern double 	API_ceil (double f);
	extern double 	API_floor(double f);
	extern double 	API_fabs (double f);
	extern double 	API_ldexp(double f, int  n);
	extern double 	API_frexp(double f, int* p);
	extern double 	API_modf (double f, double* pf);
	extern double 	API_fmod (double f1,double  f2);

	extern void 	API_sprintf(char* pStr, const char* pFmt, ...);		
	extern void* 	API_memchr(const void*, int, int);
	extern int  	API_memcmp(const void*, const void*, int);
	extern void*  	API_memcpy(void*, const void*, int);
	extern void* 	API_memmove(void*, const void*, int);
	extern void* 	API_memset(void*, int, int);
	extern char* 	API_strcat(char*, const char*);
	extern char* 	API_strchr(const char*, int);
	extern int 		API_strcmp(const char*, const char*);
	extern int 		API_strcoll(const char*, const char*);
	extern char* 	API_strcpy(char*, const char*);
	extern int 		API_strcspn(const char*, const char*);
	extern char* 	API_strerror(int); 
	extern int 		API_strlen(const char*);
	extern char* 	API_strpbrk(const char*, const char*);
	extern char* 	API_strrchr(const char*, int);
	extern int 		API_strspn(const char*, const char*);
	extern char* 	API_strstr(const char*, const char*);
	extern char* 	API_strtok(char*, const char*);
	extern int 		API_strxfrm(char*, const char*, int);
//-----------------------------------------------------------------------------------------------------------------------

	enum FILE_FLAG
	{
		F_RDONLY	=00000000,		//ֻ��
		F_WRONLY	=00000001,		//ֻд
		F_RDWR		=00000002,		//��д
		F_CREAT		=00000100,		//�Զ�����
		F_APPEND	=00002000
	};
	enum FILE_SEEK
	{
		F_SEEK_SET	=00000001,		//�ļ���ͷ
		F_SEEK_CUR	=00000002,		//��ǰλ��
		F_SEEK_END	=00000004		//�ļ���β
	};
			
	extern int 		API_fopen(const char * filename, int flags);		//���ļ��������ļ����������0�ɹ�
	extern int 		API_fclose(int fd);									//�ر��ļ������ص�ǰλ�á�
	extern int 		API_fseek(int fd,int offset ,int whence);			//�ƶ���дλ�ã�
	extern int 		API_fread(int fd,void * buf,int count);				//���ļ�������ʵ�ʶ��������ݴ�С
	extern int 		API_fwrite(int fd,const void * buf,int count);		//д�ļ�������ʵ��д������ݴ�С
	extern void* 	API_fmap(int fd,int len);							//����ӳ���ڴ��ַ��ʧ��ΪNULL
	extern void 	API_funmap(void* buf,int len);						//�ͷ�ӳ���ڴ�
	extern int 		API_fremove(const char *filename);					//ɾ���ļ���0�ɹ�����0ʧ��	
	extern int 		API_fsize(const char *filename);					//�����ļ�����,-1��ʾ�Ҳ����ļ�
	extern void		API_fsync(void);									//���ļ�ͬ��������
	
//-----------------------------------------------------------------------------------------------------------------------
	extern int 		API_system(const char *command);					//�ձ�Ӧ�ò�����
//-----------------------------------------------------------------------------------------------------------------------

#endif
