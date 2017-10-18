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
const int N = 2e2 + 6;
char str[N][N];
int n, m, h, w;
bool same(pii a, pii b) {
	bool ok = true;
	rep(i, 0, h) rep(j, 0, w) 
		if (str[a.fi + i][a.se + j] != str[b.fi + i][b.se + j]) { ok = false; break; }
	if (ok) return true; else ok = true;
	rep(i, 0, h) rep(j, 0, w)
		if (str[a.fi + h - 1 - i][a.se + w - 1 - j] != str[b.fi + i][b.se + j]) { ok = false; break; }
	if (ok) return true; else ok = true;
	if (w == h) {
		rep(i, 0, h) rep(j, 0, w)
		if (str[a.fi + h - 1 - j][a.se + i] != str[b.fi + i][b.se + j])  { ok = false; break; }
		if (ok) return true; else ok = true;
		rep(i, 0, h) rep(j, 0, w)
		if (str[a.fi + j][a.se + w - 1 - i] != str[b.fi + i][b.se + j])  { ok = false; break; }
		if (ok) return true;
	}
	return false;
}
int main() {
	
	//read
	scanf("%d%d", &n, &m);
	rep(i, 0, n) scanf("%s", str[i]);
	
	//prework
	w = 1; while (str[1][1 + w] != '#') w++;
	h = 1; while (str[1 + h][1] != '#') h++;
	//de(w); de(h);

	//work
	vector<pii> ans;
	for (int sx = 1; sx < n; sx += h + 1) 
	for (int sy = 1; sy < m; sy += w + 1) {
		bool ok = true;
		rep(i, 0, sz(ans)) if (same(ans[i], mp(sx, sy))) { ok = false; break; }
		if (ok) ans.pb(mp(sx, sy));
	}
	//rep(i, 0, sz(ans)) { dd(ans[i].fi); de(ans[i].se); }
	printf("%d", sz(ans));

return 0;
}
