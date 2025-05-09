// �����¼���C++��
// һ����n���ڵ㣬n-1������ߣ��߸�����ɫֵ�����нڵ�����һ����
// ����f(u, v) : ��u����v�ļ�·����ǡ�ó���һ�ε���ɫ������
// ��ӡ ��(u = 1..n) ��(v = u + 1..n) f(u, v) �Ľ��
// 1 <= ��ɫֵ <= n <= 2 * 10^5
// �������� : https://www.luogu.com.cn/problem/CF1681F
// �������� : https://codeforces.com/problemset/problem/1681/F
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
//�����Ҳ�ǰ��ձߵ���ɫ��������  ͬ��������Ϊ�Ǵ���
//����ĳ����ɫ�ı� �����������Ľ�����ʹ��  ���Ǽ�¼�Դ𰸵Ĺ��� 
//��Ϊһ�������ϲ�  ��ô�����ͬ��ɫ�ı߲���Ӱ��
//ֻ���������ɫ�ı߽���֮��  �ŻὫ�����ɫ�ı�ȫ����ӵ�ͼ��
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500001;
const int MAXT = 10000001;

int n, v;

int father[MAXN];
int siz[MAXN];
int rollback[MAXN][2];
int opsize = 0;

// ÿ����ɫӵ����Щ�ߵ��б�
int headc[MAXN];
int nxtc[MAXN];
int xc[MAXN];
int yc[MAXN];
int cntc = 0;

// ��ɫ���߶��������������б�
int headt[MAXN << 2];
int nxtt[MAXT];
int xt[MAXT];
int yt[MAXT];
int cntt = 0;

long long ans = 0;

void addEdgeC(int i, int x, int y) {
   nxtc[++cntc] = headc[i];
   xc[cntc] = x;
   yc[cntc] = y;
   headc[i] = cntc;
}

void addEdgeS(int i, int x, int y) {
   nxtt[++cntt] = headt[i];
   xt[cntt] = x;
   yt[cntt] = y;
   headt[i] = cntt;
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
       addEdgeS(i, jobx, joby);
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

void dfs(int l, int r, int i) {
   int unionCnt = 0;
   for (int ei = headt[i]; ei > 0; ei = nxtt[ei]) {
       Union(xt[ei], yt[ei]);
       unionCnt++;
   }
   if (l == r) {
        //�����Ҷ�ڵ� ��ôͳ�ƶԴ𰸵Ĺ���
       for (int ei = headc[l], fx, fy; ei > 0; ei = nxtc[ei]) {
           fx = find(xc[ei]);
           fy = find(yc[ei]);
           ans += 1LL * siz[fx] * siz[fy];
       }
   } else {
       int mid = (l + r) >> 1;
       dfs(l, mid, i << 1);
       dfs(mid + 1, r, i << 1 | 1);
   }
   for (int k = 1; k <= unionCnt; k++) {
       undo();
   }
}

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   cin >> n;
   v = n;
   for (int i = 1, x, y, c; i < n; i++) {
       cin >> x >> y >> c;
       addEdgeC(c, x, y);
       //��ɫΪc�ı� ��1~c-1  ��  c+1~v�ϴ���
       if (c > 1) {
           add(1, c - 1, x, y, 1, v, 1);
       }
       if (c < v) {
           add(c + 1, v, x, y, 1, v, 1);
       }
   }
   for (int i = 1; i <= n; i++) {
       father[i] = i;
       siz[i] = 1;
   }
   dfs(1, v, 1);
   cout << ans << '\n';
   return 0;
}