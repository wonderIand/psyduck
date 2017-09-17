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
const int N = 207;
const int M = 1007;
const ll LINF = 1e18 + 7;
struct Maxflow {
	int n, et, dis[N], que[N], cur[N], head[N];
	struct Edge {
		int s, t, v, nxt;
		Edge() {}
		Edge(int _s, int _t, int _v, int _nxt) {
			s = _s, t = _t, v = _v, nxt = _nxt;
		}
	} e[M << 1];
	void init(int _n) {
		n = _n, et = 0;
		memset(head, -1, sizeof(*head) * n);
	}
	void addEdge(int s, int t, int v) {
		e[et] = Edge(s, t, v, head[s]), head[s] = et++;
		e[et] = Edge(t, s, 0, head[t]), head[t] = et++;
	}
	bool bfs(int S, int T) {
		int qh = 0, qt= 0;
		memset(dis, -1, sizeof(*dis) * n);
		dis[S] = 0, que[qt++] = S;
		while (qh < qt) {
			for (int i = head[que[qh++]]; ~i; i = e[i].nxt)
				if (e[i].v && !~dis[e[i].t]) {
					dis[que[qt++] = e[i].t] = 1 + dis[e[i].s];
					if (e[i].t == T) return true;
				}
		}
		return false;
	}
	ll dinic(int S, int T) {
		int u, qt;
		ll maxflow = 0;
		while (bfs(S, T)) {
			memcpy(cur, head, sizeof(*cur) * n);
			u = S, qt = 0;
			while (~cur[S]) {
				if (u == T) {
					ll flow = LINF;
					for (int i = qt - 1; i >= 0; --i)
						flow = min(flow, (ll)e[que[i]].v);
					for (int i = qt - 1; i >= 0; --i) {
						e[que[i]].v -= flow, e[que[i] ^ 1].v += flow;
						if (!e[que[i]].v) qt = i;
					}
					u = e[que[qt]].s, maxflow += flow;
				} else if (~cur[u] && e[cur[u]].v && dis[u] + 1 == dis[e[cur[u]].t]) {
					que[qt++] = cur[u];	
					u = e[cur[u]].t;
				} else {
					while (u != S && !~cur[u]) u = e[que[--qt]].s;
					cur[u] = e[cur[u]].nxt;	
				}
			}
		}
		return maxflow;
	}
} G;
int n, m;
int main() {
	int TT;
	scanf("%d", &TT);
	rep(cas, 0, TT) {
		scanf("%d%d", &n, &m);
		G.init(n);	
		int S, T;
		scanf("%d%d", &S, &T);
		--S, --T;
		rep(i, 0, m) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			--u, --v;
			G.addEdge(u, v, (w << 10) | 1);
		}
		ll ret = G.dinic(S, T);	
//		de(ret);
		printf("%lld\n", ret & 1023);
	}
	return 0;
}
