#ifndef _DISJOINT_SET_FOREST_H_
#define _DISJOINT_SET_FOREST_H_

#define NIL NULL

typedef struct tagTreeNode
{
    struct tagTreeNode* parent;
    int key;
    // rank is the height of the node
    int rank;
}DjsTreeNode, *DjsTree, *DjsTreeNodePtr;

// ����һ�����
DjsTreeNodePtr djsforest_make_node(int k);
// ����һ�����
DjsTreeNodePtr djsforest_make_node(int k);
// ����һ������
DjsTree djsforest_make_set(DjsTreeNodePtr x);
// Ѱ�Ҹý�����ڼ��ϵĴ���
DjsTreeNodePtr djsforest_find_set(DjsTreeNodePtr x);
// ���������и���
DjsTree djsforest_link(DjsTreeNodePtr rep1, DjsTreeNodePtr rep2);
// �ϲ�����������ڵؼ���
DjsTree djsforest_union(DjsTreeNodePtr x, DjsTreeNodePtr y);

#endif /* _DISJOINT_SET_FOREST_H_ */

