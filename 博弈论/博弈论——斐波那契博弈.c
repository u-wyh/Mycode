//쳲��������ģ���ÿ��ֻ����fi�е����ָ�����ʯͷ��
//��϶��������һ����쳲����������е�����һ�����Ա�ʾΪ��������ڵ�쳲���������֮��
#include<stdio.h>
#include<stdbool.h>
#define Max 201//���Ƹ��������ֵ

int main()
{
    int a,b,max,eor;//�˴�������ʯͷ��a,bΪ�����б�̣����Ը���
    scanf("%d %d",&a,&b);
    max=a>b?a:b;
    bool appear[max+1];//����������ĺ���
    int sg[max+1];//����sg����
    sg[0]=0;
    int fi[12]={1,2,3,5,8,13,21,34,55,89,144,233};//�������ǿ���ʹ�õ���쳲���������
    for(int i=1;i<=max;i++)
    {
        for(int k=0;k<=max;k++)
        {
            appear[k]=false;//��ʼ��appear
        }
        for(int j = 0; fi[j]<=i ; j++) { // ȷ�� j ������� m
            appear[sg[i-fi[j]]] = true;
        }
        for(int s = 0; s <= max; s++) {
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
