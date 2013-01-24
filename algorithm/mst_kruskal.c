// Kruskal �㷨
// �ؼ����⣺��ν�ͼ���ڽ������ʾ�Ͳ��ཻ�������ݽṹ�������
// ��Kruskal �㷨��ʵ��ʵ����ͼ�Ͳ��ཻ���ݼ��ϵı�ʾ����Ҫ�������õ�
// �༴����ʾһ������Ķ�������һ��ָ���Ӧ���ཻ���϶����ָ�룬��֮��Ȼ��
// ��Щ���ϸ��������ʵ�������йء�
// ���ཻ���ϵ�����ֻ��Ҫ����ʾ���㣬���ñ�ʾ�ߣ������ڽ���������ʾ
// ����1
// �����ڽ�������ζԼ��ϵı߽�������
// �������1��ÿ������Ľ������ñߵ����ָ��
// �������2����һ���������±���ߵ������յ�
// ����2
// �����������ߺ������
// ����취���ڱ������ʱ�򲻸���˫��ı�
// �������Щ�߹�������С������
// �������ùܵ���˼�룺�������ͼ�����Ҳ��ͼ


#define INFINITE 0
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "disjoint_set_forest.h"

// ����ߵ�����
typedef struct tagEdge
{
    int startPointIndex;
    int endPointIndex;
}EEdge;

// ͼ�ı�ʾ�����������ڽӾ�������ʾͼ��Ҳ���Ƕ�ά����
#define NUMVERTICES 9

int calcEdge(int g[NUMVERTICES][NUMVERTICES], int cntVertices,  EEdge* edge)
{
    int i, j, edgeNum = 0;
    // ����һ���ߵ��������򶼼���
    for (i = 0; i < cntVertices; i++) {
	for(j = 0; j < i; j++)
	{
	    if (g[i][j] != INFINITE)
	    {
		if(edge != NULL)
		{
		    edge[edgeNum].startPointIndex = i;
		    edge[edgeNum].endPointIndex = j;
		}
		edgeNum++;
	    }
	}
    }
    return edgeNum;
}

void edge_print(EEdge* edge, int cntEdges)
{
    int i;
    for (i = 0; i < cntEdges; i++) {
	printf("%d -> %d\n",edge[i].startPointIndex, 
	                    edge[i].endPointIndex);
    }
    printf("\n");

}


void swapEdge(EEdge* edge, int i, int j)
{
    EEdge tmp;
    tmp.startPointIndex = edge[i].startPointIndex;
    tmp.endPointIndex = edge[i].endPointIndex;
    edge[i].startPointIndex = edge[j].startPointIndex;
    edge[i].endPointIndex = edge[j].endPointIndex;
    edge[j].startPointIndex = tmp.startPointIndex;
    edge[j].endPointIndex = tmp.endPointIndex;
}
// �����еıߣ���Ȩ�ؽ������򣬸��ݸ����ĺ�����������
void sortEdge(EEdge edge[], int cntEdges, int g[NUMVERTICES][NUMVERTICES])
{
    // ��ѡ������
    int i, j;
    for (i = 0; i < cntEdges - 1; i++) {
	for(j = i; j < cntEdges; j++)
	{
	    if (g[edge[i].startPointIndex][edge[i].endPointIndex] 
		> g[edge[j].startPointIndex][edge[j].endPointIndex])
	    {
		// ����������
		swapEdge(edge, i, j);
	    }
	}
    }

}
// ֱ�������С�������ı�
void mst_kruskal(int g[NUMVERTICES][NUMVERTICES], int cntVertices)
{
    int i;
    int cntEdges, newCntEdges;
    EEdge *edge;
    // ��η����ڴ棿
    // ����Ҫ�����������Ȼ���ٷ��䣬����һ��һ���ķ��䣿
    cntEdges = calcEdge(g, cntVertices, NULL);
    edge = (EEdge*)malloc(cntEdges * sizeof(EEdge));
    newCntEdges = calcEdge(g, cntVertices, edge);
    printf("before sort\n");
    edge_print(edge, cntEdges);
    assert(newCntEdges == cntEdges);
    // ������ָ�������
    DjsTreeNodePtr nodeArray[NUMVERTICES];
    for (i = 0; i < cntVertices; i++) {
	nodeArray[i] = djsforest_make_node(i);
	djsforest_make_set(nodeArray[i]);
    }
    // �����еıߣ���Ȩ�ؽ������򣬸��ݸ����ĺ�����������
    sortEdge(edge, cntEdges, g);
    printf("after sort\n");
    edge_print(edge, cntEdges);
    for (i = 0; i < cntEdges; i++) {
	// edge��Ȩ�ش�С��������֮��
	if (djsforest_find_set(nodeArray[edge[i].startPointIndex]) 
	    != djsforest_find_set(nodeArray[edge[i].endPointIndex]))
	{
	    printf("edge: %d -> %d\n", edge[i].startPointIndex, edge[i].endPointIndex);
	    djsforest_union(nodeArray[edge[i].startPointIndex], nodeArray[edge[i].endPointIndex]);
	}
    }
    // free the nodeArray
    for (i = 0; i < NUMVERTICES; i++) {
	free(nodeArray[i]);
    }

}
void adj_matrix_read(int g[NUMVERTICES][NUMVERTICES], int cntVertices, int start, int end, int weight)
{
    if (start >= cntVertices && end >= cntVertices)
    {
	printf("index exceed the scope: %d -> %d", start, end);
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    g[start][end] = weight;
    g[end][start] = weight;
}
void adj_matrix_print(int g[NUMVERTICES][NUMVERTICES], int cntVertices)
{
    int i, j;
    // ����һ���ߵ��������򶼼���
    for (i = 0; i < cntVertices; i++) {
	for(j = 0; j < i; j++)
	{
	    if (g[i][j] != INFINITE)
	    {
		printf("%d -> %d : %2d\t", i, j, g[i][j]);
	    }
	}
	printf("\n");
    }
}


int main(int argc, char *argv[])
{
    // �����ڽӾ���ͼ
    int graph[NUMVERTICES][NUMVERTICES];
    FILE* pf;
    memset(graph, 0, sizeof(int)*NUMVERTICES * NUMVERTICES);
    if ((pf = fopen(argv[1], "r")) == NULL)
    {
	printf("can't open file %s\n", argv[1]);
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    while(!feof(pf))
    {
	int start, end, weight;
	fscanf(pf, "%d %d %d", &start, &end, &weight);
	adj_matrix_read(graph, NUMVERTICES, start, end, weight);
    }
    adj_matrix_print(graph, NUMVERTICES);
    fclose(pf);
    mst_kruskal(graph, NUMVERTICES);
    return 0;
}
