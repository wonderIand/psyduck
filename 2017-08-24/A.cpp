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
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
const int M = 11;
ll pw[21];
pii p[100];
int id[100][100];
map<pair<ll, ll>, int> Rs, Rt; // p0, M, 21 - M
pair<ll, ll> change(pair<ll, ll> st, int p0, int p1) { // p0 is 0's position
	int x = (p0 < M ? st.fi / pw[M - 1 - p0] : st.se / pw[20 - p0]) % 10;
	int y = (p1 < M ? st.fi / pw[M - 1 - p1] : st.se / pw[20 - p1]) % 10;
	if (p0 < M) st.fi += (y - x) * pw[M - 1 - p0];
	else st.se += (y - x) * pw[20 - p0];
	if (p1 < M) st.fi += (x - y) * pw[M - 1 - p1];
	else st.se += (x - y) * pw[20 - p1];
	st.fi += (p1 - p0) * pw[M];
	return st;
}
void bfs(pair<ll, ll> S, map<pair<ll, ll>, int> &R, int lim = 12) {
	R.clear();
	queue<pair<ll, ll> > Q;
	R[S] = 0, Q.push(S);
	while (!Q.empty()) {
		pair<ll, ll> nst, st = Q.front();
		int step = R[st];
		Q.pop();
//		dd(st.fi), dd(st.se), de(step);
		if (step >= lim) continue;
		// get 0 position	
		int pos = st.fi / pw[M];
		int x = p[pos].fi, y = p[pos].se;
		// move up
		if (x > 0) {
			// ul
			if (y - 1 >= 0) {
				nst = change(st, pos, id[x - 1][y - 1]);
				if (!R.count(nst)) {
					R[nst] = step + 1;
					Q.push(nst);
				}
			}
			// ur
			if (y <= x - 1) {
				nst = change(st, pos, id[x -1][y]);
				if (!R.count(nst)) {
					R[nst] = step + 1;
					Q.push(nst);
				}
			}
		}
		// move down
		if (x < 5) {
			// dl
			nst = change(st, pos, id[x + 1][y]);
			if (!R.count(nst)) {
				R[nst] = step + 1;
				Q.push(nst);
			}
			// dr
			nst = change(st, pos, id[x + 1][y + 1]);
			if (!R.count(nst)) {
				R[nst] = step + 1;
				Q.push(nst);
			}
		}
	}
}
pair<ll, ll> encode(int a[][6]) {
	pair<ll, ll> st(0, 0);
	rep(i, 0, 6) rep(j, 0, i + 1) {
		if (id[i][j] < M) st.fi = st.fi * 10 + a[i][j];
		else st.se = st.se * 10 + a[i][j];
	}
	rep(i, 0, 6) rep(j, 0, i + 1)
		if (a[i][j] == 0) {
			st.fi += id[i][j] * pw[M];
			break;
		}
	return st;
}
int solve(pair<ll, ll> S, map<pair<ll, ll>, int> &R, int lim = 10) {
	int ret = 100;
	R.clear();
	queue<pair<ll, ll> > Q;
	R[S] = 0, Q.push(S);
	while (!Q.empty()) {
		pair<ll, ll> nst, st = Q.front();
		int step = R[st];
		Q.pop();
		//		printf("%.13lld%lld\n", st.fi, st.se);
		if (Rs.count(st)) ret = min(ret, step + Rs[st]);
		if (step >= lim || step >= ret) continue;
		// get 0 position	
		int pos = st.fi / pw[M];
		int x = p[pos].fi, y = p[pos].se;
		// move up
		if (x > 0) {
			// ul
			if (y - 1 >= 0) {
				nst = change(st, pos, id[x - 1][y - 1]);
				if (!R.count(nst)) {
					R[nst] = step + 1;
					Q.push(nst);
				}
			}
			// ur
			if (y <= x - 1) {
				nst = change(st, pos, id[x - 1][y]);
				if (!R.count(nst)) {
					R[nst] = step + 1;
					Q.push(nst);
				}
			}
		}
		// move down
		if (x < 5) {
			// dl
			nst = change(st, pos, id[x + 1][y]);
			if (!R.count(nst)) {
				R[nst] = step + 1;
				Q.push(nst);
			}
			// dr
			nst = change(st, pos, id[x + 1][y + 1]);
			if (!R.count(nst)) {
				R[nst] = step + 1;
				Q.push(nst);
			}
		}
	}
	return ret > 20 ? -1 : ret;
}
int main() {
	pw[0] = 1;
	rep(i, 1, 21) pw[i] = pw[i - 1] * 10; 
	int t = 0;	
	rep(i, 0, 6) 
		rep(j, 0, i + 1)
		id[i][j] = t, p[t] = mp(i, j), ++t;
	int a[6][6];	
	rep(i, 0, 6) rep(j, 0, 6) a[i][j] = i;	
	pair<ll, ll> st = encode(a);
	bfs(st, Rs);
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {	
		rep(i, 0, 6) rep(j, 0, i + 1) scanf("%d", &a[i][j]);
		//		rep(i, 0, 6) {
		//			rep(j, 0, i + 1) printf("%d ", a[i][j]);
		//			puts("");
		//		}
		st = encode(a);
		int ans = solve(st, Rt);
		if (~ans)
			printf("%d\n", ans);
		else
			puts("too difficult");
	}	
	return 0;
}

