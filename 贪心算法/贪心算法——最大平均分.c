#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double pass;
    double total;
    double gain;//ָ�������һ���˵Ļ���ͨ���ʿ�����߶���
} Class;

int compare(const void *a, const void *b) {
    Class *ca = (Class *)a;
    Class *cb = (Class *)b;
    if (ca->gain > cb->gain) return -1;
    if (ca->gain < cb->gain) return 1;
    return 0;
}

double maxAverageRatio(int classes[][2], int n, int m) {
    Class *c_array = (Class *)malloc(n * sizeof(Class));
    for (int i = 0; i < n; i++) {
        c_array[i].pass = classes[i][0];
        c_array[i].total = classes[i][1];
        c_array[i].gain = (c_array[i].pass + 1) / (c_array[i].total + 1) - c_array[i].pass / c_array[i].total;
    }

    // ʹ��ð������ģ�����ȶ��У���gain����
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(&c_array[j], &c_array[j + 1]) > 0) {
                Class temp = c_array[j];
                c_array[j] = c_array[j + 1];
                c_array[j + 1] = temp;
            }
        }
    }

    // ģ��������
    for (int i = 0; i < m; i++) {
        Class *top = &c_array[0];
        top->pass++;
        top->total++;
        top->gain = (top->pass + 1) / (top->total + 1) - top->pass / top->total;

        // ��������
        for (int j = 0; j < n - 1; j++) {
            for (int k = 0; k < n - j - 1; k++) {
                if (compare(&c_array[k], &c_array[k + 1]) > 0) {
                    Class temp = c_array[k];
                    c_array[k] = c_array[k + 1];
                    c_array[k + 1] = temp;
                }
            }
        }
    }

    double ans = 0;
    for (int i = 0; i < n; i++) {
        ans += c_array[i].pass / c_array[i].total;
    }

    free(c_array);
    return ans / n;
}

int main() {
    int n,m;
    scanf("%d %d",&n,&m);//n��ʾ��n���༶ m��ʾ��m�����
    int classes[n][2];
    for(int i=0;i<n;i++)
    {
        scanf("%d %d",&classes[i][0],&classes[i][1]);
    }
    printf("Max Average Pass Ratio: %f\n", maxAverageRatio(classes, n, m));
    return 0;
}
