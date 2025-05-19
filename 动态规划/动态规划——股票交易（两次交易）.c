#include<stdio.h>
#include<limits.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int min(int a,int b)
{
    return a<b?a:b;
}

int maxprofit(int *nums,int n)
{
    int dp1[n+1];
    dp1[1]=0;
    int k=nums[1];
    for(int i=2;i<=n;i++)
    {
        k=min(k,nums[i]);
        dp1[i]=max(dp1[i-1],nums[i]-k);
    }
    int dp2[n+1];
    for(int i=1;i<=n;i++)
        dp2[i]=0;
    int ans=0;
    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            dp2[i]=max(dp2[i],dp1[j]+nums[i]-nums[j]);
        }
        ans=max(ans,dp2[i]);
    }
    return ans;
}

int maxprofit2(int *nums,int n)
{
    int dp1[n+1];
    dp1[1]=0;
    for (int i = 2, k = nums[1]; i <= n; i++) {
        k = min(k, nums[i]);
        dp1[i] = max(dp1[i - 1], nums[i] - k);
    }
    // best[i] : 0...i��Χ�ϣ����е�dp1[i]-nums[i]�����ֵ�Ƕ���
    // ���������������ȫ��Ϊ��������forѭ����ö����Ϊ
    int best [n+1];
    best[1] = dp1[1] - nums[1];
    for (int i = 2; i <= n; i++) {
        best[i] = max(best[i - 1], dp1[i] - nums[i]);
    }
    // dp2[i] : 0...i��Χ�Ϸ������ν��ף����ҵڶ��ν�����iʱ����������������Ƕ���
    int dp2 [n+1];
    int ans = 0;
    for (int i = 1; i < n; i++) {
        // ����Ҫö����
        // ��Ϊ��best[i]�Ѿ���ʾ�ˣ�0...i��Χ�ϣ����е�dp1[i]-nums[i]�����ֵ�Ƕ���
        dp2[i] = best[i] + nums[i];
        ans = max(ans, dp2[i]);
    }
    return ans;
}
int maxprofit3(int* nums,int n) {
		int dp1  [n+1];
		int  best  [n+1];
		best[1] = -nums[1];
		int dp2 [n+1];
		int ans = 0;
		for (int i = 2, k = nums[1]; i <= n; i++) {
			k = min(k, nums[i]);
			dp1[i] = max(dp1[i - 1],nums[i] - k);
			best[i] =max(best[i - 1], dp1[i] - nums[i]);
			dp2[i] = best[i] + nums[i];
			ans = max(ans, dp2[i]);
		}
		return ans;
	}

	// ����ֻ��Ҫ���޼�����������������ȥ�Ϳ�����
	// �ռ�ѹ���İ汾
	// ���ǵ����д������Ҫ��������
int maxprofit4(int *nums,int n) {
    int dp1 = 0;
    int best = -nums[1];
    int ans = 0;
    for (int i = 2, k = nums[1]; i <=n; i++) {
        k = min(k, nums[i]);
        dp1 = max(dp1, nums[i] - k);
        best = max(best, dp1 - nums[i]);
        ans = max(ans, best + nums[i]); // ans = max(ans, dp2);
    }
    return ans;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    printf("%d\n",maxprofit(nums,n));
    printf("%d\n",maxprofit2(nums,n));
    printf("%d\n",maxprofit3(nums,n));
    printf("%d\n",maxprofit4(nums,n));
    return 0;
}
