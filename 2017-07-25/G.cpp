#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int ui;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
//-------
const int N = 1e5 + 7;
int n, m, q, rt, tot, w[N], f[N], id[N], r[N], L[N], R[N], Z[N], tree[N];
map<int, int> lg2;
vector<pair<int, int> > e[N];
struct SegTree {
#define ls ((t)<<1)
#define rs ((t)<<1|1)
    int add[N << 2], val[N << 2];
    inline void up(int t) {
        val[t] = max(val[ls], val[rs]);
    }
    inline void down(int t) {
        add[ls] += add[t], val[ls] += add[t];
        add[rs] += add[t], val[rs] += add[t];
        add[t] = 0;
    }
    void build(int t, int l, int r) {
        add[t] = 0;
        if (l == r) {
            val[t] = w[id[l]];
        } else {
            int z = (l + r) >> 1;
            build(ls, l, z), build(rs, z + 1, r);
            up(t);
        }
    }
    void upd(int t, int l, int r, int L, int R, int V) {
        if (L <= l && r <= R) {
            add[t] += V, val[t] += V;
            return ;
        }
        down(t);
        int z = (l + r) >> 1;
        if (L <= z) upd(ls, l, z, L, R, V);
        if (R > z) upd(rs, z + 1, r, L, R, V);
        up(t);
    }
    int qry(int t, int l, int r, int L, int R) {
        if (L <= l && r <= R)
            return val[t];
        down(t);
        int z = (l + r) >> 1, ret = -1e9;
        if (L <= z) ret = max(ret, qry(ls, l, z, L, R));
        if (R > z) ret = max(ret, qry(rs, z + 1, r, L, R));
        up(t);
        return ret;
    }
} seg;
void dfs(int u, int p) {
    L[u] = ++tot, tree[u] = rt;
    id[L[u]] = u;
    int i = 0;
    // angular
    while (i < sz(e[u]) && e[u][i].fi == -2) {
        int v = e[u][i++].se;
        if (v == p) continue;
        w[v] = w[u], f[v] = f[u];
        dfs(v, u);
    }
    Z[u] = tot;
    // linear
    while (i < sz(e[u]) && e[u][i].fi == -1) {
        int v = e[u][i++].se;
        if (v == p) continue;
        f[v] = v;
        w[v] = w[u] + lg2[r[u]] - lg2[r[v]];
        dfs(v, u);
    }
    R[u] = tot;
}
int main() {
    rep(i, 0, 31) lg2[1 << i] = i;
    while (~scanf("%d%d%d", &n, &m, &q)) {
        rep(i, 1, n + 1) L[i] = 0, e[i].clear();
        rep(i, 1, n + 1) scanf("%d", r + i);
        rep(i, 0, m) {
            int a, x, y;
            scanf("%d%d%d", &a, &x, &y);
            e[x].pb(mp(-a, y));
            e[y].pb(mp(-a, x));
        }
        rep(i, 1, n + 1) sort(all(e[i]));
        tot = 0;
        rep(i, 1, n + 1)
            if (!L[i]) {
                rt = i, w[i] = 0, f[i] = i;
                dfs(i, -1);
            }
        seg.build(1, 1, n);
        static int cas = 0;
        printf("Case #%d:\n", ++cas);
        rep(_q, 0, q) {
            int a, x, y;
            scanf("%d%d%d", &a, &x, &y);
            if (a == 1) {
                if (f[x] == x) {
                    seg.upd(1, 1, n, L[x], Z[x], lg2[r[x]] - lg2[y]);
                } else if (Z[x] < R[x]) {
                    seg.upd(1, 1, n, Z[x] + 1, R[x], lg2[y] - lg2[r[x]]);
                }
                r[x] = y;
            } else {
                int wx = seg.qry(1, 1, n, L[x], L[x]);
                int mx = seg.qry(1, 1, n, L[tree[x]], R[tree[x]]);
                double ans = (mx - wx) * log(2) + log(y);
                printf("%.3f\n", ans);
            }
        }
    }
    return 0;
}
