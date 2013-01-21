// ʵ�ֶ������һ�������ݽṹ
// ����Ѱ�����ζ�����
#include <stdio.h>
#include <stdlib.h>


#define NIL NULL
// �������ѵ����ݽṹ
typedef struct tagBinomialHeap
{
    struct tagBinomialHeap* parent;
    struct tagBinomialHeap* child;
    struct tagBinomialHeap* sibling;
    int key;
    int degree;
}*BmHeap, *BmPNode, BmNode;


// ����һ���µĶ����
BmHeap make_binomial_heap()
{
    return NIL;
}

// Ѱ����С�ؼ���
BmPNode binomial_heap_minimum(BmHeap h)
{
    // y ΪҪ���ص���С�ؼ��ֵ�ָ��
    // x Ϊ������
    // min ���ڱȽϵ���ʱ����
    BmPNode y = NIL;
    BmPNode x = h;
    int min = INT_MAX;
    while (x != NIL) {
	if (min > x->key)
	{
	    min = x->key;
	    y = x;
	}
	x = x->sibling;
    }
    return y;
}

// ���Ӷ�����y��z��y��z�Ķ�����ͬΪdegree,
// ���Ӻ��Ϊһ�Ŷ���Ϊdegree + 1�Ķ�����
void binomial_link(BmHeap y, BmHeap z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}
void binomial_heap_print_tree(BmPNode t);
void binomial_heap_print_root(BmHeap h);
// �������h1��h2�ĸ���ϳ�һ������h
// ����һ��������������������ĸ���h
BmHeap binomial_heap_merge(BmHeap h1, BmHeap h2)
{
    // ��h2���뵽h1��
    // Ѱ��ѭ������ʽ
    // h1 ʼ���ǰ���������˳�����У������ڽ���Ķ���������ͬ
    // h2 ʼ���ǰ�����������˳�����У�û�ж�����ͬ�Ľ��
    // a2 ��ÿ��ѭ���Ŀ�ʼ��ʼ��ָ��h2��ָ��Ľ�㡣
    // prev_a1ʼ��ָ��a1��ǰһ����㣬��ΪNIL
    // �������������
    // ����h1���һ������sibling��Ա��ΪNIL
    BmPNode prev_a1 = NIL;
    BmPNode a1 = h1;
    BmPNode a2 = h2;
    while (a2) {
	if (a1 == NIL)
	{
	    prev_a1->sibling = a2;
	    // ��ѭ������
	    a2 = NIL;
	}
	else if (a2->degree > a1->degree)
	{
	    prev_a1 = a1;
	    a1 = a1->sibling;
	}
	else // a2 <= a1
	{
	    h2 = a2->sibling;
	    // ��a1��ǰ�����a2
	    if (prev_a1 == NIL)
	    {
		a2->sibling = h1;
		h1 = a2;
	    }
	    else
	    {
		a2->sibling = prev_a1->sibling;
		prev_a1->sibling = a2;
	    }
		prev_a1 = a2;
		a2 = h2;
	}
    }  
//    binomial_heap_print_root(h1);
    return h1;
}
// �ϲ����������
BmHeap binomial_heap_union(BmHeap h1, BmHeap h2)
{
    // Ҫ���صľֲ�����h
    BmHeap h;
    BmPNode prev_x;
    BmPNode x;
    BmPNode next_x;    
    // �ú���û�в���
    h = make_binomial_heap();
    h = binomial_heap_merge(h1, h2);
    h1 = NIL;
    h2 = NIL;
    if (h == NIL)
    {
	return h;
    }
    prev_x = NIL;
    x = h;
    next_x = x->sibling;
    while (next_x != NIL) {
	if (x->degree != next_x->degree ||  // case 1 and case 2
	    (next_x->sibling != NIL && next_x->sibling->degree == x->degree))
	{
	    prev_x = x;
	    x = next_x;
	}
	else if(x->key <= next_x->key)  // case 3
	{
	    x->sibling = next_x->sibling;
	    // ��xΪ����㣬����next_x �� x�����Ŷ�����
	    binomial_link(next_x, x);
	}
	else                           // case 4
	{
	    if(prev_x == NIL)
	    {
		h = next_x;
	    }
	    else
	    {
		prev_x->sibling = next_x;
	    }
	    binomial_link(x, next_x);
	    x = next_x;
	}
	next_x = x->sibling;
    }
    return h;
}

