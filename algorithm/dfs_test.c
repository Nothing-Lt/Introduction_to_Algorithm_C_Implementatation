#include <stdio.h>
#include <stdlib.h>
#include "dfs.h"



int main(int argc, char *argv[])
{
    adj_list* graph = NULL;
    int numVertices;
    // �������飬�����ȱ���ͼparent[]��̽��ʱ��d[]�����ʱ��f[]
    int *parent, *d, *f;
    if (argc != 2)
    {
	printf("%s filename\n", argv[0]);
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    // ����ͼ
    graph = construct_adj_list(argv[1], graph, &numVertices);
    parent = (int *)malloc(numVertices * sizeof(int));
    d = (int *)malloc(numVertices * sizeof(int));
    f = (int *)malloc(numVertices * sizeof(int));
    dfs(graph, numVertices, parent, d, f);
    // �����ݵ�������в��ԣ���β��ԣ�
    // ͨ���������ʱ��f[]��������������ʱ��
    return 0;
}
