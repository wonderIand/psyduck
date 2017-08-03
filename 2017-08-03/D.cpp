#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
//-------
const int N = 6e4 + 7;
int n, a[N], p[N];
struct SegTree {
	#define ls ((t)<<1)
	#define rs ((t)<<1|1)
	int add[N << 2];
	double val[N << 2];
	void up(int t) {
		val[t] = min(val[ls], val[rs]);
	}
	void down(int t) {
		if (add[t] != 0) {
			add[ls] += add[t], val[ls] += add[t];
			add[rs] += add[t], val[rs] += add[t];
			add[t] = 0;
		}
	}
	void build(int t, int l, int r, double x) {
		add[t] = 0;
		if (l == r) {
			val[t] = l * x;
		} else {
			int z = (l + r) >> 1;
			build(ls, l, z, x), build(rs, z + 1, r, x);
			up(t);
		}
	}
	void upd(int t, int l, int r, int L, int R, int V) {
		if (L <= l && r <= R) {
			add[t] += V, val[t] += V;
			return ;
		}
		down(t);
		int z = (l + r) >> 1;
		if (L <= z) upd(ls, l, z, L, R, V);
		if (R > z) upd(rs, z + 1, r, L, R, V);
		up(t);
	}
	double qry(int t, int l, int r, int L, int R) {
		if (L <= l && r <= R) return val[t];
		down(t);
		int z = (l + r) >> 1;
		double ret = 1e9;
		if (L <= z) ret = min(ret, qry(ls, l, z, L, R));
		if (R > z) ret = min(ret, qry(rs, z + 1, r, L, R));
		up(t);
		return ret;
	}
} seg;
bool check(double x) {
	rep(i, 1, n + 1) p[i] = 0;
	seg.build(1, 1, n, x);
	rep(i, 1, n + 1) {
		seg.upd(1, 1, n, p[a[i]] + 1, i, 1);
		p[a[i]] = i;
		if (seg.qry(1, 1, n, 1, i) <= (i + 1) * x)
			return true;
	}
	return false;
}
double solve() {
	double l = 0, r = 1;
	rep(time, 0, 30) {
		double z = (l + r) / 2.0;
		check(z) ? r = z : l = z;
	}
	return (l + r) / 2.0;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d", &n);
		rep(i, 1, n + 1) scanf("%d", a + i);
		printf("%.9f\n", solve());
	}
	return 0;
}
