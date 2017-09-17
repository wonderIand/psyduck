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
const int N = 5e4 + 7;
const int W = 230;
const int M = 18;
int n, q, B, a[N], dep[N], f[M][N];
struct Edge {
	int v, w, nxt;
	Edge() {}
	Edge(int _v, int _w, int _nxt) {
		v = _v, w = _w, nxt = _nxt;
	}
} e[N << 1], g[(N * 10) << 1];
int et, he[N], gt, hg[N];
void dfs(int u, int p) {
	f[0][u] = p;	
	rep(i, 1, M) f[i][u] = f[i - 1][f[i - 1][u]];
	for (int i = he[u]; ~i; i = e[i].nxt) {
		int v = e[i].v;
		if (v == p) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}
int jump(int x, int d) {
	rep(i, 0, M) if (d >> i & 1) 
		x = f[i][x];
	return x;
}
int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	x = jump(x, dep[x] - dep[y]);
	if (x == y) return x;
	for (int i = M - 1; i >= 0; --i)
		if (f[i][x] != f[i][y])
			x = f[i][x], y = f[i][y];
	return f[0][x];
}
struct Query {
	int a, b, k;
} Q[N * 10];
int top, st[N], ans[N * 10], sum[N][W];
void DFS(int u, int p) {
	st[++top] = u;
	for (int i = hg[u]; ~i; i = g[i].nxt) {
		int id = g[i].v, depth = g[i].w;		
		int pos = top;
		while (pos > 0 && dep[st[pos]] >= depth) {
			ans[id] ^= a[st[pos]];	
			pos -= Q[id].k;
		}
	}
	rep(i, 1, B + 1) {
		sum[u][i] = a[u] ^ (top > i ? sum[st[top - i]][i] : 0);
	}
	for (int i = he[u]; ~i; i = e[i].nxt) {
		int v = e[i].v;
		if (v == p) continue;
		DFS(v, u);
	}
	--top;
}
int get(int u, int k, int c) {
	int v = jump(u, (c + 1) * k);
	return sum[u][k] ^ sum[v][k];
}
void add(int u, int v, int w, Edge *e, int &et, int *head) {
	e[et] = Edge(v, w, head[u]), head[u] = et++;
}
int main() {
	while (~scanf("%d%d", &n, &q)) {
		et = 0, gt = 0;
		rep(i, 1, n + 1) he[i] = hg[i] = -1;	
		rep(i, 1, n) {
			int u, v;
			scanf("%d%d", &u, &v);
//			e[u].pb(v), e[v].pb(u);
			add(u, v, 0, e, et, he);
			add(v, u, 0, e, et, he);
		}
		rep(i, 1, n + 1) scanf("%d", a + i);
		dfs(1, 0);
		B = sqrt(n) + 0.5;
		rep(i, 0, q) {
			ans[i] = 0;
			int a, b, k;
			scanf("%d%d%d", &a, &b, &k);		
			Q[i].a = a, Q[i].b = b, Q[i].k = k;
			if (k >= B) {
				int p = lca(a, b);
				int dis = dep[a] + dep[b] - 2 * dep[p];
//				g[a].pb(mp(i, dep[p]));
				add(a, i, dep[p], g, gt, hg);
				if (dep[p] < dep[b] - dis % k) {
					int nb = jump(b, dis % k);
//					g[nb].pb(mp(i, dep[p] + 1));	
					add(nb, i, dep[p] + 1, g, gt, hg);
				}
			}
		}
		top = 0, DFS(1, 1);
		rep(i, 0, q) if (Q[i].k < B) {
			int a = Q[i].a, b = Q[i].b, k = Q[i].k;	
			int p = lca(a, b);
			ans[i] ^= get(a, k, (dep[a] - dep[p]) / k);	
			int dis = dep[a] + dep[b] - 2 * dep[p];
			if (dep[p] < dep[b] - dis % k) {
				int nb = jump(b, dis % k);
				ans[i] ^= get(nb, k, (dep[nb] - dep[p] - 1) / k);
			}
		}
		rep(i, 0, q)
			printf("%d\n", ans[i]);
	}
	return 0;
}
