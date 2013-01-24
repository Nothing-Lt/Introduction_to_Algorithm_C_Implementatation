#include <stdio.h>
#include <stdlib.h>
#include "toplogical_sort.h"

int main(int argc, char *argv[])
{
    
    List list = NULL;
    AdjList* graph = NULL;
    int numVertices;
    if (argc != 2)
    {
	printf("%s filename\n", argv[0]);
	exit(EXIT_FAILURE);
    }
    // ����ͼ
    graph = construct_adjlist(argv[1], graph, &numVertices);
    // ����Ľ��Ϊsort_arr�Ķ������а����ʱ��Ӵ�С��������
    toplogical_sort(graph, numVertices, &list);
    print_list(list);
    free_list(list);
    return 0;
}
