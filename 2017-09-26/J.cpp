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
#define setIO(x) freopen(x".in","r", stdin);freopen(x".out","w",stdout);
//-------
const int N = 1e5 + 10;
vi g[N];
int fa[N] , n , m , Q , vis[2][N] , dis[2][N], times;
int F(int x){return fa[x] == x ? x : fa[x] = F(fa[x]);}

int h[2], t[2], q[2][N];

int gao(int k) {
	int D = dis[k][q[k][h[k]]];
	while (h[k] < t[k] && D == dis[k][q[k][h[k]]]) {
		int u = q[k][h[k]++];
		rep(i, 0, sz(g[u])) {
			int v = g[u][i];
			if (vis[k][v] != times) {
				vis[k][v] = times, dis[k][v] = dis[k][u] + 1, q[k][t[k]++] = v;
				if (vis[k ^ 1][v] == times)
					return dis[0][v] + dis[1][v];
			}
		}
	}
	return -1;
}

int main() {
	setIO("travelling");
	scanf("%d%d",&n,&m);
	rep(i,1,n+1) fa[i] = i;
	rep(i,0,m){
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].pb(v);
		g[v].pb(u);
		fa[F(u)] = F(v);
	}
	scanf("%d",&Q);
	rep(i,0,Q){
		int u,v;
		scanf("%d%d",&u,&v);
		if(F(u) != F(v)) puts("-1");
		else {
			++times;
			rep(i, 0, 2) h[i] = t[i] = 0;
			vis[0][u] = times, dis[0][u] = 0, q[0][t[0]++] = u;	
			vis[1][v] = times, dis[1][v] = 0, q[1][t[1]++] = v;
			while (1) {
				bool flag = false;
				rep(k, 0, 2) {
					int ret = gao(k);
					if (~ret) {
						printf("%d\n", ret);
						flag = true;
						break;
					}
				}
				if (flag) break;
			}
		}
	}
	return 0;
}
