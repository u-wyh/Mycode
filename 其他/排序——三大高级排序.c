#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define Max 100001

static int arr[Max];
static int help[Max];
static int first;
static int last;

void swap(int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(int l, int r,int  x)
{
    int a=l,xi=0;
    for(int i=l;i<=r;i++)
    {
        if(arr[i]<=x)
        {
            swap(a,i);
            if(arr[a]==x)
                xi=a;
            a++;
        }
    }
    swap(xi,a-1);
    return a-1;
}
void quicksort(int l,int r)
{
    if(l>=r)
        return ;
    int x=arr[rand()%(r-l+1)+l];
    int mid=partition(l,r,x);
    quicksort(l,mid-1);
    quicksort(mid+1,r);
}
//�����������ԭʼ�汾
void partition2(int l, int r,int  x)
{
    first=l;
    last=r;
    int i=l;
    while(i<=last)
    {
        if(arr[i]<x)
            swap(first++,i++);
        else if(arr[i]>x)
            swap(last--,i);
        else
            i++;
    }
}
void quicksort2(int l,int r)
{
    if(l>=r)
        return ;
    int x=arr[rand()%(r-l+1)+l];
    partition2(l,r,x);
    int left=first;
    int right=last;
    quicksort(l,left-1);
    quicksort(right+1,r);
}
//������������Ż���İ汾

//���Ͼ�Ϊ�����������  ������ԭʼģʽ���Ż����Ч��

/*
�����������ԭ����ܣ�ԭʼ�汾���Ż���İ汾����
    ԭʼ�汾��
        �������ѡ��һ����û���ź�����±꣬Ȼ���������±��Ӧ��ֵ�������Ϊ�������ĺ�С�ڵ������ģ�
        ���е�����С�ڵ������ķ�����ߣ����Լ�����Щ���ֵ��ұ�
        Ȼ�����ǽ���Ϊ������������ϲ������Ӷ�ʹ˳���źã�ÿ��ֻ���ź�һ������
    �Ż���İ汾��
        �������ѡ��һ����û���ź�����±꣬Ȼ���������±��Ӧ��ֵ�������Ϊ�������ĺ�С�����ģ�
        Ȼ�����ǽ���Ϊ������������ϲ������Ӷ�ʹ˳���ź�
        ���������ͬʱ��ʼ
        �Ż�����������ÿ��ѡ��Ĳ�ֻ����һ��������������ֵ��������������֣�һ�����ٿ������һ��
*/

void merge(int l,int m,int r)
{
    int a=l;
    int b=m+1;
    int i=l;
    while(a<=m&&b<=r)
        help[i++]=arr[a]<=arr[b]?arr[a++]:arr[b++];
    while(a<=m)
        help[i++]=arr[a++];
    while(b<=r)
        help[i++]=arr[b++];
    for(i=l;i<=r;i++)
        arr[i]=help[i];
}
void mergesort(int l,int r)
{
    if(l>=r)
        return ;
    int m=(l+r)/2;
    mergesort(l,m);
    mergesort(m+1,r);
    merge(l,m,r);
}
void mergesort2(int t)
{
    for(int l,m,r,step=1;step<t;step*=2)
    {
        l=0;
        while(l<t)
        {
            m=l+step-1;
            if(m+1>=t)
                break;
            r=(l+step*2-1)<(t-1)?(l+step*2-1):(t-1);
            merge(l,m,r);
            l=r+1;
        }
    }
}
//�����ǹ鲢��������ַ�ʽ��һ����ֱ�ӵݹ飬����һ����û��ʹ�õݹ�ķ�ʽ

/*
�鲢����ԭ����ܣ��ݹ�ͷǵݹ飩��
    �ݹ�棺
        ���ǽ����е����ַ�Ϊ�������飬Ȼ�����������ڸ��Եĵݹ���ʵ�������򻯣����ǽ��������������ϲ�Ϊһ�����������
        �Ӷ�ʵ������Ĺ���
    �ǵݹ�棺
        ͨ�����Ӳ�����ʵ������
*/

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
        int best=((l+1)<size&&arr[l+1]>arr[l])?(l+1):l;
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
        swap(0,--size);
        heapify(0,size);
    }
}//ʵ�ֶ�����ÿ�ν���һ���������һ�������������Ҽ������ֹ�ģ��ʹ��������������
//���ǴӶ����׽���
void heapsort2(int t)
{
    for(int i=t-1;i>0;i--)
    {
        heapify(i,t);
    }
    int size=t;
    while(size>1)
    {
        swap(0,--size);
        heapify(0,size);
    }
}
//���������Ƕ�����Ĵ���ʵ�֣�һ���ǴӶ����׽��ѣ�����һ���Ǵӵ׵�������

/*
������ԭ����ͣ������� �� �׵�������
    �Ӷ����׽��ѣ�
        ���������һ���ѵ�ʱ�����ѡ�����ַ��������е�һ�����ǰ����������ַ������
    �ӵ׵������ѣ�
        ���������һ���ѵ�ʱ�����ѡ�����ַ��������еڶ������ǰ����������ַ�����׶�
    �������ԭ���ǰ���������������������Ϊ���ĵ����־�����ˣ�����������������������֮�󣬰ѶѵĴ�С����1
    �Ӷ�ʵ�����������
*/
int main()
{
    int t;
    scanf("%d",&t);
    srand(time(NULL));
    int max=0;
    for(int i=0;i<t;i++)
    {
        arr[i]=rand()%100;
        if(max<arr[i])
            max=arr[i];
        printf("%3d",arr[i]);
    }

    printf("\n");

    mergesort(0,t-1);
    //mergesort2(t);
    //quicksort(0,t-1);
    //quicksort2(0,t-1);
    //heapsort1(t);
    //heapsort2(t);
    for(int i=0;i<t;i++)
        printf("%3d",arr[i]);
    return 0;
}
