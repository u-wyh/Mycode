#include<stdio.h>
int fun(int num,int *cnt,int n,int len,int m,int offset,int *nums)
/*�������ͣ�
    num �����ǲ��ܳ���������   cnt �������Ѿ�׼���õı�  n nums����ĳ���
    len �������Ѿ���õ�λ��   m ��cnt�ĳ���  offset �������� nums����
*/
{
    if(len==m)
        return 1;
    int ans=0;
    int cur=num/offset%10;
    for(int i=1;i<=n;i++)
    {
        if(nums[i]<cur)
            ans+=cnt[m-len-1];
        else if(nums[i]==cur)
            ans+=fun(num,cnt,n,len+1,m,offset/10,nums);
        else
            break;
    }
    return ans;
}

int main()
{
    int n,num;
    printf("please enter the length of nums(n)  and  the num  : ");
    scanf("%d %d",&n,&num);
    int nums[n+1];
    printf("please enter the nums: ");
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int tmp = num / 10;
    int len = 1;
    int offset = 1;
    while (tmp > 0) {
        tmp /= 10;
        len++;
        offset *= 10;
    }//len��num�ĳ���   offset��һ����������
    int cnt[len+1];
    cnt[0]=1;
    int ans=0;
    for(int i=1;i<len;i++)
    {
        cnt[i]=cnt[i-1]*n;
        ans+=cnt[i];
    }
    printf("%d\n",ans+fun(num,cnt,n,0,len,offset,nums));
    return 0;
}
