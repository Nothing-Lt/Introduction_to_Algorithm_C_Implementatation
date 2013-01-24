#ifndef _DFS_H_
#define _DFS_H_
#include "adj_table.h"
#include "include/require.h"


EBool dfs_visit(int i, AdjList* graph, int numVertices, EColor* color, int* parent, int* d, int* f);
// �ٶ�graph parent, d, f���ڴ��ѷ����
EBool dfs(AdjList* graph, int numVertices, int *parent, int* d, int* f, int *seq);
void print_edgetype(int start, int end, int type);
void print_array(const char* arr_name, int arr[], int length);



#endif /* _DFS_H_ */
