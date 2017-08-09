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
int n, m, K, Q, tot;
ll ans[N];
set<int> S, Y[N];
set<int>::iterator it;
struct Node {
	int x, y, id;
	Node() {
	}
	Node(int _x, int _y, int _id) {
		x = _x, y = _y, id = _id;
	}
	bool operator<(const Node &p) const {
		return x < p.x;
	}
} a[N << 1];
struct SegTree {
	#define ls ((t)<<1)
	#define rs ((t)<<1|1)
	#define md ((l+r)>>1)
	int mn[N << 2], mx[N << 2];
	ll lmn[N << 2], lmx[N << 2], rmn[N << 2], rmx[N << 2];
	ll qlmn(int t, int l, int r, int V) {
		if (V <= mn[t]) return 1ll * V * (r - l + 1);	
		if (l == r) return mn[t];	
		if (V <= mn[rs]) return 1ll * V * (r - md) + qlmn(ls, l, md, V);
		return lmn[t] + qlmn(rs, md + 1, r, V);
	}
	ll qlmx(int t, int l, int r, int V) {
		if (V >= mx[t]) return 1ll * V * (r - l + 1);
		if (l == r) return mx[t];	
		if (V >= mx[rs]) return 1ll * V * (r - md) + qlmx(ls, l, md, V);
		return lmx[t] + qlmx(rs, md + 1, r, V);	
	}
	ll qrmn(int t, int l, int r, int V) {
		if (V <= mn[t]) return 1ll * V * (r - l + 1);		
		if (l == r) return mn[t];
		if (V <= mn[ls]) return 1ll * V * (md - l + 1) + qrmn(rs, md + 1, r, V);	
		return rmn[t] + qrmn(ls, l, md, V);	
	}
	ll qrmx(int t, int l, int r, int V) {
		if (V >= mx[t]) return 1ll * V * (r - l + 1);
		if (l == r) return mx[t];	
		if (V >= mx[ls]) return 1ll * V * (md - l + 1) + qrmx(rs, md + 1, r, V);
		return rmx[t] + qrmx(ls, l, md, V);
	}
	inline void up(int t, int l, int r) {
		mn[t] = min(mn[ls], mn[rs]);
		mx[t] = max(mx[ls], mx[rs]);
		lmn[t] = qlmn(ls, l, md, mn[rs]);	
		lmx[t] = qlmx(ls, l, md, mx[rs]);
		rmn[t] = qrmn(rs, md + 1, r, mn[ls]);
		rmx[t] = qrmx(rs, md + 1, r, mx[ls]);
	}
	void build(int t, int l, int r) {
		if (l == r) {
			mx[t] = 0, it = Y[l].begin(), ++it, mn[t] = *it; 
			return ;
		}
		build(ls, l, md), build(rs, md + 1, r);
		up(t, l, r);
	}
	void updmin(int t, int l, int r, int P, int V) {
		if (l == r) {
			mn[t] = V;		
			return ;
		}
		if (P <= md) updmin(ls, l, md, P, V);
		else updmin(rs, md + 1, r, P, V);
		up(t, l, r);
	}
	void updmax(int t, int l, int r, int P, int V) {
		if (l == r) {
			mx[t] = V;
			return ;
		}
		if (P <= md) updmax(ls, l, md, P, V);
		else updmax(rs, md + 1, r, P, V);
		up(t, l, r);
	}
	ll qlmn(int t, int l, int r, int L, int R, int &V) {
		if (R < l || r < L) return 0;
		if (L <= l && r <= R) {
			ll ret = qlmn(t, l, r, V);
			V = min(V, mn[t]);
			return ret;
		}
		return qlmn(rs, md + 1, r, L, R, V) + qlmn(ls, l, md, L, R, V);	
	}
	ll qlmx(int t, int l, int r, int L, int R, int &V) {
		if (R < l || r < L) return 0;
		if (L <= l && r <= R) {
			ll ret = qlmx(t, l, r, V);
			V = max(V, mx[t]);
			return ret;
		}
		return qlmx(rs, md + 1, r, L, R, V) + qlmx(ls, l, md, L, R, V);
	}
	ll qrmn(int t, int l, int r, int L, int R, int &V) {
		if (R < l || r < L) return 0;
		if (L <= l && r <= R) {
			ll ret = qrmn(t, l, r, V);
			V = min(V, mn[t]);
			return ret;
		}
		return qrmn(ls, l, md, L, R, V) + qrmn(rs, md + 1, r, L, R, V);
	}
	ll qrmx(int t, int l, int r, int L, int R, int &V) {
		if (R < l || r < L) return 0;
		if (L <= l && r <= R) {
			ll ret = qrmx(t, l, r, V);
			V = max(V, mx[t]);
			return ret;
		}
		return qrmx(ls, l, md, L, R, V) + qrmx(rs, md + 1, r, L, R, V);
	}
} seg;
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d%d%d%d", &n, &m, &K, &Q);
		rep(i, 1, m + 1) Y[i].clear(), Y[i].insert(0), Y[i].insert(n + 1);
		tot = 0;
		rep(i, 0, K) {
			int x, y;scanf("%d%d", &x, &y);
			a[tot++] = Node(x, y, 0);
			Y[y].insert(x);
		}
		rep(i, 1, Q + 1) {
			int x, y;scanf("%d%d", &x, &y);
			a[tot++] = Node(x, y, i);
		}
		seg.build(1, 1, m), sort(a, a + tot);
		for (int ai = 0, aj; ai < tot; ai = aj) {
			aj = ai + 1, S.clear();
			while (aj < tot && a[aj].x == a[ai].x) ++aj;
			rep(i, ai, aj) if (!a[i].id) { 
				S.insert(a[i].y);
				seg.updmax(1, 1, m, a[i].y, a[i].x);
			}
			S.insert(0), S.insert(m + 1);
			rep(i, ai, aj) if (a[i].id) {
				ll cnt = 0;
				int l, r, v;
				cnt += seg.qlmn(1, 1, m, 1, a[i].y, v = n + 1);
				cnt += seg.qrmn(1, 1, m, a[i].y, m, v = n + 1);
				cnt -= seg.qlmx(1, 1, m, 1, a[i].y, v = 0);
				cnt -= seg.qrmx(1, 1, m, a[i].y, m, v = 0);
				it = S.lower_bound(a[i].y);
				r = *it, --it, l = *it;
				cnt -= r - l - 1;	
				it = Y[a[i].y].lower_bound(a[i].x);	
				r = *it, --it, l = *it;
				cnt -= r - l;
				ans[a[i].id] = cnt;
			}
			rep(i, ai, aj) if (!a[i].id) {
				it = Y[a[i].y].upper_bound(a[i].x);
				seg.updmin(1, 1, m, a[i].y, *it);
			}
		}
		rep(i, 1, Q + 1) printf("%lld\n", ans[i]);
	}
	return 0;
}
