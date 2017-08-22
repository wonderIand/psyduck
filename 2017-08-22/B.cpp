#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef double db;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 1e5 + 7;
const int M = 25;
int n, m, c[N], dep[N], f[N][M];
vector<int> V, e[N];
int tot, rt[N], ls[N * M], rs[N * M];
ll sum[N * M];
void ins(int &t, int e, int l, int r, int p) {
	t = ++tot;
	sum[t] = ls[t] = rs[t] = 0;
	if (l >= r) {
		sum[t] = sum[e] + V[p - 1];
		return ;
	}
	int z = (l + r) >> 1;
	if (p <= z) {
		rs[t] = rs[e];	
		ins(ls[t], ls[e], l, z, p);
	} else {
		ls[t] = ls[e];
		ins(rs[t], rs[e], z + 1, r, p);
	}
	sum[t] = sum[ls[t]] + sum[rs[t]];
}
ll qry(int t, int l, int r, int L, int R) {
	if (!t) return 0;
	if (L <= l && r <= R) return sum[t];
	int z = (l + r) >> 1;
	if (R <= z) return qry(ls[t], l, z, L, R);
	if (L > z) return qry(rs[t], z + 1, r, L, R);
	return qry(ls[t], l, z, L, R) + qry(rs[t], z + 1, r, L, R);
}
void dfs(int u, int p) {
	f[u][0] = p;
	rep(j, 1, M) f[u][j] = f[f[u][j - 1]][j - 1];
	ins(rt[u], rt[p], 1, sz(V), c[u]);	
	rep(i, 0, sz(e[u])) {
		int v = e[u][i];
		if (v == p) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}
pair<pii, pii> q[N];
int _lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	int D = abs(dep[x] - dep[y]);
	rep(i, 0, M)
		if (D >> i & 1)
			x = f[x][i];
	if (x == y) return x;

	for (int i = M - 1; i >= 0; --i)
		if (f[x][i] != f[y][i])
			x = f[x][i], y = f[y][i];
	return f[x][0];
}
int main() {
	while (~scanf("%d%d", &n, &m)) {
		tot = 0, V.clear();
		rep(i, 1, n + 1) scanf("%d", &c[i]), V.pb(c[i]);
		rep(i, 1, n + 1) e[i].clear();
		rep(i, 1, n) {
			int x, y;
			scanf("%d%d", &x, &y);
			e[x].pb(y), e[y].pb(x);
		}
		rep(i, 0, m) {
			int s, t, a, b;
			scanf("%d%d%d%d", &s, &t, &a, &b);
			q[i] = mp(mp(s, t), mp(a, b));
			V.pb(a), V.pb(b);
		}
		sort(all(V));
		V.erase(unique(all(V)), V.end());
		rep(i, 1, n + 1)
			c[i] = lower_bound(all(V), c[i]) - V.begin() + 1;
		dfs(1, 0);
		rep(i, 0, m) {
			q[i].se.fi = lower_bound(all(V), q[i].se.fi) - V.begin() + 1;
			q[i].se.se = lower_bound(all(V), q[i].se.se) - V.begin() + 1;
		}
		rep(i, 0, m) {
			int s = q[i].fi.fi, t = q[i].fi.se;
			int a = q[i].se.fi, b = q[i].se.se;
			int x = _lca(s, t);
//			printf("lca(%d, %d) = %d\n", s, t, x);
//			printf("a = %d, b = %d, c[x] = %d\n", a, b, c[x]);
//			printf("(%d, %d), (%d, %d), (%d, %d)\n", s, qry(rt[s], 1, sz(V), a, b), t, qry(rt[t], 1, sz(V), a, b), 
//					x, qry(rt[x], 1, sz(V), a, b));
			ll ans = qry(rt[s], 1, sz(V), a, b) + qry(rt[t], 1, sz(V), a, b) - 2 * qry(rt[x], 1, sz(V), a, b);
			if (a <= c[x] && c[x] <= b) ans += V[c[x] - 1];
			printf("%lld%c", ans, " \n"[i == m - 1]);
		}	
	}
	return 0;
}
