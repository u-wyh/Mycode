#include<stdio.h>
#define Max 100

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int nums[Max];
    int i=0;
    while(scanf("%d",&nums[i++])==1);
    int n=i-1;
    int start[n];
    start[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        // nums[i]
        // nums[i] + start[i+1]
        start[i] = max(nums[i], nums[i] + start[i + 1]);
    }
    int ans = start[0];
    // end : �����������i-1��β�����е�����ۼӺ�
    int end = nums[0];
    // maxEnd :
    // 0~i-1��Χ�ϣ�
    // �����������0��β�����е�����ۼӺ�
    // �����������1��β�����е�����ۼӺ�
		// ...
    // �����������i-1��β�����е�����ۼӺ�
    // ��������У������Ǹ��ۼӺ;���maxEnd
    int maxEnd = nums[0];
    for (int i = 1; i < n; i++) {
        // maxend   i....
        // ö�ٻ��ֵ� i...
        ans = max(ans, maxEnd + start[i]);
        // �����������i��β�����е�����ۼӺ�
        end = max(nums[i], end + nums[i]);
        maxEnd = max(maxEnd, end);
    }
    ans = max(ans, maxEnd);
    printf("%5d\n",ans);
    return 0;
}
