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
//-------
const int P = 998244353 , N = 3e5 + 10;
int T , n , du[N] , vis[N] , vis2[N];
vector<pii> F[N] , G[N];

void link(int a,int b,int c){
	F[a].pb(mp(b , c));
	G[b].pb(mp(a , c));
	du[b] ++ ;
}
int q[N] , _;

void solve(){
	scanf("%d",&n);
	rep(i,1,n+1) F[i].clear() , G[i].clear() , vis[i] = vis2[i] = 0 , du[i] = 0;
	int x,y;
	rep(i,1,n+1){
		rep(t,0,2){
			scanf("%d%d",&x,&y);
			link(i , x , y);
		}
	}
	_ = 0;
	rep(i,1,n+1) if(du[i] == 1) q[_++] = i , vis2[i] = 1;
	int ans = 1;
	rep(i,0,_){
		int c = q[i];
		for(auto e : G[c]) if(!vis[e.fi]){
			vis[e.fi] = 1;
			ans = 1ll * ans * e.se % P;
			for(auto f : F[e.fi]) if(--du[f.fi]==1) q[_++] = f.fi , vis2[f.fi] = 1;
			break;
		}
	}
	rep(i,1,n+1) if(!vis[i]){
		_ = 0;
		int w1 = 1 , w2 = 1;
		q[_++] = i;vis[i] = 1;
		rep(i,0,_){
			int c=q[i];
			if(i & 1){
				for(auto e : G[c]) if(!vis[e.fi]){
					vis[e.fi] = 1;
					q[_++] = e.fi;
					w2 = 1ll * w2 * e.se % P;
					break;
				}
			} else {
				for(auto e : F[c]) if(!vis2[e.fi]){
					vis2[e.fi] = 1;
					q[_++] = e.fi;
					w1 = 1ll * w1 * e.se % P;
					break;
				}
			}
		}
		for(auto e : F[i]) if(e.fi == q[_-1]){
			w2 = 1ll * w2 * e.se % P;
			break;
		}
		ans = 1ll * ans * (w1 + w2) % P;
	}
	printf("%d\n",ans);
}

int main() {
	scanf("%d",&T);
	rep(i,0,T) solve();
	return 0;
}
