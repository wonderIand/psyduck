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
const int N = 1e5 + 7;
int n, k, a[N];
int solve() {
	sort(a, a + n);
	int ret = 1;		
	for (int i = n - 2; i >= 0; --i) {
		if (a[i + 1] - a[i] > k)
			break;
		++ret;
	}
	return ret;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d%d", &n, &k);
		rep(i, 0, n) scanf("%d", a + i);
		printf("%d\n", solve());
	}

	return 0;
}
