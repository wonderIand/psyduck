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
int n, m, w, a[N], b[N];
bitset<1007> f0, g0;
bitset<N> f, g;
vector<pii> A, B;
char ans[N << 1];
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d%d%d", &n, &m, &w);
		A.clear(), B.clear();
		rep(i, 0, n) scanf("%d", a + i), A.pb(mp(a[i], i));
		rep(i, 0, m) scanf("%d", b + i), B.pb(mp(b[i], i));
		if (n + m <= 1000) {
			f0.reset(), g0.reset();	
			sort(all(A)), sort(all(B));
			int i = 0;	
			while (i < sz(A) && A[i].fi == 0) ++i;
			int j = sz(B) - 1;
			while (j >= 0 && B[j].fi > w) g0[B[j].se] = 1, --j;
			while (i < sz(A) && A[i].fi == 1) {
				f0 |= g0 << A[i].se;	
				++i;	
			}
			g0.reset();
			for (int j = sz(B) - 1; i < sz(A); ++i) {
				while (j >= 0 && B[j].fi && (B[j].fi > 1 && 0ll + A[i].fi + B[j].fi > w || A[i].fi > w)) {
					g0[B[j].se] = 1;
					--j;
				}
				f0 |= g0 << A[i].se;
			}
			rep(i, 0, n + m - 1) ans[i] = (f0[i] ? 'Y' : 'N');
			ans[n + m - 1] = '\0';
		} else {
			f.reset(), g.reset();	
			sort(all(A)), sort(all(B));
			int i = 0;	
			while (i < sz(A) && A[i].fi == 0) ++i;
			int j = sz(B) - 1;
			while (j >= 0 && B[j].fi > w) g[B[j].se] = 1, --j;
			while (i < sz(A) && A[i].fi == 1) {
				f |= g << A[i].se;	
				++i;	
			}
			g.reset();
			for (int j = sz(B) - 1; i < sz(A); ++i) {
				while (j >= 0 && B[j].fi && (B[j].fi > 1 && 0ll + A[i].fi + B[j].fi > w || A[i].fi > w)) {
					g[B[j].se] = 1;
					--j;
				}
				f |= g << A[i].se;
			}
			rep(i, 0, n + m - 1) ans[i] = (f[i] ? 'Y' : 'N');
			ans[n + m - 1] = '\0';
		}
		puts(ans);
	}
	return 0;
}
