#include"head.h"
#include"rwfile.h"
#include"build_tree.h"
#include"decode.h"
Decode::Decode(BuildTree &btpara,RWFile &rwfpara)
			:bt(btpara),rwf(rwfpara){}
void Decode::decode(unsigned char code,bool is_end,int len)
{
	unsigned char mask = 0x01;
	for(int i = 0;i < len;++i){
		mask = 0x1;
		mask  = mask << i;
		if((mask & code) == 0x0){
			node_pos = node_pos * 2;
		}else
			node_pos = node_pos * 2 + 1;

		if(bt.tree[node_pos].flag == true){
			rwf.write_to_file(bt.tree[node_pos].data,false);
			node_pos = 1;
		}
	}
	if(is_end == true){
		rwf.write_to_file('\0',true);
	}
}
