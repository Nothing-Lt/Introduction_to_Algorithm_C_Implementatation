/** 
 * �о���ν�β�ݹ����ת��Ϊ��������
 */

// 쳲���������
// ��������
int iter_fibonacci(int i)
{
  int a = 0;
  int b = 1;
  int c;
  int count;

  for(count = 0; count < i; count++)
    {
      c = a + b;
      a = b;
      b = c;
    }   
  return a;
}

// �ݹ����
int recsv_fibonacci(int i)
{
  if (i == 0)
    {
      return 0;
    }
  else if (i == 1)
    {
      return 1;
    }
  else
    {
      return recsv_fibonacci(i - 1) + recsv_fibonacci(i - 2);
    }      
}

#include <stdio.h>
int main()
{
  int i;
  for(i = 0; i < 10; i++)
    {
      printf("%d ", recsv_fibonacci(i));
      printf("%d ", iter_fibonacci(i));
    }
  printf("\n");
  return 0;
}
