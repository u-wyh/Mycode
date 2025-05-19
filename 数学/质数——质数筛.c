#include <stdio.h>
#include <string.h>

// ����ɸͳ��0 ~ n��Χ�ڵ���������
// ʱ�临�Ӷ�O(n * log(logn))
int ehrlich(int n) {
    // ��ʼʱ��Ϊ0~n������������������0��1��������
    int visit[n + 1];
    memset(visit, 0, sizeof(visit)); // 0��ʾ������1��ʾ����

    for (int i = 2; i * i <= n; i++) {
        if (!visit[i]) {
            for (int j = i * i; j <= n; j += i) {
                visit[j] = 1; // ���Ϊ����
            }
        }
    }

    int cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (!visit[i]) {
            cnt++; // ��������
        }
    }

    return cnt;
}

// ŷ��ɸͳ��0 ~ n��Χ�ڵ���������
// ʱ�临�Ӷ�O(n)
//ŷ��ɸ����������ÿ�����ֵ���С������
int euler(int n) {
    int visit[n + 1];
    memset(visit, 0, sizeof(visit)); // 0��ʾ������1��ʾ����
    int prime[n / 2 + 1];
    int cnt = 0;

    for (int i = 2; i <= n; i++) {
        if (!visit[i]) {
            prime[cnt++] = i;
        }

        for (int j = 0; j < cnt && i * prime[j] <= n; j++) {
            //ÿһ�δ���С��������ʼ
            visit[i * prime[j]] = 1; // ���Ϊ����
            if (i % prime[j] == 0) {
                //���i��������prime[j]˵��һ���������������
                //��ô��������Ļ�  ���ǽ������������ֵİ�����һ��������Ϊ������С�������ų���
                //������С�������ų���  ���Բ��ܼ���  Ҫ��������
                break; // ÿ������ֻ������С��������ɸȥһ��
            }
        }
    }

    return cnt;
}

// �Ľ��氣��ɸ��������
int ehrlich2(int n) {
    if (n <= 1) {
        return 0;
    }

    int visit[n + 1];
    memset(visit, 0, sizeof(visit)); // 0��ʾ������1��ʾ����

    // ��ʼ���Ƶ�����������ֻ��������
    int cnt = (n + 1) / 2;

    for (int i = 3; i * i <= n; i += 2) {
        if (!visit[i]) {
            for (int j = i * i; j <= n; j += 2 * i) {
                if (!visit[j]) {
                    visit[j] = 1; // ���Ϊ����
                    cnt--;
                }
            }
        }
    }
    return cnt;
}

int main() {
    int n ;
    scanf("%d",&n);
    printf("Ehrlich's Sieve: %d\n", ehrlich(n));
    printf("Euler's Sieve: %d\n", euler(n));
    printf("Optimized Ehrlich's Sieve: %d\n", ehrlich2(n));
    return 0;
}
