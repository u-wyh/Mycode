#include <stdio.h>
#include <stdlib.h>

// ����jump����
int jump(int* arr, int n) {

    // ��ǰ�����ڣ����ҵ���
    int cur = 0;

    // �����һ����(��ǰ��+1)���ڣ����ҵ���
    int next = 0;

    // һ����Ҫ������
    int ans = 0;

    for (int i = 0; i < n; i++) {
        // ����i�±�
        // cur������i���ڵ�λ�ã����ø������ⲽ��
        // curû�а���i���ڵ�λ�ã���Ҫ�������ⲽ��
        if (cur < i) {
            ans++;
            cur = next;
        }
        // ����next������ǰ����������һ�������ܵ������Զ����
        next = (next > i + arr[i]) ? next : i + arr[i];
    }

    return ans;
}

int main() {
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    // ����jump��������ӡ���
    int result = jump(arr, n);
    printf("Minimum jumps to reach the end: %d\n", result);

    return 0;
}
