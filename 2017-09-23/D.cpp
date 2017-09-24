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
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 1e5 + 7;
const ll LINF = 1e18 + 7;
int n, m, L, DN, fa[N];
ll dis[N], S[N], V[N];
vector<pii> e[N];
void dfs(int u, int p, ll _dis) {
	fa[u] = p, dis[u] = _dis;
	if (dis[u] > dis[DN]) DN = u;
	rep(i, 0, sz(e[u])) {
		int v = e[u][i].fi, w = e[u][i].se;
		if (v == p) continue;
		dfs(v, u, _dis + w);
	}
}
bool vis[N];
ll DFS(int u, ll _dis) {
	ll ret = _dis;
	vis[u] = true;
	rep(i, 0, sz(e[u])) {
		int v = e[u][i].fi, w = e[u][i].se;
		if (vis[v]) continue;
		ret = max(ret, DFS(v, _dis + w));
	}
	return ret;
}
vector<int> P;
int a[N], b[N];
bool cmpa(const int &x, const int &y) {
	return -S[x] + V[x] < -S[y] + V[y];	
}
bool cmpb(const int &x, const int &y) {
	return S[x] + V[x] > S[y] + V[y];
}
bool check(ll M) {
	ll PLUS = -LINF, MINU = LINF;
	pair<ll, ll> BP(-LINF, LINF), BM(-LINF, LINF);
	for (int i = 0, j = 0; i < m; ++i) {
		while (j < m && S[b[j]] - S[a[i]] 
			+ V[b[j]] + V[a[i]] > M) {
			PLUS = max(PLUS, S[b[j]] + V[b[j]]);
			MINU = min(MINU, S[b[j]] - V[b[j]]);
			++j;
		}	
		if (!j) continue;
		ll vp = S[a[i]] + V[a[i]];
		ll vm = S[a[i]] - V[a[i]];
		BP.fi = max(BP.fi, vp + PLUS + L - M);		
		BP.se = min(BP.se, vm + MINU - L + M);
		BM.fi = max(BM.fi, vp - MINU + L - M);
		BM.se = min(BM.se, vm - PLUS - L + M);
	}	
	if (BP.fi > BP.se || BM.fi > BM.se) return false;
	int pl = 0, pr = 0, ml = m - 1, mr = m - 1;
	while (pl < m && S[0] + S[pl] < BP.fi) ++pl;	
	while (pr < m && S[0] + S[pr] <= BP.se) ++pr;
	while (ml >= 0 && S[0] - S[ml] < BM.fi) --ml;	
	while (mr >= 0 && S[0] - S[mr] <= BM.se) --mr;
	rep(i, 0, m) {
		while (pl - 1 >= 0 && S[i] + S[pl - 1] >= BP.fi) --pl;
		while (pr - 1 >= 0 && S[i] + S[pr - 1] > BP.se) --pr;
		while (ml + 1 < m && S[i] - S[ml + 1] >= BM.fi) ++ml;	
		while (mr + 1 < m && S[i] - S[mr + 1] > BM.se) ++mr;	
/*
		dd(i), dd(pl), dd(pr), dd(ml), de(mr);
		rep(j, i, m) {
			if (BP.fi <= S[i] + S[j] && S[i] + S[j] <= BP.se) {
				assert(pl <= j && j < pr);
			}
			if (BM.fi <= S[i] - S[j] && S[i] - S[j] <= BM.se) {
				assert(mr < j && j <= ml);
			}
		}
*/
		if (pl < pr && mr < ml && !(ml < pl || pr - 1 < mr + 1)) 
			return true;			
	}
	return false;
}
ll solve() {
	dfs(DN = 1, 0, 0);
	dfs(DN, 0, 0);
	P.clear();
	for (int i = DN; i; i = fa[i]) P.pb(i);
	m = sz(P), reverse(all(P));	
	rep(i, 1, n + 1) vis[i] = false;
	rep(i, 0, m) a[i] = b[i] = i, vis[P[i]] = true;	
	rep(i, 0, m) S[i] = dis[P[i]], V[i] = DFS(P[i], 0);
/*
	rep(i, 0, m) printf("%d ", P[i]);puts("P");
	rep(i, 0, m) printf("%lld ", S[i]);puts("S");
	rep(i, 0, m) printf("%lld ", V[i]);puts("V");
*/
	sort(a, a + m, cmpa), sort(b, b + m, cmpb);
	ll l = 0, r = S[m - 1];
	while (l + 1 < r) {
		ll z = (l + r) >> 1;
		check(z) ? r = z : l = z;
	}
	return check(l) ? l : r;
}
int main() {
	/*
	while (~scanf("%d%d", &n, &L)) {
		if (n == 0 && L == 0) break;
		rep(i, 1, n + 1) e[i].clear();
		rep(i, 1, n) {
			int a, b, l;
			scanf("%d%d%d", &a, &b, &l);
			e[a].pb(mp(b, l));
			e[b].pb(mp(a, l));
		}
		ll ans = solve();
		printf("%lld\n", ans);
	}
	*/
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d", &n);
		L = 1;
		rep(i, 1, n + 1) e[i].clear();	
		rep(i, 1, n) {
			int a, b;
			scanf("%d%d", &a, &b);
			e[a].pb(mp(b, 1));
			e[b].pb(mp(a, 1));
		}
		ll ans = solve();
		printf("%lld\n", ans);
	}
	return 0;
}
