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
const int N = 2e2 + 7;
const db EPS = 1e-8;
const db PI = acos(-1.0);
const db g = 9.8;
const int INF = 1e6 + 7;
int sign(db x) {
	if (fabs(x) < EPS) return 0;
	return x < 0 ? -1 : 1;
}
struct Node {
	db v;
	Node() {}
	Node(db _v) {
		v = _v;
	}
	bool operator<(const Node &p) const {
		return v < p.v;
	}
	bool operator==(const Node &p) const {
		return sign(v - p.v) == 0;
	}
};
int n;
db H, L1, R1, L2, R2, v[N];
db dis(db a, db v) {
	db vy = v * sin(a);
	db dt = vy * vy + 2 * g * H;
	db t = (vy + sqrt(dt)) / g;
	return t * v * cos(a);
/*
	db vy = v * sin(a); 
	db t1 = vy / g;
	db d1 = vy * vy / 2 / g;
	db t2 = sqrt(2 * (d1 + H) / g);
	return v * cos(a) * (t1 + t2);
*/
}

pair<db, db> gao(db v) {
	db l = -PI / 2.0, r = PI / 2.0;
	rep(time, 0, 60) {
		db ll = (l + r) * 0.5;
		db rr = (ll + r) * 0.5;	
		dis(ll, v) < dis(rr, v) ? l = ll : r = rr;
	}
	return mp(l, dis(l, v));
}
db getix(db l, db r, db y, db v) {
	rep(time, 0, 60) {
		db z = (l + r) * 0.5;
		dis(z, v) < y ? l = z : r = z;			
	}
	return l;
}
db getdx(db l, db r, db y, db v) {
	rep(time, 0, 60) {
		db z = (l + r) * 0.5;
		dis(z, v) > y ? l = z : r = z;
	}
	return l;
}
int solve() {
	vector<Node> V;
	vector<pair<int, pair<Node, Node> > > S;
	rep(i, 0, n) {
		pair<db, db> F = gao(v[i]);
		rep(t, 0, 2) {
			db L = !t ? L1 : L2;
			db R = !t ? R1 : R2;
			int w = !t ? 1 : -INF;
//			dd(L), dd(R), de(w);
			if (sign(L - F.se) <= 0) {
				Node x[4];
				x[0] = getix(-PI / 2.0, F.fi, L, v[i]);
				x[3] = getdx(F.fi, PI / 2.0, L, v[i]);
				if (sign(R - F.se) < 0) {
					x[1] = getix(x[0].v, F.fi, R, v[i]);
					x[2] = getdx(F.fi, x[3].v, R, v[i]);
					rep(i, 0, 4) V.pb(x[i]);
//					rep(i, 0, 4) printf("%lf ", x[i].v); puts("x");
					S.pb(mp(w, mp(x[0], x[1])));		
					S.pb(mp(w, mp(x[2], x[3])));		
				} else {
					V.pb(x[0]), V.pb(x[3]);
					S.pb(mp(w, mp(x[0], x[3])));
				}	
			}
		}
	}
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	vector<int> add(sz(V) + 1, 0);	
	rep(i, 0, sz(S)) {
//		printf("%d %lf %lf\n", S[i].fi, S[i].se.fi.v, S[i].se.se.v);
		int p = lower_bound(all(V), S[i].se.fi) - V.begin();
		add[p] += S[i].fi;
		p = lower_bound(all(V), S[i].se.se) - V.begin() + 1;	
		add[p] -= S[i].fi;
	}
	int ret = 0, sum = 0;
	rep(i, 0, sz(V) - 1) {
		sum += add[i];
		ret = max(ret, sum);
	}
	return ret;
}
int main() {
	while (~scanf("%d", &n)) {
		if (n == 0) break;
		scanf("%lf%lf%lf%lf%lf", &H, &L1, &R1, &L2, &R2);	
		rep(i, 0, n) scanf("%lf", v + i);
		if (sign(L2 - L1) <= 0 && sign(R1 - R2) <= 0) {
			puts("0");
			continue;
		}
		int ans = solve();
		printf("%d\n", ans);
	}
	return 0;
}
