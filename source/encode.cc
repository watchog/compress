#include"head.h"
#include"rwfile.h"
#include"build_tree.h"
#include"bit_operation.h"
#include"encode.h"
/*
*编码格式：最低4位表示编码的长度，从第五位起为字节新的编码，第24位设置为1表示
*这是个有效的编码。
*/

Encode::Encode(BuildTree &btpara)
		:bt(btpara){}
void Encode::encode()
{
	for(int i = 0;i < 256;++i)
		code[i] = 0x0000;
	root = bt.root();
	int code_t = 0x800000;	//将一个较高位设置为1表示第一次插入
	walk_through_tree(root,code_t);
}
void Encode::walk_through_tree(int node,int code_t)
{
	int left = bt.tree[node].left_child;
	int right = bt.tree[node].right_child;
	if(left == -1 && right == -1){
		code_t = code_t | 0x800000; //表示这个编码是有效的
		code[bt.tree[node].data] = code_t;
		return ;
	}
	//从编码树从上往下移动时，向左时往编码中压入0，向右压入1
	if(left != -1)
		walk_through_tree(left,push_bit(code_t,false));
	if(right != -1)
		walk_through_tree(right,push_bit(code_t,true));
}
