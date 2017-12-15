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
int a, b, c;
void gao(int lx, int ly, int lz) {
	//xoy: a;
	//xoz: b
	//yoz: c
	vector<pair<int, pii> > ans; ans.pb({0, {0, 0}});
	rep(i, 1, lx) ans.pb({i, {0, 0}});
	rep(i, 1, ly) ans.pb({0, {i, 0}});
	rep(i, 1, lz) ans.pb({0, {0, i}});
	a -= lx + ly - 1;
	b -= lx + lz - 1;
	c -= ly + lz - 1;
	rep(x, 1, lx) {
		rep(y, 1, ly) {
			if (!a) break; else a--;
			ans.pb({x, {y, 0}});
		}
	}
	rep(x, 1, lx) {
		rep(z, 1, lz) {
			if (!b) break; else b--;
			ans.pb({x, {0, z}});
		}
	}
	rep(y, 1, ly) {
		rep(z, 1, lz) {
			if (!c) break; else c--;
			ans.pb({0, {y, z}});
		}
	}
	printf("%d\n", sz(ans));
	rep(i, 0, sz(ans)) printf("%d %d %d\n", ans[i].fi, ans[i].se.fi, ans[i].se.se);
}
void solve() {
	for (int h = 1; h <= b; h++)
		for (int w = 1; w <= c; w++) if (h * w >= a) {
			int b2 = b - h;
			int c2 = c - w;
			if (c2 >= b2) {
				if (c2 - b2 <= (w - 1) * min(b2, c2)) {
					gao(h, w, min(b2, c2) + 1);
					return;
				}
			}
			else {
				if (b2 - c2 <= (h - 1) * min(b2, c2)) {
					gao(h, w, min(b2, c2) + 1);
					return;
				}
			}
		}
	puts("-1");
}
int main() {
	while (~scanf("%d%d%d", &a, &b, &c)) solve();
	return 0;
}
