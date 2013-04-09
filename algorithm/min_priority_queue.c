#include "min_priority_queue.h"
#include <limits.h>
#include <stdlib.h>

// the queue start from 1
// ʵ����С���ȼ����е�4����������
// Ϊ����ʵ��huffman����׼��
// Insert(S, x)
// Minimum(S)
// Extract_min(S)
// Increase_key(S, x, k)
// ���ʵ��Ԫ���ǽṹ������ȼ����У�
// ѡ��һ�����ȼ������еĶ������飬�����Ԫ�ص���ָ��ṹ��ָ��(Ԥ��)
// ѡ��������ȼ������еĶ������飬�����Ԫ���ǽṹ��
// ѡ���������ȼ������еĶ��ö��������ڵ�Ϊ�ṹ��


int parent(int i)
{
    return i/2;
}

int left(int i)
{
    return 2*i;
}

int right(int i)
{
    return 2*i + 1;
}

qNode* create_node(char c, int key)
{
    qNode* pn = (qNode*)malloc(sizeof(qNode));
    pn->c = c;
    pn->key = key;
    return pn;
}
// ���ֶѵ�����
void min_heapify(qNode* A[], int length, int i)
{
    int l = left(i);
    int r = right(i);
    int min = i;
    // �ڸ��ڵ����������֮��Ѱ����С�Ľڵ�
    if (l <= length && A[l]->key < A[i]->key)
    {
	min = l;
    }
    if (r <= length && A[r]->key < A[min]->key)
    {
	min = r;
    }
    if (min != i)
    {
	// exchange the ith value and min value
	swap(A[i], A[min]);
	min_heapify(A, length, min);
    }
}
// the queue start from 1
// the length of A is sizeof(A) - 1
// A[0] == NULL
qNode* queue_minimum(qNode* A[])
{
    return A[1];
}

qNode* queue_extract_min(qNode* A[], int* plength)
{
    qNode* ret;
    if (*plength < 1)
    {
	printf("queue overflow\n");
	fflush(stdout);
	return NULL;
    }
    ret = A[1];
    swap(A[1], A[*plength]);
    (*plength)--;
    min_heapify(A, *plength, 1);
    return ret;
}

void queue_decrease_key(qNode* A[], int i, int key)
{
    if (A[i]->key < key)
    {
	printf("error\n");
	fflush(stdout);
	return;
    }
    A[i]->key = key;
    while (i > 1 && A[i]->key < A[parent(i)]->key)
    {
	swap(A[i], A[parent(i)]);
	i = parent(i);
    }
}

void min_queue_insert(qNode* A[], int* plength, qNode* x)
{
    int key = x->key;
    x->key = INT_MAX;
    A[++(*plength)] = x;
    queue_decrease_key(A, *plength, key);    
}

void min_queue_output(qNode* A[], int length)
{
    int i;
    for (i = 1; i <= length; i++) {
	printf("the %dth element, char: %c, keyvalue: %d\n", i, A[i]->c, A[i]->key);
	fflush(stdout);
    }
    printf("\n");
}
