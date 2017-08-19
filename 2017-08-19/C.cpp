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
const int MAX_N = 3000 + 7;
bitset<MAX_N> tab[MAX_N], inv[MAX_N];
int main() {
	
	int tcase = 0; scanf("%d", &tcase);
	rep(icase, 0, tcase) {
		///read
		int n; cin >> n;
		rep(i, 1, n + 1) tab[i].reset(), inv[i].reset();
		rep(i, 1, n + 1) rep(j, i + 1, n + 1) {
			int dig; scanf("%d", &dig);
			if (dig == 1) tab[i][j] = tab[j][i] = 1;
			if (dig == 0) inv[i][j] = inv[i][j] = 1;
		}
		if (n >= 6) {
			puts("Bad Team!");
			continue;
		}
		///work
		bool ans = false;
		rep(i, 1, n + 1) if (tab[i].count()) {
			rep(j, i + 1, n + 1) if (tab[j].count() && tab[i][j]) {
				if ((tab[i] & tab[j]).count()) { 
					ans = true; 
					break;
				}
			}
			if (ans) break;
		}
		if (!ans)
		rep(i, 1, n + 1) if (inv[i].count()) {
			rep(j, i + 1, n + 1) if (inv[j].count() && inv[i][j]) {
				if ((inv[i] & inv[j]).count()) {
					ans = true;
					break;
				}
			}
			if (ans) break;
		}
		
		///print
		puts(!ans ? "Great Team!" : "Bad Team!");
	}

	return 0;
}
