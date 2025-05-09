// ����Ϳɫ��C++��
// һ����n���㣬����m������ߣ�һ��ʼÿ��������ɫ��һ����k����ɫ
// �Ϸ�״̬�Ķ���Ϊ��������Ⱦ��k����ɫ�е��κ�һ����ɫ�ıߣ�ͼ����һ�Ŷ���ͼ
// һ����q��������ÿ��������ʽ����
// ���� e c : ��e���ߣ�����ҪͿ��c��ɫ
//           ���ִ�д˲���֮������ͼ���ǺϷ�״̬����ôִ�в���ӡ"YES"
//           ���ִ�д˲���֮������ͼ�����ǺϷ�״̬����ô��ִ�в���ӡ"NO"
// 1 <= n��m��q <= 5 * 10^5    1 <= k <= 50
// �������� : https://www.luogu.com.cn/problem/CF576E
// �������� : https://codeforces.com/problemset/problem/576/E
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
//�����������ĵط�����������߸���ɫ���²��Ϸ� ��ô��Ҫ��������ԭ������ɫ  ���ܶ���
//�������ǽ��ߵ�ʱ�� ������ֱ�ӽ�xy��Ϊ������  ���ǽ��޸ı�Ŵ���
//����������ɫ�Ĳ��� ��ô������޸Ĳ�������ɫ�ĳ���һ�ε���ɫ  ��������Ҫ��
//����֮�� ��Ҫά�������ɫ���鼯 find�Ⱥ���ҲҪ��color���β�
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500001;
const int MAXK = 51;
const int MAXT = 10000001;

int n, m, k, q;

int u[MAXN];
int v[MAXN];

//��¼������Ϣ
int e[MAXN];//�޸ĵıߵı��
int c[MAXN];//�޸ĺ����ɫ  ����޷��޸ģ����޸ĺ󲻺Ϸ��� ��ô����ᷢ���仯
int post[MAXN];//���Դ��ڵķ�Χ  ����һ���޷�����ĵ��λ��

//�ɳ������鼯 ������ɫά��������鼯
int father[MAXK][MAXN << 1];
int siz[MAXK][MAXN << 1];
int rollback[MAXN << 1][3];
int opsize = 0;

//�����Ϲ��ŵĲ����� xy  ���ǲ����ı��
//��Ϊ���������ݿ��ܻᷢ���仯
int head[MAXN << 2];
int nxt[MAXT];
int qid[MAXT];
int cnt = 0;

//��¼��������ǰ��ʲô��ɫ��
int lastColor[MAXN];

bool ans[MAXN];

void addEdge(int i, int qi) {
   nxt[++cnt] = head[i];
   qid[cnt] = qi;
   head[i] = cnt;
}

int find(int color, int i) {
   while (i != father[color][i]) {
       i = father[color][i];
   }
   return i;
}

void Union(int color, int x, int y) {
   int fx = find(color, x);
   int fy = find(color, y);
   if (siz[color][fx] < siz[color][fy]) {
       int tmp = fx;
       fx = fy;
       fy = tmp;
   }
   father[color][fy] = fx;
   siz[color][fx] += siz[color][fy];
   rollback[++opsize][0] = color;
   rollback[opsize][1] = fx;
   rollback[opsize][2] = fy;
}

void undo() {
   int color = rollback[opsize][0];
   int fx = rollback[opsize][1];
   int fy = rollback[opsize--][2];
   father[color][fy] = fy;
   siz[color][fx] -= siz[color][fy];
}

void add(int jobl, int jobr, int jobq, int l, int r, int i) {
   if (jobl <= l && r <= jobr) {
       addEdge(i, jobq);
   } else {
       int mid = (l + r) >> 1;
       if (jobl <= mid) {
           add(jobl, jobr, jobq, l, mid, i << 1);
       }
       if (jobr > mid) {
           add(jobl, jobr, jobq, mid + 1, r, i << 1 | 1);
       }
   }
}

void dfs(int l, int r, int i) {
   int unionCnt = 0;
   int color, x, y, xn, yn, fx, fy, fxn, fyn;
   for (int ei = head[i]; ei > 0; ei = nxt[ei]) {
       color = c[qid[ei]];
       x = u[e[qid[ei]]];
       y = v[e[qid[ei]]];
       xn = x + n;
       yn = y + n;
       fx = find(color, x);
       fy = find(color, y);
       fxn = find(color, xn);
       fyn = find(color, yn);
       if (fx != fyn) {
           Union(color, fx, fyn);
           unionCnt++;
       }
       if (fy != fxn) {
           Union(color, fy, fxn);
           unionCnt++;
       }
   }
   if (l == r) {
        //����Ҷ�ڵ� ��ѯ�Ƿ�����޸�
       if (find(c[l], u[e[l]]) == find(c[l], v[e[l]])) {
            //��������ߵ���ɫ���ܱ仯 ��ô�ͽ�������ɫ�ĳ���һ�ε���ɫ
           ans[l] = false;
           c[l] = lastColor[e[l]];
       } else {
            //������һ����������ɫ���ó������ɫ
           ans[l] = true;
           lastColor[e[l]] = c[l];
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

void prepare() {
   for (int color = 1; color <= k; color++) {
       for (int i = 1; i <= n; i++) {
           father[color][i] = i;
           father[color][i + n] = i + n;
           siz[color][i] = 1;
           siz[color][i + n] = 1;
       }
   }
   for (int i = 1; i <= m; i++) {
       post[i] = q;
   }
   //����Ӻ���ǰ����
   for (int i = q; i >= 1; i--) {
       if (i + 1 <= post[e[i]]) {
           add(i + 1, post[e[i]], i, 1, q, 1);
       }
       post[e[i]] = i;
   }
}

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   cin >> n >> m >> k >> q;
   for (int i = 1; i <= m; i++) {
       cin >> u[i] >> v[i];
   }
   for (int i = 1; i <= q; i++) {
       cin >> e[i] >> c[i];
   }
   prepare();
   dfs(1, q, 1);
   for (int i = 1; i <= q; i++) {
       if (ans[i]) {
           cout << "YES" << "\n";
       } else {
           cout << "NO" << "\n";
       }
   }
   return 0;
}