#include <stdio.h>

#define MOD 1000000007
#define LIMIT 1000

// �׳˱�
long long fac[LIMIT + 1];
// �׳˵���Ԫ��
long long inv[LIMIT + 1];

// �����ݼ��� a^b % MOD
long long power(long long a, int b) {
    long long ans = 1;
    a = a % MOD;
    while (b > 0) {
        if (b & 1) {
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ans;
}

// �����׳˱����Ԫ��
void build() {
    fac[0] = 1;
    for (int i = 1; i <= LIMIT; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }
    inv[LIMIT] = power(fac[LIMIT], MOD - 2);
    for (int i = LIMIT - 1; i >= 0; i--) {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
}


int c1(int n, int m) {
    // �����������
    if (m > n) return 0;
    if (m == 0 || m == n) return 1;
    // ʹ����Ԫ���������
    long long ans = ((inv[m] * inv[n-m]) % MOD) * power(inv[n], MOD - 2) % MOD;
    return (int)ans;
}


// ��������� C(n, m) % MOD��ʹ�ý׳˱����Ԫ��
int c2(int n, int m) {
    long long ans = fac[n];
    ans = (ans * inv[m]) % MOD;
    ans = (ans * inv[n - m]) % MOD;
    return (int)ans;
}


int main() {
    printf("���Կ�ʼ\n");
    build();

    int n = 500;
    for (int m = 0; m <= n; m++) {
        int ans2 = c2(n, m);
        int ans3 = c1(n, m);
        // ע�⣺û��c1�������бȽϣ���ΪC���Դ����˴���ֱ�ӳ���
        printf("C(%d, %d) %% %d = %d  %d\n", n, m, MOD, ans2,ans3);
    }

    printf("���Խ���\n");
    //���������Cn m  m��0��500  n==500

    int a ;
    int b ;
    scanf("%d %d",&a,&b);
    printf("���� C ( %d , %d ) %% %d\n", a, b, MOD);
    printf("������ : %d\n", c2(a, b));
    printf("������ : %d\n", c1(a, b));
    return 0;
}
