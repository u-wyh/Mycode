#include<stdio.h>
#include<stdbool.h>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int sg[n+1]; // �����СΪ n+1
    bool appear[m+1]; // ���� m �ǿ��ܵ� sg ֵ������

    sg[0] = 0;
    for(int i = 1; i <= n; i++) { // �� 1 ��ʼ��������Ϊ sg[0] �Ѿ�����
        for(int k = 0; k <= m; k++) {
            appear[k] = false;
        }
        for(int j = 1; j <= i && j <= m; j++) { // ȷ�� j ������� m
            appear[sg[i-j]] = true;
        }
        for(int s = 0; s <= m; s++) {
            if(!appear[s]) {
                sg[i] = s;
                break; // �ҵ� s ���˳�ѭ��
            }
        }
    }
    for(int i = 0; i <= n; i++) { // ������ n����Ϊ sg ���������� n+1 ��Ԫ��
        printf("%5d %5d\n",i, sg[i]);
    }
    printf("\n"); // ��ӻ��з��Ը��������ʽ
    return 0;
}
