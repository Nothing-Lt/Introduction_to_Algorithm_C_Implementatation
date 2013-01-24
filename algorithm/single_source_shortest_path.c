// ʵ�ֵ�Դ���·���㷨�Ĺ�������
// ͼ���ڽ�����ʵ��
// ��С���ȶ�����Fibonacci��ʵ��
// ��Ҫʵ�ֵĺ���������
// ��ʼ������
// �ɳں���
// ��δ��ÿ����������·������d[v]
// ���������ȶ��н�������ʽ����ؼ���Ϊ���·������
// ��δ��ÿ�������ǰ��parent[v]
// �������һ�����ö�̬������

#include "single_source_shortest_path.h"


// �ٶ���̬����d[],parent[]�ѷ����
// �ٶ��ڽ������ѷ���ã����ȸ���
// ����DRYԭ���Ƿ�Ҫȥ��length����
// ͨ������graph�����graph�ĳ����أ�
void initialize_single_source(AdjList* graph, int length, int s, 
			      int d[], int parent[])
{
    int i;
    for (i = 0; i < length; i++) {
	d[i] = INT_MAX;
	parent[i] = NILVALUE;
    }
    d[s] = 0;
}

// ʵ���ɳں���
// ��v�����ɳڣ�w��u->v�ıߵ�Ȩֵ
void relax(int u, int v, int w, int d[], int parent[])
{
    if (d[v] > d[u] + w)
    {
	d[v] = d[u] + w;
	parent[v] = u;
    }
}

// Bellman-Ford �㷨

// �ٶ�graph, d[], parent[]���ѷ����
EBool bellman_ford(AdjList* graph, int length, int s, int d[], int parent[])
{
    int i, m;
    initialize_single_source(graph, length, s, d, parent);
    for (i = 0; i < length - 1; i++) {
	// ����ÿ���ߣ���ÿ���߽����ɳ�
	int j;
	for (j = 0; j < length; j++) {
	    AdjListNodePtr x = graph[j];
	    while (x) {
		relax(j, x->vertex, x->weight, d, parent);
		x = x->next;
	    }
	}
    }
    // �����Ƿ��и�Ȩ��·
    for (m = 0; m < length; m++) {
	AdjListNodePtr x = graph[m];
	while(x) {
	    if (d[x->vertex] > d[m] + x->weight)
	    {
		return FALSE;
	    }
	    x = x->next;
	}
    }
    return TRUE;    
}
