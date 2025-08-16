// 文艺平衡树，FHQ-Treap实现范围翻转，C++版本
// 长度为n的序列，下标从1开始，一开始序列为1, 2, ..., n
// 接下来会有k个操作，每个操作给定l，r，表示从l到r范围上的所有数字翻转
// 做完k次操作后，从左到右打印所有数字
// 1 <= n, k <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P3391
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//主要运用到了懒更新思想
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int head = 0;
int cnt = 0;
int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
double priority[MAXN];
bool rev[MAXN];//懒更新信息
int ans[MAXN];
int ansi;

void up(int i) {
    sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
}

//懒更新的下发
void down(int i) {
    if (rev[i]) {
        swap(ls[i], rs[i]);
        rev[ls[i]] ^= 1;
        rev[rs[i]] ^= 1;
        rev[i] = false;
    }
}

//这道题也是根据排名分裂
//这道题利用的也是位置信息 所以使用排名
//使用中序遍历得到答案
void split(int l, int r, int i, int rank) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        down(i);
        if (sz[ls[i]] + 1 <= rank) {
            rs[l] = i;
            split(i, r, rs[i], rank - sz[ls[i]] - 1);
        } else {
            ls[r] = i;
            split(l, i, ls[i], rank);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        down(l);//下发懒信息
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        down(r);
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

void inorder(int i) {
    if (i != 0) {
        down(i);
        inorder(ls[i]);
        ans[++ansi] = key[i];
        inorder(rs[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        key[++cnt] = i;
        sz[cnt] = 1;
        priority[cnt] = (double)rand() / RAND_MAX;
        head = merge(head, cnt);
    }
    for (int i = 1, x, y, l, m, lm, r; i <= k; i++) {
        cin >> x >> y;
        split(0, 0, head, y);
        lm = rs[0];//表示<=y的树的头结点
        r = ls[0];//表示>y的树的头结点
        split(0, 0, lm, x - 1);
        l = rs[0];//表示<=x-1的树的头结点
        m = ls[0];//表示>=x的树的头结点
        rev[m] ^= 1;
        head = merge(merge(l, m), r);
    }
    ansi = 0;
    inorder(head);
    for (int i = 1; i <= ansi; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}