#include<stdio.h>
#include<stdbool.h>

int main()
{
    int m,k=0;
    scanf("%d",&m);//�˴���m�������ܳ���
    int arr[m],max=0;
    for(int i=0;i<m;i++)
    {
        scanf("%d",&arr[i]);//��������ѵ�ʯͷ��Ŀ
        if(arr[i]>=max)
            max=arr[i];//��������е����ֵ��Ϊsg������׼��
    }
    int sg[max+1];//����sg����
    sg[0]=0;
    bool appear[max+1];
    for(int i=1;i<=max;i++)
    {
        for(int k=0;k<=max;k++)
        {
            appear[k]=false;//��ʼ��appear
        }
        for(int j = 1; j <= i && j <= max; j++) { // ȷ�� j ������� m
            appear[sg[i-j]] = true;
        }
        for(int s = 0; s <= max; s++) {
            if(!appear[s]) {
                sg[i] = s;
                break; // �ҵ� s ���˳�ѭ��
            }
        }
    }
    for(int i = 0; i < m; i++) { // ������ n����Ϊ sg ���������� n+1 ��Ԫ��
        printf("%5d %5d\n",arr[i], sg[arr[i]]);
        k=k^sg[arr[i]];
    }
    printf("%d",k);
    return 0;
}
