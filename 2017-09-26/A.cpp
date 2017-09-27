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
struct ele{
	ll a,b;
	void read(){cin >> a >> b;}
	bool operator < (const ele&y) const {
		return a + b < y.a + y.b;
	}
}e[N];
int n;
vector<ll> A;
#define rt 1,0,sz(A)-1
ll sum[N << 2] , cnt[N << 2];
void ins(int c,int l,int r,int x){
	if(l == r){
		cnt[c]++ , sum[c] += A[l];
	} else {
		int m=(l+r)>>1;
		if(x<=m) ins(c<<1,l,m,x);
		else ins(c<<1|1,m+1,r,x);
		cnt[c]=cnt[c<<1]+cnt[c<<1|1];
		sum[c]=sum[c<<1]+sum[c<<1|1];
	}
}
int query(int c,int l,int r,ll need){
	if(need == 0) return 0;
	if(sum[c] < need) return n + 1;
	if(l == r) return (need + A[l] - 1) / A[l];
	int m = (l+r)>>1;
	if(sum[c<<1|1]>=need) return query(c<<1|1,m+1,r,need);
	int res = cnt[c<<1|1];
	need -= sum[c<<1|1];
	return res + query(c<<1,l,m,need);
}


int main() {
	setIO("artifact");
	cin >> n;
	rep(i,0,n) e[i].read() , A.pb(e[i].a);
	sort(e , e + n);
	sort(all(A));A.erase(unique(all(A)) , A.end());
	int ans = n + 1;
	rep(i,0,n){
#define rk(x) lower_bound(all(A),x) - A.begin()
		ins(rt,rk(e[i].a));
		ans=min(ans,query(rt,e[i].a+e[i].b));
	}
	if(ans > n) puts("-1");
	else printf("%d\n",ans);
	return 0;
}
