// 园丁的烦恼，C++版
// 有n棵树，每棵树给定位置坐标(x, y)，接下来有m条查询，格式如下
// 查询 a b c d : 打印左上角(a, b)、右下角(c, d)的区域里有几棵树
// 0 <= n <= 5 * 10^5
// 1 <= m <= 5 * 10^5
// 0 <= 坐标值 <= 10^7
// 测试链接 : https://www.luogu.com.cn/problem/P2163
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题我最初的时候想用的是离散化 但是即使离散化也是无法完成的
//需要使用cdq分治  按照x分组  y重新排序
//这里由于没有使用到高级数据结构 为了维护时间复杂度  没有使用内置sort函数 
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500001 * 5;

// op == 1代表树木，x、y
// op == 2代表查询，x、y、效果v、查询编号q
struct Node {
   	int op, x, y, v, q;
};

bool NodeCmp(Node a, Node b) {
	if (a.x != b.x) {
		return a.x < b.x;
	}
	return a.op < b.op;
}

int n, m;

Node arr[MAXN];

int cnt = 0;

// 归并排序需要
Node tmp[MAXN];

// 问题的答案
int ans[MAXN];

void addTree(int x, int y) {
	arr[++cnt].op = 1;
	arr[cnt].x = x;
	arr[cnt].y = y;
}

void addQuery(int x, int y, int v, int q) {
	arr[++cnt].op = 2;
	arr[cnt].x = x;
	arr[cnt].y = y;
	arr[cnt].v = v;
	arr[cnt].q = q;
}

void merge(int l, int m, int r) {
	int p1, p2, tree = 0;
	for (p1 = l - 1, p2 = m + 1; p2 <= r; p2++) {
		while (p1 + 1 <= m && arr[p1 + 1].y <= arr[p2].y) {
			p1++;
			if (arr[p1].op == 1) {
				tree++;
			}
		}
		if (arr[p2].op == 2) {
			ans[arr[p2].q] += tree * arr[p2].v;
		}
	}
	//每次的复原操作其实都在merge开始做了  tree=0就是复原了  消去了原来的影响
	// 下面是经典归并的过程，为啥不直接排序了？
	// 因为没有用到高级数据结构，复杂度可以做到O(n * log n)
	// 那么就维持最好的复杂度，不用排序
	p1 = l;
	p2 = m + 1;
	int i = l;
	while (p1 <= m && p2 <= r) {
		tmp[i++] = arr[p1].y <= arr[p2].y ? arr[p1++] : arr[p2++];
	}
	while (p1 <= m) {
		tmp[i++] = arr[p1++];
	}
	while (p2 <= r) {
		tmp[i++] = arr[p2++];
	}
	for (i = l; i <= r; i++) {
		arr[i] = tmp[i];
	}
}

void cdq(int l, int r) {
	if (l == r) {
		return;
	}
	int mid = (l + r) / 2;
	cdq(l, mid);
	cdq(mid + 1, r);
	merge(l, mid, r);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1, x, y; i <= n; i++) {
		cin >> x >> y;
		addTree(x, y);
	}
	for (int i = 1, a, b, c, d; i <= m; i++) {
		cin >> a >> b >> c >> d;
		addQuery(c, d, 1, i);
		addQuery(a - 1, b - 1, 1, i);
		addQuery(a - 1, d, -1, i);
		addQuery(c, b - 1, -1, i);
	}
	sort(arr + 1, arr + cnt + 1, NodeCmp);
	cdq(1, cnt);
	for (int i = 1; i <= m; i++) {
		cout << ans[i] << '\n';
	}
	return 0;
}