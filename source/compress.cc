#include"head.h"
#include"rwfile.h"
#include"build_tree.h"
#include"encode.h"
#include"bit_operation.h"
#include"compress.h"

void Compress::compress()
{
	rwf.open_write_only(filename);
	unsigned char type_len = (unsigned char)strlen(filetype);//文件类型长度
	if(type_len > 20)
		type_len = 20;
	rwf.write_to_file(type_len,false);	
	for(int i = 0;i < type_len;++i){	//写入文件类型
		rwf.write_to_file(filetype[i],false);
	}
	unsigned char *ch_short;//将文件编码写入文件中,编码是int型的不是short
	ch_short = (unsigned char *)code.code;
	for(int i = 0;i < 4*256;++i)
		rwf.write_to_file(ch_short[i],false);
	//写入编码后文件数据
	unsigned char data = 0x00;
	unsigned char buffer[RWSIZE];
	rwf.clear_read_fd();

	//当最后一位编码无法写满一个字节时，记录最后一个编码写到的位置
	//用到end_pos最低3位
	unsigned char end_pos = 0;
	unsigned int len = 0,sd = 0,sc = 0;
	while(true){
		rwf.read_from_file(buffer,len);
		for(int i = 0;i < len;){
			get_code(data,sd,code.code[buffer[i]],sc);
			if(sd == 0){
				rwf.write_to_file(data,false);
				data = 0x0;
			}
			if(sc == 0)
				++i;
		}
		int remain_byte = rwf.file_length()-rwf.curr_fd_pos();
		if(remain_byte == 0){
			if(sd != 0){
				end_pos = (unsigned char)sd;
				rwf.write_to_file(data,false);
				rwf.write_to_file(end_pos,false);
			}else{
				rwf.write_to_file(0x8,false);
			}
			rwf.write_to_file('\0',true);//强制将缓存中的数据写入文件中,'\0'不写入
			break;
		}
	}
}
//获取文件类型，构造压缩文件名
void Compress::compress_file_name(const char *file)
{
	if(file == NULL){
		std::cerr<<"Compress::compress_file_name(): filename ";
		std::cerr<<"is NULL."<<std::endl;
		exit(EXIT_FAILURE);
	}
	int len = strlen(file);
	int i = len -1;
	for( ;i >= 0;--i){
		if(file[i] == '.' && i != len-1){
			strcpy(filetype,file+i+1);
			break;
		}
	}
	strncpy(filename,file,strlen(file));
	if(i < 0){
		strncpy(filename+strlen(file),".rjf",4);
	}else{
		memset(filename+i+1,'\0',255-i);
		strncpy(filename+i+1,"rjf",3);
	}
}
