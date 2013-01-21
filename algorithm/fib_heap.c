// ʵ��Fibnacci heap
// �ɺϲ��Ѳ���
// INSERT
// MINIMUM
// EXTRACT-MIN
// UNION
// ��ͨ����
// DECREASE-KEY
// DLETE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fib_heap.h"

/* ����һ������ʵ�ָ�������� */
// �ٶ�root1����������
// �ٶ�root2����������
void concatenate_root_list(RootTblPtr root1, RootTblPtr root2)
{
    /* ��root1����߰ѻ��򿪣�ͬʱ��root2���ұ߰ѻ��� */
    /* �������������Խ��� */
    /* ����root1��root2������ΪNIL����� */
    /* ���Ӻ󷵻�root1 */
    RootTblPtr root1Left;
    RootTblPtr root2Right;
    if (root1 != NIL && root2 != NIL)
    {
	// ��ʱh1 �� h2 ����ΪNIL
	root1Left = root1->left;
    	root2Right = root2->right;
	root1->left = root2;
	root1Left->right = root2Right;
	root2->right = root1;
	root2Right->left = root1Left;
    }    
}


/* ����һ���µ�Fibnacci �� */
FibHeap make_fib_heap()
{
    FibHeap h = (FibHeap)malloc(sizeof(*h));
    h->n = 0;
    h->min = NIL;
    return h;
}

/* ����һ����� */
int fib_heap_insert(FibHeap h, FbhPNode x)
{
    x->degree = 0;
    x->parent = NIL;
    x->child = NIL;
    x->left = x;
    x->right = x;
    x->mark = FALSE;
    /* concatenate the root list containing x with root list H */
    /* ��min����߽��в��� */
    /* rootTbl����ΪNULL */
    /* rootLeft����ΪNIL */
    concatenate_root_list(h->min, x);
    if (h->min == NIL || x->key < h->min->key)
    {
	h->min = x;
    }
    h->n++;    
    return 0;
}

// ����ָ����С����ָ��
FbhPNode fib_heap_minimum(FibHeap h)
{
    return h->min;
}

// �ϲ�����Fibonacci ��
FibHeap fib_heap_union(FibHeap h1, FibHeap h2)
{
    FibHeap h = make_fib_heap();
    h->min = h1->min;
    /* concatenate the root list of h2 with the root list of h */
    concatenate_root_list(h->min, h2->min);
    if (h1->min == NIL || (h2->min != NIL && h2->min->key < h1->min->key))
    {
	h->min = h2->min;
    }
    h->n = h1->n + h2->n;
    // free h1 and h2
    h1->min = NIL;
    h2->min = NIL;
    free(h1);
    free(h2);
    return h;
}

// �ٶ�x��y����ΪNIL����x��y��Ϊ�����еĽ��
// ��y��Ϊx���ӽ��
// �޸�y��x�ı�������y -> bechild x -> beparent
void fib_heap_link(FibHeap h, FbhPNode y, FbhPNode x)
{
    // remove y from the root list of h
    y->right->left = y->left;
    y->left->right = y->right;
    y->left = y;
    y->right = y;
    // make y a child of x, incrementing degree[x]
    concatenate_root_list(x->child, y);
    if(x->child == NIL)
    {
	x->child = y;
    }
    x->degree++;
    y->parent = x;
    y->mark = FALSE;
}

