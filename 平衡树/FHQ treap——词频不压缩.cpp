// FHQ-Treap，不用词频压缩，FHQ-Treap最常规的实现，C++版
// 实现一种结构，支持如下操作，要求单次调用的时间复杂度O(log n)
// 1，增加x，重复加入算多个词频
// 2，删除x，如果有多个，只删掉一个
// 3，查询x的排名，x的排名为，比x小的数的个数+1
// 4，查询数据中排名为x的数
// 5，查询x的前驱，x的前驱为，小于x的数中最大的数，不存在返回整数最小值
// 6，查询x的后继，x的后继为，大于x的数中最小的数，不存在返回整数最大值
// 所有操作的次数 <= 10^5
// -10^7 <= x <= +10^7
// 测试链接 : https://www.luogu.com.cn/problem/P3369
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//词频不压缩的一个巨大优势是在删除和加入节点时非常方便
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;
int head = 0;
int cnt = 0;
int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int size[MAXN];
double priority[MAXN];

//没有词频压缩  所以出现次数就是1
void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + 1;
}

void split(int l, int r, int i, int num) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        if (key[i] <= num) {
            rs[l] = i;
            split(i, r, rs[i], num);
        } else {
            ls[r] = i;
            split(l, i, ls[i], num);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

//没有词频压缩  直接就是新增节点
void add(int num) {
    split(0, 0, head, num);
    key[++cnt] = num;
    size[cnt] = 1;
    priority[cnt] = (double)rand() / RAND_MAX;
    head = merge(merge(rs[0], cnt), ls[0]);
}

//删除节点的时候 是将树按照num分裂  然后将<=num 的按照 num-1 分裂
//将那么 >num-1 的树头结点一定是num  只要将这个节点忽略就是删除节点
void remove(int num) {
    split(0, 0, head, num);
    int lm = rs[0];
    int r = ls[0];
    split(0, 0, lm, num - 1);
    int l = rs[0];
    int m = ls[0];
    head = merge(merge(l, merge(ls[m], rs[m])), r);
}

int getRank(int num) {
    split(0, 0, head, num - 1);
    int ans = size[rs[0]] + 1;
    head = merge(rs[0], ls[0]);
    return ans;
}

int index(int i, int x) {
    if (size[ls[i]] >= x) {
        return index(ls[i], x);
    } else if (size[ls[i]] + 1 < x) {
        return index(rs[i], x - size[ls[i]] - 1);
    } else {
        return key[i];
    }
}

int index(int x) {
    return index(head, x);
}

int pre(int i, int num) {
    if (i == 0) {
        return INT_MIN;
    }
    if (key[i] >= num) {
        return pre(ls[i], num);
    } else {
        return max(key[i], pre(rs[i], num));
    }
}

int pre(int num) {
    return pre(head, num);
}

int post(int i, int num) {
    if (i == 0) {
        return INT_MAX;
    }
    if (key[i] <= num) {
        return post(rs[i], num);
    } else {
        return min(key[i], post(ls[i], num));
    }
}

int post(int num) {
    return post(head, num);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    int n;
    cin >> n;
    for (int i = 1, op, x; i <= n; i++) {
        cin >> op >> x;
        if (op == 1) {
            add(x);
        } else if (op == 2) {
            remove(x);
        } else if (op == 3) {
            cout << getRank(x) << endl;
        } else if (op == 4) {
            cout << index(x) << endl;
        } else if (op == 5) {
            cout << pre(x) << endl;
        } else {
            cout << post(x) << endl;
        }
    }
    return 0;
}