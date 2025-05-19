#include <stdio.h>
#include <stdlib.h>

int minTaps(int n, int* ranges) {
    // ����һ���㹻����������洢ÿ��λ���ܸ��ǵ������ұ߽�
    int* right = (int*)malloc((n + 1) * sizeof(int));
    if (right == NULL) {
        // �ڴ����ʧ��
        return -1;
    }
    for (int i = 0; i <= n; ++i) {
        right[i] = 0; // ��ʼ��
    }

    // ���right����
    for (int i = 0; i <= n; ++i) {
        int start = i - ranges[i];
        start = start < 0 ? 0 : start; // ��֤start����С��0
        right[start] = i + ranges[i] > right[start] ? i + ranges[i] : right[start];
    }

    // ��ǰans������ˮ��ͷ�򿪣�Ӱ�쵽�������ұ߽�
    int cur = 0;

    // ����ٶ��һ��ˮ��ͷ��Ӱ�쵽�����ұ߽�
    int next = 0;

    // ��ˮ��ͷ������
    int ans = 0;

    for (int i = 0; i < n; i++) {
        // �ȸ�����һ����next
        next = next > right[i] ? next : right[i];

        // ����iλ��
        if (i == cur) {
            if (next > i) {
                cur = next;
                ans++;
            } else {
                // ����޷��������ǣ��򷵻�-1
                free(right); // �ͷ��ڴ�
                return -1;
            }
        }
    }

    free(right); // �ͷ��ڴ�
    return ans;
}

int main() {
    // ʾ���÷�
    int n ;
    scanf("%d",&n);
    int ranges[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&ranges[i]);
    }
    int result = minTaps(n, ranges);
    printf("Minimum taps required: %d\n", result);
    return 0;
}
