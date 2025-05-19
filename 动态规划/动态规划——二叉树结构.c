/*
��δ���������ǽ���һ���������ṹ��һ����n���ڵ㣬�߶Ȳ��ó���m��һ���ж����ַ�ʽ  ��modȡ��
dp[i][j]�ĺ����ǽ���һ���������ṹ��һ����i���ڵ㣬�߶Ȳ��ó���j��һ���ж����ַ�ʽ  ��modȡ��
��������Ҫ�Ĵ���dp[n][m]  ������������int dp[n+1][m+1]
����ÿһ����Ҫ��ͷ��㣬Ȼ���Ϊ��� �ұ߸��Զ��ٸ��ڵ�
�Դ����ƣ��õ���
*/
#include<stdio.h>
#define MOD 1000000007

static int dp[100][100];
//�������Ǳ���Ӧ������Ϊdp[n+1][m+1]������Ϊ�˷��㣬dp[100][100]�Ϳ�����

int compute(int n,int m)
{
    long ans=0;
    if(n==0)
        return 1;
    if(m==0)
        return 0;
    if(dp[n][m]!=-1)
        return (int)dp[n][m];
    for (int k = 0; k < n; k++) {
        ans = (ans + ((long) compute(k, m - 1) * compute(n - k - 1, m - 1)) % MOD) % MOD;
    }
    dp[n][m] = ans;
    return (int) ans;
}

int main()
{
    int n,m;
    printf("please enter the n and m: ");
    scanf("%d %d",&n,&m);
    //int dp[n+1][m+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=-1;
        }
    }
    printf("%5d\n",compute(n,m));
    return 0;
}
