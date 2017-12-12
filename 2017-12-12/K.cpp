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
const int N = 51 , inf = 1e8;
int dx[] = {1 , 0 , -1 , 0};
int dy[] = {0 , 1 , 0 , -1};
string go = "DRUL";
int n , m;
string s[N];
int pre[N][N][N][N];
int d[N][N][N][N];
inline bool in(int x,int y){
	return 0 <= x && x < n && 0 <= y && y < m && s[x][y] != '#';
}
void dfs(int a,int b,int c,int d,int pd){
	if(pre[a][b][c][d] != 10) return ;
	pre[a][b][c][d] = pd;
	rep(dir,0,4) {
		int na = a + dx[dir];
		int nb = b + dy[dir];
		int nc = c + dx[dir^2];
		int nd = d + dy[dir^2];
		if(in(na , nb) && in(nc , nd))
			dfs(na , nb , nc , nd , dir ^ 2);
	}
}

void bfs(int a,int b,int c,int d,int pd){
	pre[a][b][c][d] = pd;
	::d[a][b][c][d] = pd == 4 ? 0 : 1;
	vector<tuple<int,int,int,int> > v;
	v.pb(make_tuple(a , b , c , d));
	rep(i,0,sz(v)){
		tie(a , b , c , d) = v[i];
		int dis = ::d[a][b][c][d];
		if(dis + 2 > 100) continue;
		rep(dir,0,4) {
			int na = a + dx[dir];
			int nb = b + dy[dir];
			int nc = c + dx[dir^2];
			int nd = d + dy[dir^2];
			if(in(na , nb) && in(nc , nd) && pre[na][nb][nc][nd] == 10) {
				pre[na][nb][nc][nd] = dir ^ 2;
				::d[na][nb][nc][nd] = dis + 2;
				v.pb(make_tuple(na , nb , nc , nd));
			}
		}
	}
}

int dis[N * N];
int vis[N * N] , from[N * N];
inline int id(int x,int y){return x * m + y;}

int main() {
	cin >> n >> m;
	rep(i,0,n) cin >> s[i];
	rep(i,0,n) rep(j,0,m) rep(ii,0,n) rep(jj,0,m)
		pre[i][j][ii][jj] = 10;
	rep(i,0,n) rep(j,0,m) if(in(i , j)){
		bfs(i , j , i , j , 4);
		//dfs(i , j , i , j , 4);
	}
	rep(i,0,n) rep(j,0,m) if(in(i , j)) rep(dir,0,4){
		int ni = i + dx[dir];
		int nj = j + dy[dir];
		if(in(ni , nj))
			bfs(i , j , ni , nj , ~dir);
		//dfs(i , j , ni , nj , ~dir);
	}
	rep(i,0,n*m) dis[i] = inf;
	int S = 0 , T = 0;
	rep(i,0,n) rep(j,0,m) {
		if(s[i][j] == 'S') S = id(i , j);
		if(s[i][j] == 'F') T = id(i , j);
	}
	dis[S] = 0;
	int nm = n * m;
	while(1) {
		int c = -1 , mn = inf;
		rep(i,0,nm) if(!vis[i] && dis[i] < mn)
			mn = dis[i] , c = i;
		if(c == -1) break;
		vis[c] = true;
		if(c == T) break;
		int x = c / m , y = c % m;
		rep(i,0,n) rep(j,0,m) if(pre[x][y][i][j] != 10){
			int t = id(i , j);
			if(mn + 1 < dis[t])
				dis[t] = mn + 1 , from[t] = c;
		}
	}
	if(dis[T] == inf) cout << "-1" << endl;
	else {
		cout << dis[T] << endl;
		int c = T;
		vector<string> v;
		while(c != S){
			int g = from[c];
			// g --> c
			string s;
			int ax = g / m , ay = g % m;
			int bx = c / m , by = c % m;
			while(1) {
				int t = pre[ax][ay][bx][by];
				if(t == 4){
					string ss = s;
					reverse(all(ss));
					s += ss;
					break;
				}
				if(t < 0) {
					string ss = s;
					reverse(all(ss));
					s += go[~t];
					s += ss;
					break;
				}
				s += go[t];
				ax += dx[t];
				ay += dy[t];
				bx += dx[t^2];
				by += dy[t^2];
			}
			c = g;
			v.pb(s);
		}
		reverse(all(v));
		rep(i,0,sz(v)) cout << v[i] << endl;
	}
	return 0;
}
