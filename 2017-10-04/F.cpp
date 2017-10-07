#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
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
const int N = 2507;
const int M = 5007;
const int P = 1e5 + 7;
int n, m, K, tot;
pair<int, int> g[P];
struct Maxflow {
	queue<int> que;
	int dis[N];
	int n, et, pre[N], vis[N], head[N];
	struct Edge {
		int s, t, cap, cost, nxt;
		Edge() {}
		Edge(int _s, int _t, int _cap, int _cost, int _nxt) {
			s = _s, t = _t, cap = _cap, cost = _cost, nxt = _nxt;
		}
	} e[M * 2];
	void init(int _n) {
		n = _n, et = 0;
		memset(head, -1, sizeof(*head) * n);
	}
	void addEdge(int s, int t, int cap, int cost) {
		e[et] = Edge(s, t, cap, cost, head[s]), head[s] = et++;
		e[et] = Edge(t, s, 0, -cost, head[t]), head[t] = et++;
	}
	bool bfs(int S, int T) {
		rep(i, 0, n) pre[i] = -1, dis[i] = INT_MAX, vis[i] = false; 
		dis[S] = 0, vis[S] = true, que.push(S);
		while (!que.empty()) {
			int u = que.front();
			for (int i = head[u]; ~i; i = e[i].nxt) {
				int v = e[i].t;
				if (e[i].cap > 0 && dis[v] > dis[u] + e[i].cost) {
					pre[v] = i, dis[v] = dis[u] + e[i].cost;
					if (!vis[v])
						vis[v] = true, que.push(v);
				}
			}
			vis[u] = false, que.pop();
		}
		return dis[T] != INT_MAX;
	}
	pair<int, int> solve(int S, int T) {
		int maxflow = 0, mincost = 0;
		while (bfs(S, T)) {
			int flow = INT_MAX;
			for (int i = pre[T]; ~i; i = pre[e[i].s])
				flow = min(flow, e[i].cap);
			for (int i = pre[T]; ~i; i = pre[e[i].s])
				e[i].cap -= flow, e[i ^ 1].cap += flow;
			maxflow += flow, mincost += flow * dis[T];
			g[tot++] = mp(flow, dis[T]);
		}
		return mp(maxflow, mincost);
	}
} G;
ll gao(int T) {	
	ll ret = 0;
	rep(i, 0, tot) if (T >= g[i].se)
		ret += 1ll * g[i].fi * (T - g[i].se + 1);
	return ret;
}
int main() {
	while (~scanf("%d%d%d", &n, &m, &K)) {
		G.init(n);
		rep(i, 0, m) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			if (!c) continue;
			G.addEdge(a, b, c, 1);
		}
		tot = 0;
		pii fc = G.solve(0, n - 1);	
		if (fc.fi == 0) {
			if (K) {
				puts("No solution");
			} else {
				puts("0");
			}
			continue;
		}
//		rep(i, 0, tot) printf("%d ", d[i]);puts("d");
		int l = 0, r = K + m;	
		while (l + 1 < r) {
			int z = (l + r) >> 1;
			gao(z) >= K ? r = z : l = z;
		}
		int ans = gao(l) >= K ? l : r;
		printf("%d\n", ans);
	}
	return 0;
}
