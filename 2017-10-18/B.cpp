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
const int N = 20;
int x[1 << N] , y[1 << N];
int wx[N] , wy[N];
int n , m;
char s[N + N];
int A[1 << N] , topA , B[1 << N] , topB;

bool ok[1 << N];
void solve(int *a,int *weight,int n,int *ans,int&_){
	_ = 0;
	rep(i,0,1<<n) {
		int lb=i&(-i);
		a[i] = a[i ^ lb] | a[lb];
		ok[i] = __builtin_popcount(a[i]) >= __builtin_popcount(i);
	}
	rep(i,0,n) rep(j,0,1<<n) if(j >> i & 1)
		ok[j] &= ok[j ^ (1 << i)];
	rep(i,0,1<<n) if(ok[i]) {
		int w=0;
		rep(j,0,n) if(i>>j&1) w+=weight[j];
		ans[_++]=w;
	}
	sort(ans , ans + _);
}

int main() {
	scanf("%d%d",&n,&m);
	rep(i,0,n) {
		scanf("%s",s);
		rep(j,0,n) if(s[j] == '1')
			x[1 << i] |= 1 << j , y[1 << j] |= 1 << i;
	}
	rep(i,0,n) scanf("%d",wx+i);
	rep(i,0,m) scanf("%d",wy+i);
	solve(x , wx , n , A , topA);
	solve(y , wy , m , B , topB);
	int lim;
	scanf("%d",&lim);
	ll ans = 0;
	for(int i=0,j=topB;i<topA;++i){
		for(;j>0&&A[i]+B[j-1]>=lim;--j) ;
		ans += topB - j;
	}
	printf("%lld\n",ans);
	return 0;
}
