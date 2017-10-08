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
const int N = 1e3 + 7;
const int V = 25e4 + 7;
bitset<V> dp;
pii solve() {
	dp.reset();
	dp[0] = 1;
	int n, sum = 0;
	scanf("%d", &n);		
	rep(i, 1, n + 1) {
		int x;
		scanf("%d", &x);
		sum += x;
		dp |= dp << x;
	}
	for (int i = sum / 2; i > 0; --i)
		if (dp[i]) return mp(i, sum - i);
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		char ch = 'A';
		pii ans = solve();
		rep(i, 1, 3) {
			char nch = 'A' + i;
			pii tmp = solve();
			if (tmp.se - tmp.fi < ans.se - ans.fi) {
				ch = nch, ans = tmp;
			} else if (tmp.se - tmp.fi == ans.se - ans.fi && tmp.fi + tmp.se > ans.fi + ans.se) {
				ch = nch, ans = tmp;
			}
		}
		printf("%c %d %d\n", ch, ans.fi, ans.se);
	}
	return 0;
}
