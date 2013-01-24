// ʵ�ֲ��ཻ������һ���ݽṹ����֧�����²���
// MAKE-SET(x) ����һ���µļ���
// UNION(x, y) ������x��y
// FIND-SET(x) ����һ��ָ�룬ָ�����x(Ψһ)���ϵĴ���
// ���ཻ����ɭ�ֵ�ʵ��
// ͨ��������������ʽ����
// ���Ⱥϲ�
// ·��ѹ��
// ���⣺ ֻ�и����ָ�룬û����Ů����ָ�룬��α������еĽ�㣿 ����Ҫ������
#include <stdio.h>
#include <stdlib.h>
#include "disjoint_set_forest.h"

// ����һ�����
DjsTreeNodePtr djsforest_make_node(int k)
{
    DjsTreeNodePtr x = (DjsTreeNodePtr)malloc(sizeof(*x));
    x->key = k;
    x->parent = NIL;
    return x;
}

// ����һ������
DjsTree djsforest_make_set(DjsTreeNodePtr x)
{
    x->rank = 0;
    x->parent = x;
    return x;
}

// Ѱ�Ҹý�����ڼ��ϵĴ���
DjsTreeNodePtr djsforest_find_set(DjsTreeNodePtr x)
{
    // ʵ��·��ѹ���Ĺ���
    if (x != x->parent)
    {
	// �ݹ�ʵ��
	x->parent = djsforest_find_set(x->parent);
    }
    return x->parent;
}
// ���������и���
DjsTree djsforest_link(DjsTreeNodePtr rep1, DjsTreeNodePtr rep2)
{
    if (rep1->rank > rep2->rank )
    {
	rep2->parent = rep1;
	return rep1;
    }
    else
    {
	rep1->parent = rep2;
    }
    if (rep1->rank == rep2->rank)
    {
	rep2->rank++;
    }
    return rep2;
}

// �ϲ�����������ڵؼ���
DjsTree djsforest_union(DjsTreeNodePtr x, DjsTreeNodePtr y)
{
    return djsforest_link(djsforest_find_set(x), djsforest_find_set(y));
}



/* int main(int argc, char *argv[]) */
/* { */
    
/*     return 0; */
/* } */
