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
const int N = 303 , P = 1e9 + 7;
int n , sz[N];
vi G[N];
int dp[N][N + N][3] , f[N + N][3] , g[N + N][3];
inline void pp(int &x,int d){
	if((x+=d)>=P) x-=P;
}

void dfs(int c,int fa){
	sz[c] = 1;
	for(auto t : G[c]) if(t != fa){
		dfs(t , c);
		sz[c] += sz[t];
	}
	int cursz = 1;
	rep(i,-cursz,cursz + 1) rep(j,0,3) f[i + N][j] = 0;
	f[0 + N][1] = 1;
	f[0 + N][2] = 2;
	for(auto t : G[c]) if(t != fa){
		int newsz = cursz + sz[t];
		rep(i,-newsz,newsz + 1) rep(j,0,3) g[i + N][j] = 0;
		rep(i,-cursz,cursz + 1) rep(j,0,3) if(f[i + N][j]) rep(ii,-sz[t],sz[t]+1) rep(jj,0,3) if(dp[t][ii + N][jj]){
			int add = 1ll * f[i + N][j] * dp[t][ii + N][jj] % P;
			if(j == 2) {
				pp(g[i + ii + (jj == 2 ? 0 : (jj == 1 ? 1 : -1)) + N][j] , add);
			} else {
				if(jj == 2) pp(g[i + ii + N][j] , add);
				else pp(g[i + ii + N][j ^ jj] , add);
			}
		}
		rep(i,-newsz,newsz + 1) rep(j,0,3) f[i + N][j] = g[i + N][j];
		cursz = newsz;
	}
	rep(i,-sz[c],sz[c] + 1) rep(j,0,3) dp[c][i + N][j] = f[i + N][j];
}

int main() {
	while(~scanf("%d",&n)){
		rep(i,1,n+1) G[i].clear();
		rep(i,1,n){
			int u,v;
			scanf("%d%d",&u,&v);
			G[u].pb(v);
			G[v].pb(u);
		}
		dfs(1 , 0);
		int ans = 0;
		rep(i,-n,n+1) rep(j,0,3){
			int cnt = f[i + N][j];
			int val = max(0 , i + (j == 2 ? 0 : (j == 1 ? 1 : -1)));
			pp(ans , 1ll * cnt * val % P);
		}
		ans = 3ll * ans % P;
		printf("%d\n",ans);
	}
	return 0;
}
