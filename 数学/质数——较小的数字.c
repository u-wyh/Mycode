#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

// �����б�����Miller-Rabin����
static const int64_t p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

// �����ݺ��������� (n^p) % mod
int64_t power(int64_t n, int64_t p, int64_t mod) {
    int64_t ans = 1;
    while (p > 0) {
        if (p & 1) {
            ans = (ans * n) % mod;
        }
        n = (n * n) % mod;
        p >>= 1;
    }
    return ans;
}

// Miller-Rabin���Եĵ��ε���
bool witness(int64_t a, int64_t n) {
    int64_t u = n - 1;
    int t = 0;
    while ((u & 1) == 0) {
        t++;
        u >>= 1;
    }
    int64_t x1 = power(a, u, n), x2;
    for (int i = 1; i <= t; i++) {
        x2 = power(x1, 2, n);
        if (x2 == 1 && x1 != 1 && x1 != n - 1) {
            return true; // n �Ǻ���
        }
        x1 = x2;
    }
    if (x1 != 1) {
        return true; // n �Ǻ���
    }
    return false; // n ����������
}

// Miller-Rabin��������
bool millerRabin(int64_t n) {
    if (n <= 2) {
        return n == 2;
    }
    if ((n & 1) == 0) {
        return false;
    }
    for (int i = 0; i < sizeof(p) / sizeof(p[0]) && p[i] < n; i++) {
        if (witness(p[i], n)) {
            return false;
        }
    }
    return true;
}

int main() {
    int t;
    scanf("%d", &t);
    char buffer[100]; // �������ֲ��ᳬ��99λ
    for (int i = 0; i < t; i++) {
        scanf("%s", buffer);
        int64_t n = strtoll(buffer, NULL, 10); // ���ַ���ת��Ϊlong long
        printf("%s\n", millerRabin(n) ? "Yes" : "No");
    }
    return 0;
}
