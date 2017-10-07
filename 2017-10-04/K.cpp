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
namespace Centriod{
	const int N = 1e5 + 10 , P = 1e6 + 3;
	int vis[N] , sz[N] , n , val[N] , K , inv[P] , vis2[P] , opt[P] , times;
	vi g[N];
	pii best;
	void dfssz(int c,int fa,int Sz,int &rt){
		sz[c] = 1;
		for(auto t : g[c]) if(!vis[t] && t != fa) dfssz(t,c,Sz,rt) , sz[c] += sz[t];
		if(!rt && sz[c] * 2 > Sz) rt = c;
	}
	int gt[N] , id[N] , _;
	inline void Update(pii&a,int u,int v){
		if(u > v) swap(u , v);
		a = min(a , mp(u , v));
	}
	void dfs(int c,int fa,int mul){
		gt[_] = mul , id[_] = c;_++;
		for(auto t : g[c]) if(!vis[t] && t != fa)
			dfs(t , c , 1ll * mul * val[t] % P);
	}
	void dfs(int c){
		int rt=0;dfssz(c,0,0,rt);dfssz(c,0,sz[c],rt=0);
		vis[rt] = true;
		c = rt;
		times++;
		vis2[1] = times; opt[1] = c;
		for(auto t : g[c]) if(!vis[t]) {
			_ = 0;
			dfs(t , c , 1ll * val[t] % P);
			rep(i,0,_) {
				int a = 1ll * gt[i] * val[c] % P, b = id[i];
				if(a == 0) Update(best , b , c);
				else {
					int need = 1ll * inv[a] * K % P;
					//cout << a << " " << inv[a] << " " << need << " " << K << " " << b << " " << c << endl;
					if(vis2[need] == times) Update(best , b , opt[need]);
				}
			}
			rep(i,0,_) {
				int a = gt[i] , b = id[i];
				//cout << a << " " << b << " " << c << endl;
				if(vis2[a] == times) opt[a] = min(opt[a] , b);
				else vis2[a] = times , opt[a] = b;
			}
		}
		for(auto t : g[rt]) if(!vis[t]) dfs(t);
	}
	void solve(){
		inv[1] = 1;
		rep(i,2,P) inv[i] = (P - 1ll * (P / i) * inv[P % i] % P) % P;
		while(~scanf("%d%d",&n,&K)){
			rep(i,1,n+1) scanf("%d",val + i) , g[i].clear() , vis[i] = false;
			rep(i,1,n){
				int u,v;
				scanf("%d%d",&u,&v);
				g[u].pb(v);
				g[v].pb(u);
			}
			best = mp(n + 1 , n + 1);
			dfs(1);
			if(best.fi == n + 1) puts("No solution");
			else printf("%d %d\n",best.fi , best.se);
		}
	}
}

int main() {
	Centriod::solve();
	return 0;
}
