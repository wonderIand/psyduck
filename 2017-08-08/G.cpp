#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------

const int P = 998244353;
const int N = 5e4 + 10;
int n,m,f[N][200] , g[N][200] , a[200] , b[200] , c[200] , x[200] , y[200];
vi G[N];
inline void pp(int &x,int d){if((x+=d)>=P)x-=P;}
int dfs(int c,int fa){
	int sz = 1;
	int *A = f[c] , *B = g[c];
	rep(i,0,m) A[i]=B[i]=0; A[0]=B[0]=1;
	for(auto t : G[c]) if(t!=fa){
		int sonsz = dfs(t , c);
		int lft=min(m,sz) , rgt=min(m,sonsz);
		rep(i,0,rgt) a[i]=(2ll*g[t][i]+f[t][i])%P,b[i]=(a[i]+f[t][i])%P;
		rep(i,0,m) x[i]=y[i]=0;
		rep(i,0,lft) rep(j,0,rgt) pp(x[(i+j)%m],1ll*A[i]*a[j]%P);
		rep(i,0,lft) rep(j,0,rgt) pp(y[(i+j)%m],1ll*B[i]*b[j]%P);
		rep(i,0,m) A[i]=x[i],B[i]=y[i];
		sz += sonsz;
	}
	if(sz == 1) B[0]=0;
	else {
		rep(i,0,m) ::c[i]=(B[i]-A[i]+P)%P;
		rep(i,0,m) B[(i+1)%m]=::c[i];
	}
	return sz;
}

void solve(){
	scanf("%d%d",&n,&m);
	rep(i,1,n+1) G[i].clear();
	rep(i,1,n){
		int u,v;scanf("%d%d",&u,&v);
		G[u].pb(v);
		G[v].pb(u);
	}
	dfs(1,0);
	int ans=f[1][0];
	pp(ans,g[1][0]);
	printf("%d\n",ans);
}

int main() {
	int T;scanf("%d",&T);
	rep(i,0,T) solve();
	return 0;
}
