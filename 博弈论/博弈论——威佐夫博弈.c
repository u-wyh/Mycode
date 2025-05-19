#include <stdio.h>
#include <math.h>

// ����ƽ�ָ�ȵĽ���ֵ
#define PHI 1.6180339887498948482045868

int compute(int a, int b) {
    // ȷ��a <= b
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // ����(b-a)*PHI��Ȼ��ȡ����a�Ƚ�
    double result = (b - a) * PHI;
    if ((int)result == a) {
        // �����ȣ������Ӯ
        return 0;
    } else {
        // �������ȣ�������Ӯ
        return 1;
    }
}

int main() {
    int a, b;
    while (scanf("%d %d", &a, &b) != EOF) {
        printf("%d\n", compute(a, b));
    }
    return 0;
}
