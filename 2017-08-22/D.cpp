#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long double db;
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
const int N = 1e3 + 7;
const double EPS = 1e-8;
int n;
db Vx, Vy;
db x[N], y[N], k[N];
struct TPoint {
	db x, y;
	TPoint() {
	}
	TPoint(db _x, db _y) {
		x = _x, y = _y;
	}
	TPoint operator-(const TPoint &p) const {
		return TPoint(x - p.x, y - p.y);
	}
};
struct TLine {
	db a, b, c;
	TLine() {
	}
	TLine(db x1, db y1, db x2, db y2) {
		a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
		if (a < 0) a *= -1, b *= -1, c *= -1;
	}
};
pair<db, pair<db, db> > reflect(db a1, db b1, db c1, db a2, db b2, db c2) {
	db n, m, tpb, tpa, a, b, c;
	tpb = b1 * b2 + a1 * a2;
	tpa = a2 * b1 - a1 * b2;
	m = (tpb * b1 + tpa * a1) / (b1 * b1 + a1 * a1);
	n = (tpa * b1 - tpb * a1) / (b1 * b1 + a1 * a1);
	if (fabs(a1 * b2 - a2 * b1) < 1e-20) {
		a = a2, b = b2, c = c2;
	} else {
		db xx, yy;
		xx = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
		yy = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);
		a = n, b = -m, c = m * yy - n * xx;
	}
	return mp(a, mp(b, c));
}
inline int sign(double x) {
	if (fabs(x) <= EPS) return 0;
	return x < 0 ? -1 : 1;
}
TPoint line_inter(TLine l1, TLine l2) {
	TPoint tmp;
	if (sign(l1.b) == 0) {
		tmp.x = -l1.c / l1.a;
		tmp.y = (-l2.c - l2.a * tmp.x) / l2.b;
	} else {
		tmp.x = (l1.c * l2.b - l1.b * l2.c) / (l1.b * l2.a - l2.b * l1.a);
		tmp.y = (-l1.c - l1.a * tmp.x) / l1.b;
	}
	return tmp;
}
db dot(const TPoint &a, const TPoint &b) {
	return a.x * b.x + a.y * b.y;
}
db cross(const TPoint &a, const TPoint &b) {
	return a.x * b.y - a.y * b.x;
}
int pre;
int check(const TLine &now, int i) {
	TLine seg(x[i], y[i], x[i + 1], y[i + 1]);
	if (sign(now.b * seg.a - seg.b * now.a) == 0) return 0;
	TPoint ip = line_inter(now, TLine(x[i], y[i], x[i + 1], y[i + 1]));
	if (pre == -1 && sign(dot(TPoint(sign(Vx), sign(Vy)), TPoint(sign(ip.x), sign(ip.y)))) < 0) return 0;	
	return  (sign(ip.x - min(x[i], x[i + 1])) >= 0 && 
			sign(ip.x - max(x[i], x[i + 1])) <= 0) &&
			sign(ip.y - min(y[i], y[i + 1])) >= 0 && 
			sign(ip.y - max(y[i], y[i + 1])) <= 0;
}
bool isLS(TPoint a1, TPoint a2, TPoint b1, TPoint b2) {
	db c1 = cross(a2 - a1, b1 - a1), c2 = cross(a2 - a1, b2 - a1);	
	return sign(c1) * sign(c2) <= 0;
}
int solve() {
	int ret = 0;
	db I = 1;
	pre = -1;
	TPoint p(0, 0);
	TLine dir(0, 0, Vx, Vy);
	while (sign(I - 1e-4) >= 0) {
		bool flag = false;
		rep(i, 0, n) {
			if (i != pre && check(dir, i)) {
				if ((i + 1) % n != pre && check(dir, (i + 1) % n)) return ++ret;	
				if ((i - 1 + n) % n != pre && check(dir, (i - 1 + n) % n)) return ++ret;
				TLine ml = TLine(x[i], y[i], x[i + 1], y[i + 1]);
				p = line_inter(dir, ml);
				pair<db, pair<db, db> > r = reflect(ml.a, ml.b, ml.c, dir.a, dir.b, dir.c);
				dir.a = r.fi, dir.b = r.se.fi, dir.c = r.se.se;
				I *= k[i], pre = i, ++ret;
				flag = true;
				break;
			}
		}
//		if (!flag) break;
	}
	return ret;
}
int main() {
	while (~scanf("%d", &n)) {
		rep(i, 0, n) {
			double tx, ty, tk;
			scanf("%lf%lf%lf", &tx, &ty, &tk);
			x[i] = tx, y[i] = ty, k[i] = tk;
		}
		rep(i, 0, 3) x[n + i] = x[i], y[n + i] = y[i], k[n + i] = k[i];
		double vx, vy;
		scanf("%lf%lf", &vx, &vy);
		Vx = vx, Vy = vy;
		printf("%d\n", solve());
	}
	return 0;
}
