#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double db;
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
const db EPS = 1e-15;
inline int sgn(db x) {
	return (x > EPS) - (x < -EPS);
}
namespace SBT {
	const int INF = 1e5;
	typedef __int128 T;
	typedef pair<T, T> V; // V = [double|long double|fraction]
	inline T f(T x) {
		return x * x * x;
	}
	inline int cmp(const V &a, const V &b) {
		T x = f(a.fi) * b.se - f(a.se) * b.fi;
		return (x > 0) - (x < 0);
	}
	pii operator+(const pii &a, const pii &b) {
		return mp(a.fi + b.fi, a.se + b.se);
	}
	pii operator*(const pii &a, int x) {
		return mp(a.fi * x, a.se * x);
	}
	void search(V v, int MAXB, pii &lo, pii &hi, int f) {
		V x;
		int l = 0, r = f > 0 ? (hi.se ? (MAXB - lo.se) / hi.se : INF) : 
			(lo.se ? (MAXB - hi.se) / lo.se : INF);
		while (l + 1 < r) {
			int z = (l + r) >> 1;
			x = f > 0 ? lo + hi * z : lo * z + hi;
			f * cmp(x, v) <= 0 ? l = z : r = z;
		}
		x = f > 0 ? lo + hi * r : lo * r + hi;
		r = f * cmp(x, v) <= 0 ? r : l;
		f > 0 ? lo = lo + hi * r : hi = lo * r + hi;
	}
	pair<pii, pii> solve(V v, int MAXB) {
		V L = mp(v.fi * 10 - 5, v.se * 10);	
		V R = mp(v.fi * 10 + 5, v.se * 10);
		pii lo(0, 1), hi(1, 0);
		while (true) {
			V m = mp(lo.fi + hi.fi, lo.se + hi.se);	
			if (m.se > MAXB) break;
			pii tmp;
			if (cmp(m, v) <= 0) { 
				search(v, MAXB, lo, hi, 1);
			} else {
				search(v, MAXB, lo, hi, -1);
			}
		}
		return mp(lo, hi);
	}
};
typedef __int128 T;
db get(int K) {
	db l = 0, r = K;
	rep(time, 0, 100) {
		db m = (l + r) * 0.5;	
		sgn(m * m * m - 1.0 * K * K) <= 0 ? l = m : r = m;
	}
	return l;
}
int main() {
	int CAS;
	scanf("%d", &CAS);
	rep(cas, 0, CAS) {
		int K; scanf("%d", &K);
		pair<pii, pii> ans = SBT::solve(mp((T) K * K, 1), (int)1e5);
		pii lo = ans.fi, hi = ans.se;
		db x = get(K);
		db dlo = abs((db)lo.fi / lo.se - x);
		db dhi = abs((db)hi.fi / hi.se - x);
		if (sgn(dlo - dhi) < 0) {
			printf("%d/%d\n", lo.fi, lo.se);
		} else {
			printf("%d/%d\n", hi.fi, hi.se);
		}
	}
	return 0;
}
