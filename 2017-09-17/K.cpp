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
const int N = 1e6 + 10;
ll ans[N];

int main() {
	rep(i,1,N) ans[i] = 3ll * i * i + 3ll * i + 1;
	int T;
	cin >> T;
	rep(i,0,T){
		ll p;
		cin >> p;
		if(*lower_bound(ans , ans + N , p) == p) puts("YES");
		else puts("NO");
	}
	return 0;
}
