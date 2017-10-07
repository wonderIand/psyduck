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
const int N = 5e5 + 7;
int n, M;
int vis[N], vis_flag = 0;
int v[N];
//------
priority_queue<pii> que;
void add(int id1, int id2) {
	if (id2 <=0 || id2 > n) return;
	if (vis[id2] < vis_flag) vis[id2] = vis_flag, que.push(mp(abs(id1 - id2) % M, -id2));
}
void gao(int id) {
	int ls = id << 1; add(id, ls);
	int rs = id << 1 | 1; add(id, rs);
	int fa = id >> 1; add(id, fa);
}
int main() {
	
	int tcase = 0; scanf("%d", &tcase);
	rep(icase, 0, tcase) {

		///read
		scanf("%d%d%d", &n, &v[1], &M);
		while (!que.empty()) que.pop();
		
		///
		vis[v[1]] = ++vis_flag; gao(v[1]);
		rep(i, 2, n + 1) {
			v[i] = -que.top().se; que.pop();
			gao(v[i]);
		}
		
		///print
		rep(i, 1, n + 1) printf("%d%c", v[i], " \n"[i == n]);
	}
	return 0;
}
