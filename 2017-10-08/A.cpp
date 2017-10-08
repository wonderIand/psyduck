
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
char str[1000];
vi div2(vi a) {
	vi ret;
	int tmp = 0;
	bool has = false;
	rep(i, 0, sz(a)) {
		tmp = tmp * 10 + a[i];
		if (has || (tmp >> 1)) ret.pb(tmp >> 1);
		tmp &= 1;
		has= true;
	}
	return ret;
}
void out(vi a) { rep(i, 0,  sz(a)) printf("%d", a[i]); printf("\n"); }

int main() {
	
	
	for (; ~scanf(" %s", str); ) {
		///read
		int n = strlen(str);
		if (n == 1 && str[0] == '0') break;
		vi va; rep(i, 0, n) va.pb(str[i] - '0');
		
		///work
		vi vb;
		while (!va.empty()) {
			vb.pb(va.back()&1);
			va = div2(va);
		}
		
		///
		int ans1 = 0; rep(i, 0, sz(vb)) ans1 += vb[i];
		int ans2 = ans1;
		reverse(all(vb));
		for (int l = 0, r; l < sz(vb); l = r) {
			for (r = l; r < sz(vb) && vb[r] == vb[l]; r++);
			if (vb[l] == 0) continue;
			int cnt = r - l;
			if (cnt >= 2) {
				ans2 -= cnt - 2;
				if (r < sz(vb)) {
					vb[r] = 1;
				}
			}
		}
		printf("%d %d\n", ans1, ans2);

	}


	return 0;
}
