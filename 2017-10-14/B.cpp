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
#define de(x) cout << #x << " = " << x << ebdl
//-------
int n;
int main() {

	//read
	scanf("%d", &n);
	vi v;
	rep(i, 0, n) {
		int dig; scanf("%d", &dig);
		for (int j = 1; j * j <= dig; j++) if (dig % j == 0) {
			v.pb(j);
			v.pb(dig / j);
		}
	}

	//prework
	sort(all(v));
	v.erase(unique(all(v)), v.end());
	rep(i, 0, sz(v) - 1) {
		if (v[i + 1] != v[i] + 1) {
			printf("%d", v[i] + 1);
			return 0;
		}
	}
	printf("%d", v.back() + 1);

	return 0;
}
