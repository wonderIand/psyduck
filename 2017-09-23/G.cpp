#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;
#define fi frist
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


int main() {
	int n , m;
	while(~scanf("%d%d",&n,&m)){
		--n , --m;
		ll g = __gcd(n , m);
		ll l = 1ll * n * m / g;
		ll ans = l;
		ans = ans / g * (g - 1);
		ans += l / n + l / m;
		printf("%lld\n",ans);
	}
	return 0;
}
