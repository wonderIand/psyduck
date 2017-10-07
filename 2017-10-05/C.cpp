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
const db inf = 1e20 , eps = 1e-8;
int sgn(db x){return (x > eps) - (x < -eps);}
template<class T>
struct Dinic{
	const static int N = 10101 , M = N * 10;
	int s , t , n , h[N] , cur[N] , level[N] , q[N] , e , ne[M] , to[M];
	T cap[M] , flow;
	void liu(int u,int v,T w) { to[e] = v;ne[e] = h[u];cap[e] = w;h[u] = e++;}
	void link(int u,int v,T w) { liu(u , v , w);liu(v , u , 0);}
	void ini(int _n = N) { fill(h , h + (n = _n) , -1);e = 0;}
	bool bfs(){
		int L = 0 , R = 0;
		fill(level , level + n , -1);
		level[q[R++] = s] = 0;
		while(L < R && level[t] == -1){
			int c = q[L++];
			for(int k=h[c];~k;k=ne[k])
				if(sgn(cap[k]) > 0 && level[to[k]] == -1)
					level[q[R++] = to[k]] = level[c] + 1;
		}
		return ~level[t];
	}
	T dfs(int c,T mx){
		if(c == t) return mx;
		T ret = 0;
		for(int &k=cur[c];~k;k=ne[k]){
			if(level[to[k]] == level[c] + 1 && sgn(cap[k]) > 0){
				T flow = dfs(to[k] , min(mx , cap[k]));
				ret += flow;cap[k] -= flow , cap[k^1] += flow;mx -= flow;
				if(!mx) return ret;
			}
		}
		level[c] = -1;
		return ret;
	}
	T run(int _s,int _t){
		s = _s , t = _t;
		flow = 0;
		while(bfs()){
			copy(h , h + n , cur);
			flow += dfs(s , inf);
		}
		return flow;
	}
};
Dinic<db> it;
const int N = 110;
int n , a[N];
vector<pii> rev;

bool check(db K){
	int S = sz(rev) + n , T = S + 1;
	it.ini(T + 1);
	db ret = sz(rev);
	rep(i,0,sz(rev)) it.link(S , i , 1);
	rep(i,0,sz(rev)) it.link(i , rev[i].fi + sz(rev) , inf) , it.link(i , rev[i].se + sz(rev) , inf);
	rep(i,0,n) it.link(i + sz(rev) , T , K);
	db flow = it.run(S , T);
	//cout << sz(rev) << " " << flow << endl;
	return sz(rev) - flow > 0;
}

db solve(){
	scanf("%d",&n);
	rep(i,0,n) scanf("%d",a + i);
	rev.clear();
	rep(i,0,n) rep(j,i+1,n) if(a[i] > a[j]) rev.pb(mp(i , j));
	//for(auto e : rev) cout << e.fi << " " << e.se << endl;
	db l = 0. , r = 1. * (n - 1) / 2;
	rep(i,0,50){
		db mid = (l + r) / 2;
		if(check(mid)) l = mid;
		else r = mid;
	}
	return l;
}

int main() {
	int T;
	scanf("%d",&T);
	rep(i,1,T+1) printf("Case #%d: %.10f\n",i , solve());
	return 0;
}
