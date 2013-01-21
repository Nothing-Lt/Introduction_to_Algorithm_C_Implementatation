// prim �㷨
// ˼·��
// key[u] parent[u] ������ʵ�֣�Ԫ�صĸ���Ϊ����ĸ���
// ��ν��ڽ���������ڽӾ����ʾ��ͼ�������ȶ����У�
// insert_node()
// ����ж�һ��Ԫ���Ƿ������ȶ����У�
// Ϊÿ����������һλ�Ŀռ�����¼�ý���Ƿ��ڶ���Q�У��ڶ����Ƴ�����ʱ���Ը�λ���и���
// ����key��ȷ�����ȼ��Ĵ�С
// ����inq��(type is Mark)��ȷ���Ƿ������ȼ�������
// ͼ����С���ȶ�����Ҫ�໥����
// ��С���ȶ��еĽ����ʲô�������� ����

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "fib_heap.h"
#include "adj_table.h"

#define NOP -1

// ����ͼ�������ȶ���
// graphΪͼ
// gSizeΪ����ĸ���
// keyΪ���飬�����ʼ����Ȩ��
// hΪFibonacci heap
// fpnArrayΪ�������ȶ�����ÿ�����ָ�������
void construct_queue(adj_list graph[], int gSize, int key[], FibHeap h, FbhPNode fpnArray[])
{
    FbhPNode x;
    int i;
    for (i = 0; i < gSize; i++) {
	x = fib_heap_node_allocate(i);
	x->key = key[i];
	x->ref = i;
	fpnArray[i] = x;
	fib_heap_insert(h, x);
    }
}
// ��ӡ��С������
// ��С����������
// A = {(v, parent(v) : v is a member of V - {idx})}
void mst_prim_print(int parent[], int size, int idx)
{
    int i;
    for (i = 0; i < size; i++) {
	if (parent[i] != NOP)
	{
	    printf("edge: %d -> %d\n", i, parent[i]);
	}
    }
    printf("\n");
}
// adj_list��ָ�����ָ��
// graph �����飬�����Ԫ��Ϊadj_listָ��
// gSize Ϊ����Ԫ�صĸ���
// rΪ���������
// u, vΪָ��
// ����Ԫ��Ϊָ����������������ȼ������е�����Ԫ��
void mst_prim(adj_list* graph, int gSize, int rIdx)
{
    int i;
    int key[gSize];
    adj_pnode v;
    int parent[gSize];
    FibHeap h = make_fib_heap();
    FbhPNode fpnArray[gSize];
    for (i = 0; i < gSize; i++) {
	key[i] = INT_MAX;
	parent[i] = NOP;
    }
    key[rIdx] = 0;
    // ��ͼ�����еĶ���������ȼ�������
    construct_queue(graph, gSize, key, h, fpnArray);
    fib_heap_root_print(h->min);
    while (h->min != NIL) {
	FbhPNode u = fib_heap_extract_min(h);
	printf("extract_min: %d\n", u->ref);
	/* printf("after extract_min\n"); */
	/* fib_heap_root_print(h->min); */
	u->inq = FALSE;
	// u->ref ָ��ͼ���������
	// v ָ���ڽ������ĳһ���
	// ���ڵ���
	v = graph[u->ref];
	while (v) {
	    if (fpnArray[v->vertex]->inq == TRUE
		&& v->weight < fpnArray[v->vertex]->key)
	    {
		parent[v->vertex] = u->ref;
		fib_heap_decrease_key(h, fpnArray[v->vertex], v->weight);
	    }
	    v = v->next;
	}
    }
    mst_prim_print(parent, gSize, rIdx);
}



int main(int argc, char *argv[])
{
    adj_list* graph =  NULL;
    int numVertices;
    // �����ڽ����������ݴ�mst_prim.dat�ļ��ж���
    int rIdx;
    printf("input the rIdx\n");
    fflush(stdout);
    scanf("%d", &rIdx);
    graph = construct_weighted_adj_list(argv[1], graph, &numVertices);
    mst_prim(graph, numVertices, rIdx);
    return 0;
}
