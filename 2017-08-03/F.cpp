#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int ui;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
//-------
const int N = 255;
const int M = 16;
const int AM = (1 << M) - 1;
int n, m, lbit[1 << M];
char str[N];
struct Bit {
	static const int B = 9;
	static const int W = 5;
	static const int AW = (1 << W) - 1;
	ui a[B];
	void clr() {
		rep(i, 0, B) a[i] = 0;
	}
	int get(int x) {
		return a[x >> W] >> (x & AW) & 1;
	}
	void set(int x, int v = 1) {
		a[x >> W] ^= get(x) << (x & AW);
		a[x >> W] |= (ll) v << (x & AW);
	}
} e[N], ne[N], S;
void init() {
	lbit[0] = -1;
	rep(mask, 1, 1 << M) {
		rep(i, 0, M) if (mask >> i & 1) {
			lbit[mask] = i;
			break;
		}
	}
}
inline int get(ui x) {
	if (x & AM) return lbit[x & AM];
	if (x >> M) return M + lbit[x >> M];
	return -1;
}
int cnt, top, sta[N];
void dfs(int u) {
	S.set(u, 0);
	for (int i = 0, v; i < e[u].B; ++i) {
		v = get(e[u].a[i] & S.a[i]);
		if (~v) dfs(v + (i << e[u].W)), --i;
	}
	sta[++top] = u;
}
void rdfs(int u) {
	S.set(u, 0), ++cnt;
	for (int i = 0, v; i < ne[u].B; ++i) {
		v = get(ne[u].a[i] & S.a[i]);
		if (~v) rdfs(v + (i << ne[u].W)), --i;
	}
}
int Kosaraju() {
	int ret = 0;
	S.clr();
	rep(i, 0, n) S.set(i, 1);
	top = 0;
	for (int i = 0; i < S.B; ++i) {
		int u = get(S.a[i]);
		if (~u) dfs(u + (i << S.W)), --i;
	}
	S.clr();
	rep(i, 0, n) S.set(i, 1);
	while (top > 0) {
		int u = sta[top--];
		if (!S.get(u)) continue;
		cnt = 0;
		rdfs(u);
		ret += cnt * (cnt - 1) / 2;
	}
	return ret;
}
int main() {
	init();
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d%d", &n, &m);
		rep(i, 0, n) e[i].clr(), ne[i].clr();
		rep(i, 0, n) {
			scanf(" %s", str);
			rep(j, 0, n) {
				int x = str[j] - '0';
				e[i].set(j, x);
				ne[j].set(i, x);
			}
		}
		rep(_m, 0, m) {
			int ki;
			scanf("%d", &ki);
			rep(i, 0, ki) {
				int u, v, w;
				scanf("%d%d", &u, &v);
				--u, --v;
				w = e[u].get(v);
				e[u].set(v, w ^ 1);
				ne[v].set(u, w ^ 1);
			}
			printf("%d\n", Kosaraju());
		}
	}
	return 0;
}
