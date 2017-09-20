#include<bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b-1); i>=(a); i--)
#define de(x) cout << #x << " => " << x << endl
using namespace std;

#define fi first
#define se second
#define mp make_pair
typedef pair<int,int> pii;

#define pb push_back
typedef vector<int> vi;

typedef long long ll;
typedef long double ld;

const int LIM = 44;
const int N = 1e2 + 7;
const int INF = 0x3f3f3f3f;
int dig[N], n;
vi pre[N][N];
///----------------------------------------------
int ans;
void dfs(int l, int r, int score) {
	if (r - l + 1 > LIM) {
		int mx = max(dig[l], dig[r]);
		if (dig[l] == mx) l++; else r--;
		dfs(l + 1, r, score + mx - dig[l]);
		dfs(l, r - 1, score + mx - dig[r]);
	} else {
		auto &M = pre[l][r];
		int pos = lower_bound(all(M), -score + 1) - M.begin();
		if (pos < sz(M)) ans = min(ans, M[pos] + score);
	}
}
int main() {

	for (; ~scanf("%d", &n); ) {
		///read
		rep(i, 1, n + 1) scanf("%d", &dig[i]);
		///prework
		rep(i, 1, n + 1) {
			pre[i][i - 1].clear();
			pre[i][i - 1].pb(0);
		}
		rep(len, 2, min(n + 1, LIM + 1)) {
			for (int i = 1; i + len - 1 <= n; i++) {
				int l = i, r = i + len - 1;
				auto &M = pre[l][r];
				int mx = max(dig[l], dig[r]);
				if (dig[l] == mx) l++; else r--;
				auto L = pre[l + 1][r]; for (int &e : L) e += mx - dig[l];
				auto R = pre[l][r - 1]; for (int &e : R) e += mx - dig[r];
				M.resize(sz(L) + sz(R));
				merge(all(L), all(R), M.begin());
				M.erase(unique(all(M)), M.end());
			}
			for (int i = 1; i + len - 1 - 2 <= n; i++) {
				vi emp;
				swap(pre[i][i + len - 1 - 2], emp);
			}
		}
		///work
		//de(sz(pre[1][4]));
		ans = INF;
		dfs(1, n, 0);
		if (ans == INF) printf("The child will be unhappy...\n");
		else printf("%d\n", ans);
	}

	return 0;


}
