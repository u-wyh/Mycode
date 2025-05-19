/*
��δ���������ǽ�һ��ֻ���������ź�С���ŵ��ַ��������뼸���ַ�����ʹ�����ַ�������Ӧ
dp[l][r]�������Ǵ��±�l���±�r���ٲ��뼸���ַ�����ʹ֮��ȫ��Ӧ
    ���ֻ��һ���ַ�����ô����һ���Ϳ��������Ƕ�Ӧ
    ������������ַ�����ô���Ƕ�Ӧ����ôֱ�Ӿ��Ǻõ�  0
                              ����Ӧ����ô��Ҫ������������   2
    ����Ҫ����Ϊ�������߽��м���
*/
#include<stdio.h>
#include<string.h>
#include<limits.h>
#define Max 1000

static int dp[Max][Max];

int min(int a,int b)
{
    return a<b?a:b;
}

int f1(char *str,int l,int r)
{
    if(l==r)
        return 1;
    if(l==r-1)
    {
        if((str[l]=='('&&str[r]==')')||(str[l]=='['&&str[r]==']'))
            return 0;
        else
            return 2;
    }
    if(dp[l][r]!=-1)
        return dp[l][r];
    int p1=INT_MAX;
    if((str[l]=='('&&str[r]==')')||(str[l]=='['&&str[r]==']'))
        p1=f1(str,l+1,r-1);
    int p2=INT_MAX;
    for(int m=l;m<r;m++)
    {
        p2=min(p2,f1(str,l,m)+f1(str,m+1,r));
    }
    int ans=min(p1,p2);
    dp[l][r]=ans;
    return ans;
}

int compute(char *str,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            dp[i][j]=-1;
        }
    }
    return f1(str,0,n-1);
}

int main()
{
    char str[Max];
    fgets(str,Max,stdin);
    int n=strlen(str)-1;
    //n��ʵ����Ч�ַ�������
    printf("%d\n",compute(str,n));
    return 0;
}
