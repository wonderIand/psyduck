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
int n, L;
struct Node {
	int val, pre, nxt;
	Node() {
	}
	Node(int _val, int _pre, int _nxt) {
		val = _val, pre = _pre, nxt = _nxt;
	}
} a[N];
struct FS {
	int x, y;
	FS() {
	}
	FS(int _x, int _y) {
		x = _x, y = _y;	
		assert(x >= 0);
		int g = abs(__gcd(x, y));
		if (g) x /= g, y /= g;
	}
	bool operator<(const FS &p) const {
		return 1ll * x * p.y > 1ll * y * p.x;
	}
};
pair<int, pii> b[N];
FS gao(int i, int j) { // i < j, d[i] < d[j]
	int di = b[i].fi, dj = b[j].fi;
	int vi = b[i].se.fi, vj = b[j].se.fi;
	if (vi - vj < 0)
		swap(di, dj), swap(vi, vj);
	return FS((dj - di + L) % L, vi - vj);	
}
void del(int x) {
	int pre = a[x].pre, nxt = a[x].nxt;
	a[pre].nxt = nxt, a[nxt].pre = pre;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d%d", &n, &L);	
		rep(i, 0, n) scanf("%d", &b[i].fi);
		rep(i, 0, n) scanf("%d", &b[i].se.fi), b[i].se.se = i;
		sort(b, b + n);
		rep(i, 0, n) a[i] = Node(b[i].se.se, (i - 1 + n) % n, (i + 1) % n);
		priority_queue<pair<FS, pii> > que;		
		rep(i, 0, n) que.push(mp(gao(a[i].pre, i), mp(a[i].pre, i)));
		FS ans(0, 1);
		while (!que.empty()) {
			FS t = que.top().fi;		
			pii p = que.top().se;
			que.pop();
			if (a[p.fi].nxt != p.se || p.fi != a[p.se].pre)
				continue;
			ans = t;
			if (a[p.fi].val < a[p.se].val) {
				del(p.fi);
				if (a[p.se].pre != p.se)
					que.push(mp(gao(a[p.se].pre, p.se), mp(a[p.se].pre, p.se)));		
			} else {
				del(p.se);
				if (p.fi != a[p.fi].nxt)
					que.push(mp(gao(p.fi, a[p.fi].nxt), mp(p.fi, a[p.fi].nxt)));		
			}
		}
		printf("%d/%d\n", ans.x, ans.y);
	}
	return 0;
}
