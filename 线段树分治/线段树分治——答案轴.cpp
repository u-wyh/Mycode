// ��Сmex��������C++��
// ����n���㣬m���ߵ�������ͨͼ�����б�Ȩ
// ��Ȼ������S��mex����Ϊ����С�ġ�û�г�����S�е���Ȼ��
// ������Ҫ���һ�����ͼ����������ʹ�����Ȩ���ϵ�mex������С
// �Ա�����˵��ע��0����Ȼ��
// 1 <= n <= 10^6
// 1 <= m <= 2 * 10^6
// 0 <= ��Ȩ <= 10^5
// �������� : https://www.luogu.com.cn/problem/P5631
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
//������ǽ��߶������ɴ���  ��ÿ���ڵ���һ���𰸵Ĳ�ѯ ������˵����˵��
//�жϱ�ȨΪi���ǲ������յĴ�  ��0��ʼ����  
//�жϵķ�����ɾ����ȨΪi�����б�  ����ͼ�Ƿ���ͨ  �����ͨ ����ȥ��һ����Ȩ  ������Ǵ�
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000001;
const int MAXV = 100001;
const int MAXT = 30000001;

int n, m, v;

//�ɳ������鼯
int father[MAXN];
int siz[MAXN];
int rollback[MAXN][2];
int opsize = 0;

int head[MAXV << 2];
int nxt[MAXT];
int tox[MAXT];
int toy[MAXT];
int cnt = 0;

int part;//��¼��ǰ����ͼ�ж��ٸ���ͨ�� ���ֻ��һ�� ��ô������ͨ��

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
       //�����ߴ����� 0~w-1 �� w+1~n
       if (w > 0) {
           add(0, w - 1, x, y, 0, v, 1);
       }
       add(w + 1, v, x, y, 0, v, 1);
   }
   part = n;
   cout << dfs(0, v, 1) << '\n';
   return 0;
}