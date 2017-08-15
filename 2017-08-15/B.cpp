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
int T;
ll n , K;

ll special(ll n){
	ll r=0,x=n,pw=1;
	while(x){
		int rm=x&1;
		if(rm){
			if(pw != 1 && !(n & 1)) r^=pw;
		}
		pw*=2;
		x/=2;
	}
	if(n % 4 == 1 || n % 4 == 2) r ^= 1;
	return r;
}

const ll inf = 1e18 + 10;
typedef pair<ll,ll> pll;
ll lim[100] , has[100];
ll ceil(ll a,ll b){
	return (a + b - 1) / b;
}
ll solve(ll n,ll K){
	int dep=0;
	lim[0]=1;
	for(ll rm=n;rm;){
		has[dep]=min(lim[dep],rm);
		rm-=has[dep];
		if(rm){
			ll &x=lim[dep+1];
			if(lim[dep]>=ceil(inf , K)) x=inf;
			else x=lim[dep]*K;
			++dep;
		} else break;
	}
	vector<pll> v;
	ll ans=0;
	for(int i=dep;i>=0;--i){
		ll sum = 0;
		for(auto e : v) sum += e.fi;
		if(has[i] != sum){
			if((has[i] - sum) & 1) ans ^= 1;
			v.pb({has[i] - sum , 1});
		}
		if(i == 0) break;
		vector<pll> nv;
		auto ins = [&](pll x){
			nv.pb(x);
			if(x.fi & 1) ans ^= x.se;
		};
		pll rm(0,0);
		for(int i=0;i<sz(v);++i){
			auto e = v[i];
			if(rm.fi){
				ll del = min(K - rm.fi , e.fi);
				rm.fi += del;
				rm.se += del * e.se;
				e.fi -= del;
				if(rm.fi == K){
					ins({1 , rm.se + 1});
					rm.fi = 0;
					rm.se = 0;
				}
			}
			ll d = e.fi / K , r = e.fi % K;
			if(d) ins({d , e.se * K + 1});
			if(r) rm.fi+=r,rm.se+=e.se*r;
		}
		if(rm.fi != 0){
			ins({1 , rm.se + 1});
		}
		//cout <<"~~~" << endl;
		//for(auto e : nv) cout << e.fi << " " << e.se << endl;
		v = nv;
	}
	return ans;
}

int bf(int n){
	int r=0;
	rep(i,1,n+1) r^=i;
	return r;
}

int main() {
//	rep(i,1,100000) assert(bf(i) == special(i));
	cin >> T;
	rep(i,0,T){
		cin >> n >> K;
		if(K == 1) cout << special(n) << endl;
		else cout << solve(n , K) << endl;
	}
	return 0;
}
