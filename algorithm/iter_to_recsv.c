/** 
 * �о���ν���������ת��Ϊβ�ݹ����
 */

// ����ǰn��ĺ�
// �ݹ����
int recsv_sum(int i)
{
  // �������β�ݹ�ʵ�ֵĻ���ִ�е�ʵ��Ч�ʻ������
  return recsv_sum(i - 1) + i;
}

// ����ǰn��ĺ�
// ѭ��
int iter_sum(int i)
{
  // ������Ϊ״̬������
  int count;
  int sum = 0;
  for(count = 0; count <i+1; i++)
    {
      sum += count;
    }    
}

