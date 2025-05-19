#include <stdio.h>
#include <stdlib.h>

// �������
void multiply(int** a, int** b, int** result, int n, int m, int p) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            result[i][j] = 0;
            for (int c = 0; c < m; c++) {
                result[i][j] += a[i][c] * b[c][j];
            }
        }
    }
}
//��δ���û�з���ֵ�����Ǹ��Ƽ�ʹ������Ĵ���
//����a��n*m��   b��m*p��

/*
int ** multiply(int** a, int** b, int n, int m, int p) {
    int** result=createMatrix(n,p);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            result[i][j] = 0;
            for (int c = 0; c < m; c++) {
                result[i][j] += a[i][c] * b[c][j];
            }
        }
    }
    return result;
}
*/

// ��ӡ��ά����
void print(int** m, int n, int p) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            printf("%4d", m[i][j]);
        }
        printf("\n");
    }
}

// ��̬�����ά����
int** createMatrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

// �ͷŶ�ά����
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p); // ��ȡ����A��n��m�к;���B��m��p��

    int** a = createMatrix(n, m);
    int** b = createMatrix(m, p);
    int** result = createMatrix(n, p);

    // �������A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // �������B
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    // �������
    multiply(a, b, result, n, m, p);

    // ��ӡ���
    print(result, n, p);

    // �ͷ��ڴ�
    freeMatrix(a, n);
    freeMatrix(b, m);
    freeMatrix(result, n);

    return 0;
}
