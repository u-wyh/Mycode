#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define max 10001

static int arr[max];
void swap(int i,int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
void heapinsert(int i)
{
    while(arr[i]>arr[(i-1)/2])
    {
        swap(i,(i-1)/2);
        i=(i-1)/2;
    }
}//���ѽ�������    �Ӷ�����
void heapify(int i,int size)
{
    int l=i*2+1;
    while(l<size)
    {
        int best=((l+1)<size&&arr[l+1]>arr[l])?l+1:l;
        best=arr[best]>arr[i]?best:i;
        if(best==i)
            break;
        swap(best,i);
        i=best;
        l=2*i+1;
    }
}//���ѽ�������    �ӵ׵���
void heapsort1(int t)
{
    for(int i=0;i<t;i++)
    {
        heapinsert(i);
    }
    int size=t;
    while(size>1)
    {
        swap(0, --size);
        heapify(0, size);
    }
}//ʵ�ֶ�����ÿ�ν���һ���������һ�������������Ҽ������ֹ�ģ��ʹ��������������
//���ǴӶ����׽���
void heapsort2(int t)
{
    for(int i=t-1;i>=0;i--)
    {
        heapify(i,t);
    }
    int size=t;
    while(size>1)
    {
        swap(0, --size);
        heapify(0, size);
    }
}//ʵ�ֶ�����ÿ�ν���һ���������һ�������������Ҽ������ֹ�ģ��ʹ��������������
//���Ǵӵ׵�������
int main()
{
    int t;
    scanf("%d",&t);
    srand(time(NULL));
    for(int i=0;i<t;i++)
    {
        arr[i]=rand()%100+1;
        printf("%4d",arr[i]);
    }
    printf("\n");
    //heapsort1(t);
    heapsort2(t);
    for(int i=0;i<t;i++)
    {
        printf("%4d",arr[i]);
    }
    return 0;
}
