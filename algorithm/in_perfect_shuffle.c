#include "stdio.h"


// �ֻ�
// i <--> (2*i)%(Lenth + 1)
void Cycle(int Data[],int Lenth,int Start)
{
     int Cur_index,Temp1,Temp2;
     Cur_index=(Start*2)%(Lenth+1);
     Temp1=Data[Cur_index-1];
     Data[Cur_index-1]=Data[Start-1];
   
     while(Cur_index!=Start)
     {
	  Temp2=Data[(Cur_index*2)%(Lenth+1)-1];
	  Data[(Cur_index*2)%(Lenth+1)-1]=Temp1;
	  Temp1=Temp2;
	  Cur_index=(Cur_index*2)%(Lenth+1);
     }
}
 
//����ѭ����λ �ο��������
void Reverse(int Data[],int Len)
{
     int i,Temp;
     for(i=0;i<Len/2;i++)
     {
	  Temp=Data[i];
	  Data[i]=Data[Len-i-1];
	  Data[Len-i-1]=Temp;
     }
}
//����ΪLen����������ѭ���ƶ�Nλ
// ���Ӷ�:O(n)
void ShiftN(int Data[],int Len,int N)
{
     Reverse(Data,Len-N);
     Reverse(&Data[Len-N],N);
     Reverse(Data,Len);
}

//����Lenth=3^k-1��perfect shfulle��ʵ��
void Perfect1(int Data[],int Lenth)
{
     int i=1;
     if(Lenth==2)
     {
	  i=Data[Lenth-1];
	  Data[Lenth-1]=Data[Lenth-2];
	  Data[Lenth-2]=i;
	  return;
     }
     while(i<Lenth)
     {
	  Cycle(Data,Lenth,i);
	  i=i*3;
     }
}
// ������ӽ�N��3^k
// ���ҵĸ��Ӷ�:lgN
int LookUp(int N)
{
     int i=3;
     while(i<=N+1) i*=3;
     if(i>3) i=i/3;
     return i;
}
void perfect(int Data[],int Lenth)
{
     int i,startPos=0;
     while(startPos<Lenth)
     {
	  // �ҵ�<n��==3^k - 1�Ǹ���
	  i=LookUp(Lenth-startPos);  // lgn
	  ShiftN(&Data[startPos+(i-1)/2],(Lenth-startPos)/2,(i-1)/2); // O(n)
	  Perfect1(&Data[startPos],i-1); // O(n)
	  startPos+=(i-1);
     }
}
#define N 100
int main()
{
     int data[N]={0};
     int i=0;
     int n;
     printf("please input the number of data you wanna to test(should less than 100):\n");
     scanf("%d",&n);
     if(n&1)
     {
	  printf("sorry,the number should be even ");
	  return 0;
     }
     for(i=0;i<n;i++)
	  data[i]=i+1;
     perfect(data,n);
     for(i=0;i<n;i++)
	  printf("%d   ",data[i]);
     return 0;
}
