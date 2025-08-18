// 维护数列(C++版)
// 初始时给定一个数列，实现如下六种操作
// INSERT posi tot ...  : 在第posi个数字之后，插入长度为tot的数组，由...代表
// DELETE posi tot      : 从第posi个数字开始，删除长度为tot的部分
// MAKE-SAME posi tot c : 从第posi个数字开始，长度为tot的部分，值都设置成c
// REVERSE posi tot     : 从第posi个数字开始，翻转长度为tot的部分
// GET-SUM posi tot     : 从第posi个数字开始，查询长度为tot的部分的累加和
// MAX-SUM              : 查询整个数列中，非空子数组的最大累加和
// 任何时刻输入保证至少有一个数字在数列中，并且所有操作都合法
// 插入数字总数很多，但是任何时刻数列中最多有5 * 10^5个数，使用总空间要和该数量有关
// 测试链接 : https://www.luogu.com.cn/problem/P2042
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题最难的操作就是MAX-SUM  这个需要线段树去维护
//并且即使是线段树  这个也不是很好维护的信息  需要维护每个节点的pre suf all
//然后其实也不是特别难
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
const int INF = 1000000001;

int head = 0;
int arr[MAXN];
int num[MAXN];
int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
// 这个数组里拿空间编号  因为空间限制
int space[MAXN], si;
// 维护区间累加和信息
int sum[MAXN];
// 维护区间子数组最大累加和信息，要求不能为空
int all[MAXN];
// 维护区间前缀最大累加和信息，可以空
int pre[MAXN];
// 维护区间后缀最大累加和信息，可以空
int suf[MAXN];
// 懒更新信息，区间是否重新设了值
bool update[MAXN];
// 懒更新信息，如果区间重新设了值，设置成了什么
int change[MAXN];
// 懒更新信息，区间是否发生了翻转
bool rev[MAXN];

void up(int i) {
    int l = ls[i], r = rs[i];
    sz[i] = sz[l] + sz[r] + 1;
    sum[i] = sum[l] + sum[r] + num[i];
    all[i] = max(max(all[l], all[r]), suf[l] + num[i] + pre[r]);
    pre[i] = max(pre[l], sum[l] + num[i] + pre[r]);
    suf[i] = max(suf[r], suf[l] + num[i] + sum[r]);
}

int lr(int i) {
    return rs[fa[i]] == i ? 1 : 0;
}

void rotate(int i) {
    int f = fa[i], g = fa[f], soni = lr(i), sonf = lr(f);
    if (soni == 1) {
        rs[f] = ls[i];
        if (rs[f] != 0) {
            fa[rs[f]] = f;
        }
        ls[i] = f;
    } else {
        ls[f] = rs[i];
        if (ls[f] != 0) {
            fa[ls[f]] = f;
        }
        rs[i] = f;
    }
    if (g != 0) {
        if (sonf == 1) {
            rs[g] = i;
        } else {
            ls[g] = i;
        }
    }
    fa[f] = i;
    fa[i] = g;
    up(f);
    up(i);
}

void splay(int i, int goal) {
    while (fa[i] != goal) {
        int f = fa[i], g = fa[f];
        if (g != goal) {
            if (lr(i) == lr(f)) {
                rotate(f);
            } else {
                rotate(i);
            }
        }
        rotate(i);
    }
    if (goal == 0) {
        head = i;
    }
}

void setValue(int i, int val) {
    if (i != 0) {
        update[i] = true;
        change[i] = val;
        num[i] = val;
        sum[i] = sz[i] * val;
        all[i] = max(sum[i], val);
        pre[i] = max(sum[i], 0);
        suf[i] = max(sum[i], 0);
    }
}

void setReverse(int i) {
    if (i != 0) {
        swap(pre[i], suf[i]);
        rev[i] ^= 1;
    }
}

void down(int i) {
    if (update[i]) {
        setValue(ls[i], change[i]);
        setValue(rs[i], change[i]);
        update[i] = false;
    }
    if (rev[i]) {
        swap(ls[i], rs[i]);
        setReverse(ls[i]);
        setReverse(rs[i]);
        rev[i] = false;
    }
}

int init(int val) {
    int i = space[si--];
    sz[i] = 1;
    num[i] = sum[i] = all[i] = val;
    pre[i] = suf[i] = max(val, 0);
    fa[i] = ls[i] = rs[i] = 0;
    update[i] = rev[i] = false;
    return i;
}

int build(int l, int r) {
    int mid = (l + r) / 2;
    int root = init(arr[mid]);
    if (l < mid) {
        ls[root] = build(l, mid - 1);
        fa[ls[root]] = root;
    }
    if (mid < r) {
        rs[root] = build(mid + 1, r);
        fa[rs[root]] = root;
    }
    up(root);
    return root;
}

int find(int rank) {
    int i = head;
    while (i != 0) {
        down(i);
        if (sz[ls[i]] + 1 == rank) {
            return i;
        } else if (sz[ls[i]] >= rank) {
            i = ls[i];
        } else {
            rank -= sz[ls[i]] + 1;
            i = rs[i];
        }
    }
    return 0;
}

void insert(int rank, int n) {
    if (rank == 0) {
        head = build(1, n);
    } else {
        int l = find(rank);
        int r = find(rank + 1);
        splay(l, 0);
        splay(r, l);
        ls[r] = build(1, n);
        fa[ls[r]] = r;
        up(r);
        up(l);
    }
}

void recycle(int i) {
    if (i != 0) {
        space[++si] = i;
        recycle(ls[i]);
        recycle(rs[i]);
    }
}

void remove(int rank, int n) {
    int l = find(rank - 1);
    int r = find(rank + n);
    splay(l, 0);
    splay(r, l);
    recycle(ls[r]);
    ls[r] = 0;
    up(r);
    up(l);
}

void reset(int rank, int n, int val) {
    int l = find(rank - 1);
    int r = find(rank + n);
    splay(l, 0);
    splay(r, l);
    setValue(ls[r], val);
    up(r);
    up(l);
}

void reverse(int rank, int n) {
    int l = find(rank - 1);
    int r = find(rank + n);
    splay(l, 0);
    splay(r, l);
    setReverse(ls[r]);
    up(r);
    up(l);
}

int querySum(int rank, int n) {
    int l = find(rank - 1);
    int r = find(rank + n);
    splay(l, 0);
    splay(r, l);
    return sum[ls[r]];
}

int queryMax() {
    return all[head];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    si = MAXN - 1;
    for (int i = 1; i <= si; i++) {
        space[i] = i;
    }
    arr[1] = arr[n + 2] = all[0] = -INF;
    for (int i = 1, j = 2; i <= n; i++, j++) {
        cin >> arr[j];
    }
    insert(0, n + 2);
    string op;
    for (int i = 0; i < m; i++) {
        cin >> op;
        if (op == "MAX-SUM") {
            cout << queryMax() << endl;
        } else {
            int pos, len, c;
            cin >> pos >> len;
            pos++;
            if (op == "INSERT") {
                for (int j = 1; j <= len; j++) {
                    cin >> arr[j];
                }
                insert(pos, len);
            } else if (op == "DELETE") {
                remove(pos, len);
            } else if (op == "MAKE-SAME") {
                cin >> c;
                reset(pos, len, c);
            } else if (op == "REVERSE") {
                reverse(pos, len);
            } else if (op == "GET-SUM") {
                cout << querySum(pos, len) << endl;
            }
        }
    }
    return 0;
}