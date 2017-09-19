#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b)-1; i>=(a); i--)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;

typedef double db;
typedef long long ll;

#define fi first
#define se second
#define mp make_pair
typedef pair<int, int> pii;

#define pb push_back
typedef vector<int> vi;
///-----------

const int inf = 1<<30;
const int N = 1e5 + 10 , M = N;
template<class U,class V>
struct MCMF{
	int h[N] , ing[N] , pre[N] , to[M] , ne[M] , e , s , t , n;
	U cap[M];V dis[N] , cost[M];
	void ini(int _n=N) {fill(h , h + (n = _n) , -1);e = 0;}
	void liu(int u,int v,U c,V w){ to[e] = v;ne[e] = h[u];cap[e] = c;cost[e] = w;h[u] = e++;}
	void link(int u,int v,U c,V w) {liu(u , v , c , w);liu(v , u , 0 , -w);}
	bool spfa(){
		queue<int> Q;
		fill(dis,dis+n,inf);
		ing[s] = true , dis[s] = 0;
		Q.push(s);
		while(sz(Q)){
			int c = Q.front();Q.pop();
			ing[c] = false;
			for(int k=h[c];~k;k=ne[k]){
				int v=to[k];
				if(cap[k] <= 0) continue;
				if(dis[c] + cost[k] < dis[v]){
					dis[v] = dis[c] + cost[k];
					pre[v] = k;
					if(!ing[v]) Q.push(v) , ing[v] = true;
				}
			}
		}
		return dis[t] != inf;
	}
	U flow;V mincost;
	pair<U,V> run(int _s,int _t){
		s = _s , t = _t;flow = mincost = 0;
		while(spfa()){
			U pl = inf;int p , k;
			for(p=t;p!=s;p=to[k^1]) pl = min(pl , cap[k=pre[p]]);
			for(p=t;p!=s;p=to[k^1]) {k=pre[p];cap[k]-=pl;cap[k^1]+=pl;}
			mincost += pl * dis[t];
			flow += pl;
		}
		return mp(flow , mincost);
	}
};
MCMF<int,ll> it;


int T,m;
vector<pii> g[N];
char s[N] , t[N];
map<string,int> id;
int ID(string s){
	if(!id.count(s)){
		int t = sz(id);
		g[t].clear();
		id[s] = t;
	}
	return id[s];
}
void link(string s,string t,int cost){
	int S = ID(s);
	int T = ID(t);
	g[S].pb(mp(T , cost));
	g[T].pb(mp(S , cost));
}

int main(){
	scanf("%d",&T);
	rep(i,0,T){
		scanf("%d",&m);
		int cost;
		id.clear();
		rep(i,0,m){
			scanf("%s%s%d",s,t,&cost);
			link(s , t , cost);
		}
		ID("Shanghai");
		ID("Dalian");
		ID("Xian");
		int S = sz(id) << 1 , T = S + 1;
		it.ini(T + 1);
		it.link(S , ID("Shanghai") << 1, 2 , 0);
		it.link(ID("Dalian") << 1 | 1, T , 1 , 0);
		it.link(ID("Xian") << 1 | 1, T , 1 , 0);
		rep(i,0,sz(id)) for(auto e : g[i])
			it.link(i << 1 | 1 , e.fi << 1 , 1 , e.se);
		rep(i,0,sz(id)) it.link(i << 1 , i << 1 | 1 , 1 , 0);
		it.link(ID("Shanghai") << 1 , ID("Shanghai") << 1 | 1 , 1 , 0);
		auto e = it.run(S , T);
		if(e.fi != 2) puts("-1");
		else printf("%d\n",e.se);
	}
	return 0;
}

