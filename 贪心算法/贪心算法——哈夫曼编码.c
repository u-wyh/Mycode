#include <stdio.h>
#include<limits.h>
#include <stdlib.h>

// ��������������ֵ
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ���ϵ�����
void heapify(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;
    if (right < n && arr[right] < arr[smallest])
        smallest = right;
    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        heapify(arr, n, smallest);
    }
}

// �����Ѷ�Ԫ�أ�����СԪ�أ�
int extractMin(int arr[], int *n) {
    if (*n <= 0) return INT_MAX;
    if (*n == 1) {
        (*n)--;
        return arr[0];
    }
    int root = arr[0];
    arr[0] = arr[(*n) - 1];
    (*n)--;
    heapify(arr, *n, 0);
    return root;
}

// ����Ԫ�ص�����
void insertKey(int arr[], int *n, int k) {
    (*n)++;
    int i = *n - 1;
    while (i && arr[(i - 1) / 2] > k) {
        arr[i] = arr[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    arr[i] = k;
}

// �����������ӹ���
int connectSticks(int arr[], int n) {
    int heapSize = n;
    int sum = 0;

    // ������ʼ��
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, heapSize, i);

    // ���ϴӶ���ȡ��������СԪ�أ���Ӻ��ٷŻض���
    while (heapSize > 1) {
        int first = extractMin(arr, &heapSize);
        int second = extractMin(arr, &heapSize);
        int total = first + second;
        sum += total;
        insertKey(arr, &heapSize, total);
    }

    return sum;
}

int main() {
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    //int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", connectSticks(arr, n));
    return 0;
}

