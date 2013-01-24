// ��һ���ٽ��ת��
#include <stdio.h>
#include <stdlib.h>
#include "transpose_adj_table.h"

//�����ӿڵ����
// ���룺adj_list* G
// �����adj_list* G_tanspose
// �ı�Ķ���G
AdjList* transpose_adj_table(AdjList* graph, int numVertices)
{
    // Ϊת��ͼ����洢�ռ䣬����ʼ��Ϊ0
    AdjList* graph_transpose = (AdjList *)calloc(numVertices, sizeof(AdjListNodePtr));
    int i;
    AdjListNodePtr pNode = NULL;
    for (i = 0; i < numVertices; i++) {
	while (graph[i]) {
	    int vertex;
	    // ������graph[i]��ȡ����
	    // ������graph_transpose[i]��ǰ��
	    pNode = graph[i];
	    graph[i] = graph[i]->next;
	    pNode->next = NULL;
	    vertex = pNode->vertex;
	    pNode->vertex = i;
	    pNode->next = graph_transpose[vertex];
	    graph_transpose[vertex] = pNode;
	}
    }
    free(graph);
    return graph_transpose;
}

