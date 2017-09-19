#include<bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b-1); i>=(a); i--)
#define de(x) cout << #x << " => " << x << endl
using namespace std;

#define fi first
#define se second
#define mp make_pair
typedef pair<int,int> pii;

#define pb push_back
typedef vector<int> vi;

typedef long long ll;
typedef long double ld;

const int N = 5e3 + 7;
int G[N][N], n;
///----------------------------------------------
int main() {

	int tcase = 0; scanf("%d", &tcase);
	rep(icase, 0, tcase) {
		///read
		scanf("%d", &n);
		rep(i, 0, n) rep(j, i, n) G[i][j] = G[j][i] = 2 * (i != j);
		///prework
		vector<pii> vu; rep(i, 0, n) vu.pb({(n - 1) / 2, i});
		rep(i, 0, n) {
			sort(vu.begin(), vu.end());
			for (int cur = n - 1; vu[i].fi > 0; cur--) if (cur != i) {
				vu[i].fi--;
				vu[cur].fi--;
				int a = vu[cur].se;
				int b = vu[i].se;
				G[a][b] = G[b][a] = 1;
			}
		}
		///print
		int m = (n - 1) / 2;
		printf("%d\n", n * (n - 1) * (n - 2) / 6 - n * (m * (n - 1 - m)) / 2);
		rep(i, 0, n) {
			rep(j, 0, n) {
				if (j > 0) printf(" ");
				printf("%d", G[i][j]);
			}
			printf("\n");
		}
	}


}
