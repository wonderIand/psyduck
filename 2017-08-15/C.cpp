#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
const int MOD = 998244353;
const int MAX_N = 7 + 1000;
int n, m;
int col[MAX_N][MAX_N];
int tmp[MAX_N][MAX_N];
///------
void inc(int &a, int b) { if ((a += b) >= MOD) a -= MOD; }
void dec(int &a) { if ((a -= 1) < 0) a += MOD; }
bool can[MAX_N][3];
int f[MAX_N][3][3];
int work() {
	///init
	memset(can, true, sizeof(can));
	memset(f, 0, sizeof(f));
	rep(i, 1, n + 1) rep(j, 1, m + 1) if (~col[i][j]) {
		can[i][(col[i][j] ^ 1) ^ (j & 1)] = false;
	}
	f[1][0][0] = can[1][0];
	f[1][0][1] = can[1][1];
	///work
	rep(i, 2, n + 1) rep(j, 0, 2) rep(k, 0, 2) if (can[i][k]) {
		rep(p, 0, 2) {
			inc(f[i][j][k], f[i - 1][p][j]);
		}
	}

	///return
	int ret = 0;
	rep(j, 0, 2) rep(k, 0, 2) inc(ret, f[n][j][k]);
	return ret;
}
///-----
char str[MAX_N];
int main() {
	
	int tcase = 0; scanf("%d", &tcase); 
	rep(icase, 0, tcase) {
		///read
		cin >> n >> m;
		bool cut[2] = {true, true};
		rep(i, 1, n + 1) {
			scanf(" %s", str + 1);
			rep(j, 1, m + 1) {
				char c; c = str[j];
				if (c == 'R') col[i][j] = 1; else
				if (c == 'B') col[i][j] = 0; else col[i][j] = -1;
				if (~col[i][j]) {
					if (col[i][j] != ((i + j) & 1)) cut[0] = false;
					if (col[i][j] != (((i + j) & 1) ^ 1)) cut[1] = false;
				}
			}
		}

		///work
		int ans = work(); //return 0;
		rep(i, 1, n + 1) rep(j, 1, m + 1) tmp[j][i] = col[i][j]; swap(n, m);
		rep(i, 1, n + 1) rep(j, 1, m + 1) col[i][j] = tmp[i][j];
		inc(ans, work());

		///cut
		rep(i, 0, 2) if (cut[i]) dec(ans);
		cout << ans << endl;
	}


	return 0;
}
