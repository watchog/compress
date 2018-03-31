#include"head.h"
#include"rwfile.h"
#include"build_tree.h"
#include"decode.h"
#include"extract.h"
void extract_t(const char *file)
{
	if(file == NULL){
		std::cerr<<"extract() function:empty file name.";
		std::cerr<<std::endl;
		return ;
	}
	unsigned char buffer[RWSIZE];
	RWFile rwf;
	rwf.open_read_only(file);
	//获取文件长度
	unsigned long long file_length = rwf.file_length();;
	rwf.clear_read_fd();
	
	rwf.read_specific_byte(buffer,1);
	//获取文件类型
	char filetype[20],extract_filename[256];
	memset(filetype,'\0',20);
	memset(extract_filename,'\0',256);

	if(buffer[0] != 0){
		rwf.read_specific_byte((unsigned char*)filetype,(unsigned)buffer[0]);
	}
	//创建解压缩文件名
	int i;
	for(i = strlen(file)-1;i >= 0;--i){
		if(file[i] == '.')
			break;
	}
	if(i < 0){
		std::cout<<"file must be .rjf for ending"<<std::endl;
		return;
	}
	if(buffer[0] > 0){
		strncat(extract_filename,file,i+1);
		strncat(extract_filename+i+1,filetype,buffer[0]);
	}else{
		strncat(extract_filename,file,i);
	}
	rwf.open_write_only(extract_filename);
	
	unsigned char code[4*256] = {0x00};
	rwf.read_specific_byte(code,4*256);//读取编码
	int *p = (int*)code;

	BuildTree bt;
	bt.rebuild(p,256);		//重新构建编码树
	Decode de(bt,rwf);
	unsigned int len = 0;
	unsigned char end_pos;
	//解压缩
	while(true){
		rwf.read_from_file(buffer,len);
		unsigned long long curr_pos = rwf.curr_fd_pos();
		unsigned long long remain = file_length-curr_pos;

		for(i = 0;i < len-2;++i){
			de.decode(buffer[i],false,8);
		}
		if(remain == 0){
			//读到文件结尾退出
			de.decode(buffer[len-2],true,(int)buffer[len-1]);
			break;
		}else if(remain == 1){
			rwf.read_specific_byte(&end_pos,1);
			de.decode(buffer[len-2],false,8);
			de.decode(buffer[len-1],true,(int)end_pos);
			break;
		}else{
			de.decode(buffer[len-2],false,8);
			de.decode(buffer[len-1],false,8);
		}
	}
}
