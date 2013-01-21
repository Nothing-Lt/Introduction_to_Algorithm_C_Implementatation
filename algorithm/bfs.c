// ʵ���ڽ�����Ĺ����������
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "include/require.h"
#include "queue.h"
#include "stack.h"
#include "adj_table.h"
#include "bfs.h"

// ������������ı��ʵı���ͼ�������в���
// ������ҪĿ���Ƕ��ڽ������parent��Ա�Լ�distance��Ա���и�ֵ
// �ڸ�ֵ�Ĺ����У��ڽ������color��Ա���и���
// ͬʱ���и������õ���һ��FIFO queue
// �����������ض�bfs�ĺ����ӿڽ������
// ǰ��ٶ�distance��parent���ѷ����
adj_list* bfs(adj_list* pAdjl, int numVertices, int org_vertex, int* distance, int* parent)
{
    // for breadth-first search
    Color *color = (Color*)malloc(numVertices * sizeof(Color));
    int i;
    queue q;
    // ���ݶ����ʼ�����в���
// ��ʼ������Ϊ��
    q.head = q.tail = 0;

// ��ʼ������
// �ô��и�������⣬ÿ���������ɫ�����ף����룬Ӧ�÷����ںδ���
// ��һ����Ʒ�������������ڽ�����Ľṹ��ʹ�������е�Ԫ��ָ
// ��һ���ṹ�壬�ýṹ��
// ���������֣�һ����ָ������
// ��һ����Ϊ�ö������������
// ���ߺ���Ȩֵʱ������������ӳ�Աweight
// ������Ƶĺ�����
    
// �ڶ�����Ʒ���������ԭ�е��ڽ�����ļ����ݽṹ����(ֻ��������������
// �Լ�nextָ�룬�����ټ���Ȩֵ)��
// ����3������:ÿ��������±�Ϊ���������
// color[]:����ÿ���������ɫ
// distance[]:����ÿ������ľ���
// parent[]:����ÿ������ĸ����
// ˼����������Ƶ�˼·�����������������ѧ��
// Ŀǰ���õڶ��ֲ���
    for (i = 0; i < numVertices; i++) {
	if (i != org_vertex)
	{
	    color[i] = WHITE;
	    distance[i] = INFINITE;
	    parent[i] = NILVALUE;	    
	}
    }
    color[org_vertex] = GRAY;
    distance[org_vertex] = 0;
    parent[org_vertex] = NILVALUE;
// ��Ԫ��org_vertex���
    enqueue(&q, org_vertex);
// ��ʼ����
    while (q.head != q.tail) {
	int u;
	adj_list pv;
	dequeue(&q, &u);
	pv = pAdjl[u];
	while (pv) {
	    if (color[pv->vertex] != WHITE)
	    {
		pv = pv->next;
		continue;
	    }
	    color[pv->vertex] = GRAY;
	    distance[pv->vertex] = distance[u] + 1;
	    parent[pv->vertex] = u;
	    enqueue(&q, pv->vertex);
	    pv = pv->next;
	}
// �����ӵĶ��㶼��Ϊ��ɫ
	color[u] = BLACK;
    }
    free(color);
    return pAdjl;
}
static void print(int point)
{
    printf("%d ", point);
}
// ��ӡ���������·�����������м��
// �����������������·������·���о����Ķ���������s->t˳�򱣴���������
// path������ڴ��ѷ����
EBool calc_path(adj_list* graph, int numVertices, int* parent, int s, int t, Stack path)
{
    int x = t;
    while (x != s) {
	if (parent[x] == NILVALUE)
	{
	    return FALSE;
	}
	push(path, x);
	x = parent[x];
    }
    push(path, s);
    return TRUE;
}
// ��ν��ú����ĵݹ�汾�ĳɵ����汾�� �ݹ�汾��Ҫ���ݵĲ���������̫��
void print_path(adj_list* pAdjl, int numVertices, int* parent, int start, int end)
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
	print_path(pAdjl, numVertices, parent, start, parent[end]);
	print(end);
    }
}

EBool peek(Stack s, int idx, int *pv)
{
    int i;
    List x = s->next;
    for (i = 0; i < idx && x != NULL; i++) {
	x = x->next;
    }
    if (x == NULL)
    {
	return FALSE;
    }
    *pv = x->value;
    return TRUE;
}










