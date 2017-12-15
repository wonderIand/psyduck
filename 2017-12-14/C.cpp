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
int T;
int n , m , u[N << 1] , v[N << 1];
vi g[N] , rg[N];
set<pii> has;

bool in[N];
void bfs(const vi g[],bool rev){
	rep(i,1,n+1) in[i]=false;
	vi q;q.pb(1);in[1]=true;
	rep(i,0,sz(q)){
		int c=q[i];
		for(auto t : g[c]) if(!in[t]){
			in[t]=true;q.pb(t);
			int u = c , v = t;
			if(rev) swap(u , v);
			has.insert(mp(u , v));
		}
	}
}

void solve(){
	scanf("%d%d",&n,&m);
	rep(i,1,n+1) g[i].clear(),rg[i].clear();
	has.clear();
	rep(i,0,m) {
		scanf("%d%d",u + i,v + i);
		g[u[i]].pb(v[i]);
		rg[v[i]].pb(u[i]);
	}
	bfs(g , false);
	bfs(rg , true);
	int need = m - 2 * n;
	rep(i,0,m) if(!has.count(mp(u[i],v[i])) && need){
		need--;
		printf("%d %d\n",u[i],v[i]);
	}
}

int main() {
	scanf("%d",&T);
	rep(i,0,T) solve();
	return 0;
}
