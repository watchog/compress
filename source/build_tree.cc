#include"head.h"
#include"rwfile.h"
#include"bit_operation.h"
#include"build_tree.h"
BuildTree::BuildTree(){
                for(int i = 0;i < NODE_NUMBER;++i){
                        tree[i].flag = false;
                        tree[i].cnt = 0;
                        tree[i].left_child = 0;
                        tree[i].right_child = 0;
                }
}
BuildTree::BuildTree(RWFile &rwfpara){
                for(int i = 0;i < NODE_NUMBER;++i){
                        tree[i].flag = false;
                        tree[i].cnt = 0;
                        tree[i].left_child = 0;
                        tree[i].right_child = 0;
                }
                for(int i = LEAF_NODE;i < LEAF_NODE+256;++i){
                        if(rwfpara.octet[i-LEAF_NODE] > 0){
                                tree[i].flag = true;
                                tree[i].cnt = rwfpara.octet[i-LEAF_NODE];
                                tree[i].left_child = -1;
                                tree[i].right_child = -1;
                                tree[i].data = (unsigned char)(i-LEAF_NODE);
                        }
                }
}

void BuildTree::build()
{
        struct tree_node tmp;
        int cnt_node = 0;
        int min1,min2;
        while(true){
                min1 = -1,min2 = -1;
                //找出现次数最少的字节
                tmp.cnt = 0xFFFFFFFF;
                for(int i = 1;i < NODE_NUMBER;++i){
                        if(tree[i].flag == true){
                                if(tree[i].cnt!=0&&tree[i].cnt<tmp.cnt){
                                        tmp.cnt = tree[i].cnt;
                                        min1 = i;
                                }
                        }
                }
                tree[min1].flag = false;
                //找出现次数第二少的字节
                tmp.cnt = 0xFFFFFFFF;
                for(int i = 1;i < NODE_NUMBER;++i){
                        if(tree[i].flag == true){
                                if(tree[i].cnt!=0&&tree[i].cnt<tmp.cnt){
                                        tmp.cnt = tree[i].cnt;
                                        min2 = i;
                                }
                        }
                }
                tree[min2].flag = false;
                tree[parent].flag = true;
                tree[parent].cnt = tree[min1].cnt + tree[min2].cnt;
                tree[parent].left_child = min1;
                tree[parent].right_child = min2;
                parent--;
                cnt_node = 0;
                for(int i = 0;i < NODE_NUMBER;++i)
                        if(tree[i].flag == true)
                                cnt_node++;
                if(cnt_node == 1){
                        parent++;//指向第一个根节点
                        break;
                }
        }
}
void BuildTree::rebuild(int code[],unsigned size)
{
        for(int i = 0;i < size;++i){
                if((code[i] & 0x800000) == 0x800000){	//表示这是个有效的编码
                        unsigned code_len = code[i] & 0x000F;
                        unsigned j = 0,node_pos = 1;
//			std::cerr << code[i]  << std::endl;
                        while(j <= code_len){
                                int mask = 0x0010;
                                mask = mask << j;
                                if((mask & code[i]) == 0){
                                        node_pos = node_pos * 2;
                                }else
                                        node_pos = node_pos * 2 +1;
                                ++j;
                        }
                        tree[node_pos].data = i;
                        tree[node_pos].flag = true;
                }
        }
}

