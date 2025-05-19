#include <stdio.h>
#include <stdlib.h>

// ��̬�����ά����
int** createMatrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed for matrix rows\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for matrix cols\n");
            // Free previously allocated rows and exit
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}
//��������Ҫ�ľ����С���к���

// �������
int** multiply(int** a, int** b, int n) {
    int** result = createMatrix(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}
//�������˷����߱��ձ���  ���ֻ�������������������ξ���
//����Ǿ��ξ�����ô���Բο�  �����ݡ�������˷�

// ������
int** power(int** m, int p, int n) {
    int** ans = createMatrix(n, n);
    for (int i = 0; i < n; i++) {
        for(int j=0;j<n;j++)
        {
            ans[i][j]=0;
            if(i==j)
                ans[i][j]=1;
        }
    }
    for (; p != 0; p >>= 1) {
        if ((p & 1) != 0) {
            ans = multiply(ans, m,n);
        }
        m = multiply(m, m,n);
    }
    return ans;
}
//m������ָ�룬p�������ݣ�n�����Ŀ�ȣ������ξ���

// ��ӡ��ά����
void print(int** m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", m[i][j]);
        }
        printf("\n");
    }
}

// �ͷŶ�ά����
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int n, p;
    scanf("%d %d", &n, &p); // ��ȡ�����С����

    int** m = createMatrix(n, n);

    // �������m
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &m[i][j]);
        }
    }

    int** result = power(m, p, n);

    // ��ӡ�������
    print(result, n);

    // �ͷ��ڴ�
    freeMatrix(m, n);
    freeMatrix(result, n);

    return 0;
}