// ����һ����㣬�ٶ�x�ѷ����ڴ棬��key�ֶ��Ѹ�ֵ
BmHeap binomial_heap_insert(BmHeap* ph, BmPNode x)
{
    BmHeap hq = make_binomial_heap();    
    // ��ʼ��x
    x->sibling = NIL;
    x->parent = NIL;
    x->child = NIL;
    x->degree = 0;
    hq = x;
    *ph = binomial_heap_union(hq, *ph);
    return *ph;
}
// ��ȡminimum ����ǰһ������ָ��
BmPNode binomial_heap_prev_min(BmHeap h)
{
    // find the root x with the minimum key in the root list of h,
    // and remove x from the root list of h
    BmPNode prev_x = NIL;
    BmPNode x = h;
    BmPNode prev_y = NIL;
    // ��һ���ⷨ��ֻ����prev_x �� prev_y �����д���
    int min = INT_MAX;
    while (x != NIL) {
	if (min > x->key)
	{
	    min = x->key;
	    prev_y = prev_x;
	}
	prev_x = x;
	x = x->sibling;
    }
    return prev_y;
}
// reverse the order of the linked list of x's children, setting 
// the parent field of each child to NIL,
// and set hq to point to the head of the resulting list
BmHeap binomial_heap_reverse_child(BmPNode y)
{
    // ��y����Ů����ת
    BmHeap h = make_binomial_heap();
    BmPNode x;
    BmPNode iter_x;
    x = y->child;
    y->child = NIL;
    while(x != NIL)
    {
	iter_x = x->sibling;
	// ��x���뵽h��ָ��Ķ���ѵ�ǰ��
	x->sibling = h;
	h = x;
	x = iter_x;
    }
    /* printf("reverse child\n"); */
    /* iter_x = h; */
    /* while(iter_x != NIL) */
    /* { */
    /* 	printf("key: %d, degree: %d\n", iter_x->key, iter_x->degree); */
    /* 	iter_x = iter_x->sibling; */
    /* } */
    /* printf("reverse childe end\n"); */
    return h;
}


// ��ȡ������С�ؼ��ֵĽ�㣬������ָ��ý���ָ��
// need to debug
BmPNode binomial_heap_extract_min(BmHeap* ph)
{
    // ���prev_y ΪNIL��
    BmHeap prev_y = binomial_heap_prev_min(*ph);
    printf("prev_y = %p\n", prev_y);
    BmHeap y;
    BmHeap hq = make_binomial_heap();
    // y is the minimum node and the prev_y is the node adjacent to y
    // in case that prev_y is NIL
    if (prev_y == NIL)
    {
	y = *ph;
	*ph = y->sibling;
    }
    else
    {
	y = prev_y->sibling;
	prev_y->sibling = y->sibling;
    }
    y->sibling = NIL;
    // reverse the order of the linked list of x's children, setting 
    // the parent field of each child to NIL,
    // and set hq to point to the head of the resulting list
    hq = binomial_heap_reverse_child(y);
    // error here!
    *ph = binomial_heap_union(hq, *ph);
    return y;
}

