#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 1005 , M = 40005;
typedef int Type;
const Type inf = 2e9 + 7;

struct Edge{
	int u,v;
	Type dist;
	Edge(){}
	Edge(int u,int v,int d) : u(u) , v(v) , dist(d) {}
};

struct DMST{
	Edge e[M];
	int n,m,vis[N],pre[N],id[N];
	Type in[N];

	void init(int n){
		this->n = n , m = 0;
	}
	void addedge(int u,int v,Type dist) {e[m++] = Edge(u,v,dist);}
	Type run(int root){
		Type ans=0;
		while(1){
			rep(i,0,n) in[i]=inf;
			rep(i,0,m){
				int u=e[i].u , v=e[i].v;
				if(e[i].dist < in[v] && u != v){
					in[v] = e[i].dist , pre[v] = u;
				}
			}
			rep(i,0,n) {
				if(i == root) continue;
				if(in[i] == inf) return -1;
			}
			int cnt = 0;in[root] = 0;
			memset(id,-1,sizeof(*id)*n);
			memset(vis,-1,sizeof(*vis)*n);
			rep(i,0,n){
				ans+=in[i];int v=i;
				while(vis[v]!=i && id[v]==-1 && v!=root){
					vis[v] = i;v = pre[v];
				}
				if(v != root && id[v] == -1) {
					for(int u=pre[v];u != v;u = pre[u])
						id[u] = cnt;
					id[v] = cnt++;
				}
			}
			if(cnt == 0) break;
			rep(i,0,n) if(id[i] == -1) id[i] = cnt++;
			rep(i,0,m) {
				int v=e[i].v;
				e[i].u = id[e[i].u];
				e[i].v = id[e[i].v];
				if(e[i].u != e[i].v)
					e[i].dist -= in[v];
			}
			n = cnt;root = id[root];
		}
		return ans;
	}
}tree;
int x[M] , y[M] , z[M] , n , m;

int main() {
	int T;scanf("%d",&T);
	rep(i,0,T){
		scanf("%d%d",&n,&m);
		rep(i,0,m) scanf("%d%d%d",x+i,y+i,z+i), --x[i], --y[i];
		tree.init(n);
		rep(i,0,m) if(y[i] != 0) {				
			if (y[i] != n - 1)
				tree.addedge(x[i] , y[i] , -(z[i] * 2000));	
			else
				tree.addedge(x[i], y[i], -(z[i] * 2000 + (n - x[i])));
		}
		int ans = -tree.run(0);
		printf("%d %d\n",ans/2000,1 + n-ans%2000);
	}
	return 0;
}
