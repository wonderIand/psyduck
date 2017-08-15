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
const int N = 1e7 + 7;
int main() {
	vector<int> v;
	v.pb(1), v.pb(2), v.pb(2);
	rep(i, 2, sz(v)) {
		int x = 3 - v.back();	
		rep(j, 0, v[i])
			v.pb(x);
		if (sz(v) >= N) break;
	}
//	rep(i, 0, sz(v)) printf("%d ", v[i]);
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		int n;
		scanf("%d", &n);
		printf("%d\n", v[n - 1]);
	}

	return 0;
}