// �ٶ�h��ΪNIL, ��h->minҲ��ΪNIL
// ��ʱ��С�ؼ��ֵĽ���ѱ���ȡ
void consolidate(FibHeap h)
{
    // ʹ����һ����������array[0.. D(n[h])] D(n[h])Ϊ��������������֪�Ͻ�
    // D(n[h]) <= floor(��(1 + sqrt(5))/2Ϊ�׶�n�����)
    const int dupperbound = (int)(log(h->n)/log((1 + sqrt(5.0))/2.0))+1;
    FbhPNode array[dupperbound];
    FbhPNode w, x, y, sentinel;
    printf("the number of the heap node is %d\n", h->n);
    printf("the dupperbound is %d\n", dupperbound);
    int i,d;
    for (i = 0; i < dupperbound; i++) {
	array[i] = NIL;
    }
    // �����ǻ���������β��Ի�������Ľ�β��
    // �һ����������˱仯
    w = h->min;
    sentinel = w;
    do {
	x = w;
	w = w->right;
	d = x->degree;
	while (array[d] != NIL) {
	    // another node with the same degree as x
	    y = array[d];
	    // ʼ�ս�x��Ϊ�����
	    if (x->key > y->key)
	    {
		// ����x��y��ָ��
		// ���x���ڱ�sentinelָ��ͬһ�����
		// ͬʱ�ı��ڱ���ָ��
		FbhPNode tmp = x;
		x = y;
		y = tmp;
	    }
	    // ע������ڱ������ж�ѭ���Ľ���������
	    if (sentinel == y) {
		// ��w�ڵ�ǰ�����Ĺ�������ָ���ڱ�
		// ����w������ָ���µ��ڱ�
		if (w == sentinel)
		{
		    w = x;
		}
		sentinel = x;
	    }
	    // ��y��Ϊx���ӽ��
	    fib_heap_link(h, y, x);
	    array[d] = NIL;
	    d++;
	    // error here!
	    // to be continued...
	    printf("d is %d\n", d);
	    assert(d < dupperbound);
	}
	array[d] = x;
    }while (w != sentinel);
    h->min = NIL;
    // ȷ������ǰ��������֮��û����ϵ
    for (i = 0; i < dupperbound; i++) {
	if (array[i] != NIL)
	{
	    array[i]->right = array[i];
	    array[i]->left = array[i];
	}
    }

    for (i = 0; i < dupperbound; i++) {
	if (array[i] != NIL)
	{
	    // add array[i] to the root list of h
	    concatenate_root_list(h->min, array[i]);
	    if (h->min == NIL || array[i]->key < h->min->key)
	    {
		h->min = array[i];
	    }
	}
    }
}
// ��ȡ��С���
RootTblPtr fib_heap_extract_min(FibHeap h)
{
    RootTblPtr z = h->min;
    RootTblPtr x;
    RootTblPtr xright;
    if (z != NIL)
    {
	// for each child x of z
	// do add x to the root list of h
	// p[x] = NIL
	x = z->child;
	// ���������ѭ������ʽ
	while (x != NIL) {
	    // ��x��z���ӻ�����������ȡ����
	    if (x != x->right) {
		xright = x->right;
	    }
	    else {
		xright = NIL;
	    }
	    x->left->right = x->right;
	    x->right->left = x->left;
	    x->right = x;
	    x->left = x;
	    x->parent = NIL;
	    // ��z�ĺ��Ӽ��뵽������
	    concatenate_root_list(h->min, x);
	    x = xright;
	}
	// remove z from the root list of h
	z->left->right = z->right;
	z->right->left = z->left;
	if (z == z->right)
	{
	    h->min = NIL;
	}
	else
	{
	    h->min = z->right;
	    // test here!!! h->n == 8
	    consolidate(h);
	}
	z->right = z;
	z->left = z;
	h->n--;
    }
    return z;
}


// �ٶ�h->min��ΪNIL��x��ΪNIL��y��ΪNIL
void cut(FibHeap h, FbhPNode x, FbhPNode y)
{
    // remove x from the child list of y, decrementing degree[x]
    // ����x��yΨһ���ӽ�㣿
    // x == y->child?
    if (x != x->right)
    {
	// x ����y��Ψһ�ӽ��
	y->child = x->right;
	x->right->left = x->left;
	x->left->right = x->right;
	x->right = x;
	x->left = x;
    }
    else
    {
	y->child = NIL;
    }
    y->degree--;
    // add x to the root list of h
    concatenate_root_list(h->min, x);
    // p[x] = NIL
    x->parent = NIL;
    // mark[x] = FALSE
    x->mark = FALSE;
}

