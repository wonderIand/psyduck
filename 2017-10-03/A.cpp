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
const int N = 1e5 + 7;
const int P = 1ll * 365 * 24 * 60 * 60; 
int n;
struct Node {
	int a, b;
	void in() {
		scanf("%d%d", &a, &b);
	}
	bool operator<(const Node &p) const {
		return 1ll * a * p.b < 1ll * p.a * b;
	}
} t[N];
int main() {
	while (~scanf("%d", &n)) {
		if (n == 0) break;
		rep(i, 0, n) t[i].in();
		sort(t, t + n);
		ll ans = 0, sum = 0;	
		rep(i, 0, n) {
			ll now = (t[i].a + sum * t[i].b) % P;
			ans = (ans + now) % P;
			sum = (sum + now) % P;
		}
		cout << ans << endl;
	}

	return 0;
}
