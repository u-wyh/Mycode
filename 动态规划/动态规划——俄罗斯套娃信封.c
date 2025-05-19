//��������  ��½�������
#include <stdio.h>
#include <stdlib.h>

// �ṹ�嶨���ŷ�
typedef struct {
    int width;
    int height;
} Envelope;

// �ȽϺ���������qsort
int compare(const void* a, const void* b) {
    Envelope* envA = (Envelope*)a;
    Envelope* envB = (Envelope*)b;
    if (envA->width != envB->width) {
        return envA->width - envB->width;
    } else {
        return envB->height - envA->height; // ע�������ǽ���
    }
}

// ���ֲ���
int binarySearch(int* ends, int len, int num) {
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (ends[m] >= num) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}

// ����˹�����ŷ�����
int maxEnvelopes(Envelope* envelopes, int envelopesSize) {
    if (envelopesSize == 0) return 0;

    // ʹ��qsort��������
    qsort(envelopes, envelopesSize, sizeof(Envelope), compare);

    int* ends = (int*)malloc(envelopesSize * sizeof(int));
    int len = 0;

    for (int i = 0; i < envelopesSize; i++) {
        int num = envelopes[i].height;
        int find = binarySearch(ends, len, num);
        if (find == -1) {
            ends[len++] = num;
        } else {
            ends[find] = num;
        }
    }

    int result = len;
    free(ends); // �ͷ��ڴ�
    return result;
}

int main() {
    // ʾ������
    Envelope envelopes[] = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
    int envelopesSize = sizeof(envelopes) / sizeof(envelopes[0]);

    // ���ú�����������
    printf("��������һ��'����˹����'�ŷ�ĸ���Ϊ: %d\n", maxEnvelopes(envelopes, envelopesSize));

    return 0;
}
