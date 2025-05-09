// �߶�������ģ���⣬C++��
// һ����n���ڵ㣬һ����m��������ÿ���������������������е�һ��
// ���� 0 x y : ��x�͵�y֮��һ��û�бߣ���������һ����
// ���� 1 x y : ��x�͵�y֮��һ�����ڱߣ�����ɾ��������
// ���� 2 x y : ��ѯ��x�͵�y�Ƿ���ͨ
// 1 <= n <= 5000
// 1 <= m <= 500000
// ��ǿ�����ߣ��������ߴ���
// �������� : https://loj.ac/p/121
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
// ����������ֵ
const int MAXN = 5001;
// �����������ֵ
const int MAXM = 500001;
// �����������ֵ
const int MAXT = 5000001;

int n, m;

// ��������op���˵�u���˵�v
int op[MAXM];
int u[MAXM];
int v[MAXM];

// last[x][y] : ��x�͵�y�ıߣ��ϴγ��ֵ�ʱ���
int last[MAXN][MAXN];

// �ɳ������鼯
int father[MAXN];
int siz[MAXN];
int rollback[MAXN][2];
int opsize = 0;

// �߶���ÿ������ӵ����Щ������б���ʽǰ���Ǳ�ʾ
int head[MAXM << 2];
int nxt[MAXT];
int tox[MAXT];
int toy[MAXT];//ע�� ��Ϊÿ���ڵ�����ҵ���һ���� ������ x��y
int cnt = 0;

// ans[i]Ϊ��i�������Ĵ𰸣�ֻ�в�ѯ�������д�
bool ans[MAXM];

void addEdge(int i, int x, int y) {
   nxt[++cnt] = head[i];
   tox[cnt] = x;
   toy[cnt] = y;
   head[i] = cnt;
}

//�ɳ������鼯  û�б�ƽ������
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

//��jobl~jobr����߶��������������е����[jobx,joby] ��ʾjobx��joby�������ڴ������ڴ���һ������
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

//dfs������
void dfs(int l, int r, int i) {
   int unionCnt = 0;//��¼����ڵ��Ͻ����˶��ٴκϲ�����  �������ĳ�������
   for (int ei = head[i], x, y, fx, fy; ei > 0; ei = nxt[ei]) {
       x = tox[ei];
       y = toy[ei];
       fx = find(x);
       fy = find(y);
       if (fx != fy) {
           Union(fx, fy);
           unionCnt++;
       }
   }
   if (l == r) {
		//��ÿ��Ҷ�ڵ�ͳ�ƴ� 
       if (op[l] == 2) {
           ans[l] = find(u[l]) == find(v[l]);
       }
   } else {
       int mid = (l + r) >> 1;
       dfs(l, mid, i << 1);
       dfs(mid + 1, r, i << 1 | 1);
   }
   for (int j = 1; j <= unionCnt; j++) {
       undo();
   }
}

//�������е���Ϣ
void prepare() {
   for (int i = 1; i <= n; i++) {
       father[i] = i;
       siz[i] = 1;
   }
   for (int i = 1, t, x, y; i <= m; i++) {
       t = op[i];
       x = u[i];
       y = v[i];
       if (t == 0) {
			//���������
           last[x][y] = i;
       } else if (t == 1) {
			//�����ɾ����  ��ô������ζ���� last~i-1 ���ʱ����� x��y���ڱߵĹ�ϵ
           add(last[x][y], i - 1, x, y, 1, m, 1);
           last[x][y] = 0;
       }
   }
   for (int x = 1; x <= n; x++) {
       for (int y = x + 1; y <= n; y++) {
			//��ʾֱ�����û�б�ɾ���ı�  ˵�����Ǵ����һ�����뿪ʼһֱ��Ч�����
           if (last[x][y] != 0) {
               add(last[x][y], m, x, y, 1, m, 1);
           }
       }
   }
}

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   cin >> n >> m;
   for (int i = 1, t, x, y; i <= m; i++) {
       cin >> t >> x >> y;
       op[i] = t;
       u[i] = min(x, y);
       v[i] = max(x, y);
   }
   prepare();
   dfs(1, m, 1);
   for (int i = 1; i <= m; i++) {
       if (op[i] == 2) {
           if (ans[i]) {
               cout << "Y" << "\n";
           } else {
               cout << "N" << "\n";
           }
       }
   }
   return 0;
}