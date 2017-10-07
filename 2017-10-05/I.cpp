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
const int N = 3e4 + 7;
bool End[N * 32];
int n, rt, tot, nxt[N * 32][2];
void ins(ll v, int l) {
	int p = rt;
	rep(i, 0, l) {
		int x = v >> (31 - i) & 1;
		if (nxt[p][x] == -1) {
			End[tot] = false;
			memset(nxt[tot], -1, sizeof(nxt[tot]));
			nxt[p][x] = tot++;
		}
		p = nxt[p][x];
	}
	End[p] = true;
}
vector<pair<ll, int> > ans;
void dfs(int t, int L, ll v) {
//	dd(t), dd(L), de(v);
	if (t == -1) {
		if (L <= 32) ans.pb(mp(v, L));
		return ;
	}
	if (End[t]) return ;
	rep(i, 0, 2) dfs(nxt[t][i], L + 1, v | ((ll)i << (31 - L)));
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		printf("Case #%d:\n", cas + 1);
		scanf("%d", &n);
		rt = 0, tot = 1;
		memset(nxt[rt], -1, sizeof(nxt[rt]));
		rep(i, 0, n) {
			int a, b, c, d, l;
			scanf(" %d.%d.%d.%d/%d", &a, &b, &c, &d, &l);
//			dd(a), dd(b), dd(c), dd(d), de(l);
			ll v = ((ll)a << 24) | ((ll)b << 16) | ((ll)c << 8) | d;
			ins(v, l);
		}
		ans.clear();
		if (n == 0) {
			ans.pb(mp(0, 0));
		} else {
			dfs(rt, 0, 0);
		}
		printf("%d\n", sz(ans));
		rep(i, 0, sz(ans)) {
			int x[4];
//			dd(ans[i].fi), de(ans[i].se);
			rep(j, 0, 4) 
				x[j] = (ans[i].fi >> (j * 8)) & 255;
			printf("%d.%d.%d.%d/%d\n", x[3], x[2], x[1], x[0], ans[i].se);
		}
	}
	return 0;
}
