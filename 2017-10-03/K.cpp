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
int n, K;
int c[2], s[2], t[2];
void read(int &c, int &s, int &t) {
	char dc;
	scanf(" %c %d %d", &dc, &s, &t);
	switch(dc) {
		case 'N': c = 0;break;
		case 'E': c = 1;break;
		case 'S': c = 2;break;
		case 'W': c = 3;break;
	}
}
const int dx[4] = { -1, 0, 1, 0 };
const int dy[4] = { 0, 1, 0, -1 };
void move(int &x, int &y, int &c, int s) {
	int nx = x + dx[c] * s;
	int ny = y + dy[c] * s;
//	dd(x), dd(y), dd(c), dd(nx), de(ny);
	if (nx < 1 || nx > n) {
		c = (c + 2) % 4;		
		if (nx < 1) {
			nx = 1 + dx[c] * (s - (x - 1));
		} else {
			nx = n + dx[c] * (s - (n - x));
		}
	} else if (ny < 1 || ny > n) {
		c = (c + 2) % 4;		
		if (ny < 1) {
			ny = 1 + dy[c] * (s - (y - 1));
		} else {
			ny = n + dy[c] * (s - (n - y));
		}
	}
	x = nx, y = ny;
}
void solve() {
	int x[2] = { 1, n }, y[2] = { 1, n };	
	rep(k, 1, K + 1) {
		rep(i, 0, 2) move(x[i], y[i], c[i], s[i]);
		if (x[0] == x[1] && y[0] == y[1]) { // meet in k
			swap(c[0], c[1]);
		} else { 
			rep(i, 0, 2) if (k % t[i] == 0)
				c[i] = (c[i] + 3) % 4;
		}
//		de(k);
//		rep(i, 0, 2) printf("%d %d %d\n", x[i], y[i], c[i]);
	}
	rep(i, 0, 2) printf("%d %d\n", x[i], y[i]);
}
int main() {
	while (~scanf("%d", &n)) {
		if (n == 0) break;
		rep(i, 0, 2) read(c[i], s[i], t[i]);
		//		rep(i, 0, 2) dd(c[i]), dd(s[i]), de(t[i]);
		scanf("%d", &K);
		solve();
	}
	return 0;
}
