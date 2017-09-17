#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ul;
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
const int N = 3e3 + 7;
const int Q = 3e4 + 7;
const int M = 12;
const int P = 19260817;
const ll MASK = (1ll << 32) - 1;
#define cnt(x) __builtin_popcountll(x)
struct Mat {	
	const static int N = 64;
	ul r[N], c[N];	
	void clr(ul x) {
		rep(i, 0, N) r[i] = c[i] = x << i;
	}
	Mat operator*(const Mat &p) const {
		Mat ret; ret.clr(0);
		rep(i, 0, N) if (r[i]) 
			rep(j, 0, N) if (p.c[j]) {
//				ul x = (cnt((r[i] & p.c[j]) >> 32) + 
//						cnt((r[i] & p.c[j]) & MASK)) & 1;
				ul x = cnt(r[i] & p.c[j]) & 1;
				ret.r[i] |= x << j;	
				ret.c[j] |= x << i;
			}
		/*
		Mat tmp; tmp.clr(0);	
		rep(i, 0, N) rep(j, 0, N) {
			rep(k, 0, N) {
				tmp.r[i] ^= ((r[i] >> k & 1) & (p.c[j] >> k & 1)) << j; 	
			}
		}
		rep(i, 0, N) assert(tmp.r[i] == ret.r[i]);	
		*/
		return ret;
	}
	Mat operator^(int b) {
		Mat r, a = *this;
		r.out();
		while (b > 0) {
			if (b & 1) r = r * a;
			a = a * a, b >>= 1;
		}
		return r;
	}
	void out() {
		rep(i, 0, N) {
			rep(j, 0, N) cout << (r[i] >> j & 1); 
			cout << endl;
		}
	}
} a[N], f[N][M], g[N][M];
int n, q, pw[2][100];
vector<int> e[N];
int tot, w[N], s[N], dep[N], far[N], top[N], siz[N];
/*
   void dfs(int u, int p) {
   s[u] = -1, far[u] = p, siz[u] = 1;
   rep(i, 0, sz(e[u])) {
   int v = e[u][i];
   if (v == p) continue;
   dep[v] = dep[u] + 1;
   dfs(v, u);
   siz[v] += siz[u];
   if (s[u] == -1 || siz[v] > siz[s[u]])
   s[u] = v;
   }
   }
 */
void DFS(int u, int rt, int p) {
	w[u] = ++tot, top[u] = rt;	
	if (~s[u]) {
		DFS(s[u], rt, u);
	}
	rep(i, 0, sz(e[u])) {
		int v = e[u][i];
		if (v == p || v == s[u]) continue;
		DFS(v, v, u);
	}
}
int t[N][M];
void dfs(int u, int p) {	
	t[u][0] = p;	
	rep(i, 1, M) t[u][i] = t[t[u][i - 1]][i - 1];
	f[u][0] = a[u];	
	rep(i, 1, M) f[u][i] = f[u][i - 1] * f[t[u][i - 1]][i - 1];
	g[u][0] = a[u];	
	rep(i, 1, M) g[u][i] = g[t[u][i - 1]][i - 1] * g[u][i - 1];
	rep(i, 0, sz(e[u])) {
		int v = e[u][i];
		if (v == p) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}
Mat qry(int x, int y) {
	Mat U, D;
	U.clr(1), D.clr(1);
	if (dep[x] != dep[y]) {
		int d = abs(dep[x] - dep[y]);
		if (dep[x] > dep[y]) {
			rep(i, 0, M) if (d >> i & 1) {
				U = U * f[x][i];
				x = t[x][i];	
			}
		} else {
			rep(i, 0, M) if (d >> i & 1) {
				D = g[y][i] * D;
				y = t[y][i];
			}
		}
	}
	if (x == y)
		return U * a[x] * D;
//	dd(x), de(y);
	for (int i = M - 1; i >= 0; --i)
		if (t[x][i] != t[y][i]) {
			U = U * f[x][i], D = g[y][i] * D;	
			x = t[x][i], y = t[y][i];
		}
	return U * f[x][1] * g[y][0] * D;	
}
inline void inc(int &x, int y) {
	x += y;
	if (x >= P) x -= P;
}
int main() {
	rep(i, 0, 2) {
		ll B = !i ? 19 : 26;
		pw[i][0] = 1;
		rep(j, 1, 100) pw[i][j] = pw[i][j - 1] * B % P;
	}
	while (~scanf("%d%d", &n, &q)) {
		rep(i, 1, n + 1) e[i].clear();
		rep(i, 1, n) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].pb(v), e[v].pb(u);
		}
		ul seed;
		scanf("%llu", &seed);
		rep(i, 1, n + 1) {
			a[i].clr(0);
			rep(p, 1, 64 + 1) {
				seed ^= seed * seed + 15;
				rep(q, 1, 64 + 1) {
					ul x = (seed >> (q - 1)) & 1;
					a[i].r[p - 1] |= x << (q - 1);
					a[i].c[q - 1] |= x << (p - 1);
				}
			}
			//			a[i].out();
		}
		dfs(1, 0);
		rep(_q, 0, q) {
			int u, v;
			scanf("%d%d", &u, &v);
			Mat mat = qry(u, v);	
			//			mat.out();
			int ans = 0;
			rep(i, 0, 64) rep(j, 0, 64) if (mat.r[i] >> j & 1) {
				inc(ans, 1ll * pw[0][i + 1] * pw[1][j + 1] % P);
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
