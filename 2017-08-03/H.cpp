#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
//-------
const int N = 1e5 + 10;
vi tree[N];
int T,n,m,K;
int sz[N];
ll w[N];

struct ele{
	int a,b,c,d,w;
	void input(){scanf("%d%d%d%d%d",&a,&b,&c,&d,&w);}
	bool operator < (const ele&b) const{
		return w < b.w;
	}
}e[N];

int par[N][20] , dep[N];
void dfs(int c,int fa){
	par[c][0] = fa;
	rep(i,1,20) par[c][i] = par[par[c][i-1]][i-1];
	for(auto t : tree[c]) if(t != fa) dep[t] = dep[c] + 1 , dfs(t , c);
}
int lca(int a,int b){
	if(dep[a] < dep[b]) swap(a , b);
	per(i,0,20) if((dep[a]-dep[b])>>i&1) a = par[a][i];
	if(a == b) return a;
	per(i,0,20) if(par[a][i] != par[b][i])
		a = par[a][i] , b = par[b][i];
	return par[a][0];
}
int f[N] , g[N];
int F(int x){return x==f[x]?x:f[x]=F(f[x]);}
int G(int x){return x==1?1:(F(x)==F(par[x][0])?g[x]=G(g[par[x][0]]):x);}

void load(int x,int y,vi &v){
	while(G(x) != G(y)){
		v.pb(G(x));
		x = par[G(x)][0];
	}
	v.pb(G(x));
}

void solve(){
	scanf("%d%d",&n,&K);
	rep(i,1,n+1) tree[i].clear() , sz[i] = 1 , w[i] = 0 , f[i]=g[i]=i;
	int u,v;
	rep(i,1,n){
		scanf("%d%d",&u,&v);
		tree[u].pb(v);
		tree[v].pb(u);
	}
	rep(i,0,K){
		e[i].input();
	}
	dfs(1 , 0);
	sort(e , e + K);
	rep(i,0,K){
		int a = e[i].a , b = e[i].b , c = e[i].c , d = e[i].d , cost = e[i].w;
		int lca1 = lca(a , b) , lca2 = lca(c , d);
		vi v;
		load(a , lca1 , v);
		load(b , lca1 , v);
		load(c , lca2 , v);
		load(d , lca2 , v);
		for(int i=0;i+1<sz(v);i+=2){
			int x=v[i],y=v[i+1];
			int X = F(x) , Y = F(y);
			if(X != Y){
				f[Y] = X;
				sz[X] += sz[Y];
				w[X] += w[Y];
				w[X] += cost;
			}
			v.pb(X);
		}
		//for(auto e : v) cout << e << " ";cout << endl;
	}
	int top=F(1);
	printf("%d %lld\n",sz[top],w[top]);
}

int main() {
	scanf("%d",&T);
	rep(i,0,T) solve();
	return 0;
}
