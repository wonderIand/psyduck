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
ll P;
inline ll mul(ll a,ll b){
	return (a*b-ll((long double)a*b/P+0.5)*P+P)%P;
}
ll Pow(ll x,ll t){
	ll r=1;for(;t;t>>=1,x=mul(x,x)) if(t&1)r=mul(r,x);return r;
}
ll inv(ll x){
	return Pow(x,P-2);
}
const int N = 1e5 + 10;
ll a[N];
int T,n;

ll solve(ll P){
	//puts("GG");
	//puts("how to solve sancishengyu");
	return 2;
}

int main() {
	scanf("%d",&T);
	rep(i,0,T){
		scanf("%d%lld",&n,&P);
		ll G = solve(P);
		if(G == -1) {
			puts("0");
			continue;
		}
		rep(i,0,n) scanf("%lld",a + i);
		map<ll,int> Mp;
		ll ans = 0;
		rep(i,0,n) if(a[i]){
			ll need = mul(a[i] , G);
			ans += Mp[need];
			if(mul(need , G) != need) {
				need = mul(need , G);
				ans += Mp[need];
			}
			Mp[a[i]]++;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
