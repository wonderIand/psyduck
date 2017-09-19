#include<bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b-1); i>=(a); i--)
#define de(x) cout << #x << " => " << x << endl
using namespace std;

#define fi first
#define se second
#define mp make_pair
typedef pair<int,int> pii;

#define pb push_back
typedef vector<int> vi;

typedef long long ll;
typedef long double ld;

///----------------------------------------------
const int MOD = 998244353;
int qpow(int a, int b) {
	int ret = 1;
	for (; b; b >>= 1) {
		if (b & 1) ret = 1ll * ret * a % MOD;
		a = 1ll * a * a % MOD;
	}
	return ret;
}
int C(int a, int b) {
	if (a < b) return 0;
	int ret = 1;
	b = min(b, a - b);
	rep(i, 0, b) {
		ret = 1ll * ret * (a - i) % MOD;
		ret = 1ll * ret * qpow(i + 1, MOD - 2) % MOD;
	}
	return ret;
}		
int lucas(int a, int b) {
	if (b == 0) return 1;
	return 1ll * C(a % MOD, b % MOD) * lucas(a / MOD, b / MOD) % MOD;
}
int inv(int a) { return qpow(a, MOD - 2); }
///------
int n, m;
int main() {
	
	for (; ~scanf("%d%d", &n, &m); ) {
		if (n % 2 != m % 2 || m > n) puts("0"); else {
			int k = (n - m) / 2;
			int ans = 1ll * n *  inv(2) % MOD;
			ans = 1ll * ans * qpow(2, n - 2 * k) % MOD;
			ans = 1ll * ans * inv(n - k) % MOD;
			ans = 1ll * ans * lucas(n - k, k) % MOD;
			if (k & 1) ans = MOD - ans;
			printf("%d\n", ans);
		}
	}

}