// �����������Ĺؼ���
void binomial_heap_key_swap(BmPNode lhs, BmPNode rhs)
{
    // if lhs and rhs have satellite fields, exchange them too.
    int tmp = lhs->key;
    lhs->key = rhs->key;
    rhs->key = tmp;
}
// ��С�ؼ��ֵ�ֵ
void binomial_heap_decrease_key(BmHeap h, BmPNode x, int k)
{
    BmPNode y;
    BmPNode z;
    if (k > x->key )
    {
	printf("new key is greater than current key\n");
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    x->key = k;
    y = x;
    z = y->parent;
    // ���y�Ĺؼ��ֱ�z�Ĺؼ���С��ð������
    // z ����ΪNIL��
    while (z != NIL && y->key < z->key)
    {
	binomial_heap_key_swap(y, z);
	y = z;
	z = y->parent;
    }
}

// delete a node
void binomial_heap_delete(BmHeap* ph, BmPNode x)
{
    binomial_heap_decrease_key(*ph, x, INT_MIN);
    printf("derease_key completed\n");
    binomial_heap_extract_min(ph);
    free(x);
}

// ���ļ��ж������ݣ���������
BmHeap construct_binomial_heap(const char* filename)
{
    FILE* pFile;
    BmHeap h = NIL;
    BmPNode x;
    int k;
    if ((pFile = fopen(filename, "r")) == NULL)
    {
	printf("can't open file %s\n", filename);
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    while (!feof(pFile)) {
	fscanf(pFile, "%d", &k);
	x = (BmPNode)malloc(sizeof(BmNode));
	if (x == NULL)
	{
	    printf("can't malloc for var x, %s, %d\n", __FILE__, __LINE__);
	    fflush(stdout);
	    exit(EXIT_FAILURE);
	}
	x->key = k;
	binomial_heap_insert(&h, x);
	x = NULL;
    }
    fclose(pFile);
    printf("construct complete!\n");
    return h;
}
void binomial_heap_print_tree(BmPNode t)
{
    // �ݹ��ӡ���
    BmPNode x = t->child;
    printf("key: %d, degree: %d\n", t->key, t->degree);
    while (x) {
    	binomial_heap_print_tree(x);
    	x = x->sibling;
    }
    
}
void binomial_heap_print_root(BmHeap h)
{
    // ��ӡ����Ĺؼ���ֵ�Ͷ���
    BmPNode x = h;
    char * test = "�����Ǹ��õ�һ��";
    while (x) {
	binomial_heap_print_tree(x);
	x = x->sibling;
    }
    printf("%s", test);
}
// �ͷŶ����
void binomial_heap_free(BmHeap h)
{
    
}

// ��β��Զ���ѣ�
// ����ÿһ������������ÿ��������ÿһ��·��
// ���Ա߽�����
// ������һ�����õĲ���������
// ���ݽṹ���Եķ���
// ��������������������������º���
// make_heap()
// insert(h, x)
// minimum(h)
// extract_min(h)
// union(h1, h2)
// ���ϲ���Ϊ�ɺϲ���(mergeable heap)֧�ֵĲ���
// ����Ѻ�Fibonacci�ѻ�֧���������ֲ���
// decrease_key(h, x, k):���¹ؼ���ֵk(�ٶ��������ڵ�ǰ�Ĺؼ���ֵ)������h�еĽ��x
// delete(h, x)
// �Ȳ��Ժ��ĺ���UNION
int main(int argc, char *argv[])
{
    BmHeap h = make_binomial_heap();
    BmHeap h1 = make_binomial_heap();
    BmHeap h2 = make_binomial_heap();
    BmPNode min;
    if (argc < 2)
    {
	printf("%s filename.dat ... \n", argv[0]);
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    // ���ļ��ж���ؼ���ֵ�������㣬�������������
    h1 = construct_binomial_heap(argv[1]);
    binomial_heap_print_root(h1);
    h2 = construct_binomial_heap(argv[2]);
    // binomial_heap_print_root(h2);
    // h = binomial_heap_union(h1, h2);
    printf("the result of union\n");
    binomial_heap_print_root(h);
    min = binomial_heap_minimum(h1);
    printf("the minimum number is %d\n", min->key);
    fflush(stdout);
    // extract_min������
    min = binomial_heap_extract_min(&h1);
    binomial_heap_print_root(h1);
    min = binomial_heap_minimum(h1);
    printf("the minimum number is %d\n", min->key);
    fflush(stdout);
    binomial_heap_delete(&h1, min);
    min = NIL;
    binomial_heap_print_root(h1);
    binomial_heap_free(h);
    return 0;
}
