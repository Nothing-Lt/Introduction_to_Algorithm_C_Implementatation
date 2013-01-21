// ʵ��dijkstra�㷨
// ���ȼ����е�ʵ�ֶ���prim�㷨
// ���ȼ���������Ĺؼ���Ϊ�����dֵ�������·������ֵ
// ��˾�Ҫ��d��ΪFibonacci���н���ĳһ��Ա�� ��δ�����һ��չ���⣿
// ����prim�㷨������Ĺؼ���
// �㷨�������Զ���prim�㷨�͹�������㷨
// ����Fibonacci��ʵ��
// �ؼ����ڽ�����ȼ����к�ͼ���໥���õ�����
#include "include/require.h"
#include "adj_table.h"
#include "fib_heap.h"
#include "single_source_shortest_path.h"

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

void dijkstra_relax(int u, int v, int w, int parent[], FbhPNode fpnArray[], FibHeap h)
{
    if (fpnArray[v]->key > fpnArray[u]->key + w)
    {
	fib_heap_decrease_key(h, fpnArray[v], fpnArray[u]->key +w);
	parent[v] = u;
    }
}
// ��d[]���������ȶ����У������ȶ����ж�d�����޸�(decreace_key)
// ������ɺ��ٿ�������
// �ٶ�graph��d[]��parent[]���ѷ����ڴ�
void dijkstra(adj_list* graph, int numVertices, int s, int d[], int parent[])
{
    int i;
    adj_pnode v;
    FibHeap h = make_fib_heap();
    FbhPNode fpnArray[numVertices];
    initialize_single_source(graph, numVertices, s, d, parent);
    construct_queue(graph, numVertices, d, h, fpnArray);
    fib_heap_root_print(h->min);
    while(h->min !=  NIL)
    {
	FbhPNode u = fib_heap_extract_min(h);
	printf("extract_min: %d\n", u->ref);
	// ָʾ����u�Ѳ������ȶ�����
	u->inq = FALSE;
	v = graph[u->ref];
	// ����u->refΪ�����ÿ���߽����ɳ�
	while(v)
	{
	    // ���޴���������parent[]���޸ģ�
	    // ѭ������һ�ε������������ȶ����йؼ�������޸�
	    dijkstra_relax(u->ref, v->vertex, v->weight, parent, fpnArray, h);
	    v = v->next;
	}
	
    }
    // �������йؼ��ֵ�ֵ������d�У�����fpnArray[]
    for (i = 0; i < numVertices; i++) {
	d[i] = fpnArray[i]->key;
    }
    // �ͷ����ȶ����е��ڴ�...
}
