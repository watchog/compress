#include"head.h"
#include"bit_operation.h"

//插入时int型整数0x800000用于标志是不是第一次插入单个位
//最低三位标志编码的长度，第四位为编码开始处。
//注意：最低四位为零有两种情况
//第一次插入位时，0000表示还未插入任何值。
//之后插入时，0000表示已经插入一位了，0001表示已经插入两位了。
int push_bit(int x,bool bit)	//true为1，false为0
{
	if((x & 0x800000) == 0x800000){//检查是不是第一次插入
		if(bit == true){
			x = 0x0010;
		}else
			x = 0x0000;
	}else{
		int top = x & 0x000F;
		top++;
		if(bit == true){
			x = x | (0x0001 << (top+4));
		}	
		x = (x & 0xFFFFFFF0) | top;//将更新后的top，插入x.
	}
	return x;
}
//根据字符获取之前创建的字符编码中的新编码写入data
void get_code(unsigned char &data,unsigned &sd,const int code,unsigned &sc)
{
	//字符编码的长度
	int len = 0xF & code;
	int mask = (0x1 << (4+sc));//设定编码的起始位置
	for(;sc <= len && sd <= 7;++sc,++sd){
		if((mask & code) == mask){//获取编码的每一位
			unsigned char tm = 0x1 << sd;
			data = data | tm;
		}
		mask = mask << 1;
	}

	if(sd > 7)		//data写满了
		sd = 0;
	if(sc > len)		//编码的每一位都写入data中了
		sc = 0;
}
//打印short型的每一位
void print_short_bit(const short x)
{
	unsigned short t = 0x8000;
	int i = 0;
	while(i < 16){
		if((x & t) == t){
			std::cout<<"1";
		}else
			std::cout<<"0";
		t = (t >> 1);
		i++;
	}
	std::cout<<std::endl;
}
//打印char型的每一位
void print_char_bit(const char x)
{
	unsigned short t = 0x80;
	int i = 0;
	while(i < 8){
		if((x & t) == t){
			std::cout<<"1";
		}else
			std::cout<<"0";
		t = (t >> 1);
		i++;
	}
	std::cout<<std::endl;
}
