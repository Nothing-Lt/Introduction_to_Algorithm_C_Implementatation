#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "adj_table.h"



void adj_set_weight(AdjListNodePtr adjpnode, int weight)
{
    adjpnode->weight = weight;
}

// һ�������в���һ��Ԫ��
// ֱ��������ǰ�˲��룿

AdjList adj_insert(AdjList adjl, int value)
{
    // ���������������������ͷŵ�ԭ������������ڴ������
    // Ϊ�½������ڴ�
    AdjListNodePtr new = (AdjListNodePtr)malloc(sizeof(AdjListNode));
    if (!new)
    {
	printf("malloc failed\n");
	exit(EXIT_FAILURE);
    }
    
    new->vertex = value;
    new->weight = 0;
    new->next = NULL;
    // next ָ��Ҫ����λ�õ���һ��Ԫ��
    if (adjl)
    {
	// error here!!!
	new->next = adjl->next;
	adjl->next = new;
    }
    else
    {
	adjl = new;
    }
    return adjl;
    
}
// ����������һ������Ȩ�صĽ��
// adj_list��һ����������һ����㣬����...
AdjList adj_weight_insert(AdjList adjl, int value, int weight)
{
    // ���������������������ͷŵ�ԭ������������ڴ������
    // Ϊ�½������ڴ�
    AdjListNodePtr new = (AdjListNodePtr)malloc(sizeof(AdjListNode));
    if (!new)
    {
	printf("malloc failed\n");
	exit(EXIT_FAILURE);
    }
    
    new->vertex = value;
    new->weight = weight;
    new->next = NULL;
    // next ָ��Ҫ����λ�õ���һ��Ԫ��
    if (adjl)
    {
	// error here!!!
	new->next = adjl;
	adjl = new;
    }
    else
    {
	adjl = new;
    }
    return adjl;
}

