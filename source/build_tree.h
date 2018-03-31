#ifndef BUILD_TREE_H
#define BUILD_TREE_H
#include"rwfile.h"
#define NODE_NUMBER 24576
#define LEAF_NODE 512
//编码树的每一个节点
struct tree_node{
	bool flag;	//该节点是否可用
	unsigned long cnt;	//子孙节点的计数总和
	unsigned char data;	//叶节点保存八位组具体的值
	int left_child;		//指向左儿子位置
	int right_child;	//指向右儿子位置
};

class BuildTree{
	public:
		BuildTree(RWFile &rwfpara);
		BuildTree();
		void build();	//构建树
		//重新构建树
		void rebuild(int code[],unsigned len);
		//获取根节点位置
		unsigned int root()const{return parent;}

		unsigned int parent = LEAF_NODE-1;
		struct tree_node tree[NODE_NUMBER];
};
#endif
