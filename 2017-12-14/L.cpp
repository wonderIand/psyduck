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
const int K = 20;
int n, m, top;
pii path[N], seg[N], sta[N];
vi e[N];
bool vis[N];
int q[N], fa[N], siz[N], msz[N];
int find(int u) {
	int t = 1;
	q[0] = u, fa[u] = -1;
	rep(h, 0, t) {
		u = q[h];
		msz[u] = 0, siz[u] = 1;
		for (auto v : e[u]) {
			if (vis[v] || v == fa[u]) continue;
			fa[v] = u, q[t++] = v;
		}
	}
	for (int h = t - 1; h >= 0; --h) {
		u = q[h];
		msz[u] = max(msz[u], t - siz[u]);
		if (msz[u] * 2 <= t) return u;
		if (~fa[u]) {
			siz[fa[u]] += siz[u];
			msz[fa[u]] = max(msz[fa[u]], siz[u]);
		}
	}
	return 0;
}
bool inp[N];
int _lca[N], dep[N], f[K][N], vid[N];
int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int D = dep[u] - dep[v];
	rep(i, 0, K) if (D >> i & 1) u = f[i][u];
	if (u == v) return u;
	per(i, 0, K) if (f[i][u] != f[i][v]) 
		u = f[i][u], v = f[i][v];
	return f[0][u];
}
void dfs(int u, int p) {	
	inp[u] = false, f[0][u] = p;
	rep(i, 1, K) f[i][u] = f[i - 1][f[i - 1][u]];
	for (auto v : e[u]) if (!vis[v] && v != p) {
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}
inline void fail() {
	puts("No");
	exit(0);
}
void solve(int rt) {
	dfs(rt, rt);
	pii np(-1, -1);
	rep(i, 0, m) {
		int u, v; tie(u, v) = path[i];
		if (vis[u] || vis[v]) {
			_lca[i] = -1, inp[u] = inp[v] = false;
			continue;
		}
		_lca[i] = lca(u, v);
//		printf("lca(%d, %d) = %d\n", u, v, _lca[i]);
		if (_lca[i] != rt) continue;
		if (dep[u] < dep[v]) swap(u, v);
		if (np.fi == -1) {
			np = mp(u, v);
		} else if (mp(dep[u], dep[v]) > mp(dep[np.fi], dep[np.se])) {
			np = mp(u, v);
		}
	}
	if (np.fi == -1) return ;
	int u = np.fi, tot = 0, tmp;
	while (u != rt) q[tot++] = u, inp[u] = true, u = f[0][u];
	q[tot++] = rt, inp[rt] = true, u = np.se;
	tmp = tot;
	while (u != rt) q[tot++] = u, inp[u] = true, u = f[0][u];
	reverse(q + tmp, q + tot);
	rep(i, 0, tot) vid[q[i]] = i;
//	dd(np.fi), de(np.se);
//	rep(i, 0, tot) printf("%d ", q[i]);puts("q");
//	rep(i, 1, n + 1) if (inp[i]) printf("%d ", i);puts("inp");
	tot = 0;
	rep(i, 0, m) {
		int u, v; tie(u, v) = path[i];
		if (_lca[i] == -1 || !inp[_lca[i]]) continue;
		if (!inp[u] || !inp[v]) fail();
		if (vid[u] > vid[v]) swap(u, v);
		seg[tot++] = mp(vid[u], -vid[v]);
	}
	sort(seg, seg + tot);
//	de("seg");
//	rep(i, 0, tot) printf("%d,%d  ", seg[i].fi, -seg[i].se);
	top = 0;
	rep(i, 0, tot) {
		while (top && -sta[top].se < seg[i].fi) --top;
		if (top && !(-seg[i].se <= -sta[top].se)) fail();
		sta[++top] = seg[i];	
	}
}
void gao(int u) {
	u = find(u);
//	de(u);
	solve(u);
	vis[u] = true;
	for (auto v : e[u]) if (!vis[v]) gao(v);
}
int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, n) {
		int u, v; scanf("%d%d", &u, &v);
		e[u].pb(v), e[v].pb(u);
	}
	rep(i, 0, m) {
		int u, v; scanf("%d%d", &u, &v);
		path[i] = mp(u, v);
	}	
	gao(1);
	puts("Yes");
	return 0;
}
