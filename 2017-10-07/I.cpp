#include <bits/stdc++.h>
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
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define per(i,a,b) for (int i = (b) - 1; i >= (a); i--)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 4e2 + 7;
const int M = N * N;
const ll INF = 1e12;
const ll LINF = 1e18 + 7;
int n, m;
bool vis[2][N];
struct MinCost {
	struct Edge {
		ll cost;
		int s, t, cap, nxt;
		Edge() {}
		Edge(int _s, int _t, int _cap, ll _cost, int _nxt) {
			s = _s, t = _t, cap = _cap, cost = _cost, nxt = _nxt;
		}
	} e[M * 2];
	ll dis[N];
	queue<int> que;
	int n, et, pre[N], vis[N], head[N];	
	void init(int _n) {
		n = _n, et = 0;
		memset(head, -1, sizeof(*head) * n);
	}
	void addEdge(int s, int t, int cap, ll cost) {
		e[et] = Edge(s, t, cap, cost, head[s]), head[s] = et++;
		e[et] = Edge(t, s, 0, -cost, head[t]), head[t] = et++;
	}
	bool bfs(int S, int T) {
		rep(i, 0, n) pre[i] = -1, dis[i] = LINF, vis[i] = false;
		dis[S] = 0, vis[S] = true, que.push(S);	
		while (!que.empty()) {
			int u = que.front();
			for (int i = head[u]; ~i; i = e[i].nxt) {
				int v = e[i].t;
				if (e[i].cap > 0 && dis[v] > dis[u] + e[i].cost) {
					pre[v] = i, dis[v] = dis[u] + e[i].cost;
					if (!vis[v]) vis[v] = true, que.push(v);
				}
			}
			vis[u] = false, que.pop();
		}
		return dis[T] < 0;
	}
	pair<ll, ll> solve(int S, int T) {
		ll maxflow = 0, mincost = 0;
		while (bfs(S, T)) {
			if (dis[T] >= 0) break;
			ll flow = LINF;
			for (int i = pre[T]; ~i; i = pre[e[i].s])
				flow = min(flow, (ll) e[i].cap);
			for (int i = pre[T]; ~i; i = pre[e[i].s])
				e[i].cap -= flow, e[i ^ 1].cap += flow;
			maxflow += flow, mincost += flow * dis[T];
		}
		return mp(maxflow, mincost);
	}
	bool check(int S, int T, int n, int m) {
		for (int i = 0; i < et; i += 2)
			if (e[i].s == S && 1 <= e[i].t && e[i].t <= n) {
				if (::vis[0][e[i].t] && !e[i ^ 1].cap) return false;
			} else if (n + 1 <= e[i].s && e[i].s <= n + m && e[i].t == T) {
				if (::vis[1][e[i].s - n] && !e[i ^ 1].cap) return false;
			}
		return true;
	}
} G;
int main() {
	while (~scanf("%d%d", &n, &m)) {
		if (n == 0 && m == 0) break;
		memset(vis, false, sizeof(vis));
		int S = 0, T = n + m + 1;
		G.init(T + 1);
		int t;
		scanf("%d", &t);
		rep(i, 0, t) {
			int x; scanf("%d", &x);
			vis[0][x] = true;
		}
		int s;
		scanf("%d", &s);
		rep(i, 0, s) {
			int x; scanf("%d", &x);
			vis[1][x] = true;
		}
		rep(i, 1, n + 1) G.addEdge(S, i, 1, vis[0][i] ? -INF : 0);
		rep(i, 1, m + 1) G.addEdge(n + i, T, 1, vis[1][i] ? -INF : 0);
		rep(i, 1, n + 1) {
			int di; scanf("%d", &di);
			rep(j, 0, di) {
				int a, x; scanf("%d %d", &a, &x);	
				G.addEdge(i, n + a, 1, - x);
			}
		}
		pair<ll, ll> ret = G.solve(S, T);
		if (ret.se <= 1ll * (s + t) * (-INF)) {
			ll ans = (-ret.se) % INF;
			printf("%lld\n", ans);
		} else {
			puts("-1");
		}
	}
	return 0;
}
