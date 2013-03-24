#ifndef _RANDOMIZED_SELECT_H_
#define _RANDOMIZED_SELECT_H_


#include <stdlib.h>
#include <stdio.h>
#include "include/require.h"
#include "quick_sort.h"
#include "randomized_select.h"
// ˳��ͳ��ѧ���ҳ���iС����
// ��p��r(����r)֮�����ѡ��һ����
int random(int p, int r);
int randomized_partition(int* arr, int p, int r);
int randomized_select(int* arr, int p, int r, int i);

#endif /* _RANDOMIZED_SELECT_H_ */
