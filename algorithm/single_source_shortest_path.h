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

#include <stdio.h>
#include <stdlib.h>
#include "include/require.h"
#include "adj_table.h"
#include "print_path.h"


// �ٶ���̬����d[],parent[]�ѷ����
// �ٶ��ڽ������ѷ���ã����ȸ���
// ����DRYԭ���Ƿ�Ҫȥ��length����
// ͨ������graph�����graph�ĳ����أ�
void initialize_single_source(AdjList* graph, int length, int s, 
			      int d[], int parent[]);

// ʵ���ɳں���
// ��v�����ɳڣ�w��u->v�ıߵ�Ȩֵ
void relax(int u, int v, int w, int d[], int parent[]);

// Bellman-Ford �㷨

// �ٶ�graph, d[], parent[]���ѷ����
EBool bellman_ford(AdjList* graph, int length, int s, int d[], int parent[]);