void cascading_cut(FibHeap h, FbhPNode y)
{
    FbhPNode z = y->parent;
    if (z != NIL)
    {
	if (y->mark == FALSE)
	{
	    y->mark = TRUE;
	}
	else
	{
	    cut(h, y, z);
	    cascading_cut(h, z);
	}
    }
}

// ��Сһ���ؼ���
// �ٶ���������ɾ��һ����㲢���ı䱻ɾ�������κνṹ��
void fib_heap_decrease_key(FibHeap h, FbhPNode x, int k)
{
    FbhPNode y;
    if (k > x->key)
    {
	printf("new key is greater than the current key\n");
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    x->key = k;
    y = x->parent;
    if (y != NIL && x->key < y->key)
    {
	// ��x��y���ӽ����ȡ�������ŵ��������ȥ
	cut(h, x, y);
	cascading_cut(h, y);
    }
    if (x->key < h->min->key)
    {
	h->min = x;
    }
}

void fib_heap_delete(FibHeap h, FbhPNode x)
{
    fib_heap_decrease_key(h, x, INT_MIN);
    fib_heap_extract_min(h);
}

FbhPNode fib_heap_node_allocate(int key)
{
    FbhPNode x = (FbhPNode)malloc(sizeof(FbhNode));
    x->key = key;
    x->inq = TRUE;
    return x;
}

FbhPNode testPtr;
FibHeap fib_heap_construct(int arr[], int length)
{
    int i;
    FibHeap h = make_fib_heap();
    FbhPNode x;
    assert(length >= 0);
    for (i = 0; i < length; i++) {
	x = fib_heap_node_allocate(arr[i]);
	if (arr[i] == 52)
	{
	    testPtr = x;
	}
	fib_heap_insert(h, x);
    }
    return h;    
}

// ��ӡ���е�Ԫ��
void fib_heap_root_print(FbhPNode r)
{
    FbhPNode x = r;
    FbhPNode sentinel = x;
    if (x != NIL)
    {
	do 
	{
	    printf("%d \n", x->key);
	    if (x->child)
	    {
		printf("down\n");
		fib_heap_root_print(x->child);
		printf("up\n");
	    }
	    x = x->right;
	} while(x != sentinel);
    }
    fflush(stdout);
}
// test the Fibonacci heap
/* int main(int argc, char *argv[]) */
/* { */
/*     int arr1[NUMARRAY] = {23, 7, 21, 3}; */
/*     // int arr1[NUMARRAY] = {3, 7, 23, 21, 24, 18, 52, 17}; */
/*     int arr2[NUMARRAY] = {17, 24, 18, 52}; */
/*     // ������ */
/*     FibHeap h1 = fib_heap_construct(arr1, sizeof(arr1)/sizeof(*arr1)); */
/*     printf("h1:\n"); */
/*     // fib_heap_extract_min(h1); */
/*     fib_heap_root_print(h1->min); */
/*     FibHeap h2 = fib_heap_construct(arr2, sizeof(arr2)/sizeof(*arr2)); */
/*     printf("h2:\n"); */
/*     fib_heap_root_print(h2->min); */
/*     FibHeap h = fib_heap_union(h1, h2); */
/*     printf("h:\n"); */
/*     fib_heap_root_print(h->min); */
/*     RootTblPtr min = fib_heap_extract_min(h); */
/*     printf("min = %d\n", min->key); */
/*     fib_heap_root_print(h->min); */
/*     min = fib_heap_minimum(h); */
/*     fib_heap_decrease_key(h, min, 5); */
/*     printf("after decreased key h:\n"); */
/*     fib_heap_root_print(h->min); */
/*     fib_heap_delete(h, min); */
/*     printf("after delete key h:\n"); */
/*     fib_heap_root_print(h->min); */
/*     fib_heap_delete(h, testPtr); */
/*     printf("after delete key 52 h:\n"); */
/*     fib_heap_root_print(h->min); */
/*     return 0; */
/* } */
