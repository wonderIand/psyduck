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
#define de(x) cout << #x << " = " << x << ebdl
//-------
const int N = 1e5 + 7;
const int P = 1e9 + 7;
int n, dp[N], pd[N];
inline void inc(int &x, int y) {
	x += y;
	if (x >= P) x -= P;
}
int main() {
	scanf("%d", &n);
	dp[n] = 1;
	int ans = 0;
	rep(k, 0, 20) {
		rep(i, 1, n + 1) pd[i] = dp[i], dp[i] = 0, inc(ans, pd[i]);
		rep(i, 1, n + 1) inc(dp[i >> 1], pd[i]);
		for (int i = n; i > 0; --i)
			inc(dp[i], dp[i + 1]);
	}
	printf("%d\n", ans);
	return 0;
}
