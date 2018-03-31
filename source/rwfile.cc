#include"head.h"
#include"rwfile.h"

bool RWFile::open_write_only(const char* file)
{
	if((write_fd = open(file,O_WRONLY | O_CREAT | O_TRUNC,FILE_MODE)) == -1){
		std::cerr<<"RWFile::open_write_only() open "<<file;
		std::cerr<<" failed."<<std::endl;
		return false;
	}
	return true;
}
bool RWFile::open_read_only(const char* file)
{
	if((read_fd = open(file,O_RDONLY)) == -1){
		std::cerr<<"RWFile::open_read_only() open "<<file;
		std::cerr<<" failed."<<std::endl;
		exit(EXIT_FAILURE);
	}
	if(lseek(read_fd,0,SEEK_END) == 0){
		std::cerr<<"RWFile::open_read_only() :"<<file;
		std::cerr<<" is empty.."<<std::endl;
		exit(EXIT_FAILURE);
	}
	lseek(read_fd,0,SEEK_SET);
	return true;	
}
void RWFile::cnt_each_octet()
{
	unsigned char data[RWSIZE];
	int len = 0;
	while((len = read(read_fd,data,RWSIZE)) > 0){
		for(int i = 0;i < len;++i)
			++octet[data[i]];
	}
}
void RWFile::read_from_file(unsigned char buffer[],unsigned int &len)
{
	len = read(read_fd,buffer,RWSIZE);
}
void RWFile::read_specific_byte(unsigned char buffer[],unsigned len)
{
	read(read_fd,buffer,len);
}
void RWFile::write_to_file(const unsigned char ch,bool is_end)
{
	if(is_end){
		int k = write(write_fd,write_buffer,write_pos);
		write_pos = 0;
		return ;
	}

	write_buffer[write_pos++] = ch;
	if(write_pos == RWSIZE){
		write(write_fd,write_buffer,write_pos);
		write_pos = 0;
	}
}
