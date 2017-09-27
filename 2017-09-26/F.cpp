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
#define setIO(x) freopen(x".in","r", stdin);freopen(x".out","w",stdout);
//-------
const int N = 1e5 + 7;
pii p[N]; int n;
void error() { puts("-1"); exit(0); }
int main() {

	setIO("lights");
	
	///read
	scanf("%d", &n);
	rep(i, 0, n) scanf("%d%d", &p[i].fi, &p[i].se);

	///prework
	priority_queue<pii> tmp, que;
	int cur = 0;
	int _n = 1;
	ll ans = 0;
	do {
		while (_n < n && p[_n].fi <= p[cur].fi + p[cur].se) {
			p[cur].se = max(p[cur].se, p[_n].fi + p[_n].se - p[cur].fi);
			tmp.push(mp(-(p[_n].fi - p[_n].se), _n));
			_n++;
		}
		while (!tmp.empty() && -tmp.top().fi <= p[cur].fi) {
			int u = tmp.top().se; tmp.pop(); 
			if (u <= cur) continue;
			que.push(mp(p[u].fi + p[u].se, u));
		}
		while (!que.empty() && que.top().se <= cur) que.pop();
		if (que.empty()) error();
		int u = que.top().se; que.pop();
		ans += 1ll * (p[u].fi - p[cur].fi) * 3;
		cur = u;
	}	while (cur != n - 1);

	///print
	cout << ans << endl;

	return 0;
}
