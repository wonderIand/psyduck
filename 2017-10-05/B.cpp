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
//-------
char STR[5] = { "URDL" };
const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, 1, 0, -1 };
char a[10][10], b[10][10];
pair<pii, pii> ans;
inline int id(int x, int y) {
	return x * 6 + y;
}
pii p[20], que[100];
int qh, qt;
void bfs(int x, int y, int &st) {
	qh = qt = 0;
	char ch = b[x][y];
	st ^= 1 << id(x, y);
	que[qt++] = mp(x, y);
	while (qh < qt) {
		x = que[qh].fi;
		y = que[qh].se;
		b[x][y] = '*';
		++qh;
		rep(i, 0, 4) {
			int xx = x + dx[i], yy = y + dy[i];
			if (xx < 0 || xx >= 5 || yy < 0 || yy >= 6 || b[xx][yy] != ch) continue;
			if (st >> id(xx, yy) & 1)
				st ^= 1 << id(xx, yy), que[qt++] = mp(xx, yy);
		}
	}
}
void getpath(int xy, int path, int step, int &m) {
	int x = xy / 6, y = xy % 6;
	m = 0;
	p[m++] = mp(x, y);
	rep(_s, 0, step) {
		int d = ((path >> (_s << 1) & 3) + 2) & 3;
		x += dx[d], y += dy[d];	
		p[m++] = mp(x, y);
	}
	reverse(p, p + m);
}
void out(char a[][10]) {
	rep(i, 0, 5) {
		rep(j, 0, 6) putchar(a[i][j]);
		puts("");
	}
	puts("");
}
bool elim(int &combo, int &size) {
	int st = 0;	
	// horizon
	rep(i, 0, 5) rep(j, 0, 4)
		if (b[i][j] != '*' && b[i][j] == b[i][j + 1] && b[i][j] == b[i][j + 2])
			rep(k, 0, 3) st |= 1 << id(i, j + k);
	// vertical	
	rep(j, 0, 6) rep(i, 0, 3)
		if (b[i][j] != '*' && b[i][j] == b[i + 1][j] && b[i][j] == b[i + 2][j])
			rep(k, 0, 3) st |= 1 << id(i + k, j);
	if (!st) return false;
//	out(b);
	size += __builtin_popcount(st);
	rep(i, 0, 5) rep(j, 0, 6) if (st >> id(i, j) & 1)
		++combo, bfs(i, j, st);
	rep(j, 0, 6) {
		int last = 4;	
		for (int i = 4; i >= 0; --i)
			if (b[i][j] != '*') {
				char tmp = b[i][j];
				b[i][j] = '*';
				b[last--][j] = tmp;
			}
	}
	return true;
}
void gao(int xy, int step, int path) {
	int m;
	getpath(xy, path, step, m);
	rep(i, 0, 5) rep(j, 0, 6) b[i][j] = a[i][j];
	rep(i, 0, m - 1) b[p[i].fi][p[i].se] = b[p[i + 1].fi][p[i + 1].se];	
	b[p[m - 1].fi][p[m - 1].se] = a[p[0].fi][p[0].se];	
	int combo = 0, size = 0;
	while (elim(combo, size));
//	dd(xy), dd(step), dd(path), dd(combo), de(size);	
	ans = max(ans, mp(mp(combo, size), mp(-step, path << 5 | xy)));	
}
void dfs(int step, int xy, int path) {
	if (step >= 9) return ;
	int x = xy / 6, y = xy % 6;	
//	dd(step), dd(xy), de(path);
	rep(i, 0, 4) {
		if (step && (path & 3) == ((i + 2) & 3)) continue;
		int nx = x + dx[i], ny = y + dy[i];
		if (nx < 0 || nx >= 5 || ny < 0 || ny >= 6) continue;		
		gao(id(nx, ny), step + 1, path << 2 | i);	
		dfs(step + 1, id(nx, ny), path << 2 | i);	
	}	
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		rep(i, 0, 5) scanf(" %s", a[i]); 
		ans = mp(mp(-1, -1), mp(-1, -1));
//		int tmp = (1 << 16) | (0 << 14) | (1 << 12) | (0 << 10) 
//			| (1 << 8) | (2 << 6) | (3 << 4) | (2 << 2) | (2 << 0);
//		gao(id(4, 4), 9, tmp);			
		rep(i, 0, 5) rep(j, 0, 6)
			dfs(0, id(i, j), 0);
		printf("Case #%d:\n", cas + 1);		
		printf("Combo:%d Length:%d\n", ans.fi.fi, -ans.se.fi);
		int m = 0;
		int xy = ans.se.se & 31;
		int path = ans.se.se >> 5;
		getpath(xy, path, -ans.se.fi, m);
		printf("%d %d\n", 1 + p[0].fi, 1 + p[0].se);
		vector<char> vec;
		rep(i, 0, -ans.se.fi) {
			vec.pb(STR[path & 3]);
			path >>= 2;
		}
		reverse(all(vec));
		rep(i, 0, sz(vec)) putchar(vec[i]);
		puts("");
	}
	return 0;
}
