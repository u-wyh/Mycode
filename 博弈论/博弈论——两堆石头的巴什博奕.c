//����ʯͷ�İ�ʲ����
#include<stdio.h>
#include<stdbool.h>

int main()
{
    int a,b,m,max,eor;
    scanf("%d %d %d",&a,&b,&m);//��������ʯͷ���Ե������Լ�һ������ö���
    max=a>b?a:b;
    bool appear[m+1];
    int sg[max+1];
    sg[0]=0;//����sg������������ֵ
    for(int i=0;i<=max;i++)
    {
        for(int k=0;k<=m;k++)
        {
            appear[k]=false;//���appear�����ĳ�ʼ��
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
    eor=sg[a]^sg[b];
    printf("%d",eor);
    return 0;
}
