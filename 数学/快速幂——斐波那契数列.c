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

// �������
int** multiply(int** a, int** b, int n, int m, int p) {
    int** result = createMatrix(n, p);
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
            ans = multiply(ans, m,n,n,n);
        }
        m = multiply(m, m,n,n,n);
    }
    return ans;
}

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
    int  p;
    scanf("%d",&p); // ��ȡ�����С����
    int** base = createMatrix(1, 2);
    base[0][0] = 1;
    base[0][1] = 0;

    int** m = createMatrix(2, 2);
    m[0][0] = 1; m[0][1] = 1;
    m[1][0] = 1; m[1][1] = 0;

    int** result1 = power(m, p-1, 2);
    int** result2 = multiply(base,result1,1,2,2);
    // ��ӡ�������
    //print(result, n);
    printf("%d\n",result2[0][0]);
    // �ͷ��ڴ�
    //freeMatrix(m, n);
    //freeMatrix(result, n);

    return 0;
}

