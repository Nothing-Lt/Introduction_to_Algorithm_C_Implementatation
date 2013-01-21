#ifndef _ALL_PAIR_SHORTEST_PATH_H_
#define _ALL_PAIR_SHORTEST_PATH_H_
// �����ڽӾ�������ݽṹ
// ����Ԫ��rows:��ʾ����ĸ���
// int**��mat ����ߵ�Ȩֵ
#include <stdio.h>
#include "include/require.h"
#include "adj_mat.h"


// �ٶ�l��w�Ķ�������;�������������ú�
// ���ݽṹ����ָ������ʾ��
// ע��ú�����3���ڽӾ���ͬʱ��������
// l �� w�ܷ�ָ����ͬ���ڴ棿 ���������
void extend_shortest_paths(const AdjMat* l, AdjMat* lquote, const AdjMat* w);
// �ٶ�w�ѷ����ڴ棬��������ȷ��ֵ
AdjMat* slow_all_pair_shortest_path(const AdjMat* w);
AdjMat* faster_all_pair_shortest_path(const AdjMat* w);

#endif /* _ALL_PAIR_SHORTEST_PATH_H_ */
