#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
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
const int N = 3e4 + 7;
const ll LINF = 2e18 + 7;
ll K;
int w[4];
ll f[4][N * 6];
bool v[4][N * 6];
ll solve(int G) {
	rep(i, 0, 4) rep(j, 0, G) f[i][j] = LINF, v[i][j] = 0;
	priority_queue<pair<ll, pii> > que;
	que.push(mp(0, mp(1, 0)));
	while (!que.empty()) {
		ll F = -que.top().fi;
		pii p = que.top().se;
		que.pop();
		if (v[p.fi][p.se]) continue;
		f[p.fi][p.se] = F, v[p.fi][p.se] = 1;
		if (F >= K) continue;
//		printf("f[%d][%d] = %lld\n", p.fi, p.se, f[p.fi][p.se]);
		// fi - 1
		int y = (p.fi + 3) & 3;
		int g = (p.se + w[y]) % G;
		if (f[y][g] > F + w[y]) {
			f[y][g] = F + w[y];
			que.push(mp(-f[y][g], mp(y, g)));
		}
		// fi + 1
		y = (p.fi + 1) & 3;
		g = (p.se + w[p.fi]) % G;
		if (f[y][g] > F + w[p.fi]) {
			f[y][g] = F + w[p.fi];
			que.push(mp(-f[y][g], mp(y, g)));
		}
	}
	ll ans = LINF;
	rep(j, 0, G) 
		if (f[1][j] >= K) {
			ans = min(ans, f[1][j]);
		} else {
			ans = min(ans, (K - f[1][j] + G - 1) / G * G + f[1][j]);
//			printf("j = %d, f = %lld, ret = %lld\n", j, f[1][j], (K - f[1][j] + G - 1) / G * G + f[1][j]);
		}
//	dd(G), de(ans);
	return ans;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%lld", &K);	
		rep(i, 0, 4) scanf("%d", w + i);
		ll ans = LINF;	
		ans = min(ans, solve(2 * w[0]));
		ans = min(ans, solve(2 * w[1]));
//		ans = min(ans, solve(2 * (w[0] + w[3])));
//		ans = min(ans, solve(2 * (w[1] + w[2])));
//		ans = min(ans, solve(2 * (w[0] + w[3] + w[2])));
//		ans = min(ans, solve(2 * (w[1] + w[2] + w[3])));
		ans = min(ans, solve(w[0] + w[1] + w[2] + w[3]));
		cout << ans << endl;
	}
	return 0;
}
