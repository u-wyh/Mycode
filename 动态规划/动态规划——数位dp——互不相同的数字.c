// ��ȫû���ظ������ָ���
// ����������n��������[1, n]��Χ��ÿһλ��������ͬ������������
// �������� : https://leetcode.cn/problems/count-special-integers/
#include <stdio.h>
#include <stdlib.h>

int f(int *cnt, int num, int len, int offset, int status) {
    //len��ʾ���ж���λû�����
    //status��ʾ״̬�������ƣ�  ��ʾ��Щ�����Ѿ���ѡ�����
    if (len == 0) {
        return 1;
    }
    int first = (num / offset) % 10;
    //��ʾ����һλ�ϵ����ֵ�ֵ
    int ans = 0;
    for (int cur = 0; cur < first; cur++) {
        if ((status & (1 << cur)) == 0) {
            ans += cnt[len - 1];
        }
    }
    //��ʾѡ��û��ѡ���ұȵ�ǰ��ֵҪС������  ��ôֱ�ӿ��Լ���cnt�е�ֵ
    if ((status & (1 << first)) == 0) {
        ans += f(cnt, num, len - 1, offset / 10, status | (1 << first));
    }
    //��ʾѡ��ǰ��ֵ
    return ans;
}

int countSpecialNumbers(int n) {
    int len = 1;
    int offset = 1;
    int tmp = n / 10;
    while (tmp > 0) {
        len++;
        offset *= 10;
        tmp /= 10;
    }
    //��len offset��ֵ���г�ʼ��
    int *cnt = (int *)malloc(sizeof(int) * len);
    if (cnt == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    // cnt[i] :
    // һ������Ϊlen��   ��ʣiλû��ȷ����ȷ����ǰ׺Ϊlen-iλ��      ��ȷ����ǰ׺��Ϊ��
    // 0~9һ��10�����֣�û��ѡ�������ʣ��10-(len-i)��
    // ��ô�ں�����iλ�ϣ��ж���������
    // ���磺len = 4
    // cnt[4]������
    // cnt[3] = 9 * 8 * 7
    // cnt[2] = 8 * 7
    // cnt[1] = 7
    // cnt[0] = 1����ʾǰ׺��ȷ��������Ҳû���ˣ���ô����1�����У�����ǰ׺��״��
    // �ٱ��磺len = 6
    // cnt[6]������
    // cnt[5] = 9 * 8 * 7 * 6 * 5
    // cnt[4] = 8 * 7 * 6 * 5
    // cnt[3] = 7 * 6 * 5
    // cnt[2] = 6 * 5
    // cnt[1] = 5
    // cnt[0] = 1����ʾǰ׺��ȷ��������Ҳû���ˣ���ô����1�����У�����ǰ׺��״��
    // ����forѭ���������cnt�Ĵ���
    cnt[0] = 1;
    for (int i = 1, k = 10 - len + 1; i < len; i++, k++) {
        cnt[i] = cnt[i - 1] * k;
    }

    int ans = 0;
    if (len >= 2) {
        ans = 9;
        for (int i = 2, a = 9, b = 9; i < len; i++, b--) {
            a *= b;
            ans += a;//��ʱ��ans�Ǽ���λ������len�����
        }
    }

    int first = n / offset;
    ans += (first - 1) * cnt[len - 1];
    //ans���ȿ��Լ�����λ��ͬ���ҵ�һλҲһ����
    ans += f(cnt, n, len - 1, offset / 10, 1 << first);

    free(cnt);
    return ans;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("Number of special integers <= %d: %d\n", n, countSpecialNumbers(n));
    return 0;
}
