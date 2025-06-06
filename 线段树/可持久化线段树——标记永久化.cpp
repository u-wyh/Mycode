// 标记永久化，范围增加 + 查询累加和，C++版
// 给定一个长度为n的数组arr，下标1~n，一共有m条操作，操作类型如下
// 1 x y k : 将区间[x, y]每个数加上k
// 2 x y   : 打印区间[x, y]的累加和
// 这就是普通线段树，请用标记永久化的方式实现
// 测试链接 : https://www.luogu.com.cn/problem/P3372
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100001;

long long arr[MAXN];
// 不是真实累加和，而是之前的任务中
// 不考虑被上方范围截住的任务，只考虑来到当前范围 或者 往下走的任务
// 累加和变成了什么
long long sum[MAXN << 2];
// 不再是懒更新信息，变成标记信息
long long addTag[MAXN << 2];

void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = arr[l];
    } else {
        int mid = (l + r) / 2;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
    addTag[i] = 0;
}

//到了目前的这个区间 考虑这次变化会给这个区间带来什么影响
void add(int jobl, int jobr, long long jobv, int l, int r, int i) {
    int a = max(jobl, l), b = min(jobr, r);//真正影响的范围
    sum[i] += jobv * (b - a + 1);
    //这个变化对sum的影响
    if (jobl <= l && r <= jobr) {
        addTag[i] += jobv;
        //区间被全包  那么addtag信息要改变
    } else {
        int mid = (l + r) / 2;
        if (jobl <= mid) {
            add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
    }
}

long long query(int jobl, int jobr, long long addHistory, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i] + addHistory * (r - l + 1);
        //区间被全包 那么就是sum信息加上上面被拦截的标签
    }
    int mid = (l + r) >> 1;
    long long ans = 0;
    if (jobl <= mid) {
        ans += query(jobl, jobr, addHistory + addTag[i], l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += query(jobl, jobr, addHistory + addTag[i], mid + 1, r, i << 1 | 1);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    build(1, n, 1);
    int op, jobl, jobr;
    long long jobv;
    for (int i = 1; i <= m; i++) {
        cin >> op;
        if (op == 1) {
            cin >> jobl >> jobr >> jobv;
            add(jobl, jobr, jobv, 1, n, 1);
        } else {
            cin >> jobl >> jobr;
            cout << query(jobl, jobr, 0, 1, n, 1) << "\n";
        }
    }
    return 0;
}
