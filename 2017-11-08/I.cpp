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
int n , C;
pii a[N];
ll ans;
vi W;
#define lb(x) ((x)&(-(x)))
template<class T>
struct Fenwick{
	T a[N],n;
	void add(int x,T d){for(;x<=n;x+=lb(x))a[x]+=d;}
	T sum(int x){T r(0);for(;x>=1;x-=lb(x))r+=a[x];return r;}
};
Fenwick<ll> f1,f2;

void solve(int l,int r){
	if(l == r) return;
	int mid = (l + r) >> 1;
	solve(l , mid);
	solve(mid + 1 , r);
	int j=mid,i=mid+1;
	for(i=r,j=mid;i>mid;--i){
		for(;j>=l&&a[j].fi>a[i].fi;--j){
			f1.add(a[j].se,1);
			f2.add(a[j].se,W[a[j].se - 1]);
		}
		int big = mid - j;
		ans += 1ll * big * W[a[i].se - 1]+ f2.sum(f2.n);
		ans += f2.sum(a[i].se) * (C - 1);
		ans += 1ll * (big - f1.sum(a[i].se)) * W[a[i].se - 1] * (C - 1);
	}
	for(int k=j+1;k<=mid;++k){
		f1.add(a[k].se,-1);
		f2.add(a[k].se,-W[a[k].se - 1]);
	}
	inplace_merge(a + l , a + mid + 1 , a + r + 1);
}

int main() {
	scanf("%d%d",&n,&C);
	rep(i,1,n+1) scanf("%d%d",&a[i].fi,&a[i].se) , W.pb(a[i].se);
	sort(all(W));
	W.erase(unique(all(W)) , W.end());
	rep(i,1,n+1) a[i].se = upper_bound(all(W) , a[i].se) - W.begin();
	//rep(i,1,n+1) rep(j,i+1,n+1) if(a[i].fi > a[j].fi)
	//	ans += min(a[i].se , a[j].se) * C + max(a[i].se , a[j].se);
	f1.n = f2.n = sz(W);
	solve(1 , n);
	printf("%lld\n",ans);
	return 0;
}
