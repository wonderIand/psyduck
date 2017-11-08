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
const int N = 50;
int up[N][N], dig[N][N], n, m, k, s;
bool dfs(int x, int y, int suml, int can) {
	if (y == 1) suml = 0;
	//dd(x); de(y);
	if (x == n + 1) return true;
	if (can && dig[x][y] > 0) {
		up[x][y] = max(0, up[x - 1][y] - dig[x][y]);
		if (dfs(x + (y == m), (y + 1) - (y == m) * m, max(0, suml - dig[x][y]), can - 1)) return true;
	}
	up[x][y] = max(0, up[x-1][y] + dig[x][y]);
	int nex_suml = max(0, suml + dig[x][y]);
	if (nex_suml <= s && up[x][y] <= s)
		if (dfs(x + (y == m), (y + 1) - (y == m) * m, nex_suml, can)) return true;
	return false;
}

void solve() {
	//read
	rep(i, 1, n + 1) rep(j, 1, m + 1) scanf("%d", &dig[i][j]);
	if (dfs(1, 1, 0, k)) puts("Yes");
		else puts("No");
}

int main() {
	while (~scanf("%d%d%d%d", &n, &m, &k, &s)) solve(); 
	return 0;
}
