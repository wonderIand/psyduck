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
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
//-------
const int P = 998244353 , N = 2010;
int T , n , m;

inline void pp(int &x,int d){
	x += d;
	if(x >= P) x -= P;
}

template<class T>
struct Fenwick{
#define lb(x) ((x)&-(x))
	int n;T a[N];
	void ini(int _n){ fill_n(a+1,n=_n,0); }
	void Pre(){ for(int i=1,j=i+lb(i);i<=n;++i,j=i+lb(i)) if(j<=n) pp(a[j],a[i]);}
	void add(int x,T d){ for(;x<=n;x+=lb(x)) pp(a[x],d);}
	T sum(int x){ T r=0;for(;x>=1;x^=lb(x)) pp(r,a[x]);return r;}
};
Fenwick<int> f,g;

int L = 2001;
int F[N],G[N],a[N],b[N];

void solve(){
	scanf("%d%d",&n,&m);
	//f.ini(L);
	//g.ini(L);
	rep(i,1,n+1) scanf("%d",a + i);
	rep(i,1,m+1) scanf("%d",b + i);
	a[0] = b[0] = L;
	memset(F,0,sizeof(F));
	memset(G,0,sizeof(G));
	F[0] = 1;
	rep(i,1,m+1){
	//	rep(j,0,n+1) pp(f.a[L+1-a[j]],F[j]) , pp(g.a[a[j]],G[j]);
	//	f.Pre();g.Pre();
		int big=0,small=0;
		rep(j,0,n+1) if(a[j]<b[i]) pp(small,G[j]);
		rep(j,0,n+1) if(a[j]>b[i]) pp(big,F[j]);
		per(j,0,n+1) {
			//f.add(L+1-a[j],P-F[j]);
			//g.add(a[j],P-G[j]);
			if(a[j]<b[i]) pp(small,P-G[j]);
			if(a[j]>b[i]) pp(big,P-F[j]);
			if(a[j] == b[i]){
				//int x = f.sum(L - a[j]);
				//int y = g.sum(a[j] - 1);
				int x = big;
				int y = small;
				pp(G[j] , x);
				pp(F[j] , y);
			}
		}
	}
	int ans=0;
	rep(i,1,n+1) pp(ans , F[i]) , pp(ans , G[i]);
	printf("%d\n",ans);
}


int main() {
	scanf("%d",&T);
	rep(i,0,T) solve();
	return 0;
}
