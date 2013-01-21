#ifndef _LIST_H_
#define _LIST_H_
// �ڱ����߲�Ҫ�ڱ���
typedef struct tagNode
{
    int value;
    struct tagNode* next;
}Node, *PNode, *List;

List list_insert(List list, int value);
void print_list(List list);
void free_list(List list);

#endif /* _LIST_H_ */
