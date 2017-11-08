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
const int N = 88;
const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, 1, 0, -1 };
int H, W, dis[N][N][8], f[16][1 << 16], g[20][20];
bool in[N][N], vis[N][N][8], jump[5][4][N][N];
char a[N][N];
vector<pii> G;
bool inline check(int x, int y) {
	return  !(x < 0 || x >= H || y < 0 || y >= W);
}
void init() {
	rep(i, 0, H) rep(j, 0, W) in[i][j] = (a[i][j] != '!' && a[i][j] != 'W');
	rep(i, 0, H) rep(j, 0, W) rep(k, 0, 4) {
		rep(t, 0, 5) jump[t][k][i][j] = false;
		if (!in[i][j]) continue;
		int x[10], y[10];
		rep(t, 0, 6) {
			x[t] = i + t * dx[k];
			y[t] = j + t * dy[k];
		}
		if (check(x[2], y[2]) && a[x[1]][y[1]] != 'W' && in[x[2]][y[2]])
			jump[1][k][i][j] = true;
		if (check(x[3], y[3]) && a[x[1]][y[1]] != 'W' && a[x[2]][y[2]] != 'W' && in[x[3]][y[3]])
			jump[2][k][i][j] = true;
		int flag = 1, left = 0, right = 0;
		rep(t, 0, 5) {
			if (!check(x[t], y[t]) || a[x[t]][y[t]] == 'W') { flag = 0; break; }
			if (t == 4 && !in[x[t]][y[t]]) { flag = 0; break; }
			if (check(x[t] - (dx[k] == 0), y[t] - (dy[k] == 0))) 
				left += a[x[t] - (dx[k] == 0)][y[t] - (dy[k] == 0)] == 'W';	
			if (check(x[t] + (dx[k] == 0), y[t] + (dy[k] == 0))) 
				right += a[x[t] + (dx[k] == 0)][y[t] + (dy[k] == 0)] == 'W';		
		}
		if (flag && (left == 5 || right == 5)) jump[3][k][i][j] = true;
		flag = 1, left = 0, right = 0;
		rep(t, 0, 6) {
			if (!check(x[t], y[t]) || a[x[t]][y[t]] == 'W') { flag = 0; break; }
			if (t == 5 && !in[x[t]][y[t]]) { flag = 0; break; }
			if (check(x[t] - (dx[k] == 0), y[t] - (dy[k] == 0))) 
				left += a[x[t] - (dx[k] == 0)][y[t] - (dy[k] == 0)] == 'W';	
			if (check(x[t] + (dx[k] == 0), y[t] + (dy[k] == 0))) 
				right += a[x[t] + (dx[k] == 0)][y[t] + (dy[k] == 0)] == 'W';		
		}
		if (flag && (left == 6 || right == 6)) jump[4][k][i][j] = true;
	}
}
queue<int> que;
inline int get(int i, int j, int k) {
	return (k << 20) | (i << 10) | (j);
}
inline void upd(int x, int y, int c, int nd) {
	if (dis[x][y][c] > nd) {
		dis[x][y][c] = nd;
		if (!vis[x][y][c]) vis[x][y][c] = true, que.push(get(x, y, c));
	}
}
void bfs(pii S) {
	rep(i, 0, H) rep(j, 0, W) rep(k, 0, 8) vis[i][j][k] = false, dis[i][j][k] = 1 << 30;	
	vis[S.fi][S.se][0] = true, dis[S.fi][S.se][0] = 0;
	que.push(get(S.fi, S.se, 0));
	while (!que.empty()) {
		int k = que.front() >> 20, x = (que.front() >> 10) & 1023, y = que.front() & 1023;	
		vis[x][y][k] = false;
//		dd(x), dd(y), de(k);
		que.pop();
		if (!k) { // normal
			rep(i, 0, 4) {
				// walk	
				int nx = x + dx[i], ny = y + dy[i];
				if (check(nx, ny) && in[nx][ny])
					upd(nx, ny, 0, dis[x][y][k] + 1);
				if (jump[1][i][x][y]) {
					// get in dash
					if (check(nx, ny) && in[nx][ny])
						upd(nx + dx[i], ny + dy[i], i << 1 | 1, dis[x][y][k] + 2);	
					// jump
					nx += dx[i], ny += dy[i];		
					upd(nx, ny, 0, dis[x][y][k] + 2);
				}
			}
		} else {
			rep(i, 0, 4) if (i == (k >> 1)) { // keep dash
				// walk	
				int nx = x + dx[i], ny = y + dy[i];
				if (check(nx, ny) && in[nx][ny])
					upd(nx, ny, k, dis[x][y][k] + 1);	
				// jump	
				for (int t = 1; t <= 4; ++t) if (jump[t][i][x][y]) {
					nx = x + (t + 1) * dx[i], ny = y + (t + 1) * dy[i];	
					upd(nx, ny, t < 3 ? k : 0, dis[x][y][k] + t + 1);	
				}
			} else { // change
				upd(x, y, 0, dis[x][y][k]);
			}
		}
	}
}
int main() {
	while (~scanf("%d%d", &H, &W)) {
		if (H == 0 && W == 0) break;
		rep(i, 0, H) scanf(" %s", a[i]);	
		G.clear();
		rep(i, 0, H) rep(j, 0, W) if (a[i][j] == 'E') 
			G.pb(mp(i, j));	
		rep(i, 0, H) rep(j, 0, W) if (a[i][j] == '*')
			G.pb(mp(i, j));
		init();
		rep(i, 0, sz(G)) {
			bfs(G[i]);
			rep(j, 0, sz(G)) {
				int D = 1 << 30;
				rep(k, 0, 8) D = min(D, dis[G[j].fi][G[j].se][k]);
				if (D == (1 << 30)) {
					g[i][j] = -1;
				} else {
					g[i][j] = D;
				}
				//			printf("dis((%d %d), (%d %d)) = %d\n", G[i].fi, G[i].se, 
				//				G[j].fi, G[j].se, g[i][j]);
			}
		}
		rep(i, 0, sz(G)) rep(j, 0, 1 << sz(G)) f[i][j] = -1;
		f[0][1 << 0] = 0;
		rep(mask, 1, 1 << sz(G)) {
			rep(i, 0, sz(G)) if (mask >> i & 1) {
				if (f[i][mask] == -1) continue;
				rep(j, 0, sz(G)) if (~mask >> j & 1) {
					if (g[i][j] == -1) continue;
					if (f[j][mask | 1 << j] == -1 || f[j][mask | 1 << j] > f[i][mask] + g[i][j]) {
						f[j][mask | 1 << j] = f[i][mask] + g[i][j];
					}
				}
			}
		}
		pii ans(0, 0);
		rep(i, 0, sz(G)) rep(mask, 0, 1 << sz(G)) {
			if (f[i][mask] == -1 || g[i][0] == -1) continue;
			ans = max(ans, mp(__builtin_popcount(mask), -(f[i][mask] + g[i][0])));	
		}	
		printf("%d %d\n", ans.fi - 1, -ans.se);	
	}
	return 0;
}
