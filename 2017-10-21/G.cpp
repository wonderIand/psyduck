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
const int N = 55;
const int M = 1e5 + 7;
const int LOG = 6;
const ll LINF = 1e18 + 7;
int n, m, K, L, a[N][N], id[N << 1][N << 1];
struct MaxFlow {
	static const int N = ::M + 4 * ::N * ::N;
	static const int M = (1 + LOG * LOG) * N;
	int n, et, dis[N], que[N], cur[N], head[N];
	struct Edge {
		int s, t, v, nxt;
		Edge() {
		}
		Edge(int _s, int _t, int _v, int _nxt) {
			s = _s, t = _t, v = _v, nxt = _nxt;
		}
	} e[M * 2];
	void init(int _n) {
		n = _n, et = 0;
		memset(head, -1, sizeof(head[0]) * n);
	}
	void addEdge(int s, int t, int v) {
		e[et] = Edge(s, t, v, head[s]), head[s] = et++;
		e[et] = Edge(t, s, 0, head[t]), head[t] = et++;
	}
	bool bfs(int S, int T) {
		int qh = 0, qt = 0;
		memset(dis, -1, sizeof(dis[0]) * n);
		dis[S] = 0, que[qt++] = S;
		while (qh < qt)
			for (int i = head[que[qh++]]; ~i; i = e[i].nxt)
				if (e[i].v && !~dis[e[i].t]) {
					dis[que[qt++] = e[i].t] = 1 + dis[e[i].s];
					if (e[i].t == T)
						return true;
				}
		return false;
	}
	ll dinic(int S, int T) {
		int u, qt;
		ll maxflow = 0;
		while (bfs(S, T)) {
			memcpy(cur, head, sizeof(cur[0]) * n);
			u = S, qt = 0;
			while (~cur[S]) {
				if (u == T) {
					ll flow = LINF;
					for (int i = qt - 1; i >= 0; --i)
						flow = min(flow, (ll) e[que[i]].v);
					for (int i = qt - 1; i >= 0; --i) {
						e[que[i]].v -= flow, e[que[i] ^ 1].v += flow;
						if (!e[que[i]].v)
							qt = i;
					}
					u = e[que[qt]].s, maxflow += flow;
				} else if (~cur[u] && e[cur[u]].v
						&& dis[u] + 1 == dis[e[cur[u]].t]) {
					que[qt++] = cur[u];
					u = e[cur[u]].t;
				} else {
					while (u != S && !~cur[u])
						u = e[que[--qt]].s;
					cur[u] = e[cur[u]].nxt;
				}
			}
		}
		return maxflow;
	}
} G;
void gao(int u, int x, int l, int r, int cap) {
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1) G.addEdge(u, id[x][l++], cap);
		if (r & 1) G.addEdge(u, id[x][--r], cap);
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &K);
	L = K;
	rep(i, 1, 2 * n) rep(j, 1, 2 * m) id[i][j] = ++L;
	int S = 0, T = L + 1;
	G.init(T + 1);
	rep(i, 0, n) rep(j, 0, m) {
		scanf("%d", &a[i][j]);	
		G.addEdge(id[n + i][m + j], T, a[i][j]);
		for (int x = n + i; x > 0; x >>= 1)
			for (int y = m + j; y > 0; y >>= 1) {
				if (mp(x, y) == mp(n + i, m + j)) continue;			
				G.addEdge(id[x][y], id[n + i][m + j], a[i][j]);
			}
	}
	rep(u, 1, K + 1) {
		int r1, r2, c1, c2, cap;
		scanf("%d%d%d%d%d", &r1, &r2, &c1, &c2, &cap);
		--r1, --r2, --c1, --c2;
		G.addEdge(S, u, cap);
		for (int l = n + r1, r = n + r2 + 1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) gao(u, l++, m + c1, m + c2 + 1, cap); 
			if (r & 1) gao(u, --r, m + c1, m + c2 + 1, cap);
		}
	}
	ll ans = G.dinic(S, T);
	cout << ans << endl;
	return 0;
}
