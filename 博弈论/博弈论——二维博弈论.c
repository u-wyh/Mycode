//��ά������
#include<stdio.h>
#include<stdbool.h>

int main()
{
    int a,b;
    scanf("%d %d",&a,&b);//��������ʯ�ӵĸ���
    int sg[a+1][b+1];//����sg����
    sg[1][1]=0;
    bool appear[a+1][b+1];

    for(int i=0;i<=a;i++){
        for(int m=1;m<=a;m++){
            for(int n=1;n<=b;n++){
                appear[m][n]=false;//���appear�ĳ�ʼ��
            }
        }
        for(int s = 0; s <= (a+b); s++) {
            if(!appear[s]) {
                sg[i] = s;
                break; // �ҵ� s ���˳�ѭ��
            }
        }
    }
    return 0;
}
