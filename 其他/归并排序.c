#include<stdio.h>

static int arr[20];
static int help[20];

void merge(int mid,int left ,int right)
{
    int i=left;
    int a=left;
    int b=mid+1;
    while(a<=mid&&b<=right)
        help[i++]=arr[a]<=arr[b]?arr[a++]:arr[b++];
    while(a<=mid)
        help[i++]=arr[a++];
    while(b<=right)
        help[i++]=arr[b++];
    for(i=left;i<=right;i++)
    {
        arr[i]=help[i];
    }
}
//�ú�������ʵ������Ĺ鲢
void mergesort2() {
    // һ������O(logn)��
    int n=20;//�����ַ����У�n����Ԫ�صĸ����������±ꡣ
    for (int l, m, r, step = 1; step < n; step <<= 1) {
    // �ڲ�����merge��ʱ�临�Ӷ�O(n)
        l = 0;
        while (l < n) {
            m = l + step - 1;//��ʵ�����m�Ǹ���l��r�ı��ʽ������
            if (m + 1 >= n) {
                break;//�����ʾʣ�µ��������������Խ�����һ���Ƚϣ�����˵����step������
            }
            r = (l + (step << 1) - 1)> (n - 1)?(n-1):(l + (step << 1) - 1);
            merge(m,l, r);
            l = r + 1;
        }
    }
}
//�ú�����ʹ�õݹ鷽��
/*void mergesort(int left,int right)
{
    if(left==right)
        return ;
    int mid=(left+right)/2;
    mergesort(left,mid);
    mergesort(mid+1,right);
    merge(mid,left,right);
}*/
//�ú�����ʹ���õݹ鷽�����й鲢����
int main()
{
    for(int i=0;i<20;i++)
    {
        scanf("%d",&arr[i]);
    }
    //mergesort(0,19);
    mergesort2();
    for(int i=0;i<20;i++)
    {
        printf("%4d",arr[i]);
    }
    return 0;
}
