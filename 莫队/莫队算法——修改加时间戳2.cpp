#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 2e6, M = 1e6 + 10;

struct Query {
    int id, l, r, t;
}q[N];
struct Modify {
    int p, c;
}c[N];
int n, m, w[N], cnt[M];
int mq, mc, len;
int ans[N];

int get(int x) {
    return x / len;
}

bool cmp(const Query& a, const Query& b) {
    int al = get(a.l), bl = get(b.l);
    int ar = get(a.r), br = get(b.r);
    if (al != bl) return al < bl;
    if (ar != br) return ar < br;
    return a.t < b.t;
}

void add(int x, int& res) {
    if (!cnt[x]) res++;
    cnt[x]++;
}

void del(int x, int& res) {
    cnt[x]--;
    if (!cnt[x]) res--;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    for (int i = 0; i < m; i++) {
        char op[2];
        int a, b;
        scanf("%s%d%d", op, &a, &b);
        if (*op == 'Q') mq++, q[mq] = {mq, a, b, mc};
        else c[++mc] = {a, b};
    }
    len = cbrt((double)n * max(1, mc)) + 1;
    sort(q + 1, q + mq + 1, cmp);
    int res = 0;

    for (int i = 0, j = 1, t = 0, k = 1; k <= mq; k++) {
        int id = q[k].id, l = q[k].l, r = q[k].r, tm = q[k].t;
        while (i < r) add(w[++i], res);
        while (i > r) del(w[i--], res);
        while (j < l) del(w[j++], res);
        while (j > l) add(w[--j], res);
        while (t < tm) {
            t++;
            int p = c[t].p;
            if (p >= j && p <= i)
            {
                del(w[p], res);
                add(c[t].c, res);
            }
            swap(w[p], c[t].c);
        }
        while (t > tm) {
            int p = c[t].p;
            if (p >= j && p <= i)
            {
                del(w[p], res);
                add(c[t].c, res);
            }
            swap(w[p], c[t].c);
            t--;
        }
        ans[id] = res;
    }
    for (int i = 1; i <= mq; i++) cout << ans[i] << endl;
    return 0;
}
