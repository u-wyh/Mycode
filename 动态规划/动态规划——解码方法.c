/*
��δ������˼�ǽ�һ�������ַ�ת��ΪӢ���ַ��ж����ְ취
��ô������������������һ����һ�����ִ���һ���ַ����ڶ����Ǻ���һ�����ֹ�ͬ���һ���ַ�
*/
#include<stdio.h>
#include<string.h>
#define max 10000

int f1(char *s,int i,int n)
{
    if(i==n)
        return 1;
    int ans;
    if(s[i]=='0')
        ans=0;
    else
    {
        ans=f1(s,i+1,n);
        if(i+1<=n&&((s[i]-'0')*10+(s[i+1]-'0'))<=26)
            ans+=f1(s,i+2,n);
    }
    return ans;
}
//�����㷨����


int kinds(char *s,int n)
{
    int dp[n];
    for(int i=0;i<n;i++)
    {
        dp[i]=-1;
    }
    return f2(s,0,n,dp);
}

int f2(char *s,int i,int n,int *dp)
{
    if(i==n)
        return 1;
    if(dp[i]!=-1)
        return dp[i];
    int ans;
    if(s[i]=='0')
        ans=0;
    else
    {
        ans=f1(s,i+1,n);
        if(i+1<=n&&((s[i]-'0')*10+(s[i+1]-'0'))<=26)
            ans+=f1(s,i+2,n);
    }
    dp[i]=ans;
    return ans;
}


int kinds2(char *s,int n) {
    int dp[n + 1];
    dp[n] = 1;
    //����һ��Ϊʲôȫ����ʼ��1 ��Ϊdp��û�н�����ϵ  ����ֻ��һ�����ȵ��ַ�   ����Ϊ1
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '0') {
            dp[i] = 0;
        } else {
            dp[i] = dp[i + 1];
            if (i + 1 <n && ((s[i] - '0') * 10 + s[i + 1] - '0') <= 26) {
                dp[i] += dp[i + 2];
            }
        }
    }
    return dp[0];
}
//dp[i]�ĺ��������±�i��ͷ���ַ��������γɶ����ֽ��뷽��
//�����滮������� i+1  i+2Ȼ���Ƴ�i

int main()
{
    char s[max];
    gets(s);
    int n=strlen(s);
    printf("%d\n",n);
    printf("%d\n",f1(s,0,n));
    printf("%d\n",kinds(s,n));
    printf("%d\n",kinds2(s,n));
    return 0;
}
