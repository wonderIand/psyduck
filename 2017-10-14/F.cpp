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
const int N = 303;
int g[N][N] , can[N][N] , n , m;
int fa[N] , G[N][N];
vi belong[N];

int F(int x){return fa[x] == x ? x : fa[x] = F(fa[x]);}

int main() {
	scanf("%d%d",&n,&m);
	rep(i,0,n) can[i][i] = 1 , fa[i] = i;
	rep(i,0,m) {
		int u,v;
		scanf("%d%d",&u,&v);
		--u;--v;
		g[u][v] = 1;
		can[u][v] = 1;
	}
	vector<pii> ans;
	rep(k,0,n) rep(i,0,n) rep(j,0,n) can[i][j] |= can[i][k] & can[k][j];
	rep(i,0,n) rep(j,i+1,n) if(can[i][j] && can[j][i]) {
		int a = F(i) , b = F(j);
		fa[a] = b;
	}
	rep(i,0,n) belong[F(i)].pb(i);
	rep(i,0,n) if(sz(belong[i])>1) rep(j,0,sz(belong[i])) ans.pb(mp(belong[i][j]+1,belong[i][(j+1)%sz(belong[i])]+1));
	rep(i,0,n) rep(j,0,n) can[i][j]=i==j;
	rep(i,0,n) rep(j,0,n) if(g[i][j] && F(i) != F(j)) G[F(i)][F(j)]=can[F(i)][F(j)]=1;
	rep(k,0,n) rep(i,0,n) rep(j,0,n) can[i][j] |= can[i][k] & can[k][j];
	rep(i,0,n) rep(j,0,n) if(G[i][j]) {
		bool fd=false;
		rep(k,0,n) if(k!=i&&k!=j) fd|=can[i][k]&can[k][j];
		if(!fd) ans.pb(mp(i+1,j+1));
	}
	printf("%d %d\n",n,sz(ans));
	rep(i,0,sz(ans)) printf("%d %d\n",ans[i].fi,ans[i].se);
	return 0;
}
