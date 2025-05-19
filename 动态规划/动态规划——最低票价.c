/*
���Ʊ��
��һ�������к��ܻ�ӭ�Ĺ��ȣ�����ǰһ��ƻ���һЩ������
�ڽ�������һ�����Ҫ���е����ӽ���һ����Ϊ days ���������
ÿһ����һ���� 1 �� 365 ������
��Ʊ�� ���ֲ�ͬ�����۷�ʽ
һ�� Ϊ��1�� ��ͨ��֤�ۼ�Ϊ costs[0] ��Ԫ
һ�� Ϊ��7�� ��ͨ��֤�ۼ�Ϊ costs[1] ��Ԫ
һ�� Ϊ��30�� ��ͨ��֤�ۼ�Ϊ costs[2] ��Ԫ
ͨ��֤�������������Ƶ�����
���磬��������ڵ� 2 ����һ�� Ϊ�� 7 �� ��ͨ��֤
��ô���ǿ����������� 7 ��(��2~8��)
���� ����Ҫ����ڸ������б� days ���г���ÿһ�����������Ҫ���������
�������� : https://leetcode.cn/problems/minimum-cost-for-tickets/
*/

#include<stdio.h>
#include<limits.h>
#define max 365

static int durations[3]={1,7,30};
//�����ײ�ʱ������0 1 2�ֱ���1 7 30

int f1(int* days, int* price, int i,int n) {
    if (i == n) {
        // �����Ѿ���������
        return 0;
    }
    // i�±� : ��days[i]�죬��һ������
    // i.... ���ٻ����Ƕ���
    int ans = INT_MAX;
    for (int k = 0, j = i; k < 3; k++) {
        // k�Ƿ������ : 0 1 2
        while (j < n && days[i] + durations[k] > days[j]) {
            // ��Ϊ����2������������࣬30��
            // ����whileѭ�����ִ��30��
            // ö����Ϊ������Ϊ��O(1)
            // ����������  j������n
            // ѭ���е� days[i] + durations[k] > days[j]   ��ѡ��ǰ�ĵ�k�ַ����������  ����ʵ�ֵڼ�������Ŀ��
            j++;
        }
        ans = ans> (price[k] + f1(days, price, j,n))?(price[k] + f1(days, price, j,n)):ans;
    }
    return ans;
}
//�����Ǳ����㷨�������Ʊ��


int mincostTickets2(int* days, int* price,int n) {
    int dp[n];
    for (int i = 0; i < n; i++) {
        dp[i] = INT_MAX;
    }
    return f2(days,price, 0,n, dp);
}

int f2(int* days, int* price, int i, int n,int* dp) {
    if (i == n) {
        return 0;
    }
    if (dp[i] != INT_MAX) {
        return dp[i];
    }
    int ans = INT_MAX;
    for (int k = 0, j = i; k < 3; k++) {
        while (j < n && days[i] + durations[k] > days[j]) {
            j++;
        }
        ans = ans> (price[k] + f2(days, price, j,n,dp))?(price[k] + f2(days, price, j,n,dp)):ans;
    }
    dp[i] = ans;
    return ans;
}
//ʹ�ô���ķ���������ʱ��

int main()
{
    int days[max];
    int i=0;
    while(scanf("%d",&days[i++])==1);
    //days[i] ��ʾ��i��Ҫ����
    int n=--i;
    //��ʾһ����n������Ҫ���е�

    int price[3];//���巽��0 1 2������Ʊ��
    for(i=0;i<3;i++)
    {
        scanf("%d",&price[i]);
    }
    printf("\n");

    printf("%d\n",f1(days,price,0,n));
    printf("%d\n",mincostTickets2(days,price,n));
    return 0;
}
