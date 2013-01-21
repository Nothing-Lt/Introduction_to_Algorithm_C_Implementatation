#ifndef _REQUIRE_H_
#define _REQUIRE_H_

// �ڱ�д�㷨���۳���ʱ����Ҫʹ�õ��Ĺ���ͷ�ļ�
// �������õĵ��Դ�ӡ��䣬
// ���õĴ�ӡ��������
// ��ӡ����ֵ��ͬʱ����ӡ�ñ����ķ���
// ��ӡһ������
// ��ӡһ�������е�ֵ
// �������������е�ֵ
// �������������������������ֵ
// ���õĺ�
// ���õ�ö��ֵ
// ע�⣬�ô�����ı�����Ϊ���ͱ���
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define NIL NULL
// ������Ȼ��������Ч��ֵ
#define NILVALUE -1
// ���ڱ�ʾ��������������������ʱ��Ӧ�ر���
#define INFINITE INT_MAX
#define NINFINITE INT_MIN
// ����min��ע���丱����
#define min(a, b) ((a) > (b))? (b):(a)
#define inf_add(a, b)  \
    ((a) == INFINITE || (b) == INFINITE)? \
    INFINITE:((a) + (b))
    
#define inf_sub(a, b) \
    ((a) == INFINITE || (b) == INFINITE)? \
    INFINITE:((a) - (b))

#define dprint(expr) printf(#expr " = %d\n", expr)

#ifdef DEBUG
#define DEBUGP(x, args ...) fprintf(stderr, " \
[%s(), %s:%u]\n" x, __FUNCTION__, __FILE__,__LINE__, ## args)
#else
#define DEBUGP(x, args ...)
#endif

#define swap(x,y) do \
    { unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; \
	memcpy(swap_temp,&y,sizeof(x)); \
	memcpy(&y,&x,       sizeof(x)); \
	memcpy(&x,swap_temp,sizeof(x)); \
    } while(0)


typedef enum {FALSE, TRUE} EBool;

void array_swap(int A[], int m, int n);
void array_print(int array[], int length);

#endif /* _REQUIRE_H_ */
