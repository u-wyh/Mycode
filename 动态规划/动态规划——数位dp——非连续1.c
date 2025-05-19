// ��������1�ķǸ�����
// ����һ��������n������ͳ����[0, n]��Χ�ķǸ�������
// �ж��ٸ������Ķ����Ʊ�ʾ�в�����������1
// �������� : https://leetcode.cn/problems/non-negative-integers-without-consecutive-ones/
#include<stdio.h>

// cnt[len] : �����������lenλ�����ж�����״̬�в�����������1��״̬�ж��ٸ�����������
// ��num��������ʽ�ĸ�λ��ʼ����ǰ������iλ��֮ǰ��λ��ȫ��numһ��
// ����<=num�Ҳ�����������1��״̬�ж��ٸ�

//�ȴ��  �������
//�������Ϊ����ͬ��λ���з����
int f(int* cnt, int num, int i) {
    if (i == -1) {
        return 1; // num����Ϸ�
    }
    int ans = 0;
    if ((num & (1 << i)) != 0) {
        //�����λ�ϵ�������1�Ļ� ���ǿ���ѡ1��0  ����ѡ��0  ��ô����ֱ�ӾͿ��Լ���cnt��ֵ
        ans += cnt[i];//0 �� i-1     һ����iλ  ������cnt[i]
        //����ط��൱����ֱ�ӽ�����   �����ڿ��Ǻ����λ����
        //ֻҪԭ���ĵط���1   ���ǽ����λ��д0   ֱ�ӽ���
        if ((num & (1 << (i + 1))) != 0) {
            // ���num������״̬��ǰһλ��1����ǰλҲ��1
            // ���ǰ׺���ֺ�numһ��������һ�����Ϸ���
            // ������ǰ����
            //˵����ǰ����ѡ1
            return ans;
        }
    }
    // ֮ǰ�ĸ�λ��numһ�����ҺϷ�������ȥi-1λ�ݹ�
    ans += f(cnt, num, i - 1);
    //�����λ�ϵ�������0�Ļ� ����ֻ����ѡ0
    return ans;
}

int findIntegers1(int n) {
    int cnt[31];
    cnt[0] = 1;
    cnt[1] = 2;
    for (int len = 2; len <= 30; len++) {
        cnt[len] = cnt[len - 1] + cnt[len - 2];
    }
    return f(cnt, n, 30);
}

int findIntegersIterative(int n) {
    int cnt[31];
    cnt[0] = 1;
    cnt[1] = 2;
    for (int len = 2; len <= 30; len++) {
        cnt[len] = cnt[len - 1] + cnt[len - 2];
    }
    int ans = 0;
    for (int i = 30; i >= 0; i--) {
        if (i == 0) {
            ans++;
            break;
        }
        if ((n & (1 << i)) != 0) {
            ans += cnt[i];
            if ((n & (1 << (i + 1))) != 0) {
                break;
            }
        }
    }
    return ans;
}

int main()
{
    int n;
    scanf("%d",&n);
    printf("%d\n",findIntegers1(n));
    printf("%d\n",findIntegersIterative(n));
    return 0;
}
