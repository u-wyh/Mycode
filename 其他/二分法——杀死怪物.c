#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// ����Ƿ�����ָ���غ���ɱ������
int f(int* cuts, int* poisons, int cuts_len, long hp, int limit) {
    int n = (limit < cuts_len) ? limit : cuts_len;
    for (int i = 0, j = 1; i < n; i++, j++) {
        hp -= (long)cuts[i] > (limit - j) * poisons[i] ? cuts[i] : (limit - j) * poisons[i];
        if (hp <= 0) return 1;
    }
    return 0;
}

// ���ִ𰸷�
int fast2(int* cuts, int* poisons, int cuts_len, int hp) {
    int left = 1, right = hp + 1, mid, ans = INT_MAX;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (f(cuts, poisons, cuts_len, hp, mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}

// �����������ڲ���
int main() {
    int n,hp;
    scanf("%d %d",&n,&hp);
    int cuts[n],poisons[n];
    for(int i=0;i<n;i++){
        scanf("%d %d",&cuts[i],&poisons[i]);
    }
    printf("%d\n",fast2(cuts,poisons,n,hp));
    return 0;
}
