#include <stdio.h>
#include <stdlib.h>

// ����qsort�ıȽϺ���
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int minimumDeviation(int* nums, int numsSize) {
    // ����һ���㹻����������洢���п��ܵ����������������������
    int* temp = (int*)malloc(numsSize * 2 * sizeof(int));
    if (!temp) return -1; // �ڴ����ʧ��

    int tempSize = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] % 2 == 0) {
            temp[tempSize++] = nums[i];
        } else {
            temp[tempSize++] = nums[i] * 2;
        }
    }

    // ��temp�����������
    qsort(temp, tempSize, sizeof(int), compare);

    int ans = temp[tempSize - 1] - temp[0];

    // ������Java�е�whileѭ������������Ҫ�ֶ��������ֵ����Сֵ
    while (ans > 0 && temp[tempSize - 1] % 2 == 0) {
        int max = temp[tempSize - 1];
        // �Ƴ����ֵ
        tempSize--;
        // ������ֵ��һ��
        temp[tempSize++] = max / 2;
        // �����������ҵ��µ����ֵ����Сֵ
        qsort(temp, tempSize, sizeof(int), compare);
        ans = temp[tempSize - 1] - temp[0];
    }

    free(temp); // �ͷŷ�����ڴ�
    return ans;
}

int main() {
    int n;
    scanf("%d",&n);
    int nums[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&nums[i]);
    }
    printf("Minimum deviation: %d\n", minimumDeviation(nums, n));
    return 0;
}
