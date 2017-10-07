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
const int N = 505;
const db EPS = 1e-8;
db A[N][N];
namespace Gauss {
	int solve(int n, int m) {
		int i = 0, x = 0;	
		for (; i < n && x < m; ++i, ++x) {
			int r = i;
			rep(j, i + 1, n) if (fabs(A[j][x]) > fabs(A[r][x])) r = j;
			if (fabs(A[r][x]) < EPS) --i;
			else {
				if (r != i) rep(j, 0, m + 1) swap(A[r][j], A[i][j]);
				for (int j = m; j >= x; --j) A[i][j] /= A[i][x];
				rep(j, 0, n) if (i != j && fabs(A[j][x]) >= EPS)
					for (int k = m; k >= x; --k)
						A[j][k] -= A[i][k] * A[j][x];
			}
		}
		rep(k, i, n) if (fabs(A[k][m]) >= EPS) return -1;
		return m - i;
	}
};
int MOD;
ll kpow(ll a, ll b) {
	ll r = 1;
	while (b > 0) {
		if (b & 1) r = r * a % MOD;
		a = a * a % MOD, b >>= 1;
	}
	return r;
}
namespace Det {
	int A[N][N];
	int solve(int n) {
		int x = 1;
		for (int i = 0; i < n; ++i) {
			if (!A[i][i]) {
				int j;
				for (j = i + 1; j < n; ++j)
					if (A[j][i]) break;
				if (j == n) return 0;	
				for (int k = i; k < n; ++k) swap(A[i][k], A[j][k]);	
				x = 1ll * x * (MOD - 1) % MOD;
			}
			x = 1ll * x * A[i][i] % MOD;	
			int sb = kpow(A[i][i], MOD - 2);
			for (int k = i + 1; k < n; ++k)
				A[i][k] = 1ll * A[i][k] * sb % MOD;
			for (int j = i + 1; j < n; ++j)
				for (int k = i + 1; k < n; ++k)
					A[j][k] = (A[j][k] - 1ll * A[j][i] * A[i][k] % MOD + MOD) % MOD;
		}
//		de(x);
		return x;
	}
};
int P[3] = { (int)1e9 + 7, 258280327, (479 << 21) + 1};
bool isprime(int x){
	for(int i=2;i*i<=x;++i) if(x%i==0) return 0;
	return 1;
}
int solve(int n) {
	rep(t, 0, 3) {
		MOD = P[t];
		rep(i, 0, n) rep(j, 0, n) {
			Det::A[i][j] = round(100 * A[i][j]);
			if (Det::A[i][j] < 0) Det::A[i][j] += MOD;
		}
//		printf("r = %lld\n", (1ll * Det::A[0][0] * Det::A[1][1] - 1ll * Det::A[1][0] * Det::A[0][1] % MOD + MOD) % MOD);
//		rep(i, 0, n) {
//			rep(j, 0, n) printf("%d ", Det::A[i][j]);
//			puts("");
//		}
		if (Det::solve(n)) return 0;
//		rep(i, 0, n) {
//			rep(j, 0, n) printf("%d ", Det::A[i][j]);
//			puts("");
//		}
//		puts("");
	}
	return 1;
}
int main() {
	rep(t,0,3) if(!isprime(P[t])) puts("??");
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		int k;
		scanf("%d", &k);
		rep(i, 0, k) rep(j, 0, k) scanf("%lf", &A[i][j]);
		rep(i, 0, k) A[i][i] -= 1, A[i][k] = 0;
		int ret = Gauss::solve(k, k);
		//if (cas % 5) putchar(' ');
		if(cas % 5 != 0) putchar(' ');
		printf("%d", ~ret ? 1 : 0);
		if (cas % 5 == 4) puts("");
	}
	return 0;
}
