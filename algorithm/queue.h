#ifndef _QUEUE_H_
#define _QUEUE_H_

#define QSIZE 20

typedef struct tag_queue
{
    int head;
    int tail;
    int array[QSIZE];
}queue;

// ��Ӳ���
int enqueue(queue* q, int value);

// ���Ӳ���
int dequeue(queue* q, int* pvalue);

// ��ӡ�����еĳ�Ա
void printQueue(queue* q);
#endif /* _QUEUE_H_ */
