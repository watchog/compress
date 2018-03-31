/*
	编码格式：
	最高一位标志位表示short值存有编码信息
	最低三位表示编码长度
	从第四位开始是编码信息长度取决于最低三位
*/
#ifndef ENCODE_H
#define ENCODE_H

#include"build_tree.h"
class Encode{
	public:
		Encode(BuildTree &btpara);
		//进行编码
		void encode();
		//遍历整棵树
		void walk_through_tree(int node,int code);
	
		int code[256];
		unsigned int root;//指向树的根节点
		BuildTree &bt;
};
#endif


