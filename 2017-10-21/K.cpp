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
int n, k, c[N];
char str[N];
struct SegTree {
	#define ls ((t)<<1)
	#define rs ((t)<<1|1)
	static const int N = 1e3 + 7;
	int cnt[N << 2], val[N << 2];	
	inline void up(int t) {
		cnt[t] = cnt[ls] + cnt[rs];
		val[t] = val[ls] + val[rs];
	}
	void upd(int t, int l, int r, int P, int V) {
		if (l == r) {
			cnt[t] += V, val[t] += l * V;		
			return ;
		}
		int z = (l + r) >> 1;
		if (P <= z) upd(ls, l, z, P, V);
		else upd(rs, z + 1, r, P, V);
		up(t);
	}
	int qry(int t, int l, int r, int K) {
		if (cnt[t] <= K) return val[t];
		if (l == r) return K * l;
		int z = (l + r) >> 1;
		if (cnt[ls] >= K) return qry(ls, l, z, K);
		return val[ls] + qry(rs, z + 1, r, K - cnt[ls]);
	}
} seg;
pii gao() {
	pii ret(0, 0);	
	rep(i, 0, n) 
		str[i] == '(' ? ++ret.se : ret.fi = min(ret.fi, --ret.se);
	return ret;
}
void solve() {
	int minus = 0;
	rep(i, 0, n) if (c[i] < 0)
		minus += (c[i] = -c[i]), str[i] ^= '(' ^ ')';
	pii fix = gao();
	if ((n & 1) || ((-fix.fi + 1) / 2 + (fix.se - fix.fi + 1) / 2) > k) {
		printf("%d\n", -minus);
		return ;
	}
	int num = 0, sum = 0, ret = INT_MAX, V = *max_element(c, c + n);
	rep(i, 0, n) if (str[i] == ')') 
		++num, seg.upd(1, 0, V, c[i], 1);
	rep(i, 0, n + 1) {
		int left = (-sum + 1) >> 1;
		int right = (fix.se - sum + 1) >> 1;
		if (left + right + num <= k) continue;
		int cost = seg.qry(1, 0, V, k + 1 - left - right);
		ret = min(ret, cost);
		if (i == n) continue;
		if (str[i] == ')') {
			--num, --sum, seg.upd(1, 0, V, c[i], -1);
		} else {
			++num, ++sum, seg.upd(1, 0, V, c[i], 1);
		}
	}
	if (ret == INT_MAX) {
		puts("?");
		return ;
	}
	printf("%d\n", ret - minus);
}
int main() {
	scanf("%d%d %s", &n, &k, str);
	rep(i, 0, n) scanf("%d", c + i);
	solve();
	return 0;
}
