#include "print_path.h"

void print(int point)
{
    printf("%d ", point);
}
// ��ӡ���������·�����������м��
void print_path(adj_list* graph, int* parent, int start, int end)
{
    if (start == end)
    {
	print(start);
    }
    else if (parent[end] == NILVALUE)
    {
	printf("no path from %d to %d exist\n", start, end);
    }
    else
    {
	print_path(graph, parent, start, parent[end]);
	print(end);
    }
}
