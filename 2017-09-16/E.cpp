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
const int P = 1000000007;

int main2() {
	rep(n,2,20){
		ll ans = 1ll<<62;
		int best = 0;
		rep(i,0,1<<n) if((i & 1) && (~i >> (n - 1) & 1)){
			ll tmp = 0;
			rep(x,0,n) rep(y,x+1,n) if(i >> x & 1 && (~i >> y & 1)) tmp += x ^ y;
			if(tmp < ans) ans = tmp , best = i;
		}
		cout << n << " " << ans << " " << bitset<30>(best) << endl;
	}
	return 0;
}
void pp(int &x,int d){
	if((x+=d)>=P) x-=P;
}

int c2(ll x){
	return __int128(x) * (x + 1) / 2 % P;
}

int main(){
//	main2();
	ll n;
	while(cin >> n){
		--n;
		if((n & -n) == n) cout << c2(n) << endl;
		else {
			int p = 0;
			while((1ll << (p+1)) <= n) p++;
			int ans = c2((1ll<<p) - 1);
			pp(ans , n % P);
			n -= ((1ll<<p));
			// [0 , n]
			rep(i,0,61){
				ll t = (n + 1) >> (i + 1) << i;
				ll remain = (n + 1) & (((1ll)<<(i+1))-1);
				if(remain > (1ll << i)) t += remain - (1ll << i);
				if(n >> i & 1) t = n + 1 - t;
				pp(ans , __int128(t) * (1ll<<i) % P);
			}
			cout << ans << endl;
		}
	}
	return 0;
}
