
#ifndef _KS_STDLIB_H_
#define _KS_STDLIB_H_


//◎标准库定义
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
		F_RDONLY	=00000000,		//只读
		F_WRONLY	=00000001,		//只写
		F_RDWR		=00000002,		//读写
		F_CREAT		=00000100,		//自动创建
		F_APPEND	=00002000
	};
	enum FILE_SEEK
	{
		F_SEEK_SET	=00000001,		//文件开头
		F_SEEK_CUR	=00000002,		//当前位置
		F_SEEK_END	=00000004		//文件结尾
	};
			
	extern int 		API_fopen(const char * filename, int flags);		//打开文件，返回文件句柄，大于0成功
	extern int 		API_fclose(int fd);									//关闭文件，返回当前位置。
	extern int 		API_fseek(int fd,int offset ,int whence);			//移动读写位置，
	extern int 		API_fread(int fd,void * buf,int count);				//读文件，返回实际读出的数据大小
	extern int 		API_fwrite(int fd,const void * buf,int count);		//写文件，返回实际写入的数据大小
	extern void* 	API_fmap(int fd,int len);							//返回映射内存地址，失败为NULL
	extern void 	API_funmap(void* buf,int len);						//释放映射内存
	extern int 		API_fremove(const char *filename);					//删除文件，0成功，非0失败	
	extern int 		API_fsize(const char *filename);					//返回文件长度,-1表示找不到文件
	extern void		API_fsync(void);									//将文件同步到磁盘
	
//-----------------------------------------------------------------------------------------------------------------------
	extern int 		API_system(const char *command);					//普标应用不适用
//-----------------------------------------------------------------------------------------------------------------------

#endif
