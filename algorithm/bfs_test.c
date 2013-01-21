#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "adj_table.h"
#include "bfs.h"



// �����ڽ�����
// �����ڽ����������������
// ��ʾͼG��Ҫ���ڽ������ڽ�����������ĳ���
int main(int argc, char *argv[])
{
    adj_list* pAdjl = NULL;
    int numVertices;
    int source, dest;
    int *distance, *parent;
    if (argc != 3)
    {
	printf("%s filename vertex\n", argv[0]);
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
// ָ��Ҫ�����Ķ���
    sscanf((const char*)argv[2], "%d", &source);
// ����ͼ
    pAdjl = construct_adj_list(argv[1], pAdjl, &numVertices);
    distance = (int *)malloc(numVertices * sizeof(int));
    parent = (int *)malloc(numVertices * sizeof(int));    
    pAdjl = bfs(pAdjl, numVertices, source, distance, parent);
    printf("search ended, to be printed\n");
    fflush(stdout);
    printf("input the vertex that you want to go to from %d\n", source);
    fflush(stdout);
    scanf("%d", &dest);
    print_path(pAdjl, numVertices, parent, source, dest);
    free(distance);
    free(parent);
    // �ͷ��ڽ�������ڴ�
    freeAdjList(pAdjl, numVertices);
    return 0;
}
