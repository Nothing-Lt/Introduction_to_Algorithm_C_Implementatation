#ifndef _QUEUE_H_
#define _QUEUE_H_

#define QSIZE 20

typedef struct tag_queue
{
    int head;
    int tail;
    int array[QSIZE];
}Queue;

// ��Ӳ���
int enqueue(Queue* q, int value);

// ���Ӳ���
int dequeue(Queue* q, int* pvalue);

// ��ӡ�����еĳ�Ա
void printQueue(Queue* q);
#endif /* _QUEUE_H_ */
