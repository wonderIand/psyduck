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
const int N = 2e5 + 7;
int n, m, deg[N], tmp[N];
vi e[N];
pii forb;
bool vis[N];
void bfs() {
	queue<int> que;
	rep(i, 1, n + 1) if (deg[i] == 1)
		que.push(i);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (auto v : e[u]) {
			if (mp(u, v) == forb || mp(v, u) == forb) continue;
			--deg[u], --deg[v];
			if (deg[v] == 1) ++deg[u], que.push(v);
		}
	}
}

bool bfs(int S) {
	memset(vis, false, sizeof(*vis) * (n + 1));		
	queue<int> que;
	vis[S] = true, que.push(S);
	int ret = 0;
	while (!que.empty()) {
		int u = que.front();
		++ret, que.pop();
		for (auto v : e[u]) if (!vis[v]) {
			if (mp(u, v) == forb || mp(v, u) == forb) continue;	
			vis[v] = true, que.push(v);
		}
	}
	return ret == n;
}
bool dfs(int u, int p) {
	int ret = 0;
	for (auto v : e[u]) if (v != p) {
		if (mp(u, v) == forb || mp(v, u) == forb) continue;
		if (++ret > 1 || !dfs(v, u)) return false;
	}
	return true;
}
bool check(int x, int y) {
	forb = mp(x, y);
	if (!bfs(x)) return false;
	rep(i, 1, n + 1) tmp[i] = deg[i];
	--deg[x], --deg[y];
	bfs();
	rep(u, 1, n + 1) if (deg[u] >= 2) {
		if (deg[u] > 2) {
			rep(i, 1, n + 1) deg[i] = tmp[i];
			return false;
		}
		int ret = 0;
		for (auto v : e[u]) if (deg[v] < 2) {
			if (mp(u, v) == forb || mp(v, u) == forb) continue;	
			++ret;
			if (ret > 1 || !dfs(v, u)) {
				rep(i, 1, n + 1) deg[i] = tmp[i];
				return false;
			}
		}
	}
	return true;
}
vi gao(int S) {
	vi ret;
	queue<int> que;
	vis[S] = true, que.push(S);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		if (sz(e[u]) == 3) {
			ret.pb(u);
			if (sz(ret) > 2) break;
		}
		for (auto v : e[u]) if (!vis[v] && deg[v] == 2)
			vis[v] = true, que.push(v);
	}
	return ret;
}
set<pii> S;
void solve() {
	rep(u, 1, n + 1) if (deg[u] >= 3) {
		for (auto v : e[u]) if (deg[v] >= 2) {
			if (check(u, v)) {
				printf("%d %d\n", u, v);
				return ;
			}
		}
	}
	int X = -1, Y = -1;
	rep(i, 1, n + 1) if (deg[i] == 3) {
		if (X == -1) X = i;
		else Y = i;
	}
	memset(vis, false, sizeof(*vis) * (n + 1));
	vis[X] = true, vis[Y] = true;
	for (auto u : e[X]) if (!vis[u] && deg[u] == 2) {
		vi a = gao(u);
		if (sz(a) == 1) {
			for (auto v : e[a[0]]) if (vis[v] && deg[v] == 2){
				printf("%d %d", a[0], v);
				return ;
			}
		} else if (sz(a) == 2) {
			int x = a[0], y = a[1];
			if (S.count(mp(x, y)) || S.count(mp(y, x))) {
				printf("%d %d\n", x, y);
				return ;
			}
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	rep(i, 0, m) {
		int u, v; scanf("%d%d", &u, &v);
		++deg[u], e[u].pb(v);
		++deg[v], e[v].pb(u);
		S.insert(mp(u, v));
	}
	forb = mp(-1, -1);
	bfs();
	solve();
	return 0;
}
