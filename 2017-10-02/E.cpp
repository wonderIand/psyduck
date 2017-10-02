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
const int N = 2e5 + 10;
struct edge{
	int u,v,c;
	bool operator < (const edge&b) const{
		return c > b.c;
	}
	void read(){
		scanf("%d%d%d",&u,&v,&c);
	}
}e[N];
int sz[N] , fa[N] , n;
ll Max[N];
int F(int x){return fa[x] == x ? x : fa[x] = F(fa[x]);}

int main() {
	while(~scanf("%d",&n)){
		rep(i,1,n) e[i].read();
		sort(e + 1, e + n);
		rep(i,1,n+1) sz[i] = 1 , Max[i] = 0 , fa[i] = i;
		rep(i,1,n){
			int u = e[i].u , v = e[i].v , c = e[i].c;
			u = F(u) , v = F(v);
			ll g = max(Max[u] + 1ll * sz[v] * c , Max[v] + 1ll * sz[u] * c);
			fa[v] = u , sz[u] += sz[v] , Max[u] = g;
		}
		printf("%lld\n",Max[F(1)]);
	}
	return 0;
}