// �ͷ�����
void freeList(AdjList adjl)
{
    AdjList current = adjl;
    while (adjl) {
	current = current->next;
	free(adjl);
	adjl = current;
    }
}
// �ͷ��ڽ�����
void free_adjlist(AdjList adjl[], int count)
{
    int i;
    for (i = 0; i < count; i++) {
	freeList(adjl[i]);
    }
    free(adjl);
}
// ��������ĳ���
AdjList* arr_realloc(AdjList* adjList, int* parrLength)
{
    size_t newsize, oldsize = *parrLength * sizeof(AdjList);
    adjList = (AdjList *)realloc(adjList, oldsize + INCREMENT_SIZE*sizeof(AdjList));
    *parrLength += INCREMENT_SIZE;
    newsize = *parrLength * sizeof(AdjList);
    if (!adjList)
    {
	printf("realloc failed\n");
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    // ��ʹ�ñ���ʱ��Ҫʱ�̼�ס����������
    memset(adjList+(oldsize/sizeof(AdjList)), 0, newsize - oldsize);
    return adjList;
}
// ����ڽ�����
void print_adjlist(AdjList adjList[], int length)
{
    int i =0;
    printf("%d\n" ,length);
    for (i = 0; i < length; ++i)
    {
	AdjListNodePtr current = adjList[i];
	while(current != NULL)
	{
	    printf("%d -> %d, ", i, current->vertex);
	    printf("weight: %d; ", current->weight);
	    fflush(stdout);
	    current = current->next;
	}
	printf ("\n");
    }
    printf("\n");
}

AdjList* construct_weighted_adjlist(const char* filename, AdjList*
                                      adjList, int* pnumVertices)
{
    int inode;
    int icount = 0;
    int count;
    int arrLength = ALLOC_SIZE;
    FILE *pFile;
    if ((pFile = fopen(filename, "r")) == NULL)
    {
	printf("can't open %s\n", filename);
	fflush(stdout);
	fclose(pFile);
	exit(EXIT_FAILURE);
    }
    // ��ζ�̬��������Ĵ�С��
    // the memory is set to zero.
    adjList = (AdjList*)calloc(ALLOC_SIZE,  sizeof(AdjList));
    if (adjList == NULL)
    {
	printf("can't calloc for adjList\n");
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    do
    {
	int tmpvalue;
	int i = 0;
	fscanf(pFile, "%d", &inode);
	// ��̬��������ĳ���
	if (inode >= ALLOC_SIZE)
	{
	    adjList = arr_realloc(adjList, &arrLength);
	}
	icount++;
	fscanf(pFile, "%d", &count);
	if (count == 0)
	{
	    adjList[inode] = NULL;
	    continue;
	}
	do
	{
	    int tmpweight;
	    fscanf(pFile, "%d %d", &tmpvalue, &tmpweight);
	    // ������ inode�������ڽ�����
	    adjList[inode] = adj_weight_insert(adjList[inode], tmpvalue, tmpweight);
	    printf("adjnode value: %d weight: %d\n", adjList[inode]->vertex, adjList[inode]->weight);
	    i++;
	} while (i < count);
    } while (!feof(pFile));
    printf("input ended\n");
    fflush(stdout);
    print_adjlist(adjList, icount);
    fclose(pFile);
    *pnumVertices = icount;
    return adjList;
    
}
AdjList* construct_adjlist(const char* filename, AdjList* adjList,
                             int* pnumVertices)
{
     // ��ζ�̬��������Ĵ�С��
    // the memory is set to zero.
    adjList = (AdjList*)calloc(ALLOC_SIZE, sizeof(AdjList));
    // adj_list adjList[10] = {NULL};
    int inode;
    int icount = 0;
    int count;
    int arrLength = ALLOC_SIZE;
    FILE *pFile;
    if ((pFile = fopen(filename, "r")) == NULL)
    {
	printf("can't open %s\n", filename);
	fflush(stdout);
	fclose(pFile);
	exit(EXIT_FAILURE);
    }
    do
    {
	int tmpvalue;
	int i;
	//printf ("input the node\n");
	fscanf(pFile, "%d", &inode);
	// ��̬��������ĳ���
	if (inode >= ALLOC_SIZE)
	{
	    adjList = arr_realloc(adjList, &arrLength);
	}
	icount++;
	fscanf(pFile, "%d", &count);
	if (count == 0)
	{
	    continue;
	}
	i = 0;
	do
	{
	    fscanf(pFile, "%d", &tmpvalue);
	    // ������ inode�������ڽ�����
	    adjList[inode] = adj_insert(adjList[inode], tmpvalue);
	    i++;
	} while (i < count);
    } while (!feof(pFile));
    printf("input ended\n");
    fflush(stdout);
    print_adjlist(adjList, icount);
    fclose(pFile);
    *pnumVertices = icount;
    return adjList;
}
AdjList* copy_adjlist(AdjList* graph, int numVertices)
{
    int i;
    AdjList* gQuote;
    gQuote = (AdjList*)calloc(numVertices, sizeof(AdjList));
    for (i = 0; i < numVertices; i++) {
	AdjListNodePtr x = graph[i];
	while (x) {
	    gQuote[i] = adj_weight_insert(gQuote[i], x->vertex, x->weight);
	    x = x->next;
	}
    }
    // remember to free the gQuote outside the function.
    return gQuote;
}
// �ж�һ�����Ƿ����
EBool edge_exist(AdjList* graph, int numVertices, int u, int v)
{
    AdjListNodePtr x = graph[u];
    while(x)
    {
	if (x->vertex == v)
	{
	    return TRUE;
	}
	x = x->next;
    }
    return FALSE;
}

// Ҫ����һ���������磬����ͼҪ֧�ֵĹ����ǣ�����һ���ߺͼ���һ����
// ���趥�������
EBool add_edge(AdjList* graph, int numVertices, int u, int v)
{
    if (edge_exist(graph, numVertices, u, v))
    {
	return FALSE;
    }
    graph[u] = adj_insert(graph[u], v);    
    return TRUE;
}
// ���趥�������
EBool del_edge(AdjList* graph, int numVertices, int u, int v)
{
    // Ҫɾ��һ����㣬�ҵü�ס�ý���ǰһ�����
    AdjListNodePtr pre_x=NULL, x;
    if (!edge_exist(graph, numVertices, u, v))
    {
	return FALSE;
    }
    x = graph[u];
    while (x) {
	if (x->vertex == v)
	{
	    // �����������xָ���һ����㣬����xû��ָ���һ�����
	    if (x == graph[u])
	    {
		graph[u] = x->next;
		free(x);
	    }
	    else
	    {
		assert(pre_x != NULL);
		pre_x->next = x->next;
		free(x);
	    }
	}
	pre_x = x;
	x = x->next;
    }
    return TRUE;
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
/*     freeAdjList(pAdjl, numVertices); */
/*     return 0; */
/* } */
