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
int x, y;
struct FS {
	ll x, y;
	FS() {}
	FS(ll _x, ll _y) {
		x = _x, y = _y;
//		ll g = abs(__gcd(x, y));
//		if (g) x /= g, y /= g;
	}
	FS operator+(const FS &p) const {
		return FS(x * p.y + y * p.x, y * p.y);
	}
	FS operator-(const FS &p) const {
		return FS(x * p.y - y * p.x, y * p.y);
	}
	bool operator<(const FS &p) const {
		return 1ll * x * p.y < 1ll * y * p.x;
	}
};
const int INF = 1e9 + 10;
int dfs(int xi, FS p) {	
	if (xi == x || !(x * p.x < y * p.y)) {
		ll yi = x * p.x / p.y;
		if (yi <= y) return (x - xi) + y - yi;
		return INF;	
	}
	// x += 1
	int r1 = 1 + dfs(xi + 1, p);
	// y += 1
	FS q = FS(y, x) - p;
	int dy = xi * q.x / q.y;
	int r2 = 1 + dy + dfs(xi + 1, p + FS(dy, xi));
	++dy;
	int r3 = 1 + dy + dfs(xi + 1, p + FS(dy, xi));
	return min(r1, min(r2, r3));
}
ll solve() {
	if (y < x) return -1;	
	return dfs(1, FS(1, 1));
}
int main() {
	while (~scanf("%d%d", &x, &y)) {
		int ans = (y < x) ? -1 : dfs(1, FS(1, 1));
		printf("%d\n", ans);
	}
	return 0;
	rep(t, 0, 50000) {
		x = 10, y = 1e9;
		int ans = (y < x) ? -1 : dfs(1, FS(1, 1));
	}
	return 0;
}
