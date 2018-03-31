#include"head.h"
#include"rwfile.h"
#include"bit_operation.h" 
#include"build_tree.h"
#include"encode.h" 
#include"decode.h"
#include"compress.h"
#include"extract.h"
#include"compress_extract.h"


int main(int argc,char **argv)
{
	if(argc < 3){
		std::cerr << argv[0] << " opt(1-压缩 or 2-解压缩) " << "文件名";
		std::cerr << std::endl;
		return 0;
	}
	int option = std::stoi(argv[1]);
	switch(option){
		case 1:
			RjfCompress::compress(argv[2]);
			std::cout<<"压缩完成"<<std::endl;
			break;
		case 2:
			RjfCompress::extract(argv[2]);
			std::cout<<"解压缩完成"<<std::endl;
			break;
	}
	return 0;
}
