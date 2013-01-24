// ʵ���Ƚ��ȳ����е����ݽṹ���Լ����ӣ����
// ���еĳ������⣿
#include <stdio.h>
#include "queue.h"
// ��ͷ�Ͷ�β�������������������о���
// ��Ӳ���
int enqueue(Queue* q, int value)
{
    // q->tail ����ָ����Ԫ�ص�λ��
    // q->head ����ָ���ͷԪ��
    if ((q->tail + 1) % QSIZE == q->head)
    {
	printf("the queue is full\n");
	printf("q.tail is %d\n", q->tail);
	printf("q.head is %d\n", q->head);
	return 0;
    }    
    q->array[q->tail] = value;
    q->tail = (q->tail + 1) % QSIZE;
    return 1;
}

// ���Ӳ���
int dequeue(Queue* q, int* pvalue)
{
    // �ж϶����Ƿ�Ϊ��
    if (q->head == q->tail)
    {
	printf("the queue is empty\n");
	return 0;
    }
    *pvalue = q->array[q->head];
    q->head = (q->head + 1)%QSIZE;
    return 1;
}

void printQueue(Queue* q)
{
    int i = q->head;
    while (i != q->tail) {
	printf("%d ",q->array[i]);
	i = (i + 1) % QSIZE;
    }
    printf("\n");
}
