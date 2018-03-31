#ifndef COMPRESS_H
#define COMPRESS_H

#include"encode.h"
#include"rwfile.h"
/*
*压缩文件格式
*|文件类型长度|文件类型|文件编码|原文件压缩后数据|
*/
class Compress{
	public:
		Compress(Encode &codepara,RWFile &rwfpara)
			:code(codepara),rwf(rwfpara){
			memset(filename,'\0',256);	//文件名清零
			memset(filetype,'\0',20);	//文件类型清零
		}
		void compress_file_name(const char *file);//根据输入文件名构造压缩文件名
		void compress();//压缩文件

		char filename[256];
		char filetype[20];
		Encode &code;
		RWFile &rwf;
};
#endif


