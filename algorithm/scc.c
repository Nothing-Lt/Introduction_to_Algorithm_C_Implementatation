// To be modified ���޸ģ� ֮ǰ�����������˸ı�
// ��֪ͼ�Ľṹ���ҳ�ǿ��ͨ��֧
// ����������������õ�ÿ����������ʱ�䣬�Զ�������ʱ�������������
// ����ͼ��ת��ͼ
// ����ǰ��������������������ʱ��Ľ��򣬶�ת��ͼ�����������������
// ���η���ÿ�����㣬�õ�ͼ��ǿ��ͨ��֧
#include <stdio.h>
#include <stdlib.h>
#include "include/require.h"
#include "sort_arr_idx.h"
#include "dfs.h"
#include "list.h"
#include "adj_table.h"
#include "transpose_adj_table.h"

// �����ӿڵ����
// ���룺adj_list* graph��list������������
// ������ܷ������֧ͼ�� ��ӡ������ǿ��ͨ��֧�Ķ���
// �ı��ֵ�� graph����ת�õĹ�����ʹgraphת���graph_tanspose
void scc(AdjList* graph, int numVertices)
{
    int *parent, *d, *f, *seq;
    parent = (int *)malloc(numVertices * sizeof(int));
    d = (int *)malloc(numVertices * sizeof(int));
    f = (int *)malloc(numVertices * sizeof(int));
    seq = (int *)malloc(numVertices * sizeof(int));
    // �������������ͬʱ�������������������Ľ��������list��
    dfs(graph, numVertices, parent, d, f, NULL);
    // sort the index of f by its value
    printf("f: \n");
    array_print(f, numVertices);
    sort_arr_idx(f, numVertices, seq);
    rvs_arr(seq, numVertices);
    printf("seq: \n");
    array_print(seq, numVertices);
    // ת��
    graph = transpose_adj_table(graph, numVertices);
    printf("the transposed graph\n");
    print_adjlist(graph, numVertices);
    // �������������ת�õĽ�����������������
    dfs(graph, numVertices, parent, d, f, seq);
    free(parent);
    free(d);
    free(f);
    free(seq);
}

int main(int argc, char *argv[])
{
    AdjList* pAdjl = NULL;
    int numVertices;
    if (argc != 2)
    {
	printf("%s filename\n", argv[0]);
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    // ����ͼ
    pAdjl = construct_adjlist(argv[1], pAdjl, &numVertices);
    // �����ݵ�������в��ԣ���β��ԣ�
    scc(pAdjl, numVertices);
    return 0;
}
