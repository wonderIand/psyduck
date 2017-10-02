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
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 21;
ll mask[N + N][2] , all[N + N];
int n , m;

namespace solve_edgebig {
	int dp[1 << N] , pre[1 << N] , ele[1 << N];
	void main() {
		vi v;
		rep(i,1,n) if(~all[0] >> i & 1) v.pb(i);
		memset(dp , -1 , sizeof(dp));
		dp[0] = 0;
		int m = sz(v);
		rep(i,0,1<<m) if(dp[i] != -1) {
			ll forbid = 0;
			rep(j,0,m) if(i >> j & 1) {
				int a = v[j];
				forbid |= mask[0][1] & mask[a][0];
				forbid |= mask[0][0] & mask[a][1];
			}
			rep(j,0,m) if(~i >> j & 1) {
				int ni = i | (1 << j);
				int a = v[j];
				ll ok = (mask[0][1] & mask[a][1]) | (mask[0][0] & mask[a][0]);
				ok &= ((1ll << n) - 1) ^ forbid;
				if(ok) {
					dp[ni] = 0;
					pre[ni] = i;
					ele[ni] = __builtin_ctzll(ok);
				}
			}
		}
		int c = 0 , ans = 0;
		rep(i,0,1<<m) if(dp[i] != -1){
			int t = __builtin_popcount(i);
			if(t > ans) ans = t , c = i;
		}
		printf("%.16f\n",1. * (ans + __builtin_popcountll(mask[0][0])) / (n - 1));
		vector<int> way;
		ll mask = 0;
		for(;c;c=pre[c]) {
			if(~mask >> ele[c] & 1) way.pb(ele[c]) , mask |= 1ll << ele[c];
		}
		rep(i,0,n) if((all[0] >> i & 1) && (~mask >> i & 1)) way.pb(i);
		rep(i,0,sz(way)) printf("%d%c",way[i] + 1," \n"[i+1==sz(way)]);
	}
}

namespace solve_edgesmall {
	int dp[1 << N] , pre[1 << N];
	void main() {
		vi v;
		rep(i,0,n) rep(j,0,2) if(mask[0][j] >> i & 1) v.pb(i);
		memset(dp , -1 , sizeof(dp));
		dp[0] = 0;
		int m = sz(v);
		ll remain = (1ll << n) - 2;
		rep(i,0,sz(v)) remain ^= 1ll << v[i];
		rep(i,0,1<<m) if(dp[i] != -1) {	
			ll edge = 0;
			rep(j,0,m) if(i >> j & 1) edge |= 1ll << v[j];
			ll cand = remain;
			rep(j,0,n) if((cand >> j & 1) && (all[j] & edge)) cand ^= 1ll << j;
			rep(j,0,m) if(~i >> j & 1) {
				int ni = i | 1 << j;
				int a = v[j] , type = (mask[0][0] >> a & 1) ? 0 : 1;
				int t = dp[i] + __builtin_popcountll(mask[a][type] & cand);
				if(t > dp[ni]) dp[ni] = t , pre[ni] = i;
			}
		}
		int up = __builtin_popcountll(mask[0][0]) + dp[(1<<m)-1];
		printf("%.16f\n",1. * up / (n - 1));
		vi ans;
		int c = (1 << m) - 1;
		for(;c;c=pre[c]) ans.pb(__builtin_ctz(c ^ pre[c]));
		reverse(all(ans));
		rep(i,0,sz(ans)) printf("%d%c",v[ans[i]] + 1 , " \n"[i+1==sz(ans)]);
	}
}

int main() {
	cin >> n >> m;
	rep(i,0,m){
		int u , v , type;
		cin >> u >> v >> type;
		--u;--v;
		mask[u][type] |= 1ll << v;
		mask[v][type] |= 1ll << u;
	}
	rep(i,0,n) all[i] = mask[i][0] | mask[i][1];
	if(__builtin_popcountll(mask[0][0] | mask[0][1]) <= 21) solve_edgesmall::main();
	else solve_edgebig::main();
	return 0;
}
