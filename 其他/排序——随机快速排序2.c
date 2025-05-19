#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>

#define max 10001

static int first;
static int last;
static int arr[max];

void swap(int i, int j) ;
void partition(int l, int r,int  x);
void quicksort(int l,int r);

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
    printf("\n");//���岢������е�����

    quicksort(0,t-1);//��ʼ���п�������

    for(int i=0;i<t;i++)
    {
        printf("%4d",arr[i]);
    }//������кõ�����

    return 0;
}

void swap(int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}//����ָ���±����������

void partition(int l, int r,int  x)
{
    first = l;
    last = r;
    int i = l;
    while (i <= last) {
        if (arr[i] == x) {
            i++;
        } else if (arr[i] < x) {
            swap(first++, i++);
        } else {
            swap(i, last--);
        }
    }
}//ʵ�ֿ��ŵ���Ҫ����

void quicksort(int l,int r)
{
    if(l>=r)
        return ;
    int x = arr[l + rand()%(r-l+1)];
    partition(l, r, x);
    int left=first;
    int right=last;
    quicksort(l, left - 1);
    quicksort(right + 1, r);
}//ʹ�õݹ���п���
