#include <stdio.h>
#include <stdlib.h>
#include "adj_mat.h"


// �����ڽӾ���
// make �����ڴ棬��ֵΪINFINITE
// construct �����ڴ棬ͬʱ��ֵ 

// �����ڽӾ��󣬶���ĸ���ΪnumVertices
AdjMat* make_adjmat(int numVertices)
{
    int i,j;
    AdjMat *m = (AdjMat*)malloc(sizeof(AdjMat));
    m->rows = numVertices;
    m->mat = (int **)malloc(m->rows * sizeof(int *));
    for (i = 0; i < m->rows; i++) {
	m->mat[i] = (int *)malloc(m->rows * sizeof(int));
	for (j = 0; j < numVertices; j++) {
	    m->mat[i][j] = i == j? 0 : INFINITE;	    
	}
    }
    return m;    
}
AdjMat* make_param_adjmat(int numVertices, int pdv, int npdv)
{
    int i,j;
    AdjMat *m = (AdjMat*)malloc(sizeof(AdjMat));
    m->rows = numVertices;
    m->mat = (int **)malloc(m->rows * sizeof(int *));
    for (i = 0; i < m->rows; i++) {
	m->mat[i] = (int *)malloc(m->rows * sizeof(int));
	for (j = 0; j < numVertices; j++) {
	    m->mat[i][j] = i == j? pdv : npdv;
	}
    }
    return m;  
}

// ��ȡ�ļ����ݵķ�ʽ��
// �Ȼ�ö���ĸ���
// Ȼ���ٻ���������㼰��ߵ�Ȩ��
// ����ļ����� ���ǻ���ļ��ṹ��ָ�룿
// ���ݽ����ԭ��Ӧ��Ҫ��ú������ļ��򿪲�������

AdjMat* construct_adjmat(FILE* pFile)
{
    int numVertices;
    int src, dst, weight;
    AdjMat* m;
    if (pFile == NULL)
    {
	printf("invalid file pointer\n");
	exit(EXIT_FAILURE);
    }
    fscanf(pFile, "%d", &numVertices);
    // �����ڴ沢��m�е�Ԫ�ؾ���ֵΪINFINITE
    m = make_adjmat(numVertices);
    while (!feof(pFile)) {
	fscanf(pFile, "%d %d %d", &src, &dst, &weight);
	m->mat[src][dst] = weight;
    }
    return m;
}

AdjMat* construct_param_adjmat(FILE* pFile, int pdv, int npdv)
{
    int numVertices;
    int src, dst, weight;
    AdjMat* m;
    if (pFile == NULL)
    {
	printf("invalid file pointer\n");
	exit(EXIT_FAILURE);
    }
    fscanf(pFile, "%d", &numVertices);
    // �����ڴ沢��m�е�Ԫ�ؾ���ֵΪINFINITE
    m = make_param_adjmat(numVertices, pdv, npdv);
    while (!feof(pFile)) {
	fscanf(pFile, "%d %d %d", &src, &dst, &weight);
	m->mat[src][dst] = weight;
    }
    return m;
}

AdjMat* copy_adjmat(const AdjMat* m)
{
    int i, j;
    AdjMat* l = make_adjmat(m->rows);
    for (i = 0; i < m->rows; i++) {
	for (j = 0; j < m->rows; j++) {
	    l->mat[i][j] = m->mat[i][j];
	}
    }
    return l;
}

void free_adjmat(AdjMat* m)
{
    int i;
    for (i = 0; i < m->rows; i++) {
	free(m->mat[i]);
    }
    free(m->mat);
    free(m);
}


// |1   2   -3  |
// |INF INF -9  |   
void print_adjmat(const AdjMat* m)
{
    int i, j;
    for (i = 0; i < m->rows; i++) {
	printf("|");
	for (j = 0; j < m->rows; j++) {
	    if (m->mat[i][j] == INFINITE)
	    {
		printf("INF ");
	    }
	    else
	    {
		printf("%-4d", m->mat[i][j]);
	    }
	}
	printf("|\n");
    }
    printf("\n");
    fflush(stdout);
}

