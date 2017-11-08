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
const int N = 101010 , inf = 1<<30; 
vi g[N];
int col[N] , n , m;
int dis[N << 1];

int main() {
	scanf("%d%d",&n,&m);
	rep(i,0,m){
		int u , v;
		scanf("%d%d",&u,&v);
		--u;
		--v;
		g[u].pb(v);
		g[v].pb(u);
	}
	rep(i,0,n+n) dis[i] = inf;
	priority_queue<pii> Q;
	Q.push(mp(0 , 0));
	dis[0] = 0;
	while(sz(Q)){
		int c = Q.top().se , dc = -Q.top().fi;Q.pop();
		int x = c >> 1;
		if(dc == dis[c]){
			for(auto y : g[x]) {
				int d = dis[c] + 1;
				int z = (y << 1) | (~c & 1);
				if(d < dis[z])
					dis[z] = d , Q.push(mp(-dis[z] , z));
			}
		}
	}
	//rep(i,0,n+n) printf("%d%c",dis[i]," \n"[i+1==n+n]);
	int ans = inf , Max = 0;
	rep(i,0,n) Max = max(Max , dis[i << 1]);
	ans = min(ans , Max);
	Max = 0;
	rep(i,0,n) Max = max(Max , dis[i << 1 | 1]);
	ans = min(ans , Max);
	if(ans == inf) puts("-1");
	else printf("%d\n",ans);
	return 0;
}
