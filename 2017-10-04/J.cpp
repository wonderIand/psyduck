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
int main() {
	
	int na, nb, nc;
	for (; ~scanf("%d%d%d", &na, &nb, &nc); ) {
		int m = 0;
		m += min(na, 2); na -= min(na, 2);
		m += min(nb, 2); nb -= min(nb, 2);
		m += min(nc, 2); nc -= min(nc, 2);
		ll ans = 0;
		ans += ((ll)na + nb + nc) * m;
		ans += 1ll * m * (m - 1) / 2;
		printf("%lld\n", ans);
	}

	return 0;
}
