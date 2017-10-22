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
const int INF = 1e9 + 7;
const int N = 3e2 + 7;
int dig[N], ok[N][N], dp[N][N], c[N][N], n;
void mut(int &a, int b) { a = 1ll * a * b % INF; }
void inc(int &a, int b) { if ((a += b) >= INF) a -= INF; }
int main() {
	
	//read
	scanf("%d", &n);
	rep(i, 0, n) scanf("%d", &dig[i]);

	//prework
	memset(dp, 0, sizeof(dp));
	memset(ok, 0, sizeof(ok));
	memset(c, 0, sizeof(c));
	rep(i, 0, n) rep(j, 0, n) if (i != j && __gcd(dig[i], dig[j]) > 1) c[i][j] = 1;
	rep(i, 0, n) dp[i][i] = ok[i][i] = 1;
	rep(i, 0, n) dp[i][i + 1] = ok[i][i + 1] = c[i][i + 1];
	rep(len, 2, n) {
		rep(l, 0, n - len) {
			int r = l + len;
			if (c[l][r])
				rep(k, l, r) inc(ok[l][r], 1ll * dp[l][k] * dp[k + 1][r] % INF);
			rep(k, l + 1, r + 1) inc(dp[l][r], 1ll * ok[l][k] * dp[k][r] % INF);
		//	de(l);
		//	de(r);
		//	de(dp[l][r]);
		//	de(ok[l][r]);
		}
	}

	//work
	int ans = 0;
	rep(i, 1, n)
		inc(ans, 1ll * ok[0][i] * dp[i][n - 1] % INF);
	printf("%d", ans);

	return 0;
}
