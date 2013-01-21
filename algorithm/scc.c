// To be modified ���޸ģ� ֮ǰ�����������˸ı�
// ��֪ͼ�Ľṹ���ҳ�ǿ��ͨ��֧
// ����������������õ�ÿ����������ʱ�䣬�Զ�������ʱ�������������
// ����ͼ��ת��ͼ
// ����ǰ��������������������ʱ��Ľ��򣬶�ת��ͼ�����������������
// ���η���ÿ�����㣬�õ�ͼ��ǿ��ͨ��֧
#include <stdio.h>
#include <stdlib.h>
#include "dfs.h"
#include "list.h"
#include "adj_table.h"
#include "transpose_adj_table.h"

extern int Time;
extern List list;
extern int parent[];
extern Color color[];
extern int d[];
extern int f[];


void transpose_dfs(adj_list* graph, int numVertices, List lst)
{
    int i;
    // �����ݽṹ���г�ʼ������
    Time = 0;
    for (i = 0; i < ALLOC_SIZE; i++) {
	color[i] = WHITE;
	parent[i] = NIL;
	d[i] = 0;
	f[i] = 0;
    }
    while (lst) {
	if(color[lst->value] == WHITE)
	{
	    dfs_visit(lst->value, graph, numVertices);
	    printf("--------------------\n");
	}
	lst = lst->next;    
    }
    // ע��߽���������ʼ�������ͽ�������
}
// �����ӿڵ����
// ���룺adj_list* graph��list������������
// ������ܷ������֧ͼ�� ��ӡ������ǿ��ͨ��֧�Ķ���
// �ı��ֵ�� graph����ת�õĹ�����ʹgraphת���graph_tanspose
void scc(adj_list* graph, int numVertices)
{
    // �������������ͬʱ�������������������Ľ��������list��
    dfs(graph, numVertices);
    // ת��
    graph = transpose_adj_table(graph, numVertices);
    printf("the transposed graph\n");
    adj_output(graph, numVertices);
    // �������������ת�õĽ�����������������
    transpose_dfs(graph, numVertices, list);
    
}

int main(int argc, char *argv[])
{
    adj_list* pAdjl = NULL;
    int numVertices;
    if (argc != 2)
    {
	printf("%s filename\n", argv[0]);
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    // ����ͼ
    pAdjl = construct_adj_list(argv[1], pAdjl, &numVertices);
    // �����ݵ�������в��ԣ���β��ԣ�
    //
    scc(pAdjl, numVertices);
    print_list(list);    
    return 0;
}
