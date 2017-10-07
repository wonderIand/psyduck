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

const int N = 202;
vi g[N];
int w[N] , K , n;
namespace DCC{
	const int N = 1010;
	vi key , dcc[N];
	int dfn[N] , low[N] , st[N] , _st , _;
	vi ng[N];
	void dfs(int c,int dep,const vi g[]){
		int cc=0,out=1<dep;st[_st++]=c;
		dfn[c]=low[c]=dep;
		for(auto t:g[c]){
			if(!dfn[t]){
				dfs(t,dep+1,g);
				low[c]=min(low[c],low[t]);
				if(low[t]>=dfn[c]){
					if(++out==2) key.pb(c);
					while(st[--_st]!=t) dcc[st[_st]].pb(_);
					dcc[c].pb(_);dcc[t].pb(_++);
				}
			} else if(dfn[t] != dfn[c] - 1 || cc++)
				low[c] = min(low[c] , dfn[t]);
		}
	}
	const int inf = 1<<30;
	int f[N][10] , dissum[N] , wsum[N] , tmp[10];
	inline void Update(int &x,int d){
		x = min(x , d);
	}
	void dfs(int c,int fa){
		dissum[c] = 0;wsum[c] = w[c];
		rep(i,0,K+1) f[c][i] = inf;
		if(c > n) f[c][0] = 0;
		else f[c][1] = 0;
		for(auto t : ng[c]) if(t != fa){
			dfs(t , c);
			rep(i,0,K+1) tmp[i] = inf;
			rep(i,0,K+1) if(f[c][i] != inf){
				// empty
				Update(tmp[i] , f[c][i] + dissum[t] + wsum[t]);
				rep(j,1,K+1) if(f[t][j] != inf && i + j <= K)
					Update(tmp[i + j] , f[c][i] + f[t][j]);
			}
			rep(i,0,K+1) f[c][i] = tmp[i];
			dissum[c] += dissum[t] + wsum[t];
			wsum[c] += wsum[t];
		}
	//	rep(i,0,K+1) printf("%d%c",f[c][i]," \n"[i==K]);
	//	cout << c << " " << dissum[c] << " " << wsum[c] << endl;
	}
	int dis;
	void dfsdis(int c,int fa,int d){
		dis += w[c] * d;
		for(auto t : ng[c]) if(t != fa)
			dfsdis(t , c , d + 1);
	}
	int solve(int n,const vi g[]){
		fill_n(dfn,n,_=0);
		fill_n(low,n,_st=0);
		fill_n(dcc,n,key=vi());
		rep(i,0,n) if(!dfn[i]) dfs(i,1,g);
		rep(i,0,n) if(sz(dcc[i]) == 0) dcc[i].pb(_++);
		int s = n + _;
		rep(i,n,s) w[i] = 0;
		fill_n(ng,s,vi());
		rep(i,0,n) for(auto e : dcc[i]){
			int u = i , v = n + e;
			ng[u].pb(v);
			ng[v].pb(u);
		}
		dfs(0 , -1);
		int ans = inf;
		rep(i,0,n) {
			dis = 0;
			dfsdis(i , -1 , 0);
			if(f[i][K] != inf)
				Update(ans , f[i][K] + dis - dissum[i]);
		}
		return ans / 2;
	}
}

char s[10101];

int main() {
	int T;
	scanf("%d",&T);
	rep(i,0,T){
		scanf("%d%d",&n,&K);
		rep(i,0,n) g[i].clear();
		gets(s);
		rep(i,0,n) {
			gets(s);
			stringstream ss(s);
			ss >> w[i];
			int x;
			while(ss >> x) g[i].pb(x - 1);
		}
		printf("%d\n",DCC::solve(n , g));
	}
	return 0;
}
