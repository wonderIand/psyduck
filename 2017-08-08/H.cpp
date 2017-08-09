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
//------
const int N = 55;
const int M = 1e4 + 7;
int n, m, b[M];
int get(int x) {
	rep(i, 0, N) if (x >> i & 1) return i;
}
void solve() {
	vector<int> a;
	int zero = get(b[0]);
	rep(i, 0, zero) a.pb(0);
	rep(i, 0, m + 1) b[i] -= b[0] - 1;	
	int mx1 = m, mx2 = m;
	rep(i, 0, n) {
		while (!b[mx1]) --mx1;	
		mx2 = min(mx2, mx1);	
		while ((mx2 == mx1 && b[mx2] == 1) || !b[mx2]) --mx2;	
		int v = mx1 - mx2;
		rep(j, v, m + 1) b[j] -= b[j - v];
//		rep(j, 0, m + 1) printf("%d ", b[j]);puts("");
		a.pb(v);
	}
	rep(i, 0, sz(a))
		printf("%d%c", a[i], " \n"[i == sz(a) - 1]);
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d%d", &n, &m);
		rep(i, 0, m + 1) scanf("%d", b + i);	
		solve();
	}
	return 0;
}
