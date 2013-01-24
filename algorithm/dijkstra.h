#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_


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
void construct_queue(AdjList graph[], int gSize, int key[], FibHeap h, FibHeapNodePtr fpnArray[]);
void dijkstra_relax(int u, int v, int w, int parent[], FibHeapNodePtr fpnArray[], FibHeap h);
// ��d[]���������ȶ����У������ȶ����ж�d�����޸�(decreace_key)
// ������ɺ��ٿ�������
// �ٶ�graph��d[]��parent[]���ѷ����ڴ�
void dijkstra(AdjList* graph, int numVertices, int s, int d[], int parent[]);


#endif /* _DIJKSTRA_H_ */
