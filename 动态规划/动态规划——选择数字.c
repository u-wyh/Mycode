#include<stdio.h>
#include<stdbool.h>

// ���1~7��Χ�����ֶ���ѡ����ôstatus��״̬Ϊ��
// 1 1 1 1 1 1 1 1
// 7 6 5 4 3 2 1 0
// 0λ��������
// ���1~7��Χ�����֣�4��2�Ѿ�ѡ�˲�����ѡ����ôstatus��״̬Ϊ��
// 1 1 1 0 1 0 1 1
// 7 6 5 4 3 2 1 0
// 0λ��������
// f�ĺ��� :
// ���ַ�Χ1~n����ǰ�����֣����status����������״̬
// ���ۼӺͻ�ʣrest�������
// ���ص�ǰ�������ܲ���Ӯ����Ӯ����true������Ӯ����false
bool f(int n, int status, int rest, int* dp) {
    if (rest <= 0) {
        return false;
    }
    // rest > 0
    if (dp[status] != 0) {
        return dp[status] == 1;
    }
    //�����жϴ�ʱ��status�Ƿ��ǿ��Ի�ʤ��
    bool ans = false;
    for (int i = 1; i <= n; i++) {
        // �����������֣����ǲ���ѡ��֮ǰѡ�˵�����
        if ((status & (1 << i)) != 0 && !f(n, (status ^ (1 << i)), rest - i, dp)) {
            ans = true;
            break;
        }
    }
    dp[status] = ans ? 1 : -1;
    return ans;
}

bool canIWin(int n, int m) {
    if (m == 0) {
        // ������Ŀ�涨
        return true;
    }
    if (n * (n + 1) / 2 < m) {
        // ���1~n����ȫ������
        // �ۼӺͺ���n * (n+1) / 2����С��m
        // ��ô������Ӯ�ң�Ҳ����ζ�����ֲ����ʤ
        return false;
    }
    // dp[status] == 0 ����û���
    // dp[status] == 1 ���������true
    // dp[status] == -1 ���������false
    int dp [1 << (n + 1)];
    for(int i=0;i<(1<<(n+1));i++)
        dp[i]=0;
    return f(n, (1 << (n + 1)) - 1, m, dp);
}
/*
����Ҫע�����status��״̬�����ǲ��ܰ�������һ�����֣�Ҫ��������һ������λ�Ƶ�������ɵ�����
dp[status]�ĺ�������status��״̬�£������������ѡ���ܷ��ʤ
��ʵ�������յĴ�Ҳ������dp[status] status�����ֵ  �Ƿ���1
*/
int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    if(canIWin(n,m))
        printf("yes\n");
    else
        printf("no\n");
    return 0;
}
