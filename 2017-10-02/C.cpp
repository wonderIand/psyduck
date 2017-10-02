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
int n, w[5];
int left(int x) {
	int r = x % 1024;
	if (r == 0 && x > 0) r = 1024;
	return r;
}
int solve() {
	if (n <= 3) return 1024;
	if (n == 4) {
		rep(i, 0, n)
			rep(j, i + 1, n)
				rep(k, j + 1, n)
					if ((w[i] + w[j] + w[k]) % 1024 == 0)
						return 1024;
		int ret = 0;
		rep(i, 0, n) rep(j, i + 1, n)
			ret = max(ret, left(w[i] + w[j]));
		return ret;
	}
	if (n == 5) {	
		int ret = 0;
		rep(i, 0, n)
			rep(j, i + 1, n)
				rep(k, j + 1, n)
					if ((w[i] + w[j] + w[k]) % 1024 == 0) {
						int now = 0;	
						rep(t, 0, n) if (!(t == i || t == j || t == k))
							now += w[t];
						ret = max(ret, left(now));
					}
		return ret;
	}
}
int main() {
	while (~scanf("%d", &n)) {
		rep(i, 0, n) scanf("%d", w + i);
		printf("%d\n", solve());
	}
	return 0;
}
