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
const int N = 1e3 + 7;
int nc, np, ns;
vi vc[N], vp[N];
int main() {
	
	for (; ~scanf("%d%d%d", &nc, &np, &ns) && nc; ) {
		///init
		rep(i, 1, nc + 1) vc[i].clear();
		rep(i, 1, np + 1) vp[i].clear();
		///read
		int p; cin >> p;
		int sumc = 0, sump = 0;
		rep(_p, 0, p) {
			char tp1[20], tp2[20];
			int id1, id2;
			scanf(" %s%d %s%d", tp1, &id1, tp2, &id2);
			if (strcmp(tp1, "clothes") == 0) vc[id1].pb(id2), sumc++;
				else vp[id1].pb(id2), sump++;
		}
		///work
		ll ans = 1ll * nc * np * ns;
		ans -= 1ll * sumc * ns;
		ans -= 1ll * sump * nc;
		rep(i, 1, nc + 1) {
			rep(_v, 0, sz(vc[i])) {
				int v = vc[i][_v];
				ans += sz(vp[v]);
			}
		}
		///print
		cout << ans << endl;
	}
		


	return 0;
}
