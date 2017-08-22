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
const ll inf = 1ll<<60;
int T,n,m,K;
vector<pii> g[N];
pair<ll,int> a[N][2];
priority_queue<pair<ll,pii>> Q;
int iskey[N];

ll solve(){
	scanf("%d%d",&n,&m);
	int u,v,c;
	rep(i,0,n) g[i].clear();
	rep(i,0,m){
		scanf("%d%d%d",&u,&v,&c);
		--u;--v;
		g[u].pb(mp(v,c));
	}
	scanf("%d",&K);
	rep(i,0,n) iskey[i] = 0;
	rep(i,0,n) rep(j,0,2) a[i][j] = mp(inf , -1);
	while(sz(Q)) Q.pop();
	rep(i,0,K){
		int x;
		scanf("%d",&x);
		--x;
		a[x][0] = mp(0 , x);
		Q.push({0 , mp(x , 0)});
		iskey[x] = 1;
	}
	while(sz(Q)){
		ll dis = -Q.top().fi;
		int x = Q.top().se.fi , y = Q.top().se.se;
		Q.pop();
		if(iskey[x] && a[x][y].se != x){
			return dis;
		}
		if(dis == a[x][y].fi){
			int from = a[x][y].se;
			for(auto e : g[x]){
				int t = e.fi;
				ll ndis = dis + e.se;
				pair<ll,int> ne = mp(ndis , from);
				if(ne < a[t][0]) {
					swap(a[t][0] , a[t][1]);
					a[t][0] = ne;
					Q.push({-ndis,mp(t,0)});
				} else if(ne < a[t][1]){
					a[t][1] = ne;
					Q.push({-ndis,mp(t,1)});
				}
			}
		}
	}
}

int main() {
	scanf("%d",&T);
	rep(i,0,T) printf("Case #%d: %lld\n",i + 1 , solve());
	return 0;
}
