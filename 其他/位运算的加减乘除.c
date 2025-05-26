//ͨ��λ����ʵ�ּӼ��˳�
#include<stdio.h>

int add(int a,int b)
{
    int ans=a;
    while(b!=0)
    {
        ans=a^b;
        b=(a&b)<<1;
        a=ans;
    }
    return ans;
}
/*
ԭ����ͣ�
    ^�����һ�ֲ���λ���㣬��ô�����������a+b��ֵ���൱�����ǿ�����a^b+��λ��Ϣ
    �������ǵ��ص������λ��Ϣ
    &��λ��������ͬΪһ��Ϊһ������Ϊ0
    ���Կ�����õ�һ�ν�λ��Ϣ
    Ȼ��������в�����ֱ����λ��ϢΪ0
*/
int minus(int a,int b)
{
    return add(a,add(~b,1));
}
//�����൱��a+(-b)
int multiply(int a,int b)
{
    int flag=1;
    if(b<0)
    {
        b=fabs(b);
        flag=-1;
    }
    int ans=0;
    while(b!=0)
    {
        if((b&1)!=0)
        {
            ans=add(ans,a);
        }
        a<<=1;
        b>>=1;
    }
    return ans*flag;
}
/*
ԭ����ͣ�
    ����λ�Ƶĳ˷��൱��һ������ÿһλ�ϵ�����������һ�������
    b&1��Ϊ��ȷ��b�����λ�ǲ���0�������0����ô�˷���Ľ����0��û����ӵı�Ҫ
    ���üӷ�����ʽ
    a����һλ��b����һλ    ����֤�˷���������Ϊλ����������ʧ
*/
int divide(int a,int b)
{
    int ans=0;
    for(int i=30;i>=0;i=minus(i,1))
    {
        if((a>>i)>=b)
        {
            ans|=(1<<i);
            a=minus(a,b<<i);
        }
    }
    return ans;
}
int main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    printf("%d\n",add(a,b));
    printf("%d\n",minus(a,b));
    printf("%d\n",multiply(a,b));
    printf("%d\n",divide(a,b));
    return 0;
}
//�������ֻ�ܴ����������ֶ������������
