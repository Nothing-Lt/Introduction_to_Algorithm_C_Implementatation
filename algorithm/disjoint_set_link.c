// ���ʵ�ֽ��ָ�������ָ�룿
// �����ַ�ʽ
// - ÿ����㱣��ָ�������ָ��
// - ÿ������Ĵ����һ��ָ�������ָ���Ա�����ó�Աָ�������������ͨ������ָ������
// ��һ�ַ�ʽ��ȱ�����˷ѿռ�
// �ڶ��ַ�ʽ��ȱ����ʵ�ֽ����ѣ�Ҫ��̬��
// �ڶ���ʵ�ַ�ʽ�����⣬Ŀǰ���õڶ���ʵ�ַ�ʽ
// ʵ�ֲ��ཻ������һ���ݽṹ����֧�����²���
// MAKE-SET(x) ����һ���µļ���
// DISJOINT_SET_UNION(x, y) ������x��y�ļ��Ϻϲ�Ϊһ���µļ���
// FIND-SET(x) ����һ��ָ�룬ָ�����x(Ψһ)���ϵĴ���
#define NIL NULL

#include <stdio.h>
#include <stdlib.h>

typedef struct tagDjsLink *DjsLink;
typedef struct tagDjsNode
{
    int key;
    struct tagDjsNode* next;
    struct tagDjsNode* representative;
    // linkָ��������
    DjsLink link;
    
}DjsNode, *DjsPNode;

typedef struct tagDjsLink{
    int length;
    DjsPNode head;
    DjsPNode tail;
}*DjsLink;

DjsPNode make_node(int k)
{
    DjsPNode x = (DjsPNode)malloc(sizeof(*x));
    x->key = k;
    x->next = NIL;
    x->representative = NIL;
    x->link = NIL;
    return x;
}
// MAKE-SET(x) ����һ���µļ���
// xΪָ��ĳһ����ָ��
// �ý��Ϊ�ոճ�ʼ���Ľ��
DjsLink make_set(DjsPNode x)
{
    DjsLink link = (DjsLink)malloc(sizeof(*link));
    x->representative = x;
    x->link = link;
    link->head = x;
    link->tail = x;
    link->length = 1;
    return link;
}

// FIND-SET(x) ����һ��ָ�룬ָ�����x(Ψһ)���ϵĴ���
DjsPNode find_set(DjsPNode x)
{
    return x->representative;
}
// DISJOINT_SET_UNION(x, y) ������x��y�ļ��Ϻϲ�Ϊһ���µļ���
// ���´���ָ��
// ���½�������ָ��
DjsLink disjoint_set_union(DjsPNode x, DjsPNode y)
{
    DjsPNode xRep = find_set(x);
    DjsPNode yRep = find_set(y);
    DjsPNode current;
    DjsLink xLink = xRep->link;
    DjsLink yLink = yRep->link;
    if (xRep == yRep)
    {
	return xLink;
    }
    // �Ƚ���������ĳ��ȣ����̵��������ӵ����������β����
    if(xLink->length > yLink->length)
    {
	// ����xLink��yLink��ָ�룬ʹ��xLinkʼ��ָ��϶̵�����
	DjsLink tmp = xLink;
	xLink = yLink;
	yLink = tmp;
    }
    // ��x���ӵ�y�����
    yLink->tail->next = xLink->head;
    yLink->tail = xLink->tail;
    yLink->length += xLink->length;
    // ����x�������н��Ĵ���ָ�룬ָ��y���ϵĴ���
    current = xLink->head;
    while (current) 
    {
	current->representative = yLink->head;
	current->link = yLink;
	current = current->next;
    }
    free(xLink);
    return yLink;
}

// ��ӡ����
void disjoint_set_print(DjsLink link)
{
    DjsPNode x = link->head;
    while (x != NIL) {
	printf("%d ", x->key);
	x = x->next;
    }
    printf("\n");
}

// test the disjoint_set
// find_set
// make_set
// disjoint_set_union
int main(int argc, char *argv[])
{
    const int size = 16;
    int i;
    DjsPNode x[size];
    DjsPNode rep1, rep2;
    for (i = 0; i < size; i++) {
	x[i] = make_node(i);
	make_set(x[i]);
    }
    for (i = 0; i < size-1; i = i + 2) {
	disjoint_set_union(x[i], x[i+1]);
	disjoint_set_print(x[i]->link);
    }
    for (i = 0; i < size-3; i = i + 4) {
	disjoint_set_union(x[i], x[i+2]);
	disjoint_set_print(x[i]->link);
    }
    disjoint_set_union(x[1], x[5]);
    disjoint_set_print(x[1]->link);
    disjoint_set_union(x[11], x[13]);
    disjoint_set_print(x[11]->link);
    disjoint_set_union(x[1], x[10]);
    disjoint_set_print(x[1]->link);
    rep1 = find_set(x[2]);
    printf("rep1 is: %d\n", rep1->key);
    rep2 = find_set(x[9]);
    printf("rep2 is: %d\n", rep2->key);
    return 0;
}

