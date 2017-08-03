#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
//-------
char a[10][10][10] = {
	{ { ".XX."}, 
	  { "X..X"},
	  { "X..X"},
	  { "...."},
	  { "X..X"},
	  { "X..X"},
	  { ".XX."} },	

	{ { "...."}, 
	  { "...X"},
	  { "...X"},
	  { "...."},
	  { "...X"},
	  { "...X"},
	  { "...."} },	

	{ { ".XX."}, 
	  { "...X"},
	  { "...X"},
	  { ".XX."},
	  { "X..."},
	  { "X..."},
	  { ".XX."} },

	{ { ".XX."}, 
	  { "...X"},
	  { "...X"},
	  { ".XX."},
	  { "...X"},
	  { "...X"},
	  { ".XX."} },

	{ { "...."}, 
	  { "X..X"},
	  { "X..X"},
	  { ".XX."},
	  { "...X"},
	  { "...X"},
	  { "...."} },

	{ { ".XX."}, 
	  { "X..."},
	  { "X..."},
	  { ".XX."},
	  { "...X"},
	  { "...X"},
	  { ".XX."} },	

	{ { ".XX."}, 
	  { "X..."},
	  { "X..."},
	  { ".XX."},
	  { "X..X"},
	  { "X..X"},
	  { ".XX."} },	

	{ { ".XX."}, 
	  { "...X"},
	  { "...X"},
	  { "...."},
	  { "...X"},
	  { "...X"},
	  { "...."} },	

	{ { ".XX."}, 
	  { "X..X"},
	  { "X..X"},
	  { ".XX."},
	  { "X..X"},
	  { "X..X"},
	  { ".XX."} },	

	{ { ".XX."}, 
	  { "X..X"},
	  { "X..X"},
	  { ".XX."},
	  { "...X"},
	  { "...X"},
	  { ".XX."} },	
};
char s[100][100];
int check(int v, int x, int y) {
	rep(i, 0, 7) rep(j, 0, 4)
		if (a[v][i][j] != s[x + i][y + j])
			return false;
	return true;
}
int get(int x, int y) {
	rep(v, 0, 10)
		if (check(v, x, y))
			return v;
	return -1;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		rep(i, 0, 7) scanf(" %s", s[i]);
		int h = get(0, 0) * 10 + get(0, 5);
		int m = get(0, 12) * 10 + get(0, 17);
		printf("%.2d:%.2d\n", h, m);
	}
	return 0;
}
