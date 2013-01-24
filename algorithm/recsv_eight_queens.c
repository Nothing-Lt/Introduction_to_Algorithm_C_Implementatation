/** 
 * eight queens puzzle
 * �ݹ��㷨
 * 1��Ϊ��ȷ����n�лʺ��λ��
 * ������ȷ����n-1�лʺ��λ��
 * �ɴ��γɵݹ�
 * 2������n��û�����������İڷ�λ��ʱ
 * ��ʼ���ݣ�Ѱ�ҵ�n-1����������λ�õ�
 * ��һ��λ�ã���chess[8]��Ϊȫ�ֱ���������״̬)
 * �޸�chess[n-1]������n�У�����n�Ժ��λ����Ϊ-1)����Ѱ�ҵ�n�еİڷ�λ��
 * �ɴ��γ�����һ���ݹ����
 * ע��߽�����ֵ
 * 
 */
#include <stdio.h>
int chess[8];

// chess[8] ���е�λ�ó�ʼ��Ϊ-1
typedef enum{ false, true} bool;
bool posOK(int i, int n)
{
    int queenPosIndex;
    for(queenPosIndex = 0; queenPosIndex < n; queenPosIndex++)
    {
	// �жϵ�n�еĻʺ���ڵ�i��λ�öԵ�queenPosIndex��˵�Ƿ����Ҫ��
	// for ѭ��Ҳ�൱��һ���ж����
	if (chess[queenPosIndex] == i)
	{
	    return false;
	}
	else if((i - chess[queenPosIndex] == n - queenPosIndex) ||
		(i + n == queenPosIndex + chess[queenPosIndex]))
	{
	    return false;
	}     
    }
    return true;
}
void setQueenPos(int n);
bool change(int n)
{
    if ( n == -1)
    {
	return false;
    }
    //���ҵ�n���ʺ�İڷ�λ��
    int queenPos;
    if((queenPos = (find(n))) != -1)
    {
	// ������������λ�÷�����������
	chess[n] = queenPos;
	// ����n���Ժ�Ļʺ�λ��ȫ����Ϊ-1
	setQueenPos(n);
	return true;
    }
    return false;
}
// ÿ��ִ��find���ҵĶ���һ���µ�����������chess[8]
int find(int n)
{
    // �жϵ�n�еĵ�i��λ���Ƿ���Է���
    int i;
    while (1)
    {
	// find(0)
	// chess[0] + 1 == 2
	for(i = chess[n] + 1; i < 8; i++)
	{
	    if (posOK(i, n))
	    {
		return i;
	    }
	}

	if (!change(n-1))
      	{
	    return -1;
      	}
    }
    return -1;
}
void setQueenPos(int n)
{
    int i;
    for(i = n+1; i < 8; i++)
    {
	chess[i] = -1;
    }
}
// ������е�λ�ö����Թ���û���ҵ�
// �޸�ǰn-1�У��ҵ���һ������������eightQueen(n-1)
// ���������������������eightQueen(n-1)?
// ���˵�eightQueenNext(n-1)
// while ���������
// ÿ��ִ��eightQueen(n-1) �ҵ���һ�����������İڷ�λ��
// ���û��ݲ���
// ˼����ν������˵�ģ��
// ����ʧ��ģ��
// while(failed)
// {
//   ���ݣ�
//   ǰ����
// }
// �ɹ�����ӡ������;
bool eightQueen(int n)
{
    if (n == -1)
    {
	return true;
    }
    else
    {
	if(eightQueen(n-1))
	{
	    //���ҵ�n���ʺ�İڷ�λ��
	    int queenPos;
	    if((queenPos = (find(n))) != -1)
	    {
		// ������������λ�÷�����������
		chess[n] = queenPos;
		// ����n���Ժ�Ļʺ�λ��ȫ����Ϊ-1
		// if (n == 7) ��ӡ������
		setQueenPos(n);
		return true;
	    }
	}
	return false;
    }
}

void printChessboard()
{
    int i;
    for(i = 0; i < 8; i++)
    {
	fprintf(stdout, "(%d, %d) ", i+1, chess[i] + 1);
	fflush(stdout);
    }
    fprintf(stdout, "\n");
    fflush(stdout);
}
void setChess()
{
    int i;
    for(i = 0; i < 8; i++)
    {
	chess[i] = -1;
    }
}

int main()
{
    int num;
    int numOfMethod =0;
    fprintf(stdout, "input the number of queen: \n");
    fflush(stdout);
    fscanf(stdin,"%d", &num);
    fflush(stdin);
    setChess();
    while(num !=  -1)
    {
    	setChess();
    	eightQueen(num);
    	printChessboard();
    	fprintf(stdout, "input the number of queen: \n");
    	fflush(stdout);
    	fscanf(stdin, "%d", &num);
    	fflush(stdin);
    }
    /* setChess(); */
    /* if (eightQueen(7)) */
    /*   { */
    /*     printChessboard(); */
    /*     numOfMethod++; */
    /*   } */
    /* int queenPos; */
    /* while((queenPos = find(7)) != -1) */
    /*   { */
    /*     chess[7] = queenPos; */
    /*     printChessboard(); */
    /*     numOfMethod++; */
    /*   } */
    /* printf("the number of method is: %d\n", numOfMethod); */
}

