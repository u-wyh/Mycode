/*
// ������
// �� n �����򣬱��Ϊ0��n-1��ÿ�������϶�����һ�����֣���Щ���ִ�������nums��
// ����Ҫ����������е����򡣴��Ƶ� i ������
// ����Ի�� nums[i - 1] * nums[i] * nums[i + 1] öӲ��
// ����� i - 1 �� i + 1 ����� i ���ڵ�������������
// ��� i - 1�� i + 1 ����������ı߽磬��ô�͵�����һ������Ϊ 1 ������
// �����ܻ��Ӳ�ҵ��������
// �������� : https://leetcode.cn/problems/burst-balloons/
*/

#include<stdio.h>
#define Max 1000

static int dp[Max][Max];

int max(int a,int b)
{
    return a>b?a:b;
}

// nums[l...r]��Щ�������һ��˳�򣬻�����÷ַ��أ�
// һ���� : nums[l-1]һ��û����
// һ���� : nums[r+1]һ��û����
// ����ÿ����������
int f(int* nums, int l, int r) {
    if (dp[l][r] != -1) {
        return dp[l][r];
    }
    int ans;
    if(l==r)
    {
        ans = nums[l - 1] *nums[l] * nums[r + 1];
    }
    else
    {
        // l   ....r
        // l +1 +2 .. r
        ans = max( nums[l - 1] * nums[l] * nums[r + 1] + f(nums, l + 1, r), // lλ�õ���������
                   nums[l - 1] * nums[r] * nums[r + 1] + f(nums, l, r - 1));// rλ�õ���������
        for(int k = l + 1; k < r; k++) {
            // kλ�õ���������
            // l...k-1  k  k+1...r
            ans =max(ans, nums[l - 1] * nums[k] * nums[r + 1] + f(nums, l, k - 1) + f(nums, k + 1, r));
        }
    }
    dp[l][r] = ans;
    return ans;
}

int maxCoins1(int* nums,int n)
{
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            dp[i][j] = -1;
        }
    }
    return f(nums, 1, n);
}

int main()
{
    int n;
    scanf("%d",&n);
    int arr[n];
    int nums[n+2];
    nums[0]=1;
    nums[n+1]=1;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
        nums[i+1]=arr[i];
    }
    printf("%d\n",maxCoins1(nums,n));
    return 0;
}
