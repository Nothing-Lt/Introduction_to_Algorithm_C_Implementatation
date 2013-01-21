#ifndef _ADJ_MAT_H_
#define _ADJ_MAT_H_
#include "include/require.h"

typedef struct tagAdjMat
{
    int rows;
    int** mat;
}AdjMat;



// �����ڽӾ���
// make �����ڴ棬��ֵΪINFINITE
// construct �����ڴ棬ͬʱ��ֵ 

// �����ڽӾ��󣬶���ĸ���ΪnumVertices
AdjMat* make_adjmat(int numVertices);
AdjMat* make_param_adjmat(int numVertices, int pdv, int npdv);
// ��ȡ�ļ����ݵķ�ʽ��
// �Ȼ�ö���ĸ���
// Ȼ���ٻ���������㼰��ߵ�Ȩ��
// ����ļ����� ���ǻ���ļ��ṹ��ָ�룿
// ���ݽ����ԭ��Ӧ��Ҫ��ú������ļ��򿪲�������
AdjMat* construct_adjmat(FILE* pFile);
AdjMat* construct_param_adjmat(FILE* pFile, int pdv, int npdv);
AdjMat* copy_adjmat(const AdjMat* m);
void free_adjmat(AdjMat* m);
// |1   2   -3  |
// |INF INF -9  |   
void print_adjmat(const AdjMat* m);

#endif /* _ADJ_MAT_H_ */
