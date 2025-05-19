#include <stdio.h>

// ����b��n�η��Ľ��%mod
long long power(long long b, int n, int mod) {
    long long ans = 1;
    while (n > 0) {
        if (n & 1) {
            ans = (ans * b) % mod;
        }
        b = (b * b) % mod;
        n >>= 1;
    }
    return ans;
}

// ��һ�����㷽����ע�⣺����ֱ�ӽ��г������ܲ�������������
int compute1(long long a, long long b, int mod) {
    if (b == 0) return -1; // ��ֹ����0
    return (a / b) % mod; // ע�⣺����a/b�����Ƿ�������������ܲ���Ԥ��
}

// �ڶ������㷽����ʹ��ģ��Ԫ
int compute2(long long a, long long b, int mod) {
    if (b == 0) return -1; // ��ֹ����0
    long long inv = power(b, mod - 2, mod);
    return (int)(((a % mod) * inv) % mod);
}

int main() {
    int mod;
    scanf("%d",&mod);
    long long a,b;
    scanf("%lld %lld",&a,&b);

    printf("%d\n", compute1(a, b, mod)); // ע�⣺����������ܲ�������������������ܲ�����Ԥ��
    printf("%d\n", compute2(a, b, mod));

    return 0;
}
