/*
��δ���ĺ����ǣ�����һ�����ȵ��ַ�����������������̬������ÿ�ο��Խ������ļ����ַ��任Ϊ������ͬ���ַ�
                  ������С�Ĵ�����ʲô��һ��ʼ�ַ����ǿյģ�
    dp[i][j]�ĺ����Ǵ��±�i���±�j���ַ�Ҫ���Ϊ������̬����Ҫ��С�Ĵ�����ʲô
    ���ֻ��һ���ַ�  ��ôһ�ξͺ���
    ���ֻ�������ַ�  �����������  һ�ξͺ�
                              �����  ��Ҫ����
    ���򣬴�����ߵĽ��зָʹ֮��Ϊ��������  ����Сֵ
*/
#include<stdio.h>
#include<string.h>
#include<limits.h>

#define Max 51

static int dp[Max][Max];

int min(int a,int b)
{
    return a<b?a:b;
}

int compute(char *s,int n)
{
    for(int i=0;i<n-1;i++)
    {
        dp[i][i]=1;
        dp[i][i+1]= s[i]==s[i+1] ? 1 : 2;
    }
    dp[n-1][n-1]=1;
    for(int l=n-3,ans;l>=0;l--)
    {
        for(int r=l+2;r<n;r++)
        {
            if(s[l]==s[r])
                dp[l][r]=dp[l][r-1];
            else
            {
                ans=INT_MAX;
                for(int m=l;m<r;m++)
                    ans=min(ans,dp[l][m]+dp[m+1][r]);
                dp[l][r]=ans;
            }
        }
    }
    return dp[0][n-1];
}

int main()
{
    char s[Max];
    fgets(s,Max,stdin);
    int n=strlen(s)-1;
    printf("%d\n",compute(s,n));
    return 0;
}
