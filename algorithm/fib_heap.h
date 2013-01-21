#ifndef _FIB_HEAP_H_
#define _FIB_HEAP_H_

#include "include/require.h"
#define NUMARRAY 4
#define NIL NULL


typedef EBool Mark;
typedef struct tagRootTbl
{
    struct tagRootTbl* parent;
    struct tagRootTbl* child;
    struct tagRootTbl* left;
    struct tagRootTbl* right;
    int ref;
    Mark inq;
    int degree;
    int key;
    Mark mark;    
}*RootTblPtr, *FbhPNode, FbhNode;
typedef struct tagFibHeap
{
    int n;
    RootTblPtr min;
} *FibHeap;


/* ����һ������ʵ�ָ�������� */
// �ٶ�root1����������
// �ٶ�root2����������
void concatenate_root_list(RootTblPtr root1, RootTblPtr root2);

/* ����һ���µ�Fibnacci �� */
FibHeap make_fib_heap();

/* ����һ����� */
int fib_heap_insert(FibHeap h, FbhPNode x);

// ����ָ����С����ָ��
FbhPNode fib_heap_minimum(FibHeap h);

// �ϲ�����Fibonacci ��
FibHeap fib_heap_union(FibHeap h1, FibHeap h2);

// �ٶ�x��y����ΪNIL����x��y��Ϊ�����еĽ��
// ��y��Ϊx���ӽ��
// �޸�y��x�ı�������y -> bechild x -> beparent
void fib_heap_link(FibHeap h, FbhPNode y, FbhPNode x);

// �ٶ�h��ΪNIL, ��h->minҲ��ΪNIL
void consolidate(FibHeap h);

// ��ȡ��С���
RootTblPtr fib_heap_extract_min(FibHeap h);

// �ٶ�h->min��ΪNIL��x��ΪNIL��y��ΪNIL
void cut(FibHeap h, FbhPNode x, FbhPNode y);

void cascading_cut(FibHeap h, FbhPNode y);

// ��Сһ���ؼ���
// �ٶ���������ɾ��һ����㲢���ı䱻ɾ�������κνṹ��
void fib_heap_decrease_key(FibHeap h, FbhPNode x, int k);

void fib_heap_delete(FibHeap h, FbhPNode x);

FbhPNode fib_heap_node_allocate(int key);

FibHeap fib_heap_construct(int arr[], int length);

// ��ӡ���е�Ԫ��
void fib_heap_root_print(FbhPNode r);



#endif /* _FIB_HEAP_H_ */
