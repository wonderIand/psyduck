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
///--------------------------------------------------------------------------------
const int N = 507;
const int M = 26;
const int V = N * N;
int k, m, ans;
int rt, tot, cnt[V], nxt[V][M];
void ins(int L, char *str, int ni) {
	int p = rt;
	rep(i, 0, L) {
		int x = str[i] - 'A';
		if (nxt[p][x] == -1) {
			cnt[tot] = 0;
			memset(nxt[tot], -1, sizeof(nxt[tot]));
			nxt[p][x] = tot++;
		}	
		p = nxt[p][x];
	}
	cnt[p] += ni;
}
void dfs(int t, int l) {
	rep(i, 0, M) if (~nxt[t][i]) {
		dfs(nxt[t][i], l + 1);
		cnt[t] += cnt[nxt[t][i]];
	}
	if (l >= m && cnt[t] > 0)
		++ans, --cnt[t];
}
char str[N];
int main() {
	while (~scanf("%d%d", &k, &m)) {
		if (k == 0 && m == 0) break;	
		rt = 0, tot = 1;
		cnt[rt] = 0, memset(nxt[rt], -1, sizeof(nxt[rt]));
		rep(i, 0, k) {
			int ni;
			scanf(" %d %s", &ni, str);
			ins(strlen(str), str, ni);
		}
		ans = 0;
		dfs(0, 0);
		printf("%d\n", ans);
	}
	return 0;
}
