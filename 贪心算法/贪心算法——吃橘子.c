#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_ORANGES 10000
int dp[MAX_ORANGES + 1];

// ��ʼ��dp����
void initDp() {
    for (int i = 0; i <= MAX_ORANGES; i++) {
        dp[i] = INT_MAX; // ��ʼ��Ϊһ���ܴ��������ʾδ����
    }
}

int minDays(int n) {
    if (n <= 1) {
        return n;
    }
    if (dp[n] != INT_MAX) {
        return dp[n];
    }
    int ans = n % 2 + 1 + minDays(n / 2);
    ans = (ans < (n % 3 + 1 + minDays(n / 3))) ? ans : (n % 3 + 1 + minDays(n / 3));

    dp[n] = ans;
    return ans;
}

int main() {
    initDp();
    int n ;
    scanf("%d",&n) ;
    printf("Minimum days to eat %d oranges: %d\n", n, minDays(n));
    return 0;
}
