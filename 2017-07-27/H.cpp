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
#define cnt(x) __builtin_popcount(x)
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 107;
int n, m, a[N][N], u[N][N], d[N][N], o[N][N];
int top;
pair<int*, int> sta[N * N * 3];
vector<pair<int, pair<int, int> > > v;
void change(int *x, int y) {
    sta[top++] = mp(x, *x);
    *x = y;
}
void rollback() {
    --top;
    *sta[top].fi = sta[top].se;
}
int calc(int lx, int ly, int rx, int ry) {
    set<int> S;
    rep(i, lx, rx + 1)
        rep(j, ly, ry + 1)
            S.insert(a[i][j]);
    return sz(S);
}
ll br() {
    ll ret = 0;
    rep(i, 0, n) rep(j, 0, m)
        rep(x, i, n) rep(y, j, m)
            ret += calc(i, j, x, y);
    return ret;
}
int main() {
    int T;
    scanf("%d", &T);
    rep(cas, 0, T) {
        scanf("%d%d", &n, &m);
        v.clear();
        rep(i, 0, n) rep(j, 0, m) {
            int x;
            scanf("%d", &x);a[i][j] = x;
            v.pb(mp(x, mp(j, i)));
            o[i][j] = 0, u[i][j] = 0, d[i][j] = n - 1;
        }
        sort(all(v));
        ll P = 0, Q = 0;
        rep(i, 0, n) rep(j, 0, m) Q += (n - i) * (m - j);
        for (int xi = 0, xj; xi < sz(v); xi = xj) {
            xj = xi + 1;
            while (xj < sz(v) && v[xj].fi == v[xi].fi) ++xj;
            for (int i = xi, j, x, y; i < xj; i = j) {
                vector<int> r;
                j = i, y = v[i].se.fi;
                while (j < xj && v[j].se.fi == v[i].se.fi)
                    r.pb(v[j++].se.se);
                // up
                x = -1;
                rep(k, 0, sz(r)) {
                    rep(w, x + 1, r[k] + 1) change(&u[w][y], x + 1);
                    x = r[k];
                }
                rep(w, x + 1, n) change(&u[w][y], x + 1);
                ll S, R;
                rep(k, 0, sz(r)) {
                    x = r[k], S = 0, R = (m - y);
//                    de(R);
                    for (int _y = y, lx = u[x][y], rx = n - 1; _y >= 0; --_y) {
                        if (o[x][_y]) break;
                        lx = max(lx, u[x][_y]), rx = min(rx, d[x][_y]);
                        if (lx > rx) break;
                        S += 1ll * (x - lx + 1) * (rx - x + 1) * R;
                    }
                    P += S;
//                    printf("x = %d, y = %d, S = %I64d\n", x, y, S);
                }
                // down
                x = n;
                for (int k = sz(r) - 1; k >= 0; --k) {
                    for (int w = x - 1; w >= r[k]; --w) change(&d[w][y], x - 1);
                    x = r[k];
                }
                for (int w = x - 1; w >= 0; --w) change(&d[w][y], x - 1);
                rep(k, 0, sz(r)) change(&o[r[k]][y], 1);
            }
            while (top) rollback();
        }
//        de(P), de(Q), de(br());
        printf("%.9f\n", 1.0 * P / Q);
    }
    return 0;
}

