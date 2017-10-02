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

const int P = 1e9 + 7;
int n , m , K , dp[1001][1<<4];
vector<pii> ele , fac;
inline void pp(int &x,int d){if((x+=d)>=P)x-=P;}

void dfs(int c,int mul,int mask){
	if(c == sz(fac)){
		ele.pb(mp(mul , mask));
	} else {
		rep(i,0,fac[c].se+1){
			dfs(c + 1 , mul , mask | ((i == fac[c].se) << c));
			mul *= fac[c].fi;
		}
	}
}

int main() {
	while(~scanf("%d%d%d",&n,&m,&K)){
		ele.clear();
		fac.clear();
		int x = m;
		for(int i=2;i*i<=x;++i) if(x % i == 0){
			int times = 0;
			while(x % i == 0) times++ , x /= i;
			fac.pb(mp(i , times));
		}
		if(x > 1) fac.pb(mp(x , 1));
		//for(auto e : fac) cout << e.fi << " " << e.se << endl;
		dfs(0 , 1 , 0);
		sort(all(ele));
		//for(auto e : ele) cout << e.fi << " " << e.se << endl;
		//cout << "~~~" << endl;
		int p = sz(fac);
		rep(i,0,n+1) rep(j,0,1<<p) dp[i][j] = 0;
		dp[0][0] = 1;
		rep(i,0,K) per(j,0,n+1) per(k,0,1<<p) if(dp[j][k]) {
			for(auto e : ele){
				if(e.fi + j > n) break;
				pp(dp[e.fi + j][k | e.se] , dp[j][k]);
			}
			dp[j][k] = 0;
		}
		printf("%d\n",dp[n][(1<<p)-1]);
	}
	return 0;
}
