//单调栈模板
//统计每个位置左边和右边第一个比自己小的元素位置
//相等的不算
#include<bits/stdc++.h>
using namespace std;

int st[10000];
int n,r=0;
int nums[10000],L[10000],R[10000];

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    int cur;
    for(int i=0;i<n;i++){
        while(r>0&&nums[st[r-1]]>=nums[i]){
            //栈里面的元素严格大压小
            cur=st[--r];
            L[cur]=r>0?st[r-1]:-1;//如果左边没有元素 那么就是-1
            R[cur]=i;//右边的自然就是这个让他出栈的位置了
        }
        st[r++]=i;
    }

    while (r > 0) {
        //将栈中剩余的元素弹出
        cur = st[--r];
        L[cur] = r > 0 ? st[r - 1] : -1;//左边是栈中自己前面的一个元素
        R[cur] = -1;//右边一定是没有比自己小的了
    }

    for(int i=n-2;i>=0;i--){
        if(R[i]!=-1&&nums[i]==nums[R[i]]){
            //继续处理相等的情况
            //那么他的r数组就是他的r的r
            R[i]=R[R[i]];
        }
    }

    for(int i=0;i<n;i++)
        cout<<L[i]<<' '<<R[i]<<endl;
    return 0;
}