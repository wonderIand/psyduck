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
ll A, B;
ll solve() {
	if (min(A, B) == 0) 
		return 1 + (max(A, B) != 0);	
	ll ret = 1;
	while (B) {
		ll r = A % B;
		ret += (A - r) / B;
		A = B, B = r;	
	}
	return ret;
}
ll br(ll A, ll B) {
	set<ll> S;
	S.insert(A), S.insert(B);
	while (A != 0 && B != 0) {
		ll C = abs(A - B);
		S.insert(C);
		A = B, B = C;
	}
	S.insert(0);
	return sz(S);
}
ll _rand() {
	return ((ll) rand() << 31) ^ ((ll) rand() << 16) ^ (rand());
}
int main() {
//	srand(time(NULL));
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%lld%lld", &A, &B);
//		A = _rand() % 1000, B = _rand() % 1000;
//		dd(A), de(B);
//		ll tmp = br(A, B);
		ll ans = solve();
		printf("Case #%d: %lld\n", cas + 1, ans);
//		assert(ans == tmp);
	}
	return 0;
}
