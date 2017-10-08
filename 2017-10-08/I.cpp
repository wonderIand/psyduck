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
const int N = 1e5 + 10;
int n , m , K , can[N] , forbid[N] , du[N] , q[N] , incir[N] , inq[N];
vi g[N];

int dfn[N] , low[N] , id[N] , st[N] , _st;
int _ , tp[N];
void dfs(int c,int dep){
	int cc=0;st[_st++]=c;
	dfn[c]=low[c]=dep;
	for(auto t:g[c])
		if(!dfn[t]){
			dfs(t,dep+1);
			low[c]=min(low[c],low[t]);
			if(low[t]>=dfn[c]){
				_ = 0;
				while(st[--_st]!=t) tp[_++]=st[_st];
				tp[_++]=t;tp[_++]=c;
				if(_>=3){
					rep(i,0,_) incir[tp[i]]=1;
				}
			}
		} else if(dfn[t]!=dfn[c]-1||cc++)
			low[c]=min(low[c],dfn[t]);
}

inline void add(int c){
	if(!inq[c]){
		if(du[c] <= 2 && incir[c]) q[_++] = c , inq[c] = 1;
		else if(du[c] <= 1) q[_++] = c , inq[c] = 1;
	}
}
int main() {
	while(~scanf("%d",&n)){
		if(n == 0) break;
		scanf("%d%d",&m,&K);
		rep(i,0,n) g[i].clear() , can[i] = forbid[i] = du[i] = incir[i] = inq[i] = dfn[i] = low[i] = 0;
		_st = 0 , _ = 0;
		rep(i,0,m){
			int u,v;
			scanf("%d%d",&u,&v);
			--u;--v;
			g[u].pb(v);
			g[v].pb(u);
			++du[u];
			++du[v];
		}
		rep(i,0,K){
			int x;
			scanf("%d",&x);
			can[x-1] = 1;
		}
		rep(i,0,n) if(!dfn[i]) dfs(i,1);
		_ = 0;
		rep(i,0,n) add(i);
		int cnt=0;
		rep(i,0,_){
			int c=q[i];
			//de(c);de(forbid[c]);de(can[c]);
			if(can[c] && !forbid[c]) {
				++cnt;
				for(auto t : g[c]) forbid[t] = 1;
			}
			for(auto t : g[c]) --du[t] , add(t);
		}
		printf("%d\n",cnt);
	}
	return 0;
}
