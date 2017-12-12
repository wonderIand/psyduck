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
const int N = 1e5 + 7;
const int INF = 1e9 + 7;
int a[N], n;
ll ans[N], tmp[N];

void gao2(int l, int r, int b, int o) {
	priority_queue<pii> que;
	if (o) {
		rep(i, l, r) { 
			if ((a[i] & 1) == b) que.push({-a[i], i});
			if ((i & 1) == b) {
				ans[i] = -que.top().fi;
				ans[0] += abs(que.top().se - i);
				que.pop();
			}
		}
	}
	else {
		per(i, l, r) {
			if ((a[i] & 1) == b) que.push({a[i], i});
			if ((i & 1) == b) {
				ans[i] = que.top().fi;
				ans[0] += abs(que.top().se - i);
				que.pop();
			}
		}
	}
}

void gao(int b) {
	int val = 0;
	for (int l = 1, r, pre = 0; l <= n; l = r) {
		int mx = -INF, mi = INF;
		for (r = l; r <= n; r++) {
			int _val = val;
			if ((r & 1) == b) val++;
			if ((a[r] & 1) == b) val--;
			if (abs(val) == 1 && val != pre) {
				pre = val;
				val = _val;
				break;
			}
			mx = max(mx, val);
			mi = min(mi, val);
		}
/*		de(l);
		de(r);
		de(mx);
		de(mi);*/
		if (l == r) continue;
		if (mi >= 0) gao2(l, r, b, 0);
		else if (mx <= 0) gao2(l, r, b, 1);
		else assert(false);
	}
}

void solve() {
	rep(i, 1, n + 1) scanf("%d", &a[i]); 
	int base = 0;
	if (n & 1) {
		int odd = 0;
		rep(i, 1, n + 1) if (a[i] & 1) odd++;
		if (odd != (n + 1) / 2) {
			base = 1;
			rep(i, 1, n + 1) a[i]++;
		}
	}
	ans[0] = 0;
	gao(0);
	gao(1);
	if (n % 2 == 0) {
		rep(i, 0, n + 1) tmp[i] = ans[i];
		rep(i, 1, n + 1) a[i]++;
		ans[0] = 0;
		gao(0);
		gao(1);
		int p = 0; 
		if (tmp[0] == ans[0]) {
			p = 1;
			while (p <= n && tmp[p] == ans[p] - 1) p++;
		}
		if (p <= n && tmp[p] < ans[p] - (p > 0)) {
			rep(i, 1, n + 1) ans[i] = tmp[i];
		}
		else base = 1;
	}
	rep(i, 1, n + 1) printf("%lld%c", ans[i] - base, " \n"[i == n]);
}


int main() {
	while (~scanf("%d", &n)) solve();
	return 0;
}
