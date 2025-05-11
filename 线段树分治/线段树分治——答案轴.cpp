// 最小mex生成树，C++版
// 给定n个点，m条边的无向连通图，边有边权
// 自然数集合S的mex含义为：最小的、没有出现在S中的自然数
// 现在你要求出一个这个图的生成树，使得其边权集合的mex尽可能小
// 对本题来说，注意0是自然数
// 1 <= n <= 10^6
// 1 <= m <= 2 * 10^6
// 0 <= 边权 <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P5631
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题是将线段树做成答案轴  即每个节点是一个答案的查询 具体来说就是说：
//判断边权为i的是不是最终的答案  从0开始尝试  
//判断的方法是删除边权为i的所有边  整个图是否联通  如果联通 继续去下一个点权  否则就是答案
//这里我们要注意一点 就是线段树分治算法节点上的信息都是加操作信息  没有删除操作信息
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000001;
const int MAXV = 100001;
const int MAXT = 30000001;

int n, m, v;

//可撤销并查集
int father[MAXN];
int siz[MAXN];
int rollback[MAXN][2];
int opsize = 0;

int head[MAXV << 2];
int nxt[MAXT];
int tox[MAXT];
int toy[MAXT];
int cnt = 0;

int part;//记录当前整个图有多少个联通块 如果只有一个 那么就是联通的

void addEdge(int i, int x, int y) {
    nxt[++cnt] = head[i];
    tox[cnt] = x;
    toy[cnt] = y;
    head[i] = cnt;
}

int find(int i) {
    while (i != father[i]) {
        i = father[i];
    }
    return i;
}

void Union(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (siz[fx] < siz[fy]) {
        int tmp = fx;
        fx = fy;
        fy = tmp;
    }
    father[fy] = fx;
    siz[fx] += siz[fy];
    rollback[++opsize][0] = fx;
    rollback[opsize][1] = fy;
}

void undo() {
   int fx = rollback[opsize][0];
   int fy = rollback[opsize--][1];
   father[fy] = fy;
   siz[fx] -= siz[fy];
}

void add(int jobl, int jobr, int jobx, int joby, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        addEdge(i, jobx, joby);
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            add(jobl, jobr, jobx, joby, l, mid, i << 1);
        }
        if (jobr > mid) {
            add(jobl, jobr, jobx, joby, mid + 1, r, i << 1 | 1);
        }
    }
}

int dfs(int l, int r, int i) {
    int unionCnt = 0;
    for (int ei = head[i]; ei > 0; ei = nxt[ei]) {
        int fx = find(tox[ei]);
        int fy = find(toy[ei]);
        if (fx != fy) {
            Union(fx, fy);
            part--;
            unionCnt++;
        }
    }
    int ans = -1;
    if (l == r) {
        if (part == 1) {
            ans = l;
        }
    } else {
        int mid = (l + r) >> 1;
        ans = dfs(l, mid, i << 1);
        if (ans == -1) {
            ans = dfs(mid + 1, r, i << 1 | 1);
        }
    }
    for (int k = 1; k <= unionCnt; k++) {
        undo();
        part++;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    v = MAXV;
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        siz[i] = 1;
    }
    for (int i = 1; i <= m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        //这条边存在于 0~w-1 和 w+1~n
        if (w > 0) {
            add(0, w - 1, x, y, 0, v, 1);
        }
        add(w + 1, v, x, y, 0, v, 1);
    }
    part = n;
    cout << dfs(0, v, 1) << '\n';
    return 0;
}