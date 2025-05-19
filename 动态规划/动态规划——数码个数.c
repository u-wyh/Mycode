#include <stdio.h>
#include <stdlib.h>

long count(long num, int d) {
    long ans = 0;
    // ���1��
    // d != 0
    // 1 ~ 30583 , d = 5
    // cur < d�����
    // ��λcur=3 : 0000~3057 5
    // ��λ��û�ж����
    //
    // cur > d�����
    // ʮλcur=8 : 000~304 5 0~9
    // ʮλ�϶���� : 305 5 0~9
    //
    // cur == d�����
    // ��λcur=5 : 00~29 5 00~99
    // ��λ�϶���� : 30 5 00~83
    // ...
    // ���2��
    // d == 0
    // 1 ~ 30583 d = 0
    // cur > d�����
    // ��λcur=3 : 0001~3057 0
    // ��λ�϶���� : 3058 0
    //
    // cur > d�����
    // ʮλcur=8 : 001~304 0 0~9
    // ʮλ�϶���� : 305 0 0~9
    //
    // cur > d�����
    // ��λcur=5 : 01~29 0 00~99
    // ��λ�϶���� : 30 0 00~99
    //
    // cur == d�����
    // ǧλcur=0 : 1~2 0 000~099
    // ǧλ�϶���� : 3 0 000~583
    for (long right = 1, tmp = num, left, cur; tmp != 0; right *= 10, tmp /= 10) {
        left = tmp / 10;
        //left����һλ��߿����е������  ��0��ʼ
        if (d == 0) {
            left--;
        }
        //���d����0   ��ôleft��1��ʼ
        ans += left * right;
        //ans��������ߵ����������ұ����
        cur = tmp % 10;
        //cur�ǵ�ǰλ���ϵ�����
        if (cur > d) {
            ans += right;
            //���cur����d   ��ô������Ҫ����1  �ұ��Ǵ�0  ��right-1
        } else if (cur == d) {
            ans += num % right + 1;
            //���cur����d   ��ô���ǰ��ұ�ʣ������ּ���
        }
    }
    return ans;
}
//right��ȡֵʼ�ն���10 100 1000 10000 ����������

long digitsCount(int d, long a, long b) {
    return count(b, d) - count(a - 1, d);
}
//d�ĺ���������d  0 1 2 3 4 5 6 7 8 9
//�����a��b���������ֵ��������   �൱�����1��b��  ��ȥ��1��a��

int main() {
    long a, b;
    scanf("%ld %ld",&a,&b);
    for (int i = 0; i <= 9; i++) {
        printf("%ld ", digitsCount(i, a, b));
    }
    return 0;
}
