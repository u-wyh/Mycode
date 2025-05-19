#include<stdio.h>
#define Max 100

//�Ż���İ汾


// "�����������"ʹ�����¶������� :
// ends[0...len-1]���ϸ�����ģ��ҵ�>=num������λ��
// ��������ڷ���-1
//�Ż���Ч����Ҫ��������ԭ��������Ҫ��һ��max  ������ֻ��Ҫͳ��ends�ĸ����ͺ���
int bs1(int* ends, int len, int num) {
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (ends[m] >= num) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}
int lengthOfLIS2(int* nums,int n) {
    int ends [n];
    // len��ʾends����Ŀǰ����Ч������
    // ends[0...len-1]����Ч������Ч���ڵ�����һ���ϸ�����
    int len = 0;
    for (int i = 0, find; i < n; i++) {
        find = bs1(ends, len, nums[i]);
        if (find == -1) {
            ends[len++] = nums[i];
        } else {
            ends[find] = nums[i];
            //��ʾ�ڳ���Ϊfind�������  ���һ����β��nums[i]��Ŀǰ���ŵģ���С�ģ�
            //��Ϊ���һ��ֵԽС����ô������ԼӵĶ����Ϳ��ܻ�Խ�� ʵ���Ż�Ч��
        }
    }
    return len;
}

int main()
{
    int nums[Max];
    int i=0;
    while(scanf("%d",&nums[i++])==1);
    int n=i-1;
    printf("%5d\n",lengthOfLIS2(nums,n));
    return 0;
}

/*  �����㷨
int main()
{
    int nums[Max];
    int i=0;
    while(scanf("%d",&nums[i++])==1);
    int n=i-1;
    int dp[n];
    dp[0]=1;
    int max=1;
    for(i=1;i<n;i++)
    {
        dp[i]=1;
        for(int j=0;j<i;j++)
        {
            if(nums[j]<nums[i])
                dp[i]=dp[i]>(1+dp[j])?dp[i]:(1+dp[j]);
        }
        if(max<dp[i])
            max=dp[i];
    }
    printf("%5d\n",max);
    return 0;
}
*/
