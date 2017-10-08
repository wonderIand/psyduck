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
const int N = 1e3 + 7;
pii p[N];
int n, m;
int main() {
	
	int tcase = 0; scanf("%d", &tcase);
	rep(icase, 0, tcase) {
		///read
		scanf("%d%d", &n, &m);
		rep(i, 0, n) {
			int mi; scanf("%d", &mi);
			int ni; scanf("%d", &ni);
			rep(j, 0, mi) { int dig; scanf("%d", &dig); }
			p[i] = mp(ni - mi + 1, mi);
		}
		///prework
		sort(p, p + n);
		int ans = 0;
		rep(i, 0, n) ans = max(ans + 1, p[i].fi) + p[i].se - 1;
		printf("%d\n", ans);
	}

	return 0;
}
