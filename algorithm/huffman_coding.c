#include <stdlib.h>
#include <string.h>
#include "huffman_coding.h"
// ���huffman����ͽ���Ĺ���
// ʹ���㷨�������е�����
// ����һ��
// ����һ���ַ���abdface
// ��������Ķ�����λ
// ���ܶ���
// ��������Ķ�����λ
// ����������ַ���

// the type of innode is a struct type which include the struct type of
// the leaf node and the c field of the innode is always '^' to indicate the
// type of innode and to convert the type when needed according to the c field.

// ����һ�����ȶ���
// ���һ�ö�����
qNode* huffman(qNode* A[], int length)
{
    int i;
    int count = length;
    for (i = 1; i <= count-1; i++) {
	qInNode* pin = (qInNode*)malloc(sizeof(qInNode));
	qNode* left = queue_extract_min(A, &length);
	qNode* right = queue_extract_min(A, &length);
	pin->qn.c = '^';
	pin->qn.key = left->key + right->key;
	pin->left = left;
	pin->right = right;
	min_queue_insert(A, &length, (qNode *)pin);
	min_queue_output(A, length);
    }
    return queue_extract_min(A, &length);
}
int cntvalidbits(int x)
{
    int i = 0;
    while(x){
	x = x >> 1;
	i++;
    }
    return i;
}
// ���ݶ����������ַ��ͱ�����ֵ�
dict* huffman_genDict(qNode* bt, int numLeaf)
{
    
    dict* dt = (dict *)malloc(numLeaf * sizeof(dict));
    char* str = (char *)calloc(cntvalidbits(numLeaf)+1, sizeof(char));
    traverse(bt, dt, str);
    return dt;
}
void traverse(qNode* bt, dict* dt, char* str)
{
    static int i = 0;
    if (bt->c != '^')
    {
	dt[i].str = (char *)calloc(strlen(str)+1, sizeof(char));
	if (dt[i].str != NULL)
	{
	    dt[i].c = bt->c;
	    strcpy(dt[i++].str, str);
	}
    }
    else
    {
	int slen = strlen(str);
	qInNode* pin = (qInNode *)bt;
	strcat(str, "0");
	traverse((qNode*)pin->left, dt, str);
	str[slen] = '\0';
	strcat(str, "1");
	traverse((qNode*)pin->right, dt, str);
	str[slen] = '\0';
    }
}
void btree_output(qNode* bt)
{
    if (bt->c != '^')
    {
	printf("leaf node char: %c, frequency: %d\n",
	       bt->c, bt->key);
	fflush(stdout);
    }
    else
    {
	qInNode* pin = (qInNode*)bt;
	printf("in node frequency: %d\n", pin->qn.key);
	btree_output((qNode*)pin->left);
	btree_output((qNode*)pin->right);
    }
}
void dict_output(dict* dt, int length)
{
    int i;
    for (i = 0; i < length; i++) {
	printf("%dth, char: %c, bits: %s\n", i, dt[i].c, dt[i].str);
	fflush(stdout);
    }

}
void freedict(dict* dt, int length)
{
    int i;
    for (i = 0; i < length; i++) {
	free(dt[i].str);
    }
    free(dt);
}

// ����һ���ַ����������ֵ���б��롣
// ����һ����������Ϣ�������ֵ���н���
