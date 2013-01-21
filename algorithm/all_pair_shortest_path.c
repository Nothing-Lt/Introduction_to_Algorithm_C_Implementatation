// ���·�������˷�
// ע������0��ʼ�ʹ�1��ʼ������
// ���������к��д�0��ʼ
// ����ı�ʾ��ʽ�����ö�̬��ά����ʵ��
#include "all_pair_shortest_path.h"

// �ٶ�l��w�Ķ�������;�������������ú�
// lquote ���ڴ��ѷ��䣬������ΪINFINITE��lquote��Ϊ������޸�
// ���ݽṹ����ָ������ʾ��
// ע��ú�����3���ڽӾ���ͬʱ��������
// l �� w�ܷ�ָ����ͬ���ڴ棿 ���������
void extend_shortest_paths(const AdjMat* l, AdjMat* lquote, const AdjMat* w)
{
    int i, j, k;
    int n = l->rows;
    for (i = 0; i < n; i++) {
	for (j = 0; j < n; j++) {
	    lquote->mat[i][j] = INFINITE;
	    for (k = 0; k < n; k++) {
		lquote->mat[i][j] = min(lquote->mat[i][j], 
					inf_add(l->mat[i][k], w->mat[k][j]));
	    }
	}
    }
    return lquote;
}
// �ٶ�w�ѷ����ڴ棬��������ȷ��ֵ
AdjMat* slow_all_pair_shortest_path(const AdjMat* w)
{
    int i;
    int n = w->rows;
    AdjMat* l = copy_adjmat(w);
    AdjMat* lquote = make_adjmat(n);
    // �ڽӾ�����ŵ����Ϊ0
    // ѭ���Ĵ���Ϊn-2
    for (i = 1; i < n-1; i++) {
	// tmp, l, w���벻��ָ����ͬ���ڴ�
	// ÿ�ε��ö�Ҫ�����µ��ڴ棬��α��⣿
	// ����3��������ʹ�ڴ�ѭ������
	extend_shortest_paths(l, lquote, w);
	swap(l, lquote);
    }
    free_adjmat(lquote);
    return l;
}

AdjMat* faster_all_pair_shortest_path(const AdjMat* w)
{
    int i;
    int n = w->rows;
    // �Ƿ���Բ�������ָ����ͬ�����ݣ���
    AdjMat* l = copy_adjmat(w);
    AdjMat* lquote = make_adjmat(n);
#ifdef DEBUG
    DEBUGP("before");
    fflush(stdout);
#endif // DEBUG
    i = 1;
    // ѭ��ִ��n-2��
    while(i < n-1)
    {
	extend_shortest_paths(l, lquote, l);
	swap(l, lquote);
	i = 2 * i; // ��ֹi = 0
    }    
#ifdef DEBUG
    DEBUGP("after");
    fflush(stdout);
#endif // DEBUG
    free_adjmat(lquote);
    return l;
}
