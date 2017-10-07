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
const int N = 1e2 + 7;
int n, m;
vi G[N], F[N];
//-------
int degA[N][N], dpA[N][N];
int degB[N][N], dpB[N][N];
queue<pii> queA, queB;
void gao() {
	while (!queA.empty() || !queB.empty()) {
		while (!queA.empty()) {
			pii p = queA.front(); queA.pop();
			rep(_v, 0, sz(F[p.se])) {
				int v = F[p.se][_v]; if (~dpB[p.fi][v]) continue;
				if (dpA[p.fi][p.se] == 0) {
					dpB[p.fi][v] = 1;
					queB.push(mp(p.fi, v));
				}
				else if (!--degB[p.fi][v]) {
						dpB[p.fi][v] = 0;
						queB.push(mp(p.fi, v));
				}
			}
		}
		while (!queB.empty()) {
			pii p = queB.front(); queB.pop();
			rep(_v, 0, sz(F[p.fi])) {
				int v = F[p.fi][_v]; if (~dpA[v][p.se]) continue;
				if (dpB[p.fi][p.se] == 0) {
					dpA[v][p.se] = 1;
					queA.push(mp(v, p.se));
				}
				else if (!--degA[v][p.se]) {
						dpA[v][p.se] = 0;
						queA.push(mp(v, p.se));
				}
			}
		}
	}
}		
//-------
int main() {
	
	int tcase = 0; scanf("%d", &tcase);
	rep(icase, 0, tcase) {
		//read
		scanf("%d%d", &n, &m);
		rep(i, 0, n) G[i].clear(), F[i].clear();
		rep(i, 0, m) {
			int a, b; scanf("%d%d", &a, &b); a--; b--;
			G[a].pb(b);
			F[b].pb(a);
		}
		///prework
		rep(i, 0, n) rep(j, 0, n) dpA[i][j] = dpB[i][j] = -1;
		rep(i, 0, n) dpA[i][i] = 1, dpB[i][i] = 0;
		rep(i, 0, n) rep(j, 0, n) if(i != j){
			degA[i][j] = sz(G[i]);
			degB[i][j] = sz(G[j]);
			if (!degA[i][j]) dpA[i][j] = 0;
			if (!degB[i][j]) dpB[i][j] = 0;
		}
		while (!queA.empty()) queA.pop(); rep(i, 0, n) rep(j, 0, n) if (~dpA[i][j]) queA.push(mp(i, j));
		while (!queB.empty()) queB.pop(); rep(i, 0, n) rep(j, 0, n) if (~dpB[i][j]) queB.push(mp(i, j));
		///work
		gao();
		int pb, pa; scanf("%d%d", &pb, &pa); pa--; pb--;
		printf("Case #%d: ", icase + 1);
		if (~dpB[pa][pb]) puts(dpB[pa][pb] == 1 ? "Yes" : "No");
			else puts("Yes");
	}
			
		

	return 0;
}
