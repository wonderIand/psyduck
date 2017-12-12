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
ll L , R , Q;

void solve(ll x){
	int cnt = 0;
	for(ll i=1;i*i<=x;++i)if(x%i==0){
		cnt++;
		if(i*i!=x) cnt++;
	}
	cout << cnt << endl;
}

int main() {
	cin >> L >> R >> Q;
	L = max(L , Q);
	if(Q > R) cout << "infinity" << endl;
	else {
		ll LQ = L % Q;
		ll t = L - LQ;
		if(R - L >= Q - LQ) solve(__gcd(t , Q));
		else solve(t);
	}
	return 0;
}
