#include<stdio.h>

// offset�Ǹ�����������ȫ��len������ֻ��Ϊ�˷�����ȡnum��ĳһλ���֣����ǹؼ�����
// ��ʣ��lenλû�о���
// ���֮ǰ��λ�Ѿ�ȷ����numС����ôfree == 1����ʾ���µ����ֿ�������ѡ��
// ���֮ǰ��λ��numһ������ôfree == 0����ʾ���µ����ֲ��ܴ���num��ǰλ������
// ���֮ǰ��λû��ʹ�ù����֣�fix == 0
// ���֮ǰ��λ�Ѿ�ʹ�ù����֣�fix == 1
// ��������<=num�Ŀ������ж�����
int f1(int* digits, int num, int offset, int len, int free, int fix,int n) {
    if (len == 0) {
        return fix == 1 ? 1 : 0;
    }
    int ans = 0;
    // num�ڵ�ǰλ������
    int cur = (num / offset) % 10;
    if (fix == 0) {
        // ֮ǰ����û��ѡ�������
        // ��ǰ��Ȼ���Բ�Ҫ�κ����֣��ۼӺ����Ŀ�����
        ans += f1(digits, num, offset / 10, len - 1, 1, 0,n);
    }
    if (free == 0) {
        // ��������ѡ������
        for (int k=0;k<n;k++) {
            int i=digits[k];
            if (i < cur) {
                ans += f1(digits, num, offset / 10, len - 1, 1, 1, n);
            } else if (i == cur) {
                ans += f1(digits, num, offset / 10, len - 1, 0, 1, n);
            } else {
                // i > cur
                break;
            }
        }
    } else {
    // ��������ѡ������
        ans += n * f1(digits, num, offset / 10, len - 1, 1, 1, n);
    }
    return ans;
}

int f2(int* digits, int* cnt, int num, int offset, int len,int n) {
    if (len == 0) {
        // num�Լ�
        return 1;
    }
    // cur��num��ǰλ������
    int cur = (num / offset) % 10;
    int ans = 0;
    for (int k=0;k<n;k++) {
        int i=digits[k];
        if (i < cur) {
            ans += cnt[len - 1];
        } else if (i == cur) {
            ans += f2(digits, cnt, num, offset / 10, len - 1,n);
        } else {
            break;
        }
    }
    return ans;
}

int main()
{
    int n,num;
    scanf("%d %d",&n,&num);
    int nums[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int tmp = num / 10;
    int len = 1;
    int offset = 1;
    while (tmp > 0) {
        tmp /= 10;
        len++;
        offset *= 10;
    }
    //len�Ǽ���λ����   offset��10��len�η�
    //printf("%d %d\n",len,offset);
    printf("%d\n",f1(nums,num,offset,len,0,0,n));
    // cnt[i] : ��֪ǰ׺��numС��ʣ��iλû��ȷ��������ǰ׺ȷ��������£�һ���ж�������������
    // cnt[0] = 1����ʾ�����Ѿ�û���ˣ�ǰ׺��״������ȷ������ô����1��
    // cnt[1] = m
    // cnt[2] = m * m
    // cnt[3] = m * m * m
    // ...
    int cnt[len];
    cnt[0] = 1;
    int ans = 0;
    for (int i = n, k = 1; k < len; k++, i *= n) {
        cnt[k] = i;
        ans += i;//��ʱ��ans��λ������len�����  f2�Ǽ���λ��һ�������
    }
    printf("%d\n", ans + f2(nums, cnt, num, offset, len, n));
    return 0;
}
