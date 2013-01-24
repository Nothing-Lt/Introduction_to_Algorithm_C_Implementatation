// �����޻�·ͼ�ĵ�Դ���·��
// �Ƚ�����������
// ��������Ҫ�õ������������dfs
// ���������������������Ľ���������ʱ��ݽ���˳������
// ��������������˳�򣬶��Ը�����Ϊ���ı߽����ɳ�


#include <stdio.h>
#include <stdlib.h>
#include "dag_shortest_path.h"

void dag_shortest_path(AdjList* graph, int length, int s, int d[], int parent[])
{
    AdjListNodePtr adjNode;
    List list = NULL, x = NULL;
    // toplogically sort the vertices of G
    toplogical_sort(graph, length, &list);
    initialize_single_source(graph, length, s, d, parent);
    x = list;
    while(x->value != s){
	x = x->next;
    }
    while(x)
    {
	adjNode = graph[x->value];
	while(adjNode)
	{
	    relax(x->value, adjNode->vertex, adjNode->weight ,d, parent);
	    adjNode = adjNode->next;
	}
	x = x->next;
    }
    free_list(list);
}







