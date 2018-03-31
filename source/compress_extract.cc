#include"head.h"
#include"compress.h"
#include"extract.h"
#include"encode.h"
#include"rwfile.h"
#include"compress_extract.h"

void RjfCompress::compress(const char *file)
{
	RWFile rwf;
	rwf.open_read_only(file);//读取文件
	rwf.cnt_each_octet();	//对出现的字节进行计数
	BuildTree bt(rwf);	
	bt.build();		//构建树
	Encode ec(bt);		//进行编码
	ec.encode();		

	Compress cp(ec,rwf);
	cp.compress_file_name(file);//创建压缩文件名
	cp.compress();		//压缩文件
}
void RjfCompress::extract(const char *file)
{
	extract_t(file);
}
