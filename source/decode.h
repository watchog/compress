#ifndef DECODE_H
#define DECODE_H
#include"build_tree.h"
#include"rwfile.h"
class Decode{
	public:
		Decode(BuildTree &btpara,RWFile &rwfpara);
		void decode(unsigned char code,bool is_end,int len);

		unsigned int node_pos = 1;
		BuildTree &bt;
		RWFile &rwf;
};
#endif


