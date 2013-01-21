// ��һ���ٽ��ת��
#include <stdio.h>
#include <stdlib.h>
#include "transpose_adj_table.h"

//�����ӿڵ����
// ���룺adj_list* G
// �����adj_list* G_tanspose
// �ı�Ķ���G
adj_list* transpose_adj_table(adj_list* graph, int numVertices)
{
    // Ϊת��ͼ����洢�ռ䣬����ʼ��Ϊ0
    adj_list* graph_transpose = (adj_list *)calloc(numVertices, sizeof(adj_pnode));
    int i;
    adj_pnode pNode = NULL;
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
    freeAdjList(graph, numVertices);
    return graph_transpose;
}

/* int main(int argc, char *argv[]) */
/* { */
/*     adj_list* pAdjl = NULL; */
/*     int numVertices; */
/*     if (argc != 2) */
/*     { */
/* 	printf("input the data file\n"); */
/* 	exit(EXIT_FAILURE); */
/*     } */
/*     pAdjl =  construct_adj_list(argv[1], pAdjl, &numVertices); */
/*     pAdjl = transpose_adj_table(pAdjl, numVertices); */
/*     adj_output(pAdjl, numVertices); */
/*     freeAdjList(pAdjl, numVertices); */
/*     return 0; */
/* } */
