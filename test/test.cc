#include<iostream>
#include<string>
#include<cstdlib>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#define MAX_FILE_SIZE 		15000
#define BUFFER_SIZE		8192
#define BINARY_FILE_NAME	"./main"
#define src_file_name 		"file.edf"
#define tmp_file_name 		"file.edf1"
#define ext_file_name 		"file.rjf"

char buffer[BUFFER_SIZE];
void create_file(unsigned long length);
bool check_file(unsigned long length,const char *file1,const char *file2);

int main()
{
	for(int file_length = 1;file_length < MAX_FILE_SIZE;file_length+=10){
		for(int i = 0;i <= 0;++i){
			std::string compress(BINARY_FILE_NAME);
			std::string extract(BINARY_FILE_NAME);
			std::string move("mv ");
			create_file(file_length);
			compress += " 1 ";
			compress += src_file_name;
			system(compress.c_str());
			move += src_file_name;
			move += " ";
			move += tmp_file_name;
			system(move.c_str());
			extract += " 2 ";
			extract += ext_file_name;
			system(extract.c_str());
			std::cerr << "file-length: " << file_length << std::endl;
                        bool ret = check_file(file_length,tmp_file_name,src_file_name);
                        if(ret == true){
                                std::cerr << "------------correct---------" << std::endl;
                        }else
                                std::cerr << "------------error-----------" << std::endl;
		}
	}
	return 0;
}

void create_file(unsigned long length)
{
	int fd = open(src_file_name,O_CREAT | O_TRUNC | O_WRONLY,S_IRUSR | S_IWUSR);
	for(int j = 0;j < length;){
		int top = 0;
		while(top < BUFFER_SIZE){
			buffer[top++] = (char)rand() % 256;
			j++;
			if(j == length)
				break;
		}
		write(fd,buffer,top);
	}
	close(fd);
}
bool check_file(unsigned long length,const char *file1,const char *file2)
{

	struct stat buf1,buf2;
        stat(file1,&buf1);
        stat(file2,&buf2);
        int fd1 = open(file1,O_RDONLY);
        int fd2 = open(file2,O_RDONLY);
        char buff1[1024];
        char buff2[1024];
        int sum = 0;
        while(true){
                int len1 = read(fd1,buff1,1024);
                int len2 = read(fd2,buff2,1024);
                if(len1 == 0)
                        break;
                for(int i = 0;i < len1;++i){
                        sum++;
                        if((buff1[i] &  buff2[i]) != buff1[i]){
                                std::cerr << "content diff: " << length << '\t' << (int)buff1[i] << '\t' << (int)buff2[i] ;
				std::cerr << '\t' << buf1.st_size << '\t' << buf2.st_size << std::endl;
			        close(fd1);
			        close(fd2);
                                return false;
                        }
                }
        }
        if(buf1.st_size != buf2.st_size){
                std::cerr << "size diff: "<< length << '\t' << buf1.st_size << '\t' <<buf2.st_size<< std::endl;
 	       	close(fd1);
        	close(fd2);
                return false;
        }
        close(fd1);
        close(fd2);
	return true;
}
