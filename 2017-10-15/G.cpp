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
const int N = 507;
int h, w;
bool vis[N][N];
char a[N][N];
bool bfs() {
	queue<pii> que;
	rep(i, 0, w) if (a[0][i] == '.') {
		vis[0][i] = true, que.push(mp(0, i));	
	}
	while (!que.empty()) {
		int xx = que.front().fi;
		int yy = que.front().se;
		que.pop();
		if (a[xx + 1][yy] == '.' && !vis[xx + 1][yy]) {
			vis[xx + 1][yy] = true, que.push(mp(xx + 1, yy));
		} else {
			if (yy > 0 && a[xx][yy - 1] == '.' && !vis[xx][yy - 1]) 
				vis[xx][yy - 1] = true, que.push(mp(xx, yy - 1)); 
			if (yy + 1 < w && a[xx][yy + 1] == '.' && !vis[xx][yy + 1])
				vis[xx][yy + 1] = true, que.push(mp(xx, yy + 1));
		}
	}
	rep(i, 0, h) rep(j, 0, w) 
		if (a[i][j] == '.' && !vis[i][j]) {
			a[i][j] = 'X';
			return true;
		}
	return false;
}
int main() {
	scanf("%d%d", &h, &w);
	rep(i, 0, h) scanf(" %s", a[i]);
	if (bfs()) {
		puts("Yes");
		rep(i, 0, h) puts(a[i]);
	} else {
		puts("No");
	}
	return 0;
}
