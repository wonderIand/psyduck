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
const int M = N * 40;
int n, up, val[N], ans[N];
vi e[N];
int L, rt[N], lc[M], rc[M], sum[M];
ll nval[N];
vector<ll> V;
inline int newnode() {
	++L; lc[L] = rc[L] = sum[L] = 0;
	return L;
}
int merge(int a, int b) {
	if (a == 0 || b == 0) return a + b;
	int p = newnode();
	lc[p] = merge(lc[a], lc[b]);
	rc[p] = merge(rc[a], rc[b]);
	sum[p] = sum[a] + sum[b];
	return p;
}
int Query(int l, int r, int &p, int L, int R) {
	if (L <= l && r <= R) return sum[p];
	if (p == 0) return 0;
	int m = (l + r) >> 1;
	int ret = 0;
	if (L <= m) ret += Query(l, m, lc[p], L, R);
	if (R > m) ret += Query(m + 1, r, rc[p], L, R);
	return ret;
}
void Update(int l, int r, int &p, int x, int d) {
	if (p == 0) p = newnode();
	sum[p] += d;
	if (l == r) return ;
	int m = (l + r) >> 1;
	if (x <= m) Update(l, m, lc[p], x, d);
	else Update(m + 1, r, rc[p], x, d);
}
int Query_R(int l, int r, int p, int x) {
	if (p == 0 || sum[p] == 0) return 0;
	if (l == r) return l;
	int m = (l + r) >> 1, ret = 0;
	if (x <= m) ret = Query_R(l, m, lc[p], x);
	if (ret) return ret;
	return Query_R(m + 1, r, rc[p], x);	
}
void dfs(int c, int fa) {	
	rt[c] = newnode();
	rep(i, 0, sz(e[c])) {
		int t = e[c][i];
		if (t == fa) continue;
		dfs(t, c);
		rt[c] = merge(rt[c], rt[t]);
	}
	ans[c] = Query(1, up, rt[c], 1, val[c]) + 1;
//	dd(c), dd(val[c]), de(ans[c]);
	int l = val[c];
	Update(1, up, rt[c], val[c], 1);
	int r = val[c] != up ? Query_R(1, up, rt[c], val[c] + 1) : 0;
	if (r) Update(1, up, rt[c], r, -1);	
}
void DFS(int c, int fa, int dep) {
	nval[c] = ((ll)val[c] << 20) | dep;
	rep(i, 0, sz(e[c])) {
		int t = e[c][i];
		if (t == fa) continue;
		DFS(t, c, dep + 1);
	}
}
int main() {
	scanf("%d", &n);
	rep(i, 1, n + 1) {
		int p;
		scanf("%d%d", val + i, &p);
		if (p) e[p].pb(i);	
	}
	e[0].pb(1), val[0] = 1e9 + 1;
	DFS(0, 0, 1);
	rep(i, 0, n + 1) V.pb(nval[i]);
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	rep(i, 0, n + 1) val[i] = lower_bound(all(V), nval[i]) - V.begin() + 1;
	up = sz(V);
	dfs(0, 0);
	cout << ans[0] - 1 << endl;
	return 0;
}
