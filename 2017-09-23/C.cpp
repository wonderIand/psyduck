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
const int N = 307;
const int M = 10;
int n, m, P, a[N][N], lg[N], pre[N][N];
pii val[N][N][M];
inline pii _min(const pii &x, const pii &y) {
	return a[x.fi][x.se] < a[y.fi][y.se] ? x : y;
}
void gao(pii f[][M], int n) {
	rep(j, 1, M)
		for (int i = 0; i + (1 << j) - 1 < n; ++i) 
			f[i][j] = _min(f[i][j - 1], f[i + (1 << j >> 1)][j - 1]);
}
pii qry(pii f[][M], int l, int r) {
	int k = lg[r - l + 1];
	return _min(f[l][k], f[r - (1 << k) + 1][k]);
}
int getsum(int sum[], int l, int r) {
	if (!l) return sum[r];
	return sum[r] - sum[l - 1];
}
int ans;
int dp[N][2];
void solve() {
	rep(l, 0, m) rep(r, l, m) {
		if (l == 0 && r == m - 1) continue;
		dp[0][0] = getsum(pre[0], l, r);
		pii imiv = qry(val[0], l, r);
		dp[0][1] = dp[0][0] + P - a[imiv.fi][imiv.se];
		rep(i, 1, n) {
			int isum = getsum(pre[i], l, r);
			pii imiv = qry(val[i], l, r);
			dp[i][0] = max(0, dp[i - 1][0]) + isum;
			dp[i][1] = dp[i][0] + P - a[imiv.fi][imiv.se];
			dp[i][1] = max(dp[i][1], dp[i - 1][1] + isum);
		}
		rep(i, 0, n) ans = max(ans, max(dp[i][0], dp[i][1]));
	}
	vi tmp; tmp.resize(n);
	rep(i, 0, n) tmp[i] = getsum(pre[i], 0, m - 1);
	rep(i, 1, n) tmp[i] += tmp[i - 1];
	rep(i, 0, n) {
		int mi = 100000000;
		rep(j, i, n) {
			if (i == 0 && j == n - 1) continue;
			pii imiv = qry(val[j], 0, m - 1);
			mi = min(mi, a[imiv.fi][imiv.se]);
			int dai = tmp[j]; if (i > 0) dai -= tmp[i - 1];
			ans = max(ans, dai + max(0, P - mi));
		}
	}
}
int main() {
	lg[1] = 0;
	rep(i, 2, N) lg[i] = 1 + lg[i >> 1];
	while (~scanf("%d%d%d", &n, &m, &P)) {
		rep(i, 0, n) {
			rep(j, 0, m) scanf("%d", &a[i][j]), val[i][j][0] = mp(i, j);
			pre[i][0] = a[i][0];
			rep(j, 1, m) pre[i][j] = pre[i][j - 1] + a[i][j];
			gao(val[i], m);
		}
		int mi = 100000000;
		ans = 0; rep(i, 0, n) rep(j, 0, m) ans += a[i][j], mi = min(mi, a[i][j]); ans += P - mi;
		//de(ans);
		solve();
		printf("%d\n", ans);
	}
	return 0;
}
