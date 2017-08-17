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
const int N = 2e3 + 7;
const int MOD = 1e9 + 7;
int n, m, g[N][N], c[N][N], f[N];
void inc(int &x, int y) {
	x += y;
	if (x >= MOD) x -= MOD;
}
int main() {
	rep(i, 0, N) {
		c[i][0] = c[i][i] = 1;
		rep(j, 1, i) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
	}
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d%d", &n, &m);
		rep(i, 0, m + 1) rep(j, 0, n + 1) g[i][j] = 0;		
		g[0][0] = 1;
		rep(i, 0, m + 1) {
			rep(j, 0, n) {
				if (!g[i][j]) continue;	
				inc(g[i][j + 1], 1ll * i * g[i][j] % MOD);	
				if (i < m)
					inc(g[i + 1][j + 1], 1ll * g[i][j] * c[i + 1][i] % MOD);
			}
		}
//		rep(i, 1, m + 1)
//			rep(j, 1, n + 1) printf("g[%d][%d] = %d\n", i, j, g[i][j]);
		
//		de(g[1][2]);
//		de(g[2][2]);
//		rep(i, 1, m + 1) f[i] = (1ll * f[i - 1] * i % MOD + g[i][n]) % MOD;

		int ans = 0;
		rep(i, 1, m + 1) {
//			de(ans);
//			inc(ans, 1ll * c[m][i] * g[i][n] % MOD * f[m - i] % MOD);
			int tmp = 0;
			rep(j, 1, m - i + 1) {
				inc(tmp, 1ll * c[m - i][j] * g[j][n] % MOD);
			}
			inc(ans, 1ll * tmp * c[m][i] % MOD * g[i][n] % MOD);
		}
		
		printf("%d\n", ans);
	}
	return 0;
}
