#ifndef RWFILE_H
#define RWFILE_H

#include"head.h"
#define RWSIZE 8192			//文件读写缓冲区大小
#define OCTET_SIZE 256			//八位组数组大小
//文件权限
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

class RWFile{
	public:
		RWFile():write_pos(0){
			for(int i = 0;i < OCTET_SIZE;++i)
				octet[i] = 0;
		}
		//以只读的方式打开文件
		bool open_read_only(const char* file);
		//以只写的方式打开文件
		bool open_write_only(const char* file);
		//计数文件中每种八位组出现的次数
		void cnt_each_octet();
		//向文件中写
		void write_to_file(const unsigned char ch,bool is_end);
		//从文件中读
		void read_from_file(unsigned char buffer[],unsigned int &len);
		//读取特定长度字节
		void read_specific_byte(unsigned char buffer[],unsigned len);
		//将文件指针重置在开始处
		void clear_read_fd(){lseek(read_fd,0,SEEK_SET);}
		//当前读文件指针的位置
		unsigned long long
		curr_fd_pos(){return lseek(read_fd,0,SEEK_CUR);}
		unsigned long long
		curr_write_pos(){return (lseek(write_fd,0,SEEK_CUR)+write_pos);}
		//文件的长度
		unsigned long long
		file_length(){fstat(read_fd,&file_info);return file_info.st_size;}

		~RWFile(){close(read_fd);close(write_fd);}

		unsigned long octet[OCTET_SIZE];
private:
		unsigned char write_buffer[RWSIZE];
		int read_fd,write_fd;
		unsigned int write_pos;
		struct stat file_info;
};
#endif
