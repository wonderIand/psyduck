#include <bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define per(i,a,b) for (int i = (b) - 1; i >= (a); i--)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 2e3 + 7;
const db EPS = 1e-8;
struct P {
	db x, y;
	P() {}
	P(db _x, db _y) {
		x = _x, y = _y;	
	}
	void in() {
		scanf("%lf%lf", &x, &y);
	}
	void out() {
		printf("%f %f\n", x, y);
	}
	P operator+(const P &p) const {
		return P(x + p.x, y + p.y);
	}
	P operator-(const P &p) const {
		return P(x - p.x, y - p.y);
	}
	db operator^(const P &p) const {
		return x * p.y - y * p.x;
	}
};
inline int sign(db x) {
	return (x > EPS) - (x < -EPS);
}
bool isSS(P a1, P a2, P b1, P b2) {
	return sign((a2 - a1) ^ (b1 - a1)) * sign((a2 - a1) ^ (b2 - a1)) < 0 &&
		sign((b2 - b1) ^ (a1 - b1)) * sign((b2 - b1) ^ (a2 - b1)) < 0;
}
int n, f[N][N];
P p[N], d[N];
int main() {
	while (~scanf("%d", &n)) {
		if (n == 0) break;
		rep(i, 0, n) p[i].in(), d[i].in();
		p[n].in(), p[n + 1].in();
		rep(i, 0, n + 2)
			rep(j, i + 1, n + 2) {
				f[i][j] = 0;
				rep(k, 0, n) {
					P o = d[k] - p[k];	
					o.x *= 1e9, o.y *= 1e9;
					o = p[k] + o;
					if (isSS(p[i], p[j], p[k], o))
						++f[i][j];
				}
				f[j][i] = f[i][j];
//				printf("f[%d][%d] = %d\n", i, j, f[i][j]);
			}
		rep(k, 0, n + 2)
			rep(i, 0, n + 2) rep(j, 0, n + 2)
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
		printf("%d\n", f[n][n + 1]);
	}
	return 0;
}
