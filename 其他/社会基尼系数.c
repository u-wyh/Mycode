#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

double Gini(int *arr,int n)
{
    int i,j;
    int Deviation = 0 ,Total = n*100;//����ܲƸ���ʼʱ��ƽ��ÿ����100
    double G;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            Deviation+=abs(arr[i]-arr[j]);
        }
    }
    G=Deviation*1.0/(2*n*Total);
    return G;
}
//����������ϵ���Ĺ�ʽ


int main()
{
    int n,t;
    printf("please enter the number of people: ");
    scanf("%d",&n);
    printf("please enter the number of rounds: ");
    scanf("%d",&t);
    //������ݵ�����  ��������������
    int arr[n];
    for(int i=0;i<n;i++){
        arr[i]=100;
    }
    //�����ʼʱ�����˵ĲƸ�
    srand(time(NULL));//���������
    for(int i=1;i<=t;i++)
    {
        for(int j=0;j<n;j++)
        {
            int other=rand()%n;
            //printf("%5d",other);//���Լ���ǲ���������ɵ�
            if(arr[j]!=0)
            {
                if(other==j)
                    other++;
                else
                {
                    arr[j]--;
                    arr[other]++;
                }
            }
        }//��ѭ��һ�δ�����һ���˵ĲƸ��������
        for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++)
        {
            if(arr[j]<arr[min])
                min=j;
        }
        if(min!=i)
        {
            int k=arr[min];
            arr[min]=arr[i];
            arr[i]=k;
        }
    }//��ÿ���˵ĲƸ���������

    for(int i=0;i<n;i++)
    {
        printf("%4d",arr[i]);
    }
    //���ÿ���˵ĲƸ�

    printf("\n");
    printf("\n");

    }//��ѭ��һ�δ���Ƹ�һ�ֽ������


    /*for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++)
        {
            if(arr[j]<arr[min])
                min=j;
        }
        if(min!=i)
        {
            int k=arr[min];
            arr[min]=arr[i];
            arr[i]=k;
        }
    }//��ÿ���˵ĲƸ���������

    for(int i=0;i<n;i++)
    {
        printf("%4d",arr[i]);
    }
    //���ÿ���˵ĲƸ�
    printf("\n");*/

    printf("%lf\n",Gini(arr,n));
    return 0;
}
