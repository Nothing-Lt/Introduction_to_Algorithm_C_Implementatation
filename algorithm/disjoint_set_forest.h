#ifndef _DISJOINT_SET_FOREST_H_
#define _DISJOINT_SET_FOREST_H_

#define NIL NULL

typedef struct tagTreeNode
{
    struct tagTreeNode* parent;
    int key;
    // rank is the height of the node
    int rank;
}TreeNode, *Tree, *TreePNode;

// ����һ�����
TreePNode djsforest_make_node(int k);
// ����һ�����
TreePNode djsforest_make_node(int k);
// ����һ������
Tree djsforest_make_set(TreePNode x);
// Ѱ�Ҹý�����ڼ��ϵĴ���
TreePNode djsforest_find_set(TreePNode x);
// ���������и���
Tree djsforest_link(TreePNode rep1, TreePNode rep2);
// �ϲ�����������ڵؼ���
Tree djsforest_union(TreePNode x, TreePNode y);

#endif /* _DISJOINT_SET_FOREST_H_ */

