// ͼ������������㷨ʵ��
// ���ȥ��ȫ�ֱ���
// ȡ����ʹ�õĲ�������������
// �����������������Ӧ��
// ������������
// ��һ������ͼ�ֽ�Ϊ��ǿ��ͨ��֧
// ����Ӧ�������������
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dfs.h"


// ���ݽ���ʱ��f����ͼ������������
// ������������������ӿڵ����
// ����������ڽ�����adj_list*,�ڽ������ж���ĸ�����
// ����������ڽ�����adj_list*, 
// �ı��ֵ��d[],f[],color[](��������),parent[], 
// �ı��ֵ��list(save the result of the toplogical_sort() function);
EBool dfs_visit(int i, adj_list* graph, int numVertices, Color* color, int* parent, int* d, int* f);
// �ٶ�graph parent, d, f���ڴ��ѷ����
EBool dfs(adj_list* graph, int numVertices, int *parent, int* d, int* f)
{
    int i;
    // �����ݽṹ���г�ʼ������
    Color *color = (Color *)malloc(numVertices * sizeof(Color));
    for (i = 0; i < numVertices; i++) {
	color[i] = WHITE;
	parent[i] = NILVALUE;
	d[i] = 0;
	f[i] = 0;
    }
    // ע��߽���������ʼ�������ͽ�������
    for (i = 0; i < numVertices; i++) {
	if (color[i] == WHITE)
	{
	    // ��ε���dfs_visit
	    dfs_visit(i, graph, numVertices, color, parent, d, f);
	}
	printf("---------------------\n");
    }
    return TRUE;
}
void set_edge_type(int start, adj_list pendnode, Color *color, int* d);
// �ù����Ǹ��ݹ���õĹ���
EBool dfs_visit(int i, adj_list* graph, int numVertices, Color* color, int* parent, int* d, int* f)
{
    // ��̬����Time���ڶ�ε��ü䣬����storage duration
    static int Time = 0;
    // ȷ��i����Ч��Χ��
    adj_list pnode = graph[i];
    assert(i >= 0);
    color[i] = GRAY;
    d[i] = ++Time;
    printf("d[%d] = %d\n", i, d[i]);
    while (pnode) {
	set_edge_type(i, pnode, color, d);
	if (color[pnode->vertex] == WHITE)
	{
	    // pnode->edgeType = TREE;
	    // printf("the edge type of %d to %d is %d");
	    // print_edgetype(i, pnode->vertex, pnode->edgeType);
	    parent[pnode->vertex] = i;
	    printf("parent[%d] = %d\n", pnode->vertex, 
		   parent[pnode->vertex]);
	    dfs_visit(pnode->vertex, graph, numVertices, color, parent, d, f);
	}
	pnode = pnode->next;
    }
    color[i] = BLACK;
    f[i] = ++Time;  
    printf("f[%d] = %d\n", i, f[i]);
    return TRUE;
}

void print_edgetype(int start, int end, int type)
{
    char typename[10];
    switch(type){
    case TREE:
	strcpy(typename, "tree edge");
	break;
    case BACK:
	strcpy(typename, "back edge");
	break;
    case FORWARD:
	strcpy(typename, "forward edge");
	break;
    case CROSS:
	strcpy(typename, "cross edge");
	break;
    default:
	printf("wrong edge type\n");
	return;
    }
    printf("%d -> %d %s\n", start, end, typename);
}
void set_edge_type(int start, adj_list pendnode, Color *color, int *d)
{
    switch(color[pendnode->vertex])
    {
    case WHITE:
	pendnode->edgeType = TREE;
	break;
    case GRAY:
	pendnode->edgeType = BACK;
	break;
    case BLACK:
	if (d[start] < d[pendnode->vertex])
	{
	    pendnode->edgeType = FORWARD;
	}
	else
	{
	    pendnode->edgeType = CROSS;	    
	}
	break;
    default:
	printf("wrong color type\n");
    }
    print_edgetype(start, pendnode->vertex, pendnode->edgeType);
}
// output the value in every element of the array
void print_array(const char* arr_name, int arr[], int length)
{
    int i;
    for (i = 0; i < length; i++) {
	printf("%s[%d] = %d\n",arr_name, i, arr[i]);
    }
}
