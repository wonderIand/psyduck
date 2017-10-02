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
const int N = 5e2 + 7;
int a[N], b[N][N], n;
void geta(int bit, int a0) {
	a[0] = a0;
	for (int i = 1; i < n; i += 2) a[i] = a[0] ^ (b[0][i] >> bit & 1);
	for (int i = 2; i < n; i += 2) a[i] = a[1] ^ (b[1][i] >> bit & 1);
}	

bool solve(int bit, int a0) {
	geta(bit, a0);
	rep(i, 0, n) {
		rep(j, 0, n) {
			int bij;
			if (i == j) bij = 0;
			else if (i % 2 == 1 && j % 2 == 1) bij = a[i] | a[j];
			else if (i % 2 == 0 && j % 2 == 0) bij = a[i] & a[j];
			else bij = a[i] ^ a[j];
			if (bij != (b[i][j] >> bit & 1)) return false;
		}
	}
	return true;
}	

int main() {
	
	for (; ~scanf("%d", &n); ) {
		//read
		rep(i, 0, n) rep(j, 0, n) scanf("%d", &b[i][j]);
		//work
		bool ans = true;
		rep(bit, 0, 31) {
			//de(bit);
			bool ok = false;
			rep(_a0, 0, 2) if (solve(bit, _a0)) {
				ok = true;
				break;
			}
			if (!ok) { ans = false; break; }
		}
		//print
		puts(ans ? "YES" : "NO"); 
	}

	return 0;
}
