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
const int N = 2e5 + 7;
int n;
vi V;
tuple<int, int, int> OP[N];
set<pair<pii, int> > S;
struct SegTree {
	#define sqr(x) (ll(x)*(x))
	#define ls (t<<1)
	#define rs (t<<1|1)
	vi oid[N << 2];	
	void erase(vi &v, int p) {
		vi tmp;	swap(v, tmp);
		rep(i, 0, p) v.pb(tmp[i]);
		rep(i, p + 1, sz(tmp)) v.pb(tmp[i]);
	}
	void upd(int t, int l, int r, int L, int R, int V) {
		if (L <= l && r <= R) {
			int p = -1;
			rep(i, 0, sz(oid[t])) {
				int id = oid[t][i];
				if (id == V) {
					p = i;
					break;
				}
			}
			if (~p) {
				erase(oid[t], p);
			} else {
				oid[t].pb(V);
			}
			return ;
		}
		int z = (l + r) >> 1;
		if (L <= z) upd(ls, l, z, L, R, V);
		if (R > z) upd(rs, z + 1, r, L, R, V);
	}
	int qry(int t, int l, int r, int X, int Y) {
		for(auto id : oid[t]) {
			int w, x, y;
			tie(w, x, y) = OP[id];
			if (sqr(V[X] - x) + sqr(Y - y) < sqr(y)) return id;
		}
		if (l == r) return -1;
		int z = (l + r) >> 1;	
		if (X <= z) return qry(ls, l, z, X, Y);
		else return qry(rs, z + 1, r, X, Y);
	}
} seg;
int main() {
	scanf("%d", &n);
	rep(i, 0, n) {
		int t, x, y;
		scanf("%d%d%d", &t, &x, &y);
		OP[i] = make_tuple(t, x, y);
		if (t == 2) V.pb(x);
	}
	V.pb(INT_MIN), V.pb(INT_MAX);
	sort(all(V)); V.erase(unique(all(V)), V.end());
//	rep(i, 0, sz(V)) printf("%d " , V[i]);puts("");
	rep(_n, 0, n) {
		int t, x, y;
		tie(t, x, y) = OP[_n];
		if (t == 1) {
			int l = lower_bound(all(V), x - y) - V.begin(); 	
			int r = upper_bound(all(V), x + y) - V.begin() - 1;
			seg.upd(1, 0, sz(V), l, r, _n);
//			dd(l), dd(r), de(id);	
		} else {
			int p = lower_bound(all(V), x) - V.begin();
			int nid = seg.qry(1, 0, sz(V), p, y);
			if (~nid) {
				tie(t, x, y) = OP[nid];
				int l = lower_bound(all(V), x - y) - V.begin(); 	
				int r = upper_bound(all(V), x + y) - V.begin() - 1;
				seg.upd(1, 0, sz(V), l, r, nid);
			}
			printf("%d\n", ~nid ? nid + 1 : -1);
		}
	}
	return 0;
}
