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
const int N = 110;
int n , m , S , vis[N];
vi g[N];

int main() {
	while(~scanf("%d",&n)){
		if(n == 0) break;
		scanf("%d%d",&S,&m);
		rep(i,1,n+1) g[i].clear();
		rep(i,0,m){
			int u,v;
			scanf("%d%d",&u,&v);
			g[u].pb(v);
			g[v].pb(u);
		}
		pii best = mp(-1 , -(n + 1));
		rep(i,1,n+1) if(i != S){
			rep(j,1,n+1) vis[j] = false;
			vi q;q.pb(S);vis[S] = true;vis[i] = true;
			rep(i,0,sz(q)){
				int c = q[i];
				for(auto t : g[c]) if(!vis[t])
					vis[t] = true , q.pb(t);
			}
			best = max(best , mp(n - 1 - sz(q) , -i));
		}
		printf("%d\n",-best.se);
	}
	return 0;
}
