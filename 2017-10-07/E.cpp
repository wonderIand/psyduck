#include <bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define per(i,a,b) for (int i = (b) - 1; i >= (a); i--)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
using namespace std;
typedef double db;
typedef long long ll;
#define fi first
#define se second
#define mp make_pair
typedef pair<int, int> pii;
#define pb push_back
typedef vector<int> vi;
///---------------------------------------------------------------------------------
const int N = 307;
int n, m, R, S, a[N][N], s[N][N];
inline int get(int row, int c1, int c2) {
	return s[row][c2] - s[row][c1 - 1];
}
struct Seg {
	#define ls ((t)<<1)
	#define rs ((t)<<1|1)
	int cnt[N << 2], sum[N << 2];
	void build(int t, int l, int r) {
		cnt[t] = 0, sum[t] = 0;
		if (l < r) {
			int z = (l + r) >> 1;
			build(ls, l, z), build(rs, z + 1, r);
		}
	}
	void upd(int t, int l, int r, int P, int V) {
		if (l == r) {
			cnt[t] += V;
			sum[t] += V * P;
			return ;
		}
		int z = (l + r) >> 1;
		if (P <= z) upd(ls, l, z, P, V);
		else upd(rs, z + 1, r, P, V);
		cnt[t] = cnt[ls] + cnt[rs];
		sum[t] = sum[ls] + sum[rs];
	}
	int qry(int t, int l, int r, int k) {
		if (l == r) {
			return min(k, cnt[t]) * l;
		}
		if (cnt[t] <= k) return sum[t];
		int z = (l + r) >> 1;
		if (cnt[rs] >= k) {
			return qry(rs, z + 1, r, k);
		} else {
			return sum[rs] + qry(ls, l, z, k - cnt[rs]);
		}
	}
} seg;
int solve() {
	int ret = min(R, n) * m;
	for (int len = m; len > 0; --len) for (int l = 1; l + len - 1 <= m; ++l) {
		int r = l + len - 1;
		int last = 1, sum = 0;	
		seg.build(1, 0, len);
		rep(i, 1, n + 1) {	
			sum += get(i, l, r);
			seg.upd(1, 0, len, get(i, l, r), 1);	
			if (len * (i - last + 1) <= ret) continue;
//			dd(last), dd(sum), dd(i), dd(l), dd(r), de(seg.qry(1, 0, len, R));
			while (sum - seg.qry(1, 0, len, R) > S)	{
				sum -= get(last, l, r);
				seg.upd(1, 0, len, get(last, l, r), -1);
				++last;
				if (len * (i - last + 1) <= ret) break;
			}
			ret = max(ret, len * (i - last + 1));
		}
	}
	return ret;
}
int read() {
	char ch = getchar();
	while (!(ch == '0' || ch == '1')) ch = getchar();
	return ch - '0';
}
int main() {
	while (~scanf("%d%d%d%d", &n, &m, &R, &S)) {
		if (n == 0 && m == 0) break;
		rep(i, 1, n + 1) 
			rep(j, 1, m + 1) {
				scanf("%d", &a[i][j]);
				s[i][j] = s[i][j - 1] + (a[i][j] ^ 1);
			}
		printf("%d\n", solve());
	}
	return 0;
}
