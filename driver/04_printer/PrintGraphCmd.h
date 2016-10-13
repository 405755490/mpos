#ifndef __PRINT_GRAPH_CMD__
#define __PRINT_GRAPH_CMD__

//#include "Cmd.h"

#include "libbmp/ZtImage.h"


class PrintGraphCmd 
{
public:

  PrintGraphCmd(const char *imageFileName);
	PrintGraphCmd(const char *imageFileName, int mode);
	PrintGraphCmd(const char *imageFileName, int height, int m);

	virtual ~PrintGraphCmd(void);

	virtual unsigned char* getBuf();
	virtual int getLen();

	int getSteps();
	unsigned char* getStepNBuf(int i);
	unsigned char* getStepNBufLen(int i,int &len);
	int getStepLen(int i);

    ZtImage m_image;
private:
	int convertBmpToData(unsigned char *buf, int line);
	int lineheight;
	int mode;
	unsigned char *buf;
	int len;
};


#endif //__PRINT_GRAPH_CMD__

