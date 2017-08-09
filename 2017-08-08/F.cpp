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
ll n , m;

int main() {
	scanf("%d",&T);
	rep(i,0,T){
		scanf("%lld%lld",&n,&m);
		if(n == 1){
			puts("0");
			continue;
		}
		m = min(n * (n - 1) / 2 , m);
		if(m <= n - 1){
			ll sz = m + 1;
			ll ans = (sz - 1) + (n - sz) * n;
			ans += (sz - 1) * (1 + (sz - 2) * 2 + (n - sz) * n);
			ans += (n - sz) * (n - 1) * n;
			printf("%lld\n",ans);
		} else {
			ll sz = n;
			ll ans = (sz - 1) + (n - sz) * n;
			ans += (sz - 1) * (1 + (sz - 2) * 2 + (n - sz) * n);
			m -= n - 1;
			ans -= 2 * m;
			printf("%lld\n",ans);
		}
	}
	return 0;
}
