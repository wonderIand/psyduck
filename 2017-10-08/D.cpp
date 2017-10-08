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
const int N = 5e4 + 7;
const ll LINF = 1e15 + 7;
int n, k, th;
ll f[N];
struct SegTree {
	#define ls ((t)<<1)
	#define rs ((t)<<1|1)
	ll val[N << 2];
	void build(int t, int l, int r, ll v[]) {
		if (l == r) {
			val[t] = v[l];
		} else {
			int z = (l + r) >> 1;
			build(ls, l, z, v), build(rs, z + 1, r, v);
			val[t] = min(val[ls], val[rs]);
		}
	}
	ll qry(int t, int l, int r, int L, int R) {
		if (L <= l && r <= R) return val[t];
		int z = (l + r) >> 1;
		if (R <= z) return qry(ls, l, z, L, R);
		if (L > z) return qry(rs, z + 1, r, L, R);
		return min(qry(ls, l, z, L, R), qry(rs, z + 1, r, L, R));
	}
} seg;
ll solve() {
	rep(i, 0, k + 1) f[i] = 0;
	rep(i, 1, n + 1) {
		seg.build(1, 0, k, f);
		int x;
		scanf("%d", &x);
		rep(j, 0, k + 1) {
			f[j] = min(LINF, seg.qry(1, 0, k, max(0, j - th), j) + 1ll * (j - x) * (j - x));
//			printf("f[%d][%d] = %lld\n", i, j, f[j]);
		}
	}
	seg.build(1, 0, k, f);
	return seg.qry(1, 0, k, 0, k);
}
int main() {
	while (~scanf("%d", &n)) {
		if (n == 0) break;
		scanf("%d%d", &k, &th);		
		printf("%lld\n", solve());
	}
	return 0;
}
