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
const int N = 1e5 + 7;
int n;
struct Point {
	int val, nex, pre;
}	p[N];
bool vis[N];
void del(int u) {
	vis[u] = true;
	p[p[u].pre].nex = p[u].nex;
	p[p[u].nex].pre = p[u].pre;
}
int main() {

	int tcase = 0; scanf("%d", &tcase);
	rep(icase, 0, tcase) {
		///read
		scanf("%d", &n);
		rep(i, 1, n + 1) scanf("%d", &p[i].val);
		rep(i, 0, n + 1) p[i].nex = i + 1;
		rep(i, 1, n + 2) p[i].pre = i - 1;
		p[0].val = 0;
		p[n + 1].val = N;
		///prework
		vi cur, nex;
		rep(i, 1, n + 1) vis[i] = false; vis[0] = vis[n + 1] = true;
		rep(i, 1, n + 1) if (p[i].val < p[p[i].pre].val || p[i].val > p[p[i].nex].val) {
			cur.pb(i);
			vis[i] = true;
		}
		while (!cur.empty()) {
			vi tmp;
			rep(i, 0, sz(cur)) {
				int u = cur[i];
				tmp.pb(p[u].pre);
				tmp.pb(p[u].nex);
			}
			rep(i, 0, sz(cur)) del(cur[i]);
			//
			nex.clear();
			rep(i, 0, sz(tmp)) if (!vis[tmp[i]]) {
				int u = tmp[i];
				if (p[u].val < p[p[u].pre].val || p[u].val > p[p[u].nex].val) nex.pb(u);
			}
			swap(nex, cur);
		}
		///print
		int ans = 0;
		rep(i, 1, n + 1) if (!vis[i]) ans++;
		printf("%d\n", ans);
		rep(i, 1, n + 1) if (!vis[i]) printf("%d ", p[i].val);
		printf("\n");
	}
		

	return 0;
}
