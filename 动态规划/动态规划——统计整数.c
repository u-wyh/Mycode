// ͳ��������Ŀ
// �������������ַ��� num1 �� num2 ���Լ���������max_sum��min_sum
// ���һ������ x �����������������ǳ�����һ��������
// num1 <= x <= num2
// min_sum <= digit_sum(x) <= max_sum
// ���㷵�غ���������Ŀ
// �𰸿��ܴܺ��뷵�ش𰸶�10^9 + 7 ȡ���Ľ��
// ע�⣬digit_sum(x)��ʾx��λ����֮��
// �������� : https://leetcode.cn/problems/count-of-integers/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAXN 23
#define MAXM 401
#define Max  10000

int dp[MAXN][MAXM][2];
//dp[i][sum][free] ��ʾ�Ѿ�ѡ����ǰiλ�������ǵĺ�Ϊsum   free��ʾ״̬�Ƿ�������ѡ  �ķ�����
char *num;
int min, max, len;

void build() {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j <= max; j++) {
            dp[i][j][0] = -1;
            dp[i][j][1] = -1;
        }
    }
}
//���ȫ�ֱ����ĳ�ʼ��

int f(int i, int sum, int free) {
    if (sum > max)
        return 0;
    //��ʾ���ڵ�ѡ�����  �Ѿ���������  ����ֹͣ
    if (sum + (len - i) * 9 < min)
        return 0;
    //��ʾ���ڵ�ѡ���С  �Ѿ���������  ����ֹͣ
    if (i == len)
        return 1;
    //��ʾ���е������Ѿ����   �ɹ�����  ����1
    if (dp[i][sum][free] != -1)
        return dp[i][sum][free];

    int cur = num[i] - '0';
    int ans = 0;
    if (free == 0) {
        //ѡ��������
        for (int pick = 0; pick < cur; pick++) {
            ans = (ans + f(i + 1, sum + pick, 1)) % MOD;
        }
        ans = (ans + f(i + 1, sum + cur, 0)) % MOD;
    } else {
        //ѡ��û������
        for (int pick = 0; pick <= 9; pick++) {
            ans = (ans + f(i + 1, sum + pick, 1)) % MOD;
        }
    }
    dp[i][sum][free] = ans;
    return ans;
}

int count(char *num1, char *num2, int min_sum, int max_sum) {
    min = min_sum;
    max = max_sum;
    num = strdup(num2);
    len = strlen(num);
    build();
    int ans = f(0, 0, 0);
    //���Ǵ�0�������֮��Ĵ�

    free(num);
    num = strdup(num1);
    len = strlen(num);
    build();
    ans = (ans - f(0, 0, 0) + MOD) % MOD;
    //f(0,0,0)�Ǵ�0����С����-1��֮��Ĵ𰸣���С������Ҫ���У�   ��Ҫ��ȥ
    //��Ϊ����������ִ� �ı���  �����С������1000000.....�Ļ�  a-1���ô���

    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += num[i] - '0';
    }
    if (sum >= min && sum <= max) {
        ans = (ans + 1) % MOD;
    }
    //����С���Ǹ��������Ƿ����Ҫ��

    free(num);
    return ans;
}

int main() {
    char num1[Max];
    char num2[Max];
    scanf("%s",num1);
    scanf("%s",num2);
    int min_sum, max_sum;
    scanf("%d %d",&min_sum,&max_sum);
    printf("Result: %d\n", count(num1, num2, min_sum, max_sum));
    return 0;
}
