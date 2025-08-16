// FHQ-Treap，使用词频压缩，C++版
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
//这有一个要注意的是：在分裂操作的时候 小于num的所有数值放在0的右子树上  大于num的放在0的左子树上
//这样做的原因是对于每个节点上的数字 如果小于num  我们就会把它放在小于num的那颗子树上  但对于这个子树而言 当前来到的点一定是最大的  它是右儿子
//为了保证程序的正确性 我们把遍历到的小于num的节点全都放在此时小于num的子树的右边  对于0节点 我们也保持这个习惯
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int head = 0;
int cnt = 0;
int key[MAXN];
int key_count[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
double priority[MAXN];

void up(int i) {
    sz[i] = sz[ls[i]] + sz[rs[i]] + key_count[i];
}

//根据值分裂树
//这里当前来到了i节点  <=num的目前到达的节点是l  >num的目前到达的节点是r
//分裂过程中左右树的头结点其实并不重要  重要的是当前来到的节点
void split(int l, int r, int i, int num) {
    if (i == 0) {
        //表示已经无路可走了
        rs[l] = ls[r] = 0;
        //表示两棵树已经完成  那么将最后一个节点设置为0
    } else {
        if (key[i] <= num) {
            //当前值小于num  使用右节点
            //<=num的树即将来到的节点是  之前节点的右节点
            //并且要将节点i设置为 l的右节点
            //继续前往下一个节点分裂树
            //<=num的目前到达的节点  更新为i  >num的不变  来到的节点是i的右节点
            rs[l] = i;
            split(i, r, rs[i], num);
        } else {
            ls[r] = i;
            split(l, i, ls[i], num);
        }
        up(i);
    }
}

//合并两棵树
//l表示左树当前来到的头结点 r表示右树当前来到的头结点
//返回的是以l和r为头的左右树合并后的头结点
int merge(int l, int r) {
    if (l == 0 || r == 0) {
        //只要有一个节点是0  那么就不需要继续进行
        //直接返回l+r  因为肯定有一个是0  相当于返回的就是l或者r
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        //如果左树当前节点的优先级大  那么左树当前头结点往右边划
        //此时左树的右节点应该是  以原来的右节点为头的左树  和   以右树当前节点为头的右树  合并后的头结点
        //并且一定可以知道l和r合并后的头结点是l
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

//返回以i为首的子树上  权值是num的节点编号  没有找到返回0
int find(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] == num) {
        return i;
    } else if (key[i] > num) {
        return find(ls[i], num);
    } else {
        return find(rs[i], num);
    }
}

//改变词频  加上change
void changeCount(int i, int num, int change) {
    if (key[i] == num) {
        key_count[i] += change;
    } else if (key[i] > num) {
        changeCount(ls[i], num, change);
    } else {
        changeCount(rs[i], num, change);
    }
    up(i);
}

void add(int num) {
    if (find(head, num) != 0) {
        changeCount(head, num, 1);
    } else {
        split(0, 0, head, num);
        //首先将树按照num分为 <=num  和 >num的
        //right[0] 是<num  头结点  因为没有num
        //left[0]  是>num  头结点
        key[++cnt] = num;
        key_count[cnt] = sz[cnt] = 1;
        priority[cnt] = (double)rand() / RAND_MAX;
        //生成一个新节点  将该节点与<num的树合并  然后和>num的树合并
        head = merge(merge(rs[0], cnt), ls[0]);
    }
}

void remove(int num) {
    int i = find(head, num);
    if (i != 0) {
        if (key_count[i] > 1) {
            changeCount(head, num, -1);
        } else {
            //必须要删除节点
            split(0, 0, head, num);
            //将树按照num分裂  得到左树和右数节点
            //将<=num的树按照  num-1  分裂   一定会出现 <=num-1  和 num
            //此时将  <=num-1  和 >num 的树合并即可
            int lm = rs[0];
            int r = ls[0];
            split(0, 0, lm, num - 1);
            int l = rs[0];
            head = merge(l, r);
        }
    }
}

int small(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] >= num) {
        return small(ls[i], num);
    } else {
        return sz[ls[i]] + key_count[i] + small(rs[i], num);
    }
}

int getRank(int num) {
    return small(head, num) + 1;
}

int index(int i, int x) {
    if (sz[ls[i]] >= x) {
        return index(ls[i], x);
    } else if (sz[ls[i]] + key_count[i] < x) {
        return index(rs[i], x - sz[ls[i]] - key_count[i]);
    }
    return key[i];
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