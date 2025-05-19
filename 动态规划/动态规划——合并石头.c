#include<stdio.h>
#include<limits.h>
#define Max 100

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int i=0;
    int nums[Max];
    while(scanf("%d",&nums[i++])==1);
    int k;
    scanf("%d",&k);
    int n=i-1;
    if((n-1)%(k-1)!=0)
        printf("-1\n");
    else
    {
        int presum [n + 1];
        presum[0]=0;
		// �ಹ��һ��0λ�ã�l...r�ۼӺ� : presum[r+1] - presum[l]
		for (int i = 0, j = 1, sum = 0; i < n; i++, j++) {
			sum += nums[i];
			presum[j] = sum;
		}
		// dp[l][r] : l...r��Χ�ϵ�ʯͷ���ϲ��������ٺϲ���������ȷ���ģ�����С�����Ƕ���
		int dp[n][n];
		for(i=0;i<n;i++)
            dp[i][i]=0;
		for (int l = n - 2, ans; l >= 0; l--) {
			for (int r = l + 1; r < n; r++) {
				ans = INT_MAX;
				for (int m = l; m < r; m += k - 1) {
					ans = min(ans, dp[l][m] + dp[m + 1][r]);
				}
				if ((r - l) % (k - 1) == 0) {
					// ����һ���ܻ��ֳ�һ�ݣ���ô���ټӺϲ�����
					ans += presum[r + 1] - presum[l];
				}
				dp[l][r] = ans;
			}
		}
		printf("%d\n",dp[0][n-1]);
    }
    return 0;
}
