#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b)-1; i>=(a); i--)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;

typedef double db;
typedef long long ll;

#define fi first
#define se second
#define mp make_pair
typedef pair<int, int> pii;

#define pb push_back
typedef vector<int> vi;

const int N = 1e4 + 7;
vector<pii> G[N];
///-----------
int n, m;
int dp[N];
int deg[N];
int main()
{
	int tcase = 0; scanf("%d", &tcase);
	rep(icase, 0, tcase) {
		///read
		scanf("%d%d", &n, &m);
		rep(i, 1, n + 1) deg[i] = 0;
		rep(i, 1, n + 1) G[i].clear();
		rep(_m, 0, m) {
			int a, b, c; scanf("%d%d%d", &a, &b, &c);
			deg[a]++;
			G[b].pb(mp(a, c));
		}
		///work
		queue<int> que;
		rep(i, 1, n + 1) if (!deg[i]) que.push(i);
		rep(i, 1, n + 1) dp[i] = 0;
		for (; !que.empty(); que.pop()) {
			int u = que.front();
			rep(_v, 0, sz(G[u])) {
				int v = G[u][_v].fi;
				int c = G[u][_v].se;
				dp[v] = max(dp[v], dp[u] + c);
				if (!--deg[v]) que.push(v);
			}
		}
		///print
		int ans = 0;
		rep(i, 1, n + 1) ans = max(ans, dp[i]);
		printf("%d\n", ans);
	}

	return 0;
}

