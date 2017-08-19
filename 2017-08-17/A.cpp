#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 1e5 + 7;
namespace Treap {
	queue<int> Q;
	ll sum[N], ssum[N];
	int tot, v[N], l[N], r[N], hr[N], s[N];
	void init() {
		tot = 0, srand(time(0));
		while (!Q.empty()) Q.pop();
	}
	int _rand() {
		return ((ll) rand() << 14) ^ ((ll) rand());
	}
	int newnode() {
		int x;
		if (!Q.empty()) {
			x = Q.front();Q.pop();
		} else
			x = ++tot;
		l[x] = r[x] = 0, s[x] = 1, hr[x] = _rand();
		return x;
	}
	void up(int x) {
		s[x] = 1 + s[l[x]] + s[r[x]];
		sum[x] = v[x] + sum[l[x]] + sum[r[x]];
		ssum[x] = ssum[l[x]] + ssum[r[x]] + 1ll * v[x] * (s[r[x]] + 1)
				+ sum[l[x]] * (s[r[x]] + 1);
	}
	void Lr(int &x) {
		int y = r[x];
		r[x] = l[y], l[y] = x;
		up(x), up(y);
		x = y;
	}
	void Rr(int &x) {
		int y = l[x];
		l[x] = r[y], r[y] = x;
		up(y), up(x);
		x = y;
	}
	void insert(int &x, int V) {
		if (x == 0) {
			x = newnode();
			v[x] = sum[x] = ssum[x] = V;
			return ;
		}
		if (V <= v[x]) {
			insert(l[x], V);
			if (hr[l[x]] > hr[x]) Rr(x);
		} else {
			insert(r[x], V);
			if (hr[r[x]] > hr[x]) Lr(x);
		}
		up(x);
	}
	void merge(int &x, int &y) {
		if (x == 0) {
			swap(x, y);
			return ;
		}
		if (s[x] < s[y]) swap(x, y);
		queue<int> que;
		que.push(y);
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			if (!u) continue;
			insert(x, v[u]);
			if (l[u]) que.push(l[u]);
			if (r[u]) que.push(r[u]);
			Q.push(u);
		}
	}
	void out(int x) {
		dd(x), dd(s[x]), dd(sum[x]), de(ssum[x]);
	}
};
int n, rt[N], val[N];
ll ans[N];
vi g[N];
void dfs(int u, int p) {
	rt[u] = 0;
	rep(i, 0, sz(g[u])) {
		int v = g[u][i];
		if (v == p) continue;
		dfs(v, u);
		Treap::merge(rt[u], rt[v]);
	}
	Treap::insert(rt[u], val[u]);
	ans[u] = Treap::ssum[rt[u]];
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		Treap::init();
		scanf("%d", &n);
		rep(i, 1, n + 1) scanf("%d", val + i);
		rep(i, 1, n + 1) g[i].clear();
		rep(i, 1, n) {
			int u, v;
			scanf("%d%d", &u, &v);
			g[u].pb(v), g[v].pb(u);
		}
		dfs(1, 0);
		rep(i, 1, n + 1) printf("%lld ", ans[i]);
		puts("");
	}
	return 0;
}

