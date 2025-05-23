// 统计全1子矩形的数量
// 给你一个 m * n 的矩阵 mat，其中只有0和1两种值
// 请你返回有多少个 子矩形 的元素全部都是1
// 测试链接 : https://leetcode.cn/problems/count-submatrices-with-all-ones/
// 比如
//              1
//              1
//              1         1
//    1         1         1
//    1         1         1
//    1         1         1
//
//    3  ....   6   ....  8
//   left      cur        i
// 如上图，假设6位置从栈中弹出，6位置的高度为6(上面6个1)
// 6位置的左边、离6位置最近、且小于高度6的是3位置(left)，3位置的高度是3
// 6位置的右边、离6位置最近、且小于高度6的是8位置(i)，8位置的高度是4
// 此时我们求什么？
// 1) 求在4~7范围上必须以高度6作为高的矩形有几个？
// 2) 求在4~7范围上必须以高度5作为高的矩形有几个？
// 也就是说，<=4的高度一律不求，>6的高度一律不求！
// 其他位置也会从栈里弹出，等其他位置弹出的时候去求！
// 那么在4~7范围上必须以高度6作为高的矩形有几个？如下：
// 4..4  4..5  4..6  4..7
// 5..5  5..6  5..7
// 6..6  6..7
// 7..7
// 10个！什么公式？
// 4...7范围的长度为4，那么数量就是 : 4*5/2
// 同理在4~7范围上，必须以高度5作为高的矩形也是这么多
// 所以cur从栈里弹出时产生的数量 :
// (cur位置的高度-Max{left位置的高度,i位置的高度}) * ((i-left-1)*(i-left)/2)
#include<bits/stdc++.h>
using namespace std;

int st[10000];
int n,m,r=0;
int nums[1000][1000],L;
char s[1000][1000];
int ans=0;

int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
            cin>>s[i][j];
            if(s[i][j]=='F')
                nums[i][j]=1;
            if(s[i][j]=='R')
                nums[i][j]=0;
            if(i!=0){
                if(nums[i][j]!=0)
                    nums[i][j]+=nums[i-1][j];
            }
        }
    }

    for(int j=0;j<n;j++){
        int cur;
        r=0;
        for(int i=0;i<m;i++){
            while(r>0&&nums[j][st[r-1]]>=nums[j][i]){
                cur=st[--r];
                L=r>0?st[r-1]:-1;
                ans=max(ans,nums[j][cur]*(i-1-L));
            }
            st[r++]=i;
        }

        while (r > 0) {
            cur = st[--r];
            L = r > 0 ? st[r - 1] : -1;
            ans=max(ans,nums[j][cur]*(m-1-L));
        }
    }

    cout<<ans*3<<endl;
    return 0;
}
