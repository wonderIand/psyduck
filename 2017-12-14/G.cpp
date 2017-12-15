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
const int N = 3e4 + 7;
ll rnd() {
	return (((ll)rand() << 31) ^ ((ll)rand() << 16) ^ (rand())) & INT_MAX;
}
struct TREAP {
	ll v[N];
	int tot, root, l[N], r[N], hr[N], s[N];	
	void init() {
		srand(time(NULL));
		tot = root = 0;
	}
	void Lr(int &x) {
		int y;
		y = r[x], r[x] = l[y], l[y] = x;
		s[y] = s[x], s[x] = 1 + s[l[x]] + s[r[x]];
		x = y;
	}
	void Rr(int &x) {
		int y ;
		y = l[x], l[x] = r[y], r[y] = x;
		s[y] = s[x], s[x] = 1 + s[l[x]] + s[r[x]];
		x = y;
	}
	void insert(int &k, ll key) {
		if (k == 0) {
			++tot, v[tot] = key, s[tot] = 1, l[tot] = r[tot] = 0;
			hr[k = tot] = rnd();
			return ;
		}
		++s[k];
		if (key <= v[k]) {
			insert(l[k], key);
			if (hr[l[k]] > hr[k]) Rr(k);
		} else {
			insert(r[k], key);
			if (hr[r[k]] > hr[k]) Lr(k);
		}
	}
	ll del(int &k, ll key) {
		ll res;
		--s[k];
		if (key == v[k] || (l[k] == 0 && key < v[k]) 
						|| (r[k] == 0 && key >= v[k])) {
			res = v[k];
			if (l[k] == 0 || r[k] == 0) {
				k = l[k] + r[k];
				return res;
			}
			v[k] = del(l[k], key + 1);
			return res;
		}
		if (key <= v[k]) return del(l[k], key);
		else return del(r[k], key);
		return -1;
	}
	int rank(int k, ll key) {
		if (k == 0) return 0;
		if (key <= v[k]) return (key == v[k]) + rank(l[k], key);
		else return s[l[k]] + 1 + rank(r[k], key);
	}
} treap;
int n, R, K, a[N], b[N], c[N];
ll sa[N], sb[N], sc[N];
inline ll iab(int l, int r) {
	return (sb[r] - sb[l - 1]) - (sa[r] - sa[l - 1]);	
}
int gao(ll C) {
	int ret = 0;
	// no
	treap.init();
	rep(i, 1, n - R + 1 + 1) { 
		treap.insert(treap.root, iab(i, i + R - 1));
//		dd(i), de(iab(i, i + R - 1));
	}
	for (int x = 1, y = 1; x < n - R + 1; ++x) {
		while (y <= x + R - 1) {
			treap.del(treap.root, iab(y, y + R - 1));
			++y;
		}
		ll now = sa[n] + iab(x, x + R - 1);
		ret += treap.rank(treap.root, C - now);
//		dd(C - now), dd(x), dd(y), de(ret);
		if (ret >= K) return ret;
	}
	// inter
	treap.init();
	for (int x = 1, ly = 1, ry = 1; x < n - R + 1; ++x) {
		while (ry <= x + R - 1) {
			int &y = ry;
			ll add = sb[y + R - 1] - sa[y + R - 1] - sc[y - 1] + sb[y - 1];
			treap.insert(treap.root, add);
			++y;
		}
		while (ly <= x) {
			int &y = ly;
			ll add = sb[y + R - 1] - sa[y + R - 1] - sc[y - 1] + sb[y - 1];
			treap.del(treap.root, add);
			++y;
		}
		ll now = sa[n] + iab(x, x + R - 1)
			- sb[x + R - 1] + sa[x + R - 1] + sc[x + R - 1] - sb[x + R - 1];
		ret += treap.rank(treap.root, C - now);	
		if (ret >= K) return ret;
	}
	return ret;
}
ll solve() {
	ll l = 0, r = 3e10 + 7;
	while (l + 1 < r) {
		ll z = (l + r) >> 1;
		gao(z) >= K ? r = z : l = z;
	}
	return gao(l) >= K ? l : r;
}
int main() {	
	scanf("%d%d%d", &n, &R, &K);
	rep(i, 1, n + 1) scanf("%d", a + i), sa[i] = sa[i - 1] + a[i];
	rep(i, 1, n + 1) scanf("%d", b + i), sb[i] = sb[i - 1] + b[i];
	rep(i, 1, n + 1) scanf("%d", c + i), sc[i] = sc[i - 1] + c[i];
	cout << solve() << endl;
	return 0;
}
