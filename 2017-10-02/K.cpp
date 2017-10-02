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
ll n;
bool lt(ll k, ll r, ll n) {
	ll v = 1;	
	while (r) {
		if (r & 1) {
			if (v <= (n - 1) / k) {
				v *= k;
			} else {
				return false;
			}
		}
		if (k <= n / k) {
			k = k * k;
		} else {
			k = n + 1;	
		}
		r >>= 1;
	}
	return true;
}
ll kpow(ll a, ll b) {
	ll r = 1;
	while (b > 0) {
		if (b & 1) r = r * a;
		a = a * a, b >>= 1;
	}
	return r;
}
int check(ll k, ll r, ll n) {	
	if (!lt(k, r, n)) {
		return 1;	
	}
	ll t = (kpow(k, r + 1) - 1) / (k - 1) - n;
	return (t > 0) - (t < 0);
}
bool isSqr(ll x) {
	ll s = sqrt(x + 0.5);
	return s * s == x;
}
ll solve(ll R, ll n) {
	if (R == 1) {
		ll k = n - 1;	
		return k;	
	}
	if (R == 2) {
		if (!isSqr(4 * n - 3)) return -1;
		ll d = sqrt(4 * n - 3 + 0.5);
		if (!(d & 1)) return -1;
		ll k = (d - 1) >> 1; 
		if (k < 2) return -1;
		return k;
	}
	ll l = 2, r = sqrt(n) + 1;
	while (l + 1 < r) {
		ll m = (l + r) >> 1;
//		dd(R), dd(l), dd(r), dd(m), de(n);
		check(m, R, n) > 0 ? r = m : l = m;	
	}
	if (check(l, R, n) == 0) return l;	
	if (check(r, R, n) == 0) return r;
	return -1;
}
int main() {
	while (~scanf("%lld", &n)) {
		pair<ll, int> ans(-1, -1);
		rep(r, 1, 70) {
			ll k = solve(r, n);
			if (~k) if (ans.fi == -1 || mp(r * k, r) < ans)
				ans = mp(r * k, r);
			k = solve(r, n + 1);
			if (~k) if (ans.fi == -1 || mp(r * k, r) < ans)
				ans = mp(r * k, r);
		}
		printf("%d %lld\n", ans.se, ans.fi / ans.se);	
	}
	return 0;
}
