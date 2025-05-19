/*
��δ���������ǣ�����һ���������飬������100000�����֣�ÿ�����ֿ��ܻ��ظ���
                  ��������һ�����飬��ÿ�����ֵĺ������������Ҫ������ô����ͬ������
                  �������ʵ���ˣ����true���������false
*/
#include<stdio.h>
#include<stdbool.h>
#define Max1 100000
#define Max2 10

int nums[Max1];
int quantity[Max2];
int help[Max1];
int dp [1 << Max2][Max1];

void merge(int l,int m,int r)
{
    int a=l;
    int b=m+1;
    int i=l;
    while(a<=m&&b<=r)
        help[i++]=nums[a]<=nums[b]?nums[a++]:nums[b++];
    while(a<=m)
        help[i++]=nums[a++];
    while(b<=r)
        help[i++]=nums[b++];
    for(i=l;i<=r;i++)
        nums[i]=help[i];
}

void mergesort(int l,int r)
{
    if(l>=r)
        return ;
    int m=(l+r)/2;
    mergesort(l,m);
    mergesort(m+1,r);
    merge(l,m,r);
}

bool f(int* cnt, int* sum, int status, int index,int l)
{
    if (status == 0) {
        return true;
    }
    // status != 0
    if (index == l) {
        return false;
    }
    if (dp[status][index] != 0) {
        return dp[status][index] == 1;
    }
    bool ans = false;
    int k = cnt[index];
    // ��������ʵ������ĵ�ö��
    // jö����status�������Ӽ�״̬
    // �����ס
    for (int j = status; j > 0; j = (j - 1) & status) {
        if (sum[j] <= k && f(cnt, sum, status ^ j, index + 1, l)) {
            ans = true;
            break;
        }
    }
    if (!ans) {
        ans = f(cnt, sum, status, index + 1, l);
    }
    dp[status][index] = ans ? 1 : -1;
    return ans;
}

int main()
{
    int i=0;
    while(scanf("%d",&nums[i++])==1);
    int n=i-1;
    int j=0;
    while(scanf("%d",&quantity[j++])==1);
    int m=j-1;
    mergesort(0,n-1);
    //�����������������������Ȼ���½�һ�����鴢��������ֳ��ֵ�Ƶ��
    //ע�⣬��������ֻ��Ҫ�õ����ֵĳ���Ƶ�ʼ��ɣ����ֵĴ�Сû��Ҫ��

    int k = 1;
    for (int i = 1; i < n; i++) {
        if (nums[i - 1] != nums[i]) {
            k++;
        }
    }
    int cnt [k];
    int c = 1;
    for (int i = 1, j = 0; i < n; i++) {
        if (nums[i - 1] != nums[i]) {
            cnt[j++] = c;
            c = 1;
        } else {
            c++;
        }
    }
    cnt[k - 1] = c;
    //ʵ������Ƶ�ʵļ�¼

    int sum [1 << m];
    // �������ö��������quantity�е�ÿ���Ӽ�������Ҫ���ֵĸ���
    // �����Զ����Ƶ���ʽ����sum[]��������֣����ʮλ������
    //��0000000000
    //  0000000001
    //  0000000010
    //  0000000011
    //  ������������
    //  1111111111    ���λ������1��˵����������ֻ��Ҫ��Щ����
    for (int i = 0, v, h; i < m; i++) {
        v = quantity[i];
        h = 1 << i;
        for (int j = 0; j < h; j++) {
            sum[h | j] = sum[j] + v;
        }
    }
    for(int i=0;i<(1<<m);i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=0;
        }
    }
    //��ʼ��dp

    if(f(cnt, sum, (1 << m) - 1, 0,k))
        printf("yes\n");
    else
        printf("no\n");
    return 0;
}
