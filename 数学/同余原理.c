//������������ab   ��һ�����������������е�����һ�������֮Ϊ�������֣����n������
#include<stdio.h>

int gcd(int a,int b)
{
    int t=a+b;
    a=a>b?a:b;
    b=t-a;
    t=a%b;
    while(t!=0)
    {
        a=b;
        b=t;
        t=a%b;
    }
    return b;
}
//������Լ��
int main()
{
    int a,b,n;
    scanf("%d %d %d",&a,&b,&n);
    printf("%d\n",gcd(a,b));
    int lcm;//��С��Լ��
    lcm=a*b/gcd(a,b);
    long ans = 0;
    for (long l = 0, r = (long) n * (a>b?b:a), m = 0; l <= r;) {
        m = (l + r) / 2;
        if (m / a + m / b - m / lcm >= n)
        {
            ans = m;
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }//m����������Ҫ��ֵ
    printf("%ld",ans % 1000000007);
    return 0;
}
