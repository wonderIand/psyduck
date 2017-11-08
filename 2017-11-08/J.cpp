#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
//-------
const int N = 2e5 + 7;
int n, m, k, q, mi, low;
vi o; int sumo;
bitset<N> b[45] , A;
void gao(bitset<N> &b, vi &v) {
	b = A;
	for (auto e : v) {
		b |= b << e;
	}
}
void prepare() {
	rep(i, 0, n) {
		vi v; rep(j, 0, n) if (j != i) v.pb(o[j]);
		gao(b[i], v);
	}
}	

int main() {
	scanf("%d%d%d%d", &n, &m, &k, &q);
	sumo = 0;
	o.resize(n); rep(i, 0, n) scanf("%d", &o[i]), sumo += o[i];
	A[0] = 1;
	rep(i,1,m+1) {
		int left = i , right = min(k - sumo , (o[0] - 1)* i);
		int rleft = (m - i) , rright = (o[0] - 1) * (m - i);
		for(int i=left;i<=right;++i){
			A[i] = A[i] | (i + rleft <= k - sumo && k - sumo <= i + rright);
		}
	}
	prepare();
	while (q--) {
		int xi; scanf("%d", &xi);
		if (xi == 0) { puts("-1"); continue; }
		vi ans;
		rep(i, 0, n) if (!b[i][xi]) ans.pb(i);
		if (ans.empty()) puts("-1"); else {
			rep(i, 0, sz(ans)) printf("%d%c", ans[i] + 1, " \n"[i == sz(ans) - 1]);
		}
	}
		
	return 0;
}

