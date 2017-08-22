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
const int N = 1010;
int T,n,m,u,v;
vi g[N];

namespace SCC{
	int dfn[N],low[N],id[N],st[N],_st,_,cc;
	void dfs(int c,vi g[]){
		dfn[c]=low[c]=++cc;
		st[_st++]=c;
		for(auto t:g[c])
			if(!dfn[t])
				dfs(t,g),low[c]=min(low[c],low[t]);
			else if(!id[t])
				low[c]=min(low[c],dfn[t]);
		if(low[c]==dfn[c]){
			++_;
			do{id[st[--_st]]=_;}while(st[_st]!=c);
		}
	}
	vi ng[N];
	int du[N];
	int solve(int,vi g[]){
		fill_n(dfn,n,cc=0);
		fill_n(low,n,_st=0);
		fill_n(id,n,_=0);
		rep(i,0,n) if(!dfn[i]) dfs(i,g);
		rep(i,0,n) --id[i];
		if(_<=1) puts("I love you my love and our love save us!");
		else {
			rep(i,0,_) ng[i].clear() , du[i] = 0;
			rep(i,0,n) for(auto j:g[i]) if(id[i]!=id[j]){
				ng[id[j]].pb(id[i]);
				du[id[i]]++;
			}
			vi v;
			rep(i,0,_) if(du[i] == 0) v.pb(i);
			rep(i,0,sz(v)){
				if(i + 1 != sz(v)){
					puts("Light my fire!");
					return 0;
				}
				int c = v[i];
				for(auto t : ng[c]) if(!--du[t]) v.pb(t);
			}
			if(sz(v) != _) puts("Light my fire!");
			else puts("I love you my love and our love save us!");
		}
		return 0;
	}
}

int main() {
	scanf("%d",&T);
	rep(i,0,T){
		scanf("%d%d",&n,&m);
		rep(i,0,n) g[i].clear();
		rep(i,0,m){
			scanf("%d%d",&u,&v);
			--u;--v;
			g[u].pb(v);
		}
		SCC::solve(n,g);
	}
	return 0;
}
