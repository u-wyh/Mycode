/*
    ��δ���������ǣ���һ����Ч����Ϊn���������������˻�
    �����������Ҫע�⣬��Ϊ�и����Ĵ��ڣ����ǻ�Ҫ����С�����������Ÿ��ӵ�ȫ��õ����ֵ
    ���ԣ�����Ҫint min[n]   max[n]
*/
#include<stdio.h>
#define Max 100

int minest(int a,int b,int c)
{
    return (a>b?b:a)>c?c:(a>b?b:a);
}

int maxest(int a,int b,int c)
{
    return (a>b?a:b)>c?(a>b?a:b):c;
}

int main()
{
    double arr[Max];
    int i=0;
    while(scanf("%lf",&arr[i++])==1);
    int n=i-1;//n��ʵ����Ч���鳤��
    printf("%d\n",n);
    int min[n],max[n];
    min[0]=arr[0];
    max[0]=arr[0];
    int biggest=arr[0];
    for(i=1;i<n;i++)
    {
        min[i]=minest(arr[i],arr[i]*max[i-1],arr[i]*min[i-1]);
        if(min[i]>biggest)
            biggest=min[i];
        max[i]=maxest(arr[i],arr[i]*max[i-1],arr[i]*min[i-1]);
        if(max[i]>biggest)
            biggest=max[i];
    }
    printf("%5d\n",biggest);
    return 0;
}
