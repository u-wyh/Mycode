/*
 ���Ч����
 ����һ��ֻ���� '(' �� ')' ���ַ���
 �ҳ����Ч����ʽ��ȷ�������������Ӵ��ĳ��ȡ�
 �������� : https://leetcode.cn/problems/longest-valid-parentheses/
*/

#include<stdio.h>
#include<string.h>
#define max 10000

int main()
{
    int arr[max];
    char s[max];
    int i=0;
    while((s[i++]=getchar())!='\n');
    int n=i-1;
    int dp[n];//���ｨ�齫����ȫ����ʼ��Ϊ0
    for(int i=0;i<n;i++)
        dp[i]=0;
    int ans = 0;
    for (int i = 1, p; i < n; i++) {
        if (s[i] == ')') {
            p = i - dp[i - 1] - 1;
            //  ?         )
            //  p         i
            if (p >= 0 && s[p] == '(') {
                dp[i] = dp[i - 1] + 2 + (p - 1 >= 0 ? dp[p - 1] : 0);
            }
        }
        ans = ans>dp[i]?ans:dp[i];
    }
    printf("%d\n",ans);
    return 0;
}
