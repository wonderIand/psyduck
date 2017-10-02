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
const int N = 2e3 + 7;
int n, q;
struct Rec {
	int x0, x1, y0, y1;
};
vector<int> e[N];
vector<Rec> a;
bool in(pii p, Rec r) {
	return r.x0 <= p.fi && p.fi <= r.x1 && r.y0 <= p.se  && p.se <= r.y1;
}
int fa[N], sum[N], dep[N];
void dfs(int u) {
	sum[u] = sz(e[u]) == 0;
//	printf("dep[%d] = %d\n", u, dep[u]);
	rep(i, 0, sz(e[u])) {
		int v = e[u][i];
		fa[v] = u;
		dep[v] = dep[u] + 1;
		dfs(v);
		sum[u] += sum[v];
	}
//	printf("sum[%d] = %d\n", u, sum[u]);
}
int get(int x, int y) {
	for (int i = sz(a) - 1; i >= 0; --i)
		if (in(mp(x, y), a[i])) return i;
	return -1;
}
int lca(int u, int v) {
	while (dep[u] != dep[v]) {
		if (dep[u] < dep[v]) swap(u, v);
		u = fa[u];	
	}
	while (u != v) u = fa[u], v = fa[v];
	return u;
}
int main() {
	int x0, x1, y0, y1;
	while (~scanf("%d%d%d%d", &x0, &y0, &x1, &y1)) {
		a.clear();
		a.pb((Rec){x0, x1, y0, y1});
		scanf("%d%d", &n, &q);
		rep(i, 0, 2 * n + 1) e[i].clear();
		rep(i, 0, n) {
			scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
			int p;	
			for (int j = sz(a) - 1; j >= 0; --j)
				if (in(mp(x0, y0), a[j]) && in(mp(x1, y1), a[j])) {
					p = j;
					break;
				}
//			dd(i), de(p);
			e[p].pb(sz(a)), e[p].pb(sz(a) + 1);
			if (x0 == x1) {	
				a.pb((Rec){a[p].x0, x0, a[p].y0, a[p].y1});
				a.pb((Rec){x0, a[p].x1, a[p].y0, a[p].y1});
			} else {
				a.pb((Rec){a[p].x0, a[p].x1, a[p].y0, y0});
				a.pb((Rec){a[p].x0, a[p].x1, y0, a[p].y1});
			}
		}
//		dd(2 * n + 1), de(sz(a));
		dfs(0);
		rep(_q, 0, q) {
			scanf("%d%d%d%d", &x0, &y0, &x1, &y1);	
			int u = get(x0, y0), v = get(x1, y1);
			int p = lca(u, v);
			int ans = sum[0] - sum[p] + 1;
			printf("%d\n", ans);
		}
	}
	return 0;
}
