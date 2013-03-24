#include <stdlib.h>
#include <stdio.h>
#include "include/require.h"
#include "quick_sort.h"
#include "randomized_select.h"
// ˳��ͳ��ѧ���ҳ���iС����
// ��p��r(����r)֮�����ѡ��һ����
int random(int p, int r)
{
    return p + (r - p + 1) * rand()/RAND_MAX;
}

int randomized_partition(int* arr, int p, int r)
{
    int i = random(p, r);
    swap(arr[r], arr[i]);
    return partition(arr, p, r);
}


int randomized_select(int* arr, int p, int r, int i)
{
    int q, k;
    if (p == r)
    {
	return arr[p];
    }
    // q��ߵ�������arr[q]С��q�ұߵ�������arr[q]��
    q = randomized_partition(arr, p, r);
    k = q - p + 1;
    if (i == k)
    {
	return arr[q];
    }
    else if (i < k)
    {
	return randomized_select(arr, p, q-1, i);
    }
    else // i > k
    {
	return randomized_select(arr, q+1, r, i-k);
    }
    
}
