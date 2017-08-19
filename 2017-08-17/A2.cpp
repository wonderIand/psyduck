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
int n;
vector<int> e[N];
struct SegTree {
	#define ls ((t)<<1)
	#define rs ((t)<<1|1)
	ll cnt[N << 2], sum[N << 2], ssum[N << 2];	
	void build(int t, int l, int r) {
		cnt[t] = sum[t] = ssum[t] = 0;
		if (l < r) {
			int z = (l + r) >> 1;
			build(ls, l, z), build(rs, z + 1, r);
		}
	}
	void down(int t) {
		if (cnt[t] != 0) {
			ssum[ls] = ssum[ls] + ssum[t] + sum[ls] * cnt[t];	
			sum[ls] = sum[ls] + sum[t];
			cnt[ls] = cnt[ls] + cnt[t];
			ssum[rs] = ssum[rs] + ssum[t] + sum[rs] * cnt[t];	
			sum[rs] = sum[rs] + sum[t];
			cnt[rs] = cnt[rs] + cnt[t];
			cnt[t] = sum[t] = ssum[t] = 0;
		}
	}
	void upd(int t, int l, int r, int L, int R, ll V) {
		if (L <= l && r <= R) {
			ssum[t] = ssum[t] + V + sum[t];
			sum[t] = sum[t] + V;	
			cnt[t] = cnt[t] + 1;
			return ;
		}
		down(t);
		int z = (l + r) >> 1;
		if (L <= z) upd(ls, l, z, L, R, V);
		if (R > z) upd(rs, z + 1, r, L, R, V);
	}	
	ll qry(int t, int l, int r, int P) {
		if (l == r)
			return ssum[t];
		down(t);
		int z = (l + r) >> 1;
		if (P <= z) return qry(ls, l, z, P);
		return qry(rs, z + 1, r, P);
	}
} seg;
int tot, w[N], s[N], dep[N], far[N], top[N], siz[N];
void dfs(int u, int p) {
	s[u] = -1, far[u] = p, siz[u] = 1;
	rep(i, 0, sz(e[u])) {
		int v = e[u][i];
		if (v == p) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
		siz[u] += siz[v];
		if (s[u] == -1 || siz[v] > siz[s[u]])
			s[u] = v;
	}
}
void DFS(int u, int rt, int p) {
	w[u] = ++tot, top[u] = rt;
	if (~s[u]) DFS(s[u], rt, u);
	rep(i, 0, sz(e[u])) {
		int v = e[u][i];
		if (v == p || v == s[u]) continue;
		DFS(v, v, u);
	}
}
pii a[N];
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d", &n);
		rep(i, 1, n + 1) scanf("%d", &a[i].fi), a[i].se = i;
		sort(a + 1, a + 1 + n);
		seg.build(1, 1, n);		
		rep(i, 1, n + 1) e[i].clear();
		rep(i, 1, n) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].pb(v), e[v].pb(u);
		}
		tot = 0, dfs(1, 0), DFS(1, 1, 0);
		for (int i = 1; i <= n; ++i) {
			int v = a[i].fi;
			int u = a[i].se;
			while (top[u] != top[1]) {
				seg.upd(1, 1, n, w[top[u]], w[u], v);	
				u = far[top[u]];
			}
			seg.upd(1, 1, n, w[1], w[u], v);	
		}
		rep(i, 1, n + 1) {
			ll fi = seg.qry(1, 1, n, w[i]);
			printf("%lld%c", fi, " \n"[i == n + 1]);
		}
		puts("");
	}
	return 0;
}
