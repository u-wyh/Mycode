// 墨墨的等式(两次转圈法)
// 一共有n种正数，每种数可以选择任意个，个数不能是负数
// 那么一定有某些数值可以由这些数字累加得到
// 请问在[l...r]范围上，有多少个数能被累加得到
// 0 <= n <= 12
// 0 <= 数值范围 <= 5 * 10^5
// 1 <= l <= r <= 10^12
// 测试链接 : https://www.luogu.com.cn/problem/P2371
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
//之所以要转两圈  是因为每次开始转圈的时候  起点不一定是最小的
//所以需要第二圈来修正
//二次转圈法的优势是他的时间复杂度更稳定  比dj算法好
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500001;

int v[MAXN];
long dist[MAXN];
int n, x;
long l, r;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

long compute() {
    sort(v + 1, v + n + 1);
    int sz = 0;
    for (int i = 1; i <= n; i++) {
        if (v[i] != 0) {
            //统计所有非0的数字  相当于将0移到前面
            v[++sz] = v[i];
        }
    }
    //去除无效数字
    if (sz == 0) {
        //如果全都是0  那么就没必要求了
        return 0;
    }
    x = v[1];
    for(int i=0;i<x;i++){
        dist[i]=LONG_MAX;//所有点的距离都是最大值
    }
    dist[0] = 0;//0的距离是0
    for (int i = 2, d; i <= sz; i++) { // 出现基准数之外的其他数，更新最短路
        d = gcd(v[i], x); // 求最大公约数  得到环的个数
        for (int j = 0; j < d; j++) { // j是每个子环的起点
            for (int cur = j, Next, circle = 0; circle < 2; circle += cur == j ? 1 : 0) {
                //需要转两圈  circle += cur == j ? 1 : 0判断是否回到起点 即圈数加一
                Next = (cur + v[i]) % x;//表示要去的下一个点
                if (dist[cur] != LONG_MAX) {
                    dist[Next] = min(dist[Next], dist[cur] + v[i]);
                }
                cur = Next;//变换当前点
            }
        }
    }
    long ans = 0;
    //然后统计小于r  和  小于l的个数  得到答案
    for (int i = 0; i < x; i++) {
        if (r >= dist[i]) {
            ans += max((long)0, (r - dist[i]) / x + 1);
        }
        if (l >= dist[i]) {
            ans -= max((long)0, (l - dist[i]) / x + 1);
        }
    }
    return ans;
}

int main()
{
    cin>>n>>l>>r;
    l--;
    for(int i=1;i<=n;i++){
        cin>>v[i];
    }
    cout<<compute();
    return 0;
}
