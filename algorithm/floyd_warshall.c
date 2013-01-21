#include "floyd_warshall.h"



AdjMat* floyd_warshall(AdjMat* w)
{
    int i, j, k;
    int n = w->rows;
    // d �� dquote�ܲ���ָ����ͬ���ڴ棿 ��
    AdjMat* d = copy_adjmat(w);
    AdjMat* dquote = make_adjmat(w->rows);
    for (k = 0; k < n; k++) {
	for (i = 0; i < n; i++) {
	    for (j = 0; j < n; j++) {
		dquote->mat[i][j] = min(d->mat[i][j],
		                        inf_add(d->mat[i][k], d->mat[k][j]));
	    }
	}
	// ����d��dquote��ָ�� ��ʵ��
	swap(d, dquote);
    }
    free_adjmat(dquote);
    return d;
}
