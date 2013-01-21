// ϡ��ͼ�ϵ�johnson�㷨
// �������ظ�Ȩ����
// �����ڽ�����ʵ��ͼ�Ľṹ
// ������Dijkstra�㷨��Bellman-Ford�㷨��Ϊ���ӳ���
#include "johnson.h"

// Դ�㵽����������ľ���Ϊ0
// ����source���������
adj_list* add_source_vertex(adj_list* graph, int numVertices, int* sIdx)
{
    int i;
    adj_list* gQuote = copy_adjlist(graph, numVertices);
    adj_output(gQuote, numVertices);
    // realloc������ڴ棬һ��Ҫ��ס����
    gQuote = (adj_list *)realloc(gQuote, (numVertices + 1)* sizeof(adj_list));
    gQuote[numVertices] = NULL;
    if (gQuote == NULL)
    {
	printf("can't realloc for gQuote\n");
	exit(EXIT_FAILURE);
    }
    for (i = 0; i < numVertices; i++) {
	adj_weight_insert(gQuote[numVertices], i, 0);
    }
    *sIdx = numVertices;
    return gQuote;    
}

AdjMat* johnson(adj_list* graph, int numVertices)
{
    int u, v;
    adj_list* gQuote;
    int sIdx;
    int *h, *parent, *dQuote, *parentQuote;
    AdjMat* dMat = make_adjmat(numVertices);
    h = (int *)malloc((numVertices + 1) * sizeof(int));
    parent = (int *)malloc((numVertices + 1) * sizeof(int));
    dQuote = (int *)malloc((numVertices + 1) * sizeof(int));
    parentQuote = (int *)malloc((numVertices + 1) * sizeof(int));
    gQuote =  add_source_vertex(graph, numVertices, &sIdx);
    adj_output(gQuote, numVertices + 1);
#ifdef DEBUG
    printf("johnson started\n");
    fflush(stdout);
#endif // DEBUG    

    if (bellman_ford(gQuote, numVertices+1, sIdx, h, parent) == FALSE)
    {
	printf("the input graph contains a negtive-weight cycle\n");
	return NULL;
    }
    else
    {
	// ���һ������������һ����ÿ�������Ľ������޸ĵĺ�����
	int i;
	for (i = 0; i < numVertices+1; i++) {
	    adj_pnode x = gQuote[i];
	    while (x) {
		x->weight = x->weight + h[i] - h[x->vertex];
		x = x->next;
	    }
	}
    }
    for (u = 0; u < numVertices; u++) {
	// ��u��ΪԴ������Dijkstra�㷨�������·��
	// need to zero the dQuote and parentQuote?
	dijkstra(gQuote, numVertices+1, u, dQuote, parentQuote);
	for (v = 0; v < numVertices; v++) {
	    dMat->mat[u][v] = dQuote[v] + h[v] - h[u];
	}
    }
    free(h);
    free(parent);
    free(dQuote);
    free(parentQuote);
    freeAdjList(gQuote, numVertices + 1);
    // remember to free the dMat outside the function.
#ifdef DEBUG
    printf("johnson finished\n");
    fflush(stdout);    
#endif // DEBUG    
    return dMat;
}
