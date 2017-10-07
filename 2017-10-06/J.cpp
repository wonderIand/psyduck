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
template<class T>
struct Dinic{
	const static int N = 101010 , M = N * 10;
	int s , t , n , h[N] , cur[N] , level[N] , q[N] , e , ne[M] , to[M];
	T cap[M] , flow;
	void liu(int u,int v,T w) { to[e] = v;ne[e] = h[u];cap[e] = w;h[u] = e++;}
	void link(int u,int v,T w) {liu(u , v , w);liu(v , u , 0);}
	void ini(int _n = N) {fill(h , h + (n=_n) , -1);e=0;}
	bool bfs(){
		int L = 0 , R = 0;
		fill(level , level + n , -1);
		level[q[R++] = s] = 0;
		while(L < R && level[t] == -1){
			int c = q[L++];
			for(int k=h[c];~k;k=ne[k])
				if(cap[k] > 0 && level[to[k]] == -1)
					level[q[R++] = to[k]] = level[c] + 1;
		}
		return ~level[t];
	}
	T dfs(int c,T mx){
		if(c == t) return mx;
		T ret = 0;
		for(int &k=cur[c];~k;k=ne[k])
			if(level[to[k]] == level[c] + 1 && cap[k] > 0){
				T flow = dfs(to[k] , min(mx , cap[k]));
				ret += flow;cap[k] -= flow , cap[k^1] += flow;mx -= flow;
				if(!mx) return ret;
			}
		level[c] = -1;
		return ret;
	}
	T run(int _s,int _t){
		s = _s , t = _t;
		flow = 0;
		while(bfs()){
			copy(h , h + n , cur);
			flow += dfs(s , 1000);
		}
		return flow;
	}
};
const int N = 505;
Dinic<int> it;
int n , m;
bool vis[N][N];
struct edge{
	int u , v , w;
	ll cost;
	void read(){scanf("%d%d%d",&u,&v,&w);if(w < 0 || w > 10000) while(1);}
}e[N * N * 4];
ll sum[10010];

ll solve(){
	scanf("%d%d",&n,&m);
	if(n < 2 || n > 500) while(1);
	if(m >= N * N){
		while(1);
	}
	rep(i,0,n) rep(j,0,n) vis[i][j] = false;
	rep(i,0,m) {
		e[i].read();
		if(e[i].u == e[i].v) while(1);
		if(e[i].u < 0 || e[i].u >= n) while(1);
		if(e[i].v < 0 || e[i].v >= n) while(1);
		if(vis[e[i].u][e[i].v]) while(1);
		vis[e[i].u][e[i].v] = 1;
	}
	sort(e , e + m , [&](edge&a,edge&b){return a.w < b.w;});
	memset(sum , 0 , sizeof(sum));
	rep(i,0,m) sum[e[i].w] += e[i].w;
	rep(i,1,10001) sum[i] += sum[i-1];
	rep(i,0,m) e[i].cost = max(sum[e[i].w] , sum[10000] - sum[e[i].w-1]);
	sort(e , e + m , [&](edge&a,edge&b){return a.cost < b.cost;});
	int l = -1 , r = m;
	while(l + 1 < r){
		int mid = (l + r) / 2;
		int S = n * 2 , T = S + 1;
		it.ini(T + 1);
		rep(i,0,n) it.link(S , i , 1) , it.link(i + n , T , 1);
		rep(i,0,mid+1) if(e[i].u != e[i].v) it.link(e[i].u , e[i].v + n , 1);
		int flow = it.run(S , T);
		if(flow == n) r = mid;
		else l = mid;
	}
	if(r == m) return -1;
	else return e[r].cost;
}

int main() {
	int T;
	scanf("%d",&T);
	rep(i,0,T) printf("%lld\n",solve());
	return 0;
}
